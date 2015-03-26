#include "Menu.h"
#include "BackgroundLayer.h"
USING_NS_CC;


CCScene* Menu::scene()
{
    CCScene *scene = CCScene::create();
    Menu *layer = Menu::create();
    BackgroundLayer *bg = BackgroundLayer::create();
    scene->addChild(bg);
    scene->addChild(layer);
    return scene;
}

bool Menu::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();    
    CCActionInterval* waves = CCWaves3D::create(2,20,ccg(10,5),5);
    
    _screenTitle = CCSprite::create("screen_title2.png");
    _screenTitle->setAnchorPoint(ccp(0,0));
    _screenTitle->runAction(CCRepeatForever::create(waves));
    setTouchEnabled(true);
    this->addChild(_screenTitle, 0);

    return true;
}

Menu::~Menu() {

}

void Menu::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
  CCScene	*_gameScene = Bulgogi::scene();
  CCDirector::sharedDirector()->replaceScene(_gameScene);  
}

void Menu::ccTouchesMoved(CCSet* touches, CCEvent* event)
{

}

void  Menu::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

}
