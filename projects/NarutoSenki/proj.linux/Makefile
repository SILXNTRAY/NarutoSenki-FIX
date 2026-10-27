EXECUTABLE = NarutoSenki

SOURCES = main.cpp \
	../Classes/AppDelegate.cpp \
	../Classes/ActionButton.cpp \
	../Classes/CharacterBase.cpp \
	../Classes/BGLayer.cpp \
	../Classes/CreditsLayer.cpp \
	../Classes/Effect.cpp \
	../Classes/Element.cpp \
	../Classes/GameLayer.cpp \
	../Classes/GameOver.cpp \
	../Classes/GameScene.cpp \
	../Classes/GearLayer.cpp \
	../Classes/HPBar.cpp \
	../Classes/HudLayer.cpp \
	../Classes/JoyStick.cpp \
	../Classes/LoadLayer.cpp \
	../Classes/PauseLayer.cpp \
	../Classes/SelectLayer.cpp \
	../Classes/StartMenu.cpp \
	../Classes/UI/GameModeLayer.cpp \
	../Classes/MyUtils/CCScrewLayer.cpp \
	../Classes/MyUtils/CCShake.cpp \
	../Classes/MyUtils/CCStrokeLabel.cpp \
	../Classes/MyUtils/KTools.cpp \
	../Classes/MyUtils/MD5ChecksumDefines.cpp \

SHAREDLIBS += -lcocos2d -lcocosdenshion -lsqlite3 -llua -lluajit
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so \
	$(LIB_DIR)/libcocosdenshion.so \
	$(LIB_DIR)/liblua.so \
	$(LIB_DIR)/libluajit.so \

include ../../../cocos2dx/proj.linux/cocos2dx.mk

INCLUDES +=	 -I../ \
	-I../../ \
	-I../Classes \
	-I../Classes/Core \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I$(COCOS_ROOT)/extensions \
	-I$(COCOS_ROOT)/external \
	-I$(COCOS_ROOT)/scripting/lua/luajit/include \
	-I$(COCOS_ROOT)/scripting/lua/tolua \
	-I$(COCOS_ROOT)/scripting/lua/cocos2dx_support \

CXXFLAGS += -std=c++20

STATICLIBS += $(LIB_DIR)/libextension.a

####### Build rules
$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(STATICLIBS) $(SHAREDLIBS) $(LIBS)
	rm -rf ../__BIN__/NarutoSenki
	cp $(@D)/NarutoSenki ../__BIN__

####### Compile
$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
