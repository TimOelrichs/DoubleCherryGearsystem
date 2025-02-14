/*
 * Gearsystem - Sega Master System / Game Gear Emulator
 * Copyright (C) 2013  Ignacio Sanchez

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <vector>

#include <stdio.h>
#include "libretro.h"

#include "../../src/gearsystem.h"

#ifdef _WIN32
static const char slash = '\\';
#else
static const char slash = '/';
#endif

static struct retro_log_callback logging;
static retro_log_printf_t log_cb;
static char retro_system_directory[4096];
static char retro_game_path[4096];

static s16 audio_buf[2][GS_AUDIO_BUFFER_SIZE];
static int audio_sample_count[] = { 0,0 };
static int current_screen_width = 0;
static int current_screen_height = 0;
static bool allow_up_down = false;
static bool bootrom_sms = false;
static bool bootrom_gg = false;
static bool libretro_supports_bitmasks;

static GearsystemCore* cores[2];
static u8* frame_buffers[2];
static Cartridge::ForceConfiguration config;
static GearsystemCore::GlassesConfig glasses_config;

static void fallback_log(enum retro_log_level level, const char *fmt, ...)
{
    (void)level;
    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);
}

static const struct retro_variable vars[] = {
    { "gearsystem_system", "System (restart); Auto|Master System / Mark III|Game Gear|SG-1000 / Multivision" },
    { "gearsystem_region", "Region (restart); Auto|Master System Japan|Master System Export|Game Gear Japan|Game Gear Export|Game Gear International" },
    { "gearsystem_mapper", "Mapper (restart); Auto|ROM|SEGA|Codemasters|Korean|MSX|Janggun|SG-1000" },
    { "gearsystem_timing", "Refresh Rate (restart); Auto|NTSC (60 Hz)|PAL (50 Hz)" },
    { "gearsystem_bios_sms", "Master System BIOS (restart); Disabled|Enabled" },
    { "gearsystem_bios_gg", "Game Gear BIOS (restart); Disabled|Enabled" },
    { "gearsystem_glasses", "3D Glasses; Both Eyes / OFF|Left Eye|Right Eye" },
    { "gearsystem_up_down_allowed", "Allow Up+Down / Left+Right; Disabled|Enabled" },
    { NULL }
};

static retro_environment_t environ_cb;

void retro_init(void)
{
    const char *dir = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &dir) && dir) {
        snprintf(retro_system_directory, sizeof(retro_system_directory), "%s", dir);
    }
    else {
        snprintf(retro_system_directory, sizeof(retro_system_directory), "%s", ".");
    }

    cores[0] = new GearsystemCore();
    cores[1] = new GearsystemCore();

#ifdef PS2
    core->Init(GS_PIXEL_BGR555);
#else
    cores[0]->Init(GS_PIXEL_RGB565);
    cores[1]->Init(GS_PIXEL_RGB565);
    cores[0]->SetGearToGearTarget(cores[1]);
    cores[1]->SetGearToGearTarget(cores[0]);

#endif

    frame_buffers[0] = new u8[GS_RESOLUTION_MAX_WIDTH * GS_RESOLUTION_MAX_HEIGHT * 2];
    frame_buffers[1] = new u8[GS_RESOLUTION_MAX_WIDTH * GS_RESOLUTION_MAX_HEIGHT * 2];

    audio_sample_count[0] = 0;

    config.type = Cartridge::CartridgeNotSupported;
    config.zone = Cartridge::CartridgeUnknownZone;
    config.region = Cartridge::CartridgeUnknownRegion;
    config.system = Cartridge::CartridgeUnknownSystem;

    glasses_config = GearsystemCore::GlassesBothEyes;

    libretro_supports_bitmasks = environ_cb(RETRO_ENVIRONMENT_GET_INPUT_BITMASKS, NULL);
}

void retro_deinit(void)
{
    SafeDeleteArray(frame_buffers[0]);
    SafeDelete(cores[0]);
}

unsigned retro_api_version(void)
{
    return RETRO_API_VERSION;
}

void retro_set_controller_port_device(unsigned port, unsigned device)
{
    log_cb(RETRO_LOG_INFO, "Plugging device %u into port %u.\n", device, port);

    struct retro_input_descriptor joypad[] = {
        { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT,   "Left" },
        { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP,     "Up" },
        { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN,   "Down" },
        { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT,  "Right" },
        { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START,  "Start" },
        { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B,      "1" },
        { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A,      "2" },

        { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT,   "Left" },
        { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP,     "Up" },
        { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN,   "Down" },
        { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT,  "Right" },
        { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START,  "Start" },
        { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B,      "1" },
        { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A,      "2" },

        { 0, 0, 0, 0, NULL }
    };

    struct retro_input_descriptor desc[] = {
        { 0, 0, 0, 0, NULL }
    };

    if (device == RETRO_DEVICE_JOYPAD)
        environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, joypad);
    else
        environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);
}

void retro_get_system_info(struct retro_system_info *info)
{
    memset(info, 0, sizeof(*info));
    info->library_name     = "Gearsystem";
    info->library_version  = GEARSYSTEM_VERSION;
    info->need_fullpath    = false;
    info->valid_extensions = "sms|gg|sg|mv|bin|rom";
}

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;

void retro_get_system_av_info(struct retro_system_av_info *info)
{
    GS_RuntimeInfo runtime_info;
    cores[0]->GetRuntimeInfo(runtime_info);

    current_screen_width = runtime_info.screen_width;
    current_screen_height = runtime_info.screen_height*2;

    info->geometry.base_width   = runtime_info.screen_width;
    info->geometry.base_height  = runtime_info.screen_height*2;
    info->geometry.max_width    = runtime_info.screen_width;
    info->geometry.max_height   = runtime_info.screen_height*2;
    info->geometry.aspect_ratio = 0.0f;
    //info->geometry.aspect_ratio = (float)info->geometry.max_height / (float)info->geometry.max_width;
    info->timing.fps            = runtime_info.region == Region_NTSC ? 60.0 : 50.0;
    info->timing.sample_rate    = 44100.0;
}

void retro_set_environment(retro_environment_t cb)
{
    environ_cb = cb;

    if (cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &logging))
        log_cb = logging.log;
    else
        log_cb = fallback_log;

    static const struct retro_controller_description port_1[] = {
        { "Sega Master System / Game Gear", RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_JOYPAD, 0) },
    };

    static const struct retro_controller_description port_2[] = {
        { "Sega Master System / Game Gear", RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_JOYPAD, 0) },
    };

    static const struct retro_controller_info ports[] = {
        { port_1, 1 },
        { port_2, 1 },
        { NULL, 0 },
    };

    cb(RETRO_ENVIRONMENT_SET_CONTROLLER_INFO, (void*)ports);

    environ_cb(RETRO_ENVIRONMENT_SET_VARIABLES, (void *)vars);
}

void retro_set_audio_sample(retro_audio_sample_t cb)
{
    audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
    audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb)
{
    input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb)
{
    input_state_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
    video_cb = cb;
}

static void load_bootroms(void)
{
    char bootrom_sms_path[4112];
    char bootrom_gg_path[4112];

    sprintf(bootrom_sms_path, "%s%cbios.sms", retro_system_directory, slash);
    sprintf(bootrom_gg_path, "%s%cbios.gg", retro_system_directory, slash);

    cores[0]->GetMemory()->LoadBootromSMS(bootrom_sms_path);
    cores[0]->GetMemory()->LoadBootromGG(bootrom_gg_path);
    cores[0]->GetMemory()->EnableBootromSMS(bootrom_sms);
    cores[0]->GetMemory()->EnableBootromGG(bootrom_gg);

    
    cores[1]->GetMemory()->LoadBootromSMS(bootrom_sms_path);
    cores[1]->GetMemory()->LoadBootromGG(bootrom_gg_path);
    cores[1]->GetMemory()->EnableBootromSMS(bootrom_sms);
    cores[1]->GetMemory()->EnableBootromGG(bootrom_gg);
    
}

static void update_input(void)
{
    input_poll_cb();

    for (int player=0; player<2; player++)
    {
        int16_t ib;
        if (libretro_supports_bitmasks)
            ib = input_state_cb(player, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_MASK);
        else
        {
            unsigned int i;
            ib = 0;
            for (i = 0; i <= RETRO_DEVICE_ID_JOYPAD_R3; i++)
                ib |= input_state_cb(player, RETRO_DEVICE_JOYPAD, 0, i) ? (1 << i) : 0;
        }

        if (ib & (1 << RETRO_DEVICE_ID_JOYPAD_UP))
        {
            if (allow_up_down || !(ib & (1 << RETRO_DEVICE_ID_JOYPAD_DOWN)))
                cores[player]->KeyPressed(static_cast<GS_Joypads>(0), Key_Up);
        }
        else
            cores[player]->KeyReleased(static_cast<GS_Joypads>(0), Key_Up);
        if (ib & (1 << RETRO_DEVICE_ID_JOYPAD_DOWN))
        {
            if (allow_up_down || !(ib & (1 << RETRO_DEVICE_ID_JOYPAD_UP)))
                cores[player]->KeyPressed(static_cast<GS_Joypads>(0), Key_Down);
        }
        else
            cores[player]->KeyReleased(static_cast<GS_Joypads>(0), Key_Down);
        if (ib & (1 << RETRO_DEVICE_ID_JOYPAD_LEFT))
        {
            if (allow_up_down || !(ib & (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT)))
                cores[player]->KeyPressed(static_cast<GS_Joypads>(0), Key_Left);
        }
        else
            cores[player]->KeyReleased(static_cast<GS_Joypads>(0), Key_Left);
        if (ib & (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT))
        {
            if (allow_up_down || !(ib & (1 << RETRO_DEVICE_ID_JOYPAD_LEFT)))
                cores[player]->KeyPressed(static_cast<GS_Joypads>(0), Key_Right);
        }
        else
            cores[player]->KeyReleased(static_cast<GS_Joypads>(0), Key_Right);

        if (ib & (1 << RETRO_DEVICE_ID_JOYPAD_B))
            cores[player]->KeyPressed(static_cast<GS_Joypads>(0), Key_1);
        else
            cores[player]->KeyReleased(static_cast<GS_Joypads>(0), Key_1);
        if (ib & (1 << RETRO_DEVICE_ID_JOYPAD_A))
            cores[player]->KeyPressed(static_cast<GS_Joypads>(0), Key_2);
        else
            cores[player]->KeyReleased(static_cast<GS_Joypads>(0), Key_2);
        if (ib & (1 << RETRO_DEVICE_ID_JOYPAD_START))
            cores[player]->KeyPressed(static_cast<GS_Joypads>(0), Key_Start);
        else
            cores[player]->KeyReleased(static_cast<GS_Joypads>(0), Key_Start);
    }
}

static void check_variables(void)
{
    struct retro_variable var = {0};

    var.key = "gearsystem_up_down_allowed";
    var.value = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        if (strcmp(var.value, "Enabled") == 0)
            allow_up_down = true;
        else
            allow_up_down = false;
    }

    var.key = "gearsystem_system";
    var.value = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        if (strcmp(var.value, "Auto") == 0)
            config.system = Cartridge::CartridgeUnknownSystem;
        else if (strcmp(var.value, "Master System / Mark III") == 0)
            config.system = Cartridge::CartridgeSMS;
        else if (strcmp(var.value, "Game Gear") == 0)
            config.system = Cartridge::CartridgeGG;
        else if (strcmp(var.value, "SG-1000 / Multivision") == 0)
            config.system = Cartridge::CartridgeSG1000;
        else 
            config.system = Cartridge::CartridgeUnknownSystem;
    }

    var.key = "gearsystem_region";
    var.value = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        if (strcmp(var.value, "Auto") == 0)
            config.zone = Cartridge::CartridgeUnknownZone;
        else if (strcmp(var.value, "Master System Japan") == 0)
            config.zone = Cartridge::CartridgeJapanSMS;
        else if (strcmp(var.value, "Master System Export") == 0)
            config.zone = Cartridge::CartridgeExportSMS;
        else if (strcmp(var.value, "Game Gear Japan") == 0)
            config.zone = Cartridge::CartridgeJapanGG;
        else if (strcmp(var.value, "Game Gear Export") == 0)
            config.zone = Cartridge::CartridgeExportGG;
        else if (strcmp(var.value, "Game Gear International") == 0)
            config.zone = Cartridge::CartridgeInternationalGG;
        else
            config.zone = Cartridge::CartridgeUnknownZone;
    }

    var.key = "gearsystem_mapper";
    var.value = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        if (strcmp(var.value, "Auto") == 0)
            config.type = Cartridge::CartridgeNotSupported;
        else if (strcmp(var.value, "ROM") == 0)
            config.type = Cartridge::CartridgeRomOnlyMapper;
        else if (strcmp(var.value, "SEGA") == 0)
            config.type = Cartridge::CartridgeSegaMapper;
        else if (strcmp(var.value, "Codemasters") == 0)
            config.type = Cartridge::CartridgeCodemastersMapper;
        else if (strcmp(var.value, "Korean") == 0)
            config.type = Cartridge::CartridgeKoreanMapper;
        else if (strcmp(var.value, "SG-1000") == 0)
            config.type = Cartridge::CartridgeSG1000Mapper;
        else if (strcmp(var.value, "MSX") == 0)
            config.type = Cartridge::CartridgeMSXMapper;
        else if (strcmp(var.value, "Janggun") == 0)
            config.type = Cartridge::CartridgeJanggunMapper;
        else
            config.type = Cartridge::CartridgeNotSupported;
    }

    var.key = "gearsystem_timing";
    var.value = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        if (strcmp(var.value, "Auto") == 0)
            config.region = Cartridge::CartridgeUnknownRegion;
        else if (strcmp(var.value, "NTSC (60 Hz)") == 0)
            config.region = Cartridge::CartridgeNTSC;
        else if (strcmp(var.value, "PAL (50 Hz)") == 0)
            config.region = Cartridge::CartridgePAL;
        else
            config.region = Cartridge::CartridgeUnknownRegion;
    }

    var.key = "gearsystem_bios_sms";
    var.value = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        if (strcmp(var.value, "Enabled") == 0)
            bootrom_sms = true;
        else
            bootrom_sms = false;
    }

    var.key = "gearsystem_bios_gg";
    var.value = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        if (strcmp(var.value, "Enabled") == 0)
            bootrom_gg = true;
        else
            bootrom_gg = false;
    }

    var.key = "gearsystem_glasses";
    var.value = NULL;

    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        if (strcmp(var.value, "Both Eyes / OFF") == 0)
            glasses_config = GearsystemCore::GlassesBothEyes;
        else if (strcmp(var.value, "Left Eye") == 0)
            glasses_config = GearsystemCore::GlassesLeftEye;
        else if (strcmp(var.value, "Right Eye") == 0)
            glasses_config = GearsystemCore::GlassesRightEye;
        else
            glasses_config = GearsystemCore::GlassesBothEyes;

        cores[0]->SetGlassesConfig(glasses_config);
    }
}

void retro_run(void)
{
    bool updated = false;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
    {
        check_variables();
    }

    update_input();

    
    cores[0]->RunToVBlank(frame_buffers[0], audio_buf[0], &audio_sample_count[0]);

    if (audio_sample_count[0] > 0)
        audio_batch_cb(audio_buf[0], audio_sample_count[0] / 2);

    audio_sample_count[0] = 0;

    cores[1]->RunToVBlank(frame_buffers[1], audio_buf[1], &audio_sample_count[1]);
    

    GS_RuntimeInfo runtime_info;
    cores[0]->GetRuntimeInfo(runtime_info);

    /*
    //serial
    while (cores[1]->totalClocks < 702240)
    {
        cores[0]->RunToNextSerial(frame_buffers[0], audio_buf[0], &audio_sample_count[0]);
        cores[1]->RunToNextSerial(frame_buffers[1], audio_buf[1], &audio_sample_count[1]);
    }

    cores[0]->totalClocks = 0;
    cores[1]->totalClocks = 0;

    /*
   // cores[0]->GetAudio()->EndFrame(audio_buf[0], &audio_sample_count[0]);
    cores[0]->RenderFrameBuffer(frame_buffers[0]);
    if (cores[0]->seri_occer > 8778) cores[0]->seri_occer = 8778;

   
  //  cores[1]->GetAudio()->EndFrame(audio_buf[1], &audio_sample_count[1]);
    cores[1]->RenderFrameBuffer(frame_buffers[1]);
    if (cores[1]->seri_occer > 8778) cores[1]->seri_occer = 8778;
    */
    
    


    /*
    if ((runtime_info.screen_width != current_screen_width) || (runtime_info.screen_height != current_screen_height))
    {
        current_screen_width = runtime_info.screen_width;
        current_screen_height = runtime_info.screen_height;

        retro_system_av_info info;
        info.geometry.base_width   = runtime_info.screen_width;
        info.geometry.base_height  = runtime_info.screen_height;
        info.geometry.max_width    = runtime_info.screen_width;
        info.geometry.max_height   = runtime_info.screen_height;
        info.geometry.aspect_ratio = 0.0;

        environ_cb(RETRO_ENVIRONMENT_SET_GEOMETRY, &info.geometry);
    }*/

 

    //vertical layout
    
    //static u8 joined_buf[GS_RESOLUTION_MAX_WIDTH * GS_RESOLUTION_GG_HEIGHT * 2 * 2 ];
    static u8 joined_buf[GS_RESOLUTION_GG_WIDTH * GS_RESOLUTION_GG_HEIGHT * 2 * 2 ];
    const int half = sizeof(joined_buf) / 2;
    
    
    memcpy(joined_buf, frame_buffers[0], half);
    memcpy(joined_buf + half, frame_buffers[1], half);
 
    //video_cb((uint8_t*)frame_buffers[1], runtime_info.screen_width, runtime_info.screen_height, runtime_info.screen_width * sizeof(u8) * 2);
    // video_cb((uint8_t*)joined_buf, runtime_info.screen_width, runtime_info.screen_height*2, runtime_info.screen_width * sizeof(u8)*2);
    video_cb((uint8_t*)joined_buf, runtime_info.screen_width, GS_RESOLUTION_GG_HEIGHT * 2, runtime_info.screen_width * sizeof(u8) * 2);
    

    //horizontal layout  not working yet
    /*
    int height = GS_RESOLUTION_GG_HEIGHT;
    int width = GS_RESOLUTION_GG_WIDTH;
    const int line = GS_RESOLUTION_GG_WIDTH * 2;

    for (int row = 0; row < height; ++row)
    {
        memcpy(joined_buf + (row * 2 * line), frame_buffers[0] + width * row, width);
        memcpy(joined_buf + (row * 2 * line + 1), frame_buffers[1] + width * row, width);
  
    }

    video_cb((uint8_t*)joined_buf, current_screen_width, current_screen_height, current_screen_width * sizeof(u8) * 2);
    */


   
    
}

