LOCAL_PATH := $(call my-dir)

ROOT_DIR   := $(LOCAL_PATH)/../../..
CORE_DIR   := $(ROOT_DIR)/platforms/libretro
SOURCE_DIR := $(ROOT_DIR)/src

include $(CORE_DIR)/Makefile.common

COREFLAGS := -DHAVE_STDINT_H -DHAVE_INTTYPES_H -D__LIBRETRO__ -DGEARSYSTEM_DISABLE_DISASSEMBLER

include $(CLEAR_VARS)
LOCAL_MODULE    := retro
LOCAL_SRC_FILES := $(SOURCES_CXX)
LOCAL_CXXFLAGS  := $(COREFLAGS)
LOCAL_LDFLAGS   := -Wl,-version-script=$(CORE_DIR)/link.T
LOCAL_LDLIBS 	:= -llog
include $(BUILD_SHARED_LIBRARY)
