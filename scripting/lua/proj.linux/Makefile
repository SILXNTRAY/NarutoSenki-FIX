TARGET = liblua.so

INCLUDES += -I.. \
	-I../tolua \
	-I../xxtea \
	-I../luajit/include \
	-I../../../CocosDenshion/include \
	-I../../../extensions \
	-I../../../external \
	-I../../../projects/NarutoSenki/Classes \
	-I../../../projects/NarutoSenki/Classes/Core \

SOURCES = ../tolua/tolua_event.c \
	../tolua/tolua_is.c \
	../tolua/tolua_map.c \
	../tolua/tolua_push.c \
	../tolua/tolua_to.c \
	../cocos2dx_support/tolua_fix.c \
	../cocos2dx_support/CCLuaBridge.cpp \
	../cocos2dx_support/CCLuaEngine.cpp \
	../cocos2dx_support/CCLuaStack.cpp \
	../cocos2dx_support/CCLuaValue.cpp \
	../cocos2dx_support/Cocos2dxLuaLoader.cpp \
	../cocos2dx_support/LuaCocos2d.cpp \
	../cocos2dx_support/LuaCocoStudio.cpp \
	../cocos2dx_support/lua_cocos2dx_manual.cpp \
	../cocos2dx_support/lua_cocos2dx_extensions_manual.cpp \
	../cocos2dx_support/lua_cocos2dx_cocostudio_manual.cpp \
	../xxtea/xxtea.cpp

include ../../../cocos2dx/proj.linux/cocos2dx.mk

CXXFLAGS += -std=c++20

TARGET := $(LIB_DIR)/$(TARGET)

SHAREDLIBS += -lcocos2d -lcocosdenshion -lextension -lluajit

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -shared -o $@ $(SHAREDLIBS) $(STATICLIBS)
	cp $(COCOS_ROOT)/scripting/lua/luajit/linux/libluajit.so $(LIB_DIR)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -g -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -g -c $< -o $@
