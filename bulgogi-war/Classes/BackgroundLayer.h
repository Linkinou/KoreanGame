#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class BackgroundLayer : public cocos2d::CCLayer
{
private:
  CCSize	_screenSize;
  bool		_running;
  CCSprite	*_sky;
  CCSprite	*_sky2;
  CCSprite	*_aste1;
  CCSprite	*_aste2;
  float		_skySpeed;
  float		_asteSpeed;
  int		_asteNum;

public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  ~BackgroundLayer(void);
  void		createLayer();

  CREATE_FUNC(BackgroundLayer);
  void	update(float dt);
  void ccTouchesBegan(CCSet* touches, CCEvent* event);
  void ccTouchesMoved(CCSet* touches, CCEvent* event);
  void ccTouchesEnded(CCSet* touches, CCEvent* event);
};

#endif
