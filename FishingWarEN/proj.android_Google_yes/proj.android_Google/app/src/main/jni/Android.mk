LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Adjust/Adjust2dx.cpp \
                   ../../Classes/Adjust/AdjustAttribution2dx.cpp \
                   ../../Classes/Adjust/AdjustConfig2dx.cpp \
                   ../../Classes/Adjust/AdjustEvent2dx.cpp \
                   ../../Classes/Adjust/AdjustProxy2dx.cpp \
                   ../../Classes/AllRobot.cpp \
                   ../../Classes/BiBei.cpp \
                   ../../Classes/Bullet.cpp \
                   ../../Classes/Cannon.cpp \
                   ../../Classes/CannonLayer.cpp \
                   ../../Classes/CannonUpgrade.cpp \
                   ../../Classes/ChallengeBoss.cpp \
                   ../../Classes/CoinAndAni.cpp \
                   ../../Classes/DialogText.cpp \
                   ../../Classes/Fish.cpp \
                   ../../Classes/FishAnimate.cpp \
                   ../../Classes/FishBaiKe.cpp \
                   ../../Classes/FishGroup.cpp \
                   ../../Classes/FishingNet.cpp \
                   ../../Classes/FishLayer.cpp \
                   ../../Classes/FishLineup.cpp \
                   ../../Classes/FishRandSwatch.cpp \
                   ../../Classes/FishScript.cpp \
                   ../../Classes/FishTrack.cpp \
                   ../../Classes/Game_Hall_Kefu1.cpp \
                   ../../Classes/GameBegin.cpp \
                   ../../Classes/GameData.cpp \
                   ../../Classes/GameEmail.cpp \
                   ../../Classes/GameHallLayer.cpp \
                   ../../Classes/GameHelp.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/GameSet.cpp \
                   ../../Classes/GameTextIn.cpp \
                   ../../Classes/Gonggao.cpp \
                   ../../Classes/Gongxi.cpp \
                   ../../Classes/HongBao.cpp \
                   ../../Classes/InitPlayer.cpp \
                   ../../Classes/LoadRes.cpp \
                   ../../Classes/LoginReward.cpp \
                   ../../Classes/LogoLayer.cpp \
                   ../../Classes/LvUp.cpp \
                   ../../Classes/MatchPlayer.cpp \
                   ../../Classes/Mission.cpp \
                   ../../Classes/MissionSuc.cpp \
                   ../../Classes/OnlineReward.cpp \
                   ../../Classes/Shark.cpp \
                   ../../Classes/Shop.cpp \
                   ../../Classes/ShopJJ.cpp \
                   ../../Classes/smShop.cpp \
                   ../../Classes/sqlite3.c \
                   ../../Classes/StaticData.cpp \
                   ../../Classes/TcpClientSocket.cpp \
                   ../../Classes/TiShi.cpp \
                   ../../Classes/UIWebViewTest.cpp \
                   ../../Classes/UnLockLayer.cpp \
                   ../../Classes/VIPgongxi.cpp \
                   ../../Classes/Waiting.cpp \
                   ../../Classes/Weapon.cpp \
                   ../../Classes/JNative/JNativeToCPlusPlusUtil.cpp \
                   ../../Classes/JNative/JNativeToJavaUtil.cpp \
                   ../../Classes/ZuanPan.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
