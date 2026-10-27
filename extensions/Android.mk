LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES := \
GUI/CCControlExtension/CCControl.cpp \
GUI/CCControlExtension/CCControlButton.cpp \
GUI/CCControlExtension/CCControlColourPicker.cpp \
GUI/CCControlExtension/CCControlHuePicker.cpp \
GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
GUI/CCControlExtension/CCControlSlider.cpp \
GUI/CCControlExtension/CCControlSwitch.cpp \
GUI/CCControlExtension/CCControlUtils.cpp \
GUI/CCControlExtension/CCInvocation.cpp \
GUI/CCControlExtension/CCScale9Sprite.cpp \
GUI/CCControlExtension/CCControlPotentiometer.cpp \
GUI/CCControlExtension/CCControlStepper.cpp \
GUI/CCScrollView/CCScrollView.cpp \
GUI/CCScrollView/CCTableView.cpp \
GUI/CCScrollView/CCTableViewCell.cpp \
GUI/CCScrollView/CCSorting.cpp \
GUI/CCEditBox/CCEditBox.cpp \
GUI/CCEditBox/CCEditBoxImplAndroid.cpp \
CocoStudio/Armature/CCArmature.cpp \
CocoStudio/Armature/CCBone.cpp \
CocoStudio/Armature/animation/CCArmatureAnimation.cpp \
CocoStudio/Armature/animation/CCProcessBase.cpp \
CocoStudio/Armature/animation/CCTween.cpp \
CocoStudio/Armature/datas/CCDatas.cpp \
CocoStudio/Armature/display/CCBatchNode.cpp \
CocoStudio/Armature/display/CCDecorativeDisplay.cpp \
CocoStudio/Armature/display/CCDisplayFactory.cpp \
CocoStudio/Armature/display/CCDisplayManager.cpp \
CocoStudio/Armature/display/CCSkin.cpp \
CocoStudio/Armature/utils/CCArmatureDefine.cpp \
CocoStudio/Armature/utils/CCArmatureDataManager.cpp \
CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.cpp \
CocoStudio/Armature/utils/CCTransformHelp.cpp \
CocoStudio/Armature/utils/CCTweenFunction.cpp \
CocoStudio/Armature/utils/CCUtilMath.cpp \
CocoStudio/GUI/BaseClasses/UIWidget.cpp \
CocoStudio/GUI/Layouts/UILayout.cpp \
CocoStudio/GUI/Layouts/UILayoutParameter.cpp \
CocoStudio/GUI/Layouts/UILayoutDefine.cpp \
CocoStudio/GUI/System/CocosGUI.cpp \
CocoStudio/GUI/System/UIHelper.cpp \
CocoStudio/GUI/System/UITouchGroup.cpp \
CocoStudio/GUI/UIWidgets/ScrollWidget/UIListView.cpp \
CocoStudio/GUI/UIWidgets/ScrollWidget/UIPageView.cpp \
CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollView.cpp \
CocoStudio/GUI/UIWidgets/UIButton.cpp \
CocoStudio/GUI/UIWidgets/UICheckBox.cpp \
CocoStudio/GUI/UIWidgets/UIImageView.cpp \
CocoStudio/GUI/UIWidgets/UILabel.cpp \
CocoStudio/GUI/UIWidgets/UILabelAtlas.cpp \
CocoStudio/GUI/UIWidgets/UILabelBMFont.cpp \
CocoStudio/GUI/UIWidgets/UILoadingBar.cpp \
CocoStudio/GUI/UIWidgets/UISlider.cpp \
CocoStudio/GUI/UIWidgets/UITextField.cpp \
CocoStudio/GUI/UIWidgets/UIRichText.cpp \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/GUI/CCControlExtension \
                           $(LOCAL_PATH)/GUI/CCScrollView \
                           $(LOCAL_PATH)/CocoStudio/Armature \
                           $(LOCAL_PATH)/CocoStudio

LOCAL_CFLAGS := -fexceptions
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
