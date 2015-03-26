#include "targetFall.h"
#include "Palipali.h"
#include	"BackgroundLayer.h"
USING_NS_CC;


CCScene* targetFall::scene()
{
    CCScene *scene = CCScene::create();
    targetFall *layer = targetFall::create();
    scene->addChild(layer);
    return scene;
}

bool targetFall::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }    

    _mapFPtr["addTarget"] = &targetFall::addTarget;
    _mapFPtr["gameEnd"] = &targetFall::gameEnd;

    _visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    _origin = CCDirector::sharedDirector()->getVisibleOrigin();
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    setTouchEnabled(true);
    CCSprite*	background = CCSprite::create("targetfall_bg.png");
    background->setAnchorPoint(ccp(0,0));
    this->addChild(background);

    //INIT SOME VALUES FOR THE GAME
    _currentFrame = 0;
    _currentScore = 0;
    _winningScore = 0;

    //INIT SOME FUNCTIONS
    loadLevel();

    //SCHEDULE
    this->schedule(schedule_selector(targetFall::update));
    return true;
}

targetFall::~targetFall() {

}

void targetFall::loadLevel() {

  CCObject* jt = NULL;
  std::string levelsFile = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("targetFall.plist");
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

void	targetFall::update(float dt) {

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
}

int		targetFall::myRand(const int min_limit, const int max_limit)
{ 
  return rand() % (max_limit - min_limit + 1) + min_limit;
}
void targetFall::gameEnd(std::map<std::string, const CCString*> infos) {
  CCScene		*_gameScene = CCScene::create();
  Palipali		*palipali = Palipali::create();
  BackgroundLayer*	bg = BackgroundLayer::create();
  if (_currentScore == _winningScore)
    palipali->setGameLevel(2);
  else
    palipali->setGameLevel(1);
  _gameScene->addChild(palipali, 1, 4242);
  _gameScene->addChild(bg);
  CCDirector::sharedDirector()->replaceScene((CCScene*)CCTransitionSlideInR::create(0.5,_gameScene));
}

void targetFall::addTarget(std::map<std::string, const CCString*> infos) {
  std::cout << "Adding target" << std::endl;
  CCSprite*	target = CCSprite::create("target_normal.png");
  target->setPosition(ccp(myRand(0.0f, _screenSize.width), _screenSize.height));
  CCAction	*topBot = CCMoveTo::create(5.0f, ccp(target->getPositionX(), -200));
  target->runAction(topBot);
  _items.push_back(target);
  this->addChild(target);
  _winningScore++;
}
 
void targetFall::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
  CCTouch *touch = (CCTouch*)touches->anyObject();
  CCPoint location = convertTouchToNodeSpace(touch);

  for (int i = 0; i < _items.size(); i++)
    {
      CCRect		bbox = CCRectMake( _items[i]->getPosition().x - (_items[i]->getContentSize().width/2)
						 , _items[i]->getPosition().y - (_items[i]->getContentSize().height/2)
						 , _items[i]->getContentSize().width
						 , _items[i]->getContentSize().height);
      if (CCRect::CCRectContainsPoint(bbox, location))
	{
	  _items[i]->setTexture(CCTextureCache::sharedTextureCache()->addImage("target_touched.png"));
	  _currentScore++;
	}
    }
}

void targetFall::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
}

void  targetFall::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
}

std::string	targetFall::intToString(int value) {
  std::string	s;
  std::stringstream out;
  out << value;
  s = out.str();
  return s;
}

void targetFall::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

