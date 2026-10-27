TARGET = libextension.a

COCOS_ROOT=../..

INCLUDES = -I$(COCOS_ROOT)/external \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I.. \
	-I../GUI/CCControlExtension \
	-I../GUI/CCEditBox \
	-I../CocoStudio/Armature \
	-I../CocoStudio/GUI \

SOURCES = ../GUI/CCScrollView/CCScrollView.cpp \
../GUI/CCScrollView/CCSorting.cpp \
../GUI/CCScrollView/CCTableView.cpp \
../GUI/CCScrollView/CCTableViewCell.cpp \
../GUI/CCControlExtension/CCControlButton.cpp \
../GUI/CCControlExtension/CCControlColourPicker.cpp \
../GUI/CCControlExtension/CCControl.cpp \
../GUI/CCControlExtension/CCControlHuePicker.cpp \
../GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
../GUI/CCControlExtension/CCControlSlider.cpp \
../GUI/CCControlExtension/CCControlSwitch.cpp \
../GUI/CCControlExtension/CCControlUtils.cpp \
../GUI/CCControlExtension/CCInvocation.cpp \
../GUI/CCControlExtension/CCScale9Sprite.cpp \
../GUI/CCControlExtension/CCControlPotentiometer.cpp \
../GUI/CCControlExtension/CCControlStepper.cpp \
../GUI/CCEditBox/CCEditBox.cpp \
../GUI/CCEditBox/CCEditBoxImplLinux.cpp \
../CocoStudio/Armature/CCArmature.cpp \
../CocoStudio/Armature/CCBone.cpp \
../CocoStudio/Armature/animation/CCArmatureAnimation.cpp \
../CocoStudio/Armature/animation/CCProcessBase.cpp \
../CocoStudio/Armature/animation/CCTween.cpp \
../CocoStudio/Armature/datas/CCDatas.cpp \
../CocoStudio/Armature/display/CCBatchNode.cpp \
../CocoStudio/Armature/display/CCDecorativeDisplay.cpp \
../CocoStudio/Armature/display/CCDisplayFactory.cpp \
../CocoStudio/Armature/display/CCDisplayManager.cpp \
../CocoStudio/Armature/display/CCSkin.cpp \
../CocoStudio/Armature/utils/CCArmatureDefine.cpp \
../CocoStudio/Armature/utils/CCArmatureDataManager.cpp \
../CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.cpp \
../CocoStudio/Armature/utils/CCTransformHelp.cpp \
../CocoStudio/Armature/utils/CCTweenFunction.cpp \
../CocoStudio/Armature/utils/CCUtilMath.cpp \
../CocoStudio/GUI/BaseClasses/UIWidget.cpp \
../CocoStudio/GUI/Layouts/UILayout.cpp \
../CocoStudio/GUI/Layouts/UILayoutParameter.cpp \
../CocoStudio/GUI/Layouts/UILayoutDefine.cpp \
../CocoStudio/GUI/System/CocosGUI.cpp \
../CocoStudio/GUI/System/UIHelper.cpp \
../CocoStudio/GUI/System/UITouchGroup.cpp \
../CocoStudio/GUI/UIWidgets/ScrollWidget/UIListView.cpp \
../CocoStudio/GUI/UIWidgets/ScrollWidget/UIPageView.cpp \
../CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollView.cpp \
../CocoStudio/GUI/UIWidgets/UIButton.cpp \
../CocoStudio/GUI/UIWidgets/UICheckBox.cpp \
../CocoStudio/GUI/UIWidgets/UIImageView.cpp \
../CocoStudio/GUI/UIWidgets/UILabel.cpp \
../CocoStudio/GUI/UIWidgets/UILabelAtlas.cpp \
../CocoStudio/GUI/UIWidgets/UILabelBMFont.cpp \
../CocoStudio/GUI/UIWidgets/UILoadingBar.cpp \
../CocoStudio/GUI/UIWidgets/UISlider.cpp \
../CocoStudio/GUI/UIWidgets/UITextField.cpp \
../CocoStudio/GUI/UIWidgets/UIRichText.cpp \

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

CXXFLAGS += -Wno-multichar -Wno-delete-non-virtual-dtor

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_AR)$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -g -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -g -c $< -o $@
