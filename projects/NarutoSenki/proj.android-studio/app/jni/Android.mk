LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := cocos2dcpp
LOCAL_MODULE_FILENAME := libcocos2dcpp
COCOS_ROOT := $(abspath $(LOCAL_PATH)/../../../../../)

LOCAL_SRC_FILES := main.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/AppDelegate.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/ActionButton.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/CharacterBase.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/BGLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/CreditsLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/Effect.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/Element.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/GameLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/GameOver.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/GameScene.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/GearLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/HPBar.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/HudLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/JoyStick.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/LoadLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/PauseLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/SelectLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/StartMenu.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/MyUtils/CCScrewLayer.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/MyUtils/CCShake.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/MyUtils/CCStrokeLabel.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/MyUtils/KTools.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/MyUtils/MD5ChecksumDefines.cpp \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/UI/GameModeLayer.cpp \
    $(COCOS_ROOT)/external/sqlite3/src/sqlite3.c

LOCAL_C_INCLUDES := \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes \
    $(COCOS_ROOT)/projects/NarutoSenki/Classes/Core \
    $(COCOS_ROOT)/cocos2dx \
    $(COCOS_ROOT)/cocos2dx/include \
    $(COCOS_ROOT)/cocos2dx/platform/android \
    $(COCOS_ROOT)/cocos2dx/platform/android/jni \
    $(COCOS_ROOT)/external \
    $(COCOS_ROOT)/external/fmt/include \
    $(COCOS_ROOT)/external/sqlite3/src
# To ensure the {fmt} library is treated as header-only across old engine files, define FMT_HEADER_ONLY
LOCAL_CPPFLAGS := -std=c++2a -frtti -fexceptions -DFMT_HEADER_ONLY
LOCAL_CFLAGS := -fexceptions -DFMT_HEADER_ONLY
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
include $(BUILD_SHARED_LIBRARY)
$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,scripting/lua/proj.android)
$(call import-module,extensions)