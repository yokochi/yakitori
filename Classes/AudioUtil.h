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

#define SOUND_GAME_PLAY "game_music.mp3"
#define SOUND_ENTER "enter.mp3"
#define SOUND_GAMEOVER_SCENE "game_over.mp3"
#define SOUND_CORRECT_ANSWER "correct_answer.mp3"
#define SOUND_NON_CORRECT_ANSWER "non_correct_answer.mp3"
#define SOUND_PUT "put.mp3"

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
