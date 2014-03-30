//
//  AudioUtil.h
//  jump
//
//  Created by Akio Yamazaki on 2013/12/01.
//
//

#ifndef __jump__AudioUtil__
#define __jump__AudioUtil__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define SOUND_GAME_PLAY "game_play.mp3"
#define SOUND_ENTER "enter.mp3"
#define SOUND_TITLE "game_title.mp3"
#define SOUND_JUMP "jump.mp3"
#define SOUND_GAMEOVER_SCENE "gameover_scene.mp3"
#define SOUND_EXPLOSION "explosion.mp3"

class AudioUtil
{
private:
    AudioUtil();
    virtual ~AudioUtil();
    static AudioUtil* m_mySingleton;
    
public:
    bool isVolume;
    bool isPlay;
    
    static AudioUtil* sharedEngine();
    void changeVolume();
    
    unsigned int playEffect(const char* pszFilePath, bool bLoop);
    void stopEffect(unsigned int nSoundId);
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);
    void stopBackgroundMusic(bool bReleaseData);
};

#endif /* defined(__jump__AudioUtil__) */