void retro_reset(void)
{
    check_variables();
    load_bootroms();
    cores[0]->ResetROMPreservingRAM(&config);
}

bool retro_load_game(const struct retro_game_info *info)
{
    check_variables();
    load_bootroms();

    if (!cores[0]->LoadROMFromBuffer(reinterpret_cast<const u8*>(info->data), info->size, &config))
    {
        log_cb(RETRO_LOG_ERROR, "Invalid or corrupted ROM.\n");
        return false;
    }
    if (!cores[1]->LoadROMFromBuffer(reinterpret_cast<const u8*>(info->data), info->size, &config))
    {
        log_cb(RETRO_LOG_ERROR, "Invalid or corrupted ROM.\n");
        return false;
    }

    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;
    if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
    {
        log_cb(RETRO_LOG_INFO, "RGB565 is not supported.\n");
        return false;
    }

    snprintf(retro_game_path, sizeof(retro_game_path), "%s", info->path);

    bool achievements = true;
    environ_cb(RETRO_ENVIRONMENT_SET_SUPPORT_ACHIEVEMENTS, &achievements);

    ////set game gear serial communication on 

    cores[0]->GetProcessor()->GetIOPOrts()->DoOutput(0x05, 0x38);   
    cores[1]->GetProcessor()->GetIOPOrts()->DoOutput(0x05, 0x38);


    return true;
}

