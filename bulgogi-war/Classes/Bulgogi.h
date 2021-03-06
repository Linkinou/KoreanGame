//
//  bulgogi.h
//  bulgogi-war
//
//  Created by 우 유진 on 13. 10. 7..
//
//

#ifndef __bulgogi_war__bulgogi__
#define __bulgogi_war__bulgogi__

#include "cocos2d.h"
#include "Unit.h"
#include "BackgroundLayer.h"
#include "Gameover.h"
#include <map>
#include <vector>
#include <sstream>
USING_NS_CC;

#define CCStringMake(str) CCString::create(str)
#define ccs CCStringMake

class Bulgogi : public cocos2d::CCLayer
{
 public:
  typedef void (Bulgogi::*fPtr) (std::map<std::string, const CCString*>);
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  
  //METHODS
  virtual ~Bulgogi();
  void scrollBackground();
  void spawnLine(std::map<std::string, const CCString*>);
  void spawnPlayer(std::map<std::string, const CCString*>);
  void spawnEnemy(std::map<std::string, const CCString*>);
  void spawnBullet(Unit* unit);
  void updateUnits();
  void	removeUnits();
  void update(float dt);
  void loadLevel();
  void timer();
  void ccTouchesBegan(CCSet* touches, CCEvent* event);
  void ccTouchesMoved(CCSet* touches, CCEvent* event);
  void ccTouchesEnded(CCSet* touches, CCEvent* event);
  void spriteMoveFinished(CCNode* sender);
  void	playerShooting();
  void	enemyShooting();
  void	increaseScore();
  std::string intToString(int);
  void menuCloseCallback(CCObject* pSender);
  
  CREATE_FUNC(Bulgogi);
  
 private:
  std::map<std::string, fPtr> _mapFPtr;
  std::map< float, std::map<std::string, const CCString*> >  _mapEvents;
  CCSprite* _bg1;
  CCSprite* _bg2;
  CCLabelTTF* _scoreLabel;
  CCSize _visibleSize;
  CCPoint _origin;
  CCSize	_screenSize;
  std::vector<Unit*> _enemiesPool;
  std::vector<Unit*> _bulletsPool;
  std::vector<Unit*> _playersBulletsPool;
  std::vector<Unit*> _playersPool;
  CCArray *_levels;
  CCDictionary* _levelData;
  CCPoint	_lastTouchLocation;
  bool		_touching;
  int _currentFrame;
  int _playerColumn;
  int _enemyColumn;
  int _ennemySpeed;
  int _bulletSpeed;
  int _backgroundSpeed;
  int _currentLevel;
  int _score;
};

#endif // __BULGOGI_SCENE_H__




