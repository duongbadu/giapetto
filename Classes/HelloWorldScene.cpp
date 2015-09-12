#include "HelloWorldScene.h"

USING_NS_CC;

enum
{
    kTagSprite = 1,
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    
    //
    //  My game code
    //
    
    // create hero sprite
    auto hero = Sprite::create("hero.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    hero->setPosition(Vec2(origin.x + 200, origin.y + 200));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    this->addChild(hero, 1, kTagSprite);
    
    // move hero (only last action will be run)
    //hero->runAction(MoveTo::create(2, Vec2(50, 50)));
    auto moveBy = MoveBy::create(0.3, Vec2(100, 100));
    auto shrinkSize = ScaleBy::create(0.5f, 0.5f);
    auto growSize = ScaleBy::create(0.5f, 2.0f);
    hero->runAction(Sequence::create(moveBy, shrinkSize, moveBy, growSize, nullptr));
    
    // event listener code for touch events
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event  *event) {
        return true;
    };
    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event  *event) {
        hero->runAction( MoveTo::create(0.2, touch->getLocation() ) );
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    //this->schedule(schedule_selector(HelloWorld::update));
    TMXTiledMap *map = TMXTiledMap::create("isometric_grass_and_water.tmx");
    addChild(map, 0);
    
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event  *event)
{
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event  *event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction( MoveTo::create(0.1, Vec2(location.x, location.y) ) );
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
