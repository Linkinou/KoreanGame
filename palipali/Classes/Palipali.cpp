#include "Palipali.h"
#include			"BackgroundLayer.h"
#include			"targetFall.h"
#include			"fallingGift.h"

USING_NS_CC;


CCScene* Palipali::scene()
{
    CCScene *scene = CCScene::create();
    Palipali *layer = Palipali::create();
    BackgroundLayer *bg = BackgroundLayer::create();
    scene->addChild(bg);
    scene->addChild(layer, 4242);
    return scene;
}

bool Palipali::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }    

    _mapFPtr["addCrystal"] = &Palipali::addCrystal;
    _mapFPtr["setReady"] = &Palipali::setReady;
    
    _visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    _origin = CCDirector::sharedDirector()->getVisibleOrigin();
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    setTouchEnabled(true);
    _levelLabel = CCLabelTTF::create("Level : 0", "Helvetica", 12,
				     CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCMenuItemImage *pShoot = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(Palipali::menuCloseCallback));
    
    pShoot->setPosition(ccp(_origin.x + _visibleSize.width - pShoot->getContentSize().width/2 , _origin.y + pShoot->getContentSize().height/2));
    CCMenu* pMenu = CCMenu::create(pShoot, NULL);
    pMenu->setPosition(CCPointZero);
    CCSprite*	levelsBg = CCSprite::create("scorescreen_levels.png");
    levelsBg->setAnchorPoint(ccp(0, 0));
    this->addChild(levelsBg, 1);
    this->addChild(pMenu, 1);
    this->addChild(_levelLabel);

    _crystal1 = CCSprite::create("crystal1.png");
    _crystal2 = CCSprite::create("crystal2.png");
    _crystal3 = CCSprite::create("crystal3.png");
    _crystal1->setPosition(ccp(-100, _screenSize.height - 100));
    _crystal2->setPosition(ccp(-100, _screenSize.height - 200));
    _crystal3->setPosition(ccp(-100, _screenSize.height - 300));
    this->addChild(_crystal1, 2);
    this->addChild(_crystal2, 2);
    this->addChild(_crystal3, 2);
    //INIT SOME VALUES FOR THE GAME
    _currentFrame = 0;
    _speedValue = 0.2;
    _gameSpeed = 1 + _gameLevel * _speedValue;
    _ready = false;

    //INIT SOME FUNCTIONS
    loadLevel();
    //SCHEDULE
    this->schedule(schedule_selector(Palipali::update));
    return true;
}

Palipali::~Palipali() {

}

void Palipali::loadLevel() {

  CCObject* jt = NULL;
  std::string levelsFile = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("palipali.plist");
  _levels = CCArray::createWithContentsOfFileThreadSafe(levelsFile
							.c_str());
  _levels->retain();
  _levelData = (CCDictionary *) _levels->objectAtIndex(0); //TODO
  CCArray * spawns = (CCArray *) _levelData->objectForKey("levels");
  CCARRAY_FOREACH(spawns, jt)
    {
      CCDictionary * data = (CCDictionary *) jt;
      std::map<std::string, const CCString*> enemyProperty;
      enemyProperty.insert(std::pair<std::string, const CCString*>("function", data->valueForKey("function")));
      _mapEvents.insert(std::pair<float, std::map<std::string, const CCString*> >(data->valueForKey("time")->floatValue(), enemyProperty));
    }
}

void	Palipali::update(float dt) {

    //Main loop for spawning events according to the game timeline in Resources/levels.plist
  for (std::map<float, std::map<std::string, const CCString*> >::iterator it = _mapEvents.begin(); it != _mapEvents.end(); ++it)
    {
      if (it->first == _currentFrame) {
	std::map<std::string, fPtr>::iterator result = _mapFPtr.find(it->second["function"]->getCString());
	if (result != _mapFPtr.end())
	  (this->*(result->second))(it->second);
      }
    }
  //Keep in mind at which frame of the game we are
  _currentFrame++;
  std::cout << "Frame : " << _currentFrame << std::endl;
}
 
void Palipali::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
  CCTouch *touch = (CCTouch*)touches->anyObject();
  _lastTouchLocation = convertTouchToNodeSpace(touch);
  if (_ready) {
    if (_gameLevel == 1) {
      CCScene		*_gameScene = targetFall::scene();
      CCDirector::sharedDirector()->replaceScene((CCScene*)CCTransitionCrossFade::create(0.5, _gameScene));
    }
    if (_gameLevel == 2) {
       CCScene		*_gameScene = fallingGift::scene();
       CCDirector::sharedDirector()->replaceScene((CCScene*)CCTransitionCrossFade::create(0.5, _gameScene));
    }
  }
}

void Palipali::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
  CCTouch *touch = (CCTouch*)touches->anyObject();
  CCPoint location = convertTouchToNodeSpace(touch);
  //location.x = _playerColumn;
  //_lastTouchLocation.x = _playerColumn; 
  //  for (int i = 0; i < _playersPool.size(); i++) 
  // {
  //  CCSprite*	sprite = _playersPool[i]->getSprite();
  //  sprite->setPosition(ccpAdd(sprite->getPosition(), ccpSub(location, _lastTouchLocation ) ) );
  //  _lastTouchLocation = location;
  //}
}

void  Palipali::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
}

std::string	Palipali::intToString(int value) {
  std::string	s;
  std::stringstream out;
  out << value;
  s = out.str();
  return s;
}

void	Palipali::addCrystal(std::map<std::string, const CCString*> infos) {
  CCAction*	moveCrystal1 = CCEaseOut::create(CCMoveBy::create(1.0f, ccp(200, 0)), 6);
CCAction*	moveCrystal2 = CCEaseOut::create(CCMoveBy::create(1.0f, ccp(200, 0)), 6);
CCAction*	moveCrystal3 = CCEaseOut::create(CCMoveBy::create(1.0f, ccp(200, 0)), 6);
  if (_gameLevel >= 2)
    _crystal1->runAction(moveCrystal1);
  if (_gameLevel >= 3)
    _crystal2->runAction(moveCrystal2);
  if (_gameLevel >= 4)
    _crystal3->runAction(moveCrystal3);
    
}

void	Palipali::setReady(std::map<std::string, const CCString*> infos) {
  _ready = true;
}

void	Palipali::setGameLevel(int level) {
  _gameLevel = level;
}

void Palipali::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

