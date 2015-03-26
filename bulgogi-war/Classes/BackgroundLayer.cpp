#include		"BackgroundLayer.h"

USING_NS_CC;

BackgroundLayer::~BackgroundLayer() {

}

CCScene* BackgroundLayer::scene()
{
    CCScene *scene = CCScene::create();
    BackgroundLayer *layer = BackgroundLayer::create();

    scene->addChild(layer);
    return scene;
}

bool BackgroundLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _running = false;
    _skySpeed = 0.2;
    _asteSpeed = 1;
    _asteNum = 3;

    createLayer();
    
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(BackgroundLayer::update));
    return true;
}

void	BackgroundLayer::update(float dt)
{
  CCPoint	skyPos = _sky->getPosition();
  CCPoint	skyPos2 = _sky2->getPosition();
  CCPoint	aste1Pos = _aste1->getPosition();
  CCPoint	aste2Pos = _aste2->getPosition();

  _sky->setPosition(ccp(skyPos.x - _skySpeed, skyPos.y));
  _sky2->setPosition(ccp(skyPos2.x - _skySpeed, skyPos2.y));
  _aste1->setPosition(ccp(aste1Pos.x - _asteSpeed, aste1Pos.y));
  _aste2->setPosition(ccp(aste2Pos.x - _asteSpeed, aste2Pos.y));
  if (skyPos.x < -_sky->getContentSize().width)
    _sky->setPosition(ccp(_sky->getContentSize().width - _skySpeed*2, 0));
  if (skyPos2.x < -_sky2->getContentSize().width)
    _sky2->setPosition(ccp(_sky2->getContentSize().width - _skySpeed*2, 0));
  if (aste1Pos.x < (-_aste1->getContentSize().width))
    _aste1->setPosition(ccp(_screenSize.width, 0));
  if (aste2Pos.x < (-_aste2->getContentSize().width))
    _aste2->setPosition(ccp(_screenSize.width + 300, 0));
}

void	BackgroundLayer::createLayer() {
  
  _sky = CCSprite::create("sky_background.jpg");
  _sky->setAnchorPoint(ccp(0,0));
  this->addChild(_sky, 0);

  _sky2 = CCSprite::create("sky_background.jpg");
  _sky2->setAnchorPoint(ccp(0,0));
  _sky2->setPosition(ccp(_sky->getContentSize().width, 0));
  this->addChild(_sky2, 0);

  _aste1 = CCSprite::create("aste1.png");
  _aste1->setAnchorPoint(ccp(0,0));
  _aste1->setPosition(ccp(_screenSize.width, 0));
  this->addChild(_aste1, 1);

  _aste2 = CCSprite::create("aste2.png");
  _aste2->setAnchorPoint(ccp(0,0));
  _aste2->setPosition(ccp(_screenSize.width + 300, 0));
  this->addChild(_aste2, 1);
}

void BackgroundLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
}

void BackgroundLayer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
   
}

void  BackgroundLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
  //Next assignement
}
