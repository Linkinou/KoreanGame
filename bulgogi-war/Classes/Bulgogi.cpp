//
//  bulgogi.cpp
//  bulgogi-war
//
//  Created by 우 유진 on 13. 10. 7..
//
//

#include "Bulgogi.h"
USING_NS_CC;


CCScene* Bulgogi::scene()
{
    CCScene *scene = CCScene::create();
    Bulgogi *layer = Bulgogi::create();
    BackgroundLayer *bg = BackgroundLayer::create();
    scene->addChild(bg);
    scene->addChild(layer);
    return scene;
}

bool Bulgogi::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }    

    _mapFPtr["line"] = &Bulgogi::spawnLine;
    _mapFPtr["enemy"] = &Bulgogi::spawnEnemy;
    _mapFPtr["player"] = &Bulgogi::spawnPlayer;

    _visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    _origin = CCDirector::sharedDirector()->getVisibleOrigin();
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    setTouchEnabled(true);
    _scoreLabel = CCLabelTTF::create("Score : 0", "Helvetica", 12,
				     CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCMenuItemImage *pShoot = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(Bulgogi::menuCloseCallback));
    
    pShoot->setPosition(ccp(_origin.x + _visibleSize.width - pShoot->getContentSize().width/2 , _origin.y + pShoot->getContentSize().height/2));
    CCMenu* pMenu = CCMenu::create(pShoot, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    this->addChild(_scoreLabel, 1);
    //INIT SOME VALUES FOR THE GAME
    _score = 0;
    _currentLevel = 1;
    _touching = false;
    _currentFrame = 0;
    _ennemySpeed = 7;
    _bulletSpeed = 6;
    _playerColumn = _visibleSize.width / 7;
    _enemyColumn = _visibleSize.width + 10;

    //INIT SOME FUNCTIONS
    loadLevel();

    //SCHEDULE
    this->schedule(schedule_selector(Bulgogi::update));
    this->schedule(schedule_selector(Bulgogi::playerShooting), 0.05f);
    this->schedule(schedule_selector(Bulgogi::enemyShooting), 3.0f);
    this->schedule(schedule_selector(Bulgogi::increaseScore), 3.0f);
    return true;
}

Bulgogi::~Bulgogi() {

}

