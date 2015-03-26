#ifndef				__FALLING_GIFT_H__
#define				__FALLING_GIFT_h__

#include			<map>
#include			<vector>
#include			<sstream>
#include			"cocos2d.h"

USING_NS_CC;

#define CCStringMake(str) CCString::create(str)
#define ccs CCStringMake

class fallingGift : public cocos2d::CCLayer
{
 public:
  typedef void (fallingGift::*fPtr) (std::map<std::string, const CCString*>);
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  
  //METHODS
  virtual ~fallingGift();
  void update(float dt);
  void loadLevel();
  void	animationDone();
  void ccTouchesBegan(CCSet* touches, CCEvent* event);
  void ccTouchesMoved(CCSet* touches, CCEvent* event);
  void ccTouchesEnded(CCSet* touches, CCEvent* event);
  void addGift(std::map<std::string, const CCString*>);
  std::string intToString(int);
  void menuCloseCallback(CCObject* pSender);
  int	myRand(const int, const int);
  void	collideWith(std::vector<CCSprite*>);
  CREATE_FUNC(fallingGift);
  
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
  int	_playerLine;
  CCSprite*	_player;
  int	_playerMove;
  bool	_touched;
  int	_winCondition;
  int	_currentScore;
  CCNode*	_gameBatchNode;
  CCAction*	_santaWalk;
};

#endif // __PALIPALI_SCENE_H__




