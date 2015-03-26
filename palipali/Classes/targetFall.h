#ifndef				__TARGETFALL_H__
#define				__TARGETFALL_h__

#include			<map>
#include			<vector>
#include			<sstream>
#include			"cocos2d.h"

USING_NS_CC;

#define CCStringMake(str) CCString::create(str)
#define ccs CCStringMake

class targetFall : public cocos2d::CCLayer
{
 public:
  typedef void (targetFall::*fPtr) (std::map<std::string, const CCString*>);
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  
  //METHODS
  virtual ~targetFall();
  void update(float dt);
  void loadLevel();
  void ccTouchesBegan(CCSet* touches, CCEvent* event);
  void ccTouchesMoved(CCSet* touches, CCEvent* event);
  void ccTouchesEnded(CCSet* touches, CCEvent* event);
  void addTarget(std::map<std::string, const CCString*>);
  void gameEnd(std::map<std::string, const CCString*>);
  std::string intToString(int);
  void menuCloseCallback(CCObject* pSender);
  int	myRand(const int, const int);
  
  CREATE_FUNC(targetFall);
  
 private:
  std::map<std::string, fPtr> _mapFPtr;
  std::map< float, std::map<std::string, const CCString*> >  _mapEvents;
  CCSize _visibleSize;
  CCPoint _origin;
  CCSize	_screenSize;
  CCArray *_levels;
  CCDictionary* _levelData;
  CCPoint	_lastTouchLocation;
  int _currentFrame;
  std::vector<CCSprite*> _items;
  int	_currentScore;
  int	_winningScore;
};

#endif // __PALIPALI_SCENE_H__