void Bulgogi::loadLevel() {

  CCObject* jt = NULL;
  std::string levelsFile = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("levels.plist");
  _levels = CCArray::createWithContentsOfFileThreadSafe(levelsFile
							.c_str());
  _levels->retain();
  _levelData = (CCDictionary *) _levels->objectAtIndex(_currentLevel - 1);
  CCArray * spawns = (CCArray *) _levelData->objectForKey("spawns");
  CCARRAY_FOREACH(spawns, jt)
    {
      CCDictionary * data = (CCDictionary *) jt;
      std::map<std::string, const CCString*> enemyProperty;
      enemyProperty.insert(std::pair<std::string, const CCString*>("image", data->valueForKey("image")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("pattern", data->valueForKey("pattern")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("yPos", data->valueForKey("yPos")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("xPos", data->valueForKey("xPos")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("motion", data->valueForKey("motion")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("god", data->valueForKey("god")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("lives", data->valueForKey("lives")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("numLine", data->valueForKey("numLine")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("spaceLine", data->valueForKey("spaceLine")));
      enemyProperty.insert(std::pair<std::string, const CCString*>("tag", data->valueForKey("tag")));
      _mapEvents.insert(std::pair<float, std::map<std::string, const CCString*> >(data->valueForKey("time")->floatValue(), enemyProperty));
    }
}

void Bulgogi::updateUnits() {
    
  for (int i = 0; i < _enemiesPool.size(); i++)
    {
      _enemiesPool[i]->update();
      _enemiesPool[i]->collideWith(_playersBulletsPool);
      _enemiesPool[i]->collideWith(_playersPool);
    }
  for (int i = 0; i < _playersPool.size(); i++)
   {
     _playersPool[i]->update();
     _playersPool[i]->collideWith(_bulletsPool);
   }
  for (int i = 0; i < _bulletsPool.size(); i++)
   {
     _bulletsPool[i]->update();
   }
  for (int i = 0; i < _playersBulletsPool.size(); i++)
   {
     _playersBulletsPool[i]->update();
   }
}

void Bulgogi::removeUnits() {

  for (int i = 0; i < _playersPool.size(); i++)
    {
      if (_playersPool[i]->toDelete())
	{
	  this->removeChild(_playersPool[i]->getSprite(), true);
	  _playersPool.erase(_playersPool.begin() + i);
	  if (_playersPool.size() < 1) {
	    CCScene	*gameoverScene = Gameover::scene();
	    CCDirector::sharedDirector()->replaceScene(gameoverScene);
	  }
	}
    }
  for (int i = 0; i < _enemiesPool.size(); i++)
    {
      if (_enemiesPool[i]->toDelete())
	{
	  //this->addChild(_enemiesPool[i]->getExplosion());
	  //_enemiesPool[i]->_explosion->release();
	  this->removeChild(_enemiesPool[i]->getSprite(), true);
	  _enemiesPool.erase(_enemiesPool.begin() + i);
	}
    }
  for (int i = 0; i < _bulletsPool.size(); i++)
    {
      if (_bulletsPool[i]->toDelete())
	{
	  this->removeChild(_bulletsPool[i]->getSprite(), true);
	  _bulletsPool.erase(_bulletsPool.begin() + i);
	}
    }
  for (int i = 0; i < _playersBulletsPool.size(); i++)
    {
      if (_playersBulletsPool[i]->toDelete())
	{
	  this->removeChild(_playersBulletsPool[i]->getSprite(), true);
	  _playersBulletsPool.erase(_playersBulletsPool.begin() + i);
	}
    }
}

void		Bulgogi::playerShooting() {

  for (int i = 0; i < _playersPool.size(); i++)
    {
      if (_touching)
	spawnBullet(_playersPool[i]);
    }
}

void		Bulgogi::enemyShooting() {

  for (int i = 0; i < _enemiesPool.size(); i++)
    {
      if (_enemiesPool[i]->getTag() == 1) // If enemy
	spawnBullet(_enemiesPool[i]);
    }
}

void	Bulgogi::update(float dt) {
  std::cout << _score << std::endl;
  //Delete all the units set as deleted
  removeUnits();
  //Main loop for spawning events according to the game timeline in Resources/levels.plist
  for (std::map<float, std::map<std::string, const CCString*> >::iterator it = _mapEvents.begin(); it != _mapEvents.end(); ++it)
    {
      if (it->first == _currentFrame) {
	std::map<std::string, fPtr>::iterator result = _mapFPtr.find(it->second["pattern"]->getCString());
	if (result != _mapFPtr.end())
	  (this->*(result->second))(it->second);
      }
    }

  //Updates functions
  updateUnits();

  //Keep in mind at which frame of the game we are
  _currentFrame++;
}
 
void Bulgogi::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
  CCTouch *touch = (CCTouch*)touches->anyObject();
  _lastTouchLocation = convertTouchToNodeSpace(touch);
  _touching = true;
}

void Bulgogi::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
  CCTouch *touch = (CCTouch*)touches->anyObject();
  CCPoint location = convertTouchToNodeSpace(touch);
  location.x = _playerColumn;
  _lastTouchLocation.x = _playerColumn; 
  for (int i = 0; i < _playersPool.size(); i++) 
    {
      CCSprite*	sprite = _playersPool[i]->getSprite();
      sprite->setPosition(ccpAdd(sprite->getPosition(), ccpSub(location, _lastTouchLocation ) ) );
      _lastTouchLocation = location;
    }
}

void  Bulgogi::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
  _touching = false;
}

void Bulgogi::spawnBullet(Unit* unit)
{
  CCSprite*	sprite = unit->getSprite();
  std::string	*imagePath;


  if (unit->getTag() == 0)
    imagePath = new std::string("bullet.png");
  else
    imagePath = new std::string("purplebullet.png");

  Unit *bullet = new Unit(imagePath,
			  1,
			  sprite->getPosition().x,
			  sprite->getPosition().y,
			  false,
			  2,
			  unit->getWeapon(),
			  _playersPool);
  if (unit->getTag() == 1)
    _bulletsPool.push_back(bullet);
  else
    _playersBulletsPool.push_back(bullet);
  this->addChild(bullet->getSprite(), 1, bullet->getTag());
}

void Bulgogi::spawnLine(std::map<std::string, const CCString*> enemyInfo) {
  int max = enemyInfo["numLine"]->intValue();
  int space = enemyInfo["spaceLine"]->intValue();
  std::string	*s_yPos = new std::string(enemyInfo["yPos"]->getCString());
  std::string	*s_xPos = new std::string(enemyInfo["xPos"]->getCString());
  int		xPos = 0;
  int		yPos = 0;
  
  if (s_xPos->compare("WIDTH") == 0)
    xPos = _screenSize.width;
  else
    xPos = enemyInfo["xPos"]->intValue();
  if (s_yPos->compare("HEIGHT") == 0)
    yPos = _screenSize.height;
  else
    yPos = enemyInfo["yPos"]->intValue();

  for (int i = 0; i < max; i++) {
    xPos += space;
    enemyInfo["xPos"] = ccs(intToString(xPos).c_str());
    spawnEnemy(enemyInfo);
  }
}

void Bulgogi::spawnEnemy(std::map<std::string, const CCString*> enemyInfo) {

  std::string	*imagePath = new std::string(enemyInfo["image"]->getCString());
  std::string	*motion = new std::string(enemyInfo["motion"]->getCString());
  std::string	*s_yPos = new std::string(enemyInfo["yPos"]->getCString());
  std::string	*s_xPos = new std::string(enemyInfo["xPos"]->getCString());
  int		xPos = 0;
  int		yPos = 0;

  if (s_xPos->compare("WIDTH") == 0)
    xPos = _screenSize.width;
  else
    xPos = enemyInfo["xPos"]->intValue();
  if (s_yPos->compare("HEIGHT") == 0)
    yPos = _screenSize.height;
  else
    yPos = enemyInfo["yPos"]->intValue();

  Unit *enemy = new Unit(imagePath,
			 enemyInfo["lives"]->intValue(),
			 xPos,
			 yPos,
			 enemyInfo["god"]->boolValue(),
			 enemyInfo["tag"]->intValue(),
			 motion,
			 _playersPool);
  _enemiesPool.push_back(enemy);
  this->addChild(enemy->getSprite(), 1, enemy->getTag());
}

void Bulgogi::spawnPlayer(std::map<std::string, const CCString*> playerInfo) {
  
  std::string	*imagePath = new std::string(playerInfo["image"]->getCString());
  std::string	*motion = new std::string(playerInfo["motion"]->getCString());
  Unit *player = new Unit(imagePath,
			  playerInfo["lives"]->intValue(),
			  _playerColumn,
			  _visibleSize.height / 2 + _origin.y,
			  playerInfo["god"]->boolValue(),
			  0,
			  motion,
			  _playersPool);
  _playersPool.push_back(player);
  this->addChild(player->getSprite(), 5, player->getTag());
}

std::string	Bulgogi::intToString(int value) {
  std::string	s;
  std::stringstream out;
  out << value;
  s = out.str();
  return s;
}

void		Bulgogi::increaseScore() {
  _score += 50;
}


void Bulgogi::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

