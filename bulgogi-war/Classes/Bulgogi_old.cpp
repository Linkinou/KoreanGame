#include "Bulgogi.h"
#include "AppMacros.h"
USING_NS_CC;


CCScene* Bulgogi::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Bulgogi *layer = Bulgogi::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Bulgogi::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    _visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    _origin = CCDirector::sharedDirector()->getVisibleOrigin();
    setTouchEnabled(true);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Bulgogi::menuCloseCallback));
    
    pCloseItem->setPosition(ccp(_origin.x + _visibleSize.width - pCloseItem->getContentSize().width/2 , _origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    //INIT SOME VALUES FOR THE GAME
    ennemyNb = 1;
    _playerColumn = _visibleSize.width / 5;
    for (int i = 0; i < ennemyNb; i++) {
      ennemies.push_back(new Ennemy(10));
    }
    for (int i = 0; i < ennemies.size(); i++) {
      this->addChild(ennemies[i]->getSprite());
      std::cout << "addChild()" << std::endl;
    }

    //CREATE SPRITES
    _bg1 = CCSprite::create("bg.png");
    _bg2 = CCSprite::create("bg.png");
    _player = CCSprite::create("flight.png");
    CCSprite* _test = CCSprite::create("flight2.png");

    //CONFIG SPRITES
    _bg1->setPosition(ccp(_visibleSize.width/2, _visibleSize.height/2 + _origin.y));
    _bg2->setPosition(ccp((_visibleSize.width/2 * 3) + _origin.x, _visibleSize.height/2 + _origin.y));
    _player->setPosition(ccp(_playerColumn, _visibleSize.height/2 + _origin.y));
    _bg2->setScaleX(-1.0f);
    _bg2->setScaleY(-1.0f);
    _test->setPosition(ccp(100, 100));
    //ADD SPRITES
    this->addChild(_bg1, 0);
    this->addChild(_bg2, 0);
    this->addChild(_player, 1, 100);
    this->addChild(_test, 1, 100);

    this->schedule(schedule_selector(Bulgogi::update));
    return true;
}

void Bulgogi::scrollBackground() { 

  _bg1->setPosition(ccp(_bg1->getPositionX() - 5, _bg1->getPositionY() ));
  _bg2->setPosition(ccp(_bg2->getPositionX() - 5, _bg2->getPositionY() )); 
 
  if (_bg1->getPositionX() + _visibleSize.width/2 <= _origin.x) { 
    _bg1->setPosition( ccp((_visibleSize.width/2) * 3 , 
				   _visibleSize.height/2 + _origin.y));
  }
  if (_bg2->getPositionX() + _visibleSize.width/2 <= _origin.x) { 
    _bg2->setPosition( ccp((_visibleSize.width/2) * 3 , 
				   _visibleSize.height/2 + _origin.y)); 
  }

}

void Bulgogi::update() {
  scrollBackground();
}

void Bulgogi::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
  
}  

void Bulgogi::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
  CCPoint location = getPositionFromTouches(touches, event);
  CCSprite *player = (CCSprite*) getChildByTag(100);
  player->setPosition(ccp(location.x,location.y));
}

void  Bulgogi::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

}

CCPoint Bulgogi::getPositionFromTouches(CCSet* _touches, CCEvent* event) {
  CCArray *allTouches = CCArray::create();

  CCSetIterator it;

  for( it = _touches->begin(); it != _touches->end(); it++)
    {
      allTouches->addObject((CCTouch *)*it);
    }
  CCTouch* fingerOne = (CCTouch *)allTouches->objectAtIndex(0);
  CCPoint  pointOne = CCDirector::sharedDirector()->convertToUI(fingerOne->getLocationInView());
  CCTouch* pTouch = (CCTouch*)(_touches->anyObject());
  CCPoint location = pTouch->locationInView();
  location = CCDirector::sharedDirector()->convertToGL(location);
  return location;
}

void Bulgogi::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
