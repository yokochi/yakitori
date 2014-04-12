#import "NativeBridge.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

USING_NS_CC;

#define CLASS_NAME "jp/shinobigames/yakitori/Yakitori"

const char* NativeBridge::getLocalizeString(const char *key)
{
    JniMethodInfo methodInfo;
    if (!JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getLocalizeString", "(Ljava/lang/String;)Ljava/lang/String;")) {
        CCLog("Failed to find static method of getLocalizeString");
        return "";
    }
    // Javaのプログラムを呼び出す
    jstring stringArg1 = methodInfo.env->NewStringUTF(key);
    jstring objResult = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, stringArg1);
    
    const char* result = methodInfo.env->GetStringUTFChars(objResult, 0);

    // 解放処理
    methodInfo.env->DeleteLocalRef(stringArg1);
    methodInfo.env->DeleteLocalRef(objResult);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    
    return result;
}

void NativeBridge::openTweetDialog(int score)
{
}

void NativeBridge::openFacebookDialog(int score)
{
}

void NativeBridge::openAppStore()
{
}

void NativeBridge::openAppStoreList()
{
}

const char* NativeBridge::getCurrentLanguage()
{
    JniMethodInfo methodInfo;
    
    if (!JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getLanguage", "()Ljava/lang/String;")) {
        CCLog("Failed to find static method of getCurrentLanguage");
        return "";
    }
    // Javaのプログラムを呼び出す
    jstring objResult = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
    
    const char* result = methodInfo.env->GetStringUTFChars(objResult, 0);
    
    // 解放処理
    methodInfo.env->DeleteLocalRef(objResult);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    
    return result;
}

void NativeBridge::showAppCMarqueeView()
{
}

void NativeBridge::removeAppCMarqueeView()
{
}

/**
 * GameCenter score送信
 */
void NativeBridge::sendRecordSales(int yen)
{
}

/**
 * GameCenter score送信
 */
void NativeBridge::sendGrossSales(int yen)
{
}

/**
 * GameCenter ランキング表示
 */
void NativeBridge::showBord()
{
}
