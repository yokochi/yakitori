//
//  AudioUtil.cpp
//  jump
//
//  Created by Akio Yamazaki on 2013/12/01.
//
//

#include "AudioUtil.h"

AudioUtil* AudioUtil::m_mySingleton = NULL;

AudioUtil::AudioUtil()
{
    isVolume = true;
    isPlay = false;
}

AudioUtil::~AudioUtil()
{
    
}

AudioUtil* AudioUtil::sharedEngine()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new AudioUtil();
    }
    
    //Return the singleton object
    return m_mySingleton;
}

void AudioUtil::changeVolume()
{
    isVolume = !isVolume;
}

unsigned int AudioUtil::playEffect(const char *pszFilePath, bool bLoop)
{
    if (isVolume) {
        return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pszFilePath, bLoop);
    } else {
        return 0;
    }
}

void AudioUtil::stopEffect(unsigned int nSoundId)
{
    if (0 != nSoundId) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(nSoundId);
    }
}


void AudioUtil::playBackgroundMusic(const char *pszFilePath, bool bLoop)
{
    if (isVolume) {
        isPlay = true;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pszFilePath, bLoop);
    }
}

void AudioUtil::stopBackgroundMusic(bool bReleaseData)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(bReleaseData);
    isPlay = false;
}