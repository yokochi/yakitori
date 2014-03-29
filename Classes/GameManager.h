//
//  GameManager.h
//  jump
//
//  Created by Akio Yamazaki on 2013/11/30.
//
//

#ifndef __jump__GameManager__
#define __jump__GameManager__

#include <iostream>
#include "cocos2d.h"

#define HIGH_SCORE "highScore"
#define ALL_SCORE "allScore"

using namespace cocos2d;

class GameManager
{
private:
    int m_point;
    
    GameManager();
    virtual ~GameManager();
    static GameManager* m_mySingleton;
    
public:
    static GameManager* sharedGameManager();
    
    int getHighScore();
    int getAllScore();
    void setPoint(int point);
    int getPoint();
    bool putScore(int score);
};

#endif /* defined(__jump__GameManager__) */
