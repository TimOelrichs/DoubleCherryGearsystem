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

#ifndef GAMEGEARIOPORTS_H
#define	GAMEGEARIOPORTS_H

#include "IOPorts.h"

class Audio;
class Video;
class Input;
class Cartridge;
class Memory;

class GameGearIOPorts : public IOPorts
{
public:
    GameGearIOPorts(Audio* pAudio, Video* pVideo, Input* pInput, Cartridge* pCartridge, Memory* pMemory);
    virtual ~GameGearIOPorts();
    void Reset();
    virtual u8 DoInput(u8 port);
    virtual void DoOutput(u8 port, u8 value);
    virtual void SaveState(std::ostream& stream);
    virtual void LoadState(std::istream& stream);
    void SetBaudrate(u8 selection) { m_current_serial_baudrate = m_serial_baurate_options[selection]; };
    int GetBaudrate() { return m_current_serial_baudrate; };
private:
    Audio* m_pAudio;
    Video* m_pVideo;
    Input* m_pInput;
    Memory* m_pMemory;
    Cartridge* m_pCartridge;
    u8 m_Port3F;
    u8 m_Port3F_HC;

    int m_serial_baurate_options[4] = { 4800,2400,1200,300 };
    int m_current_serial_baudrate = 4800;
};

#endif	/* GAMEGEARIOPORTS_H */
