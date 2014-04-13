//
//  ZYWebView.cpp
//  CCXWebview
//
//  Created by Vincent on 12-11-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ZYWebView.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

/*
 More info about JNI using, check this:
 http://go3k.org/?p=49
 */

#warning If you want to use this CCXWebview in your project, please modify this packageName as your Android project.
const char* kJNIPakageName = "jp/shinobigames/yakitori/Yakitori";

ZYWebView::ZYWebView()
{
    
}

ZYWebView::~ZYWebView()
{
    
}

bool ZYWebView::init()
{
	return true;
}

void ZYWebView::showWebView(const char* url, float x, float y, float width, float height)
{
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 kJNIPakageName,
                                                 "getJavaActivity",
                                                 "()Ljava/lang/Object;");
    jobject activityObj;
    if (isHave) {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    
    isHave = JniHelper::getMethodInfo(minfo,kJNIPakageName,"displayWebView", "(IIII)V");
    
    if (isHave) {
        jint jX = (int)x;
        jint jY = (int)y;
        jint jWidth = (int)width;
        jint jHeight = (int)height;
        minfo.env->CallVoidMethod(activityObj, minfo.methodID, jX, jY, jWidth, jHeight);
    }
    
    isHave = JniHelper::getMethodInfo(minfo,kJNIPakageName,"updateURL", "(Ljava/lang/String;)V");
    
    if (isHave) {
        jstring jmsg = minfo.env->NewStringUTF(url);
        minfo.env->CallVoidMethod(activityObj, minfo.methodID, jmsg);
    }
}

void ZYWebView::updateURL(const char* url)
{
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 kJNIPakageName,
                                                 "getJavaActivity",
                                                 "()Ljava/lang/Object;");
    jobject activityObj;
    if (isHave) {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    
    isHave = JniHelper::getMethodInfo(minfo,kJNIPakageName,"updateURL", "(Ljava/lang/String;)V");
    
    if (isHave) {
        jstring jmsg = minfo.env->NewStringUTF(url);
        minfo.env->CallVoidMethod(activityObj, minfo.methodID, jmsg);
    }
}

void ZYWebView::removeWebView()
{
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 kJNIPakageName,
                                                 "getJavaActivity",
                                                 "()Ljava/lang/Object;");
    jobject activityObj;
    if (isHave) {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    
    isHave = JniHelper::getMethodInfo(minfo,kJNIPakageName,"removeWebView", "()V");
    
    if (isHave) {
        minfo.env->CallVoidMethod(activityObj, minfo.methodID);
    }
}

