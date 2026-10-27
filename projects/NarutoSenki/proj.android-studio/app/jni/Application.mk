LOCAL_PATH := $(call my-dir)

APP_STL := c++_static
APP_CPPFLAGS += -std=c++2a -frtti -fexceptions
APP_LDFLAGS := -latomic
APP_SHORT_COMMANDS := true

NDK_MODULE_PATH := $(LOCAL_PATH)/../../../../../

ifeq ($(NDK_DEBUG),1)
    APP_CPPFLAGS += -DNDEBUG -DCOCOS2D_DEBUG=1
else
    APP_CPPFLAGS += -DCOCOS2D_DEBUG=0
endif

APP_ABI := armeabi-v7a arm64-v8a
APP_PLATFORM := android-21
