#include "cocos2d.h"

class NativeBridge
{
public:
    static const char* getLocalizeString(const char* key);
    static void openTweetDialog(int score);
    static void openFacebookDialog(int score);
    static void openAppStore();
    static void openAppStoreList();
    static const char* getCurrentLanguage();
};