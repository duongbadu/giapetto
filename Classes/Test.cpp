//
//  Test.cpp
//  Giapetto
//
//  Created by Jason Mak on 2015-02-16.
//
//

#include "Test.h"

bool HelloWorld::onTouchBegan(Touch* touch, Event  *event)
{
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event  *event)
{
    auto location = touch->getLocation();
    
    auto s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction( MoveTo::create(1, Vec2(location.x, location.y) ) );
}