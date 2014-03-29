//
//  GameManager.cpp
//  jump
//
//  Created by Akio Yamazaki on 2013/11/30.
//
//

#include "GameManager.h"

GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager()
{
    m_point = 0;
}

GameManager::~GameManager()
{
    
}

GameManager* GameManager::sharedGameManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new GameManager();
    }
    
    //Return the singleton object
    return m_mySingleton;
}

int GameManager::getHighScore()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(HIGH_SCORE, 0);
}

int GameManager::getAllScore()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(ALL_SCORE, 0);
}


bool GameManager::putScore(int score)
{
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    int highScore = this->getHighScore();
    int allScore = this->getAllScore();
    
    userDefault->setIntegerForKey(ALL_SCORE, allScore + score);
    if (highScore <= score) {
        userDefault->setIntegerForKey(HIGH_SCORE, score);
        return true;
    }
    
    return false;
}

void GameManager::setPoint(int point)
{
    m_point = point;
}

int GameManager::getPoint()
{
    return m_point;
}