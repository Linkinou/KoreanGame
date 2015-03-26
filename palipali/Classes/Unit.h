#ifndef				__UNIT_H__
#define				__UNIT_H__

#define CCCA(x)   (x->copy()->autorelease())


#include			"cocos2d.h"
USING_NS_CC;

enum				unitType {
  PLAYER,
  ENEMY,
  BULLET,
  BULLETENEMY,
  BOSS,
  ASTE,
  OTHER
};

class				Unit {

 public:
  typedef void (Unit::*fPtr) ();
  Unit(std::string*, int, int, int, bool, int, std::string*, std::vector<Unit*>);
  virtual			~Unit();

  CCSprite			*getSprite();
  bool				isGod();
  int				getLives();
  bool				toDelete();
  int				getTag();
  CCParticleSun			*getExplosion();
  std::string*			getWeapon();
  void				setDelete(bool);
  void				setLives(int);
  void				update();
  void				collideWith(std::vector<Unit*>);
  void				initCCActions();
  void				runActions(std::string*);
  void				actionLeftToRight();
  void				actionRightToLeft();
  void				actionHighLeftToRight();
  void				actionHighRightToLeft();
  void				actionLeftToRightRotate();
  void				actionSimpleFading();
  void				actionBezierUpDown();
  void				actionSpiralWeapon();
  void				actionFocusPlayer();
  void				actionTouchBlink();
  void				actionRotateAste();
  void				actionBounce();
  void				actionElasticTop();
  void				actionElasticBot();

  CCAction			*_leftToRight;
  CCAction			*_rightToLeft;
  CCAction			*_highLeftToRight;
  CCAction			*_highRightToLeft;
  CCAction			*_rotate;
  CCAction			*_fadein;
  CCAction			*_fadeout;
  CCAction			*_blink;
  CCAction			*_scaleup;
  ccBezierConfig		_bezierUpDown;
  CCParticleSun			*_explosion;

 private:
  std::map<std::string, fPtr>	_mapFPtr;
  std::vector<Unit*>		_playersPool;
  CCSprite			*_sprite;
  std::string			*_weapon;
  bool				_god;
  int				_lives;
  bool				_toDelete;
  int				_tag;
  CCSize			_visibleSize;
  CCPoint			_origin;
  CCSize			_screenSize;
};

#endif
