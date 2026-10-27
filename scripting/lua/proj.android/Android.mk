LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_lua_static

LOCAL_MODULE_FILENAME := liblua

LOCAL_SRC_FILES := ../cocos2dx_support/CCLuaBridge.cpp \
          ../cocos2dx_support/CCLuaEngine.cpp \
          ../cocos2dx_support/CCLuaStack.cpp \
          ../cocos2dx_support/CCLuaValue.cpp \
          ../cocos2dx_support/Cocos2dxLuaLoader.cpp \
          ../cocos2dx_support/LuaCocos2d.cpp \
          ../cocos2dx_support/LuaCocoStudio.cpp \
          ../cocos2dx_support/lua_cocos2dx_manual.cpp \
          ../cocos2dx_support/lua_cocos2dx_extensions_manual.cpp \
          ../cocos2dx_support/lua_cocos2dx_cocostudio_manual.cpp \
          ../tolua/tolua_event.c \
          ../tolua/tolua_is.c \
          ../tolua/tolua_map.c \
          ../tolua/tolua_push.c \
          ../tolua/tolua_to.c \
          ../cocos2dx_support/tolua_fix.c \
          ../xxtea/xxtea.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../tolua \
                           $(LOCAL_PATH)/../cocos2dx_support \
                           $(LOCAL_PATH)/../xxtea \
			               $(LOCAL_PATH)/../luajit/include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/../tolua \
                    $(LOCAL_PATH)/../luajit/include \
                    $(LOCAL_PATH)/../../../cocos2dx \
                    $(LOCAL_PATH)/../../../cocos2dx/include \
                    $(LOCAL_PATH)/../../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../../cocos2dx/platform/android \
                    $(LOCAL_PATH)/../../../cocos2dx/kazmath/include \
                    $(LOCAL_PATH)/../../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../../extensions \
                    $(LOCAL_PATH)/../xxtea \
                    $(LOCAL_PATH)/../../../external/sqlite3/src \
                    $(LOCAL_PATH)/../../../projects/NarutoSenki/Classes \
                    $(LOCAL_PATH)/../../../projects/NarutoSenki/Classes/Core \
                    $(LOCAL_PATH)/../../../projects/NarutoSenki/Classes/MyTools

LOCAL_WHOLE_STATIC_LIBRARIES := luajit_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_STATIC_LIBRARY)

$(call import-module,scripting/lua/luajit)
$(call import-module,extensions)
