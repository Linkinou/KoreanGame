#ifndef		__BAP_WAR_H__
#define		__BAP_WAR_H__

#include	"cocos2d.h"
#include	"Palipali.h"

USING_NS_CC;

class		Menu : public cocos2d::CCLayer
{
 public:
  virtual bool init();
  static cocos2d::CCScene* scene();

  virtual ~Menu();
  void ccTouchesBegan(CCSet* touches, CCEvent* event);
  void ccTouchesMoved(CCSet* touches, CCEvent* event);
  void ccTouchesEnded(CCSet* touches, CCEvent* event);

  CREATE_FUNC(Menu);

  CCSprite	*_screenTitle;
  CCSize	_screenSize;
};

#endif
