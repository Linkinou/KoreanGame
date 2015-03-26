#ifndef __BULGOGI_H__
#define __BULGOGI_H__

#include <vector>
#include "cocos2d.h"
#include "Ennemy.h"

USING_NS_CC;

class Bulgogi : public cocos2d::CCLayer
{
 private:
  CCSprite* _bg1;
  CCSprite* _bg2;
  CCSprite* _player;
  CCSize _visibleSize;
  CCPoint _origin;
  int _playerColumn;
  int ennemyNb;
  std::vector<Ennemy*> ennemies;


public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    //METHODS
    void scrollBackground();
    void update();
    void ccTouchesBegan(CCSet* touches, CCEvent* event);
    void ccTouchesMoved(CCSet* touches, CCEvent* event);
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    CCPoint getPositionFromTouches(CCSet* _touches, CCEvent* event);

    // implement the "static node()" method manually
    CREATE_FUNC(Bulgogi);
};

#endif // _BULGOGI_SCENE_H__
