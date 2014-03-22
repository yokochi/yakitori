//
//  TitleScene.h
//  Yakitori
//
//  Created by Akio Yamazaki on 2014/03/16.
//
//

#ifndef __Yakitori__TitleScene__
#define __Yakitori__TitleScene__

#include <iostream>

#include "cocos2d.h"

class TitleScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuStartCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TitleScene);
    
private:
    void initCompornent();
};

#endif /* defined(__Yakitori__TitleScene__) */
