#ifndef __PALIPALI_H__
#define __PALIPALI_h__

#include			<map>
#include			<vector>
#include			<sstream>
#include			"cocos2d.h"


USING_NS_CC;

#define CCStringMake(str) CCString::create(str)
#define ccs CCStringMake

class Palipali : public cocos2d::CCLayer
{
 public:
  typedef void (Palipali::*fPtr) (std::map<std::string, const CCString*>);
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  
  //METHODS
  virtual ~Palipali();
  void update(float dt);
  void ccTouchesBegan(CCSet* touches, CCEvent* event);
  void ccTouchesMoved(CCSet* touches, CCEvent* event);
  void ccTouchesEnded(CCSet* touches, CCEvent* event);
  std::string intToString(int);
  void menuCloseCallback(CCObject* pSender);
  void	addCrystal(std::map<std::string, const CCString*> infos);
  void	setReady(std::map<std::string, const CCString*> infos);
  void loadLevel();
  void	setGameLevel(int);
  CREATE_FUNC(Palipali);
  
 private:
  std::map<std::string, fPtr> _mapFPtr;
  std::map< float, std::map<std::string, const CCString*> >  _mapEvents;
  CCSize	_visibleSize;
  CCPoint	_origin;
  CCSize	_screenSize;
  CCArray*	_levels;
  CCDictionary* _levelData;
  CCPoint	_lastTouchLocation;
  int		_currentFrame;
  float		_speedValue;
  float		_gameSpeed;
  int		_gameLevel;
  CCLabelTTF*	_levelLabel;
  CCSprite*	_crystal1;
  CCSprite*	_crystal2;
  CCSprite*	_crystal3;
  bool		_ready;
};

#endif // __PALIPALI_SCENE_H__




