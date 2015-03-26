#ifndef		__GAMEOVER_H__
#define		__GAMEOVER_H__

#include	"cocos2d.h"
#include	"Bulgogi.h"
#include	"Menu.h"
USING_NS_CC;

class		Gameover : public cocos2d::CCLayer
{
 public:
  virtual bool init();
  static cocos2d::CCScene* scene();

  virtual ~Gameover();
  void ccTouchesBegan(CCSet* touches, CCEvent* event);
  void ccTouchesMoved(CCSet* touches, CCEvent* event);
  void ccTouchesEnded(CCSet* touches, CCEvent* event);

  CREATE_FUNC(Gameover);

  CCSize	_screenSize;
  CCSprite	*_background;
  CCSprite	*_gameoverText;
  CCSprite	*_tryagainText;
  CCSprite	*_bap;
  int		_state;
};

#endif