void retro_unload_game(void)
{
}

unsigned retro_get_region(void)
{
    return cores[0]->GetCartridge()->IsPAL() ? RETRO_REGION_PAL : RETRO_REGION_NTSC;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num)
{
    return false;
}

size_t retro_serialize_size(void)
{
    size_t size = 0;
    cores[0]->SaveState(NULL, size);
    return size;
}

bool retro_serialize(void *data, size_t size)
{
    return cores[0]->SaveState(reinterpret_cast<u8*>(data), size);
}

bool retro_unserialize(const void *data, size_t size)
{
    return cores[0]->LoadState(reinterpret_cast<const u8*>(data), size);
}

void *retro_get_memory_data(unsigned id)
{
    switch (id)
    {
        case RETRO_MEMORY_SAVE_RAM:
            return cores[0]->GetMemory()->GetCurrentRule()->GetRamBanks();
        case RETRO_MEMORY_SYSTEM_RAM:
            return cores[0]->GetMemory()->GetMemoryMap() + 0xC000;
    }

    return NULL;
}

size_t retro_get_memory_size(unsigned id)
{
    switch (id)
    {
        case RETRO_MEMORY_SAVE_RAM:
            return cores[0]->GetMemory()->GetCurrentRule()->GetRamSize();
        case RETRO_MEMORY_SYSTEM_RAM:
            return 0x2000;
    }

    return 0;
}

void retro_cheat_reset(void)
{
    cores[0]->ClearCheats();
}

void retro_cheat_set(unsigned index, bool enabled, const char *code)
{
    cores[0]->SetCheat(code);
}
