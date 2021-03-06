#include		"Unit.h"

Unit::Unit(std::string* image, int lives, int posX, int posY, bool god, int tag, std::string *motion, std::vector<Unit*> playersPool) {

  _sprite = CCSprite::create(image->c_str());
  _sprite->setPosition(ccp(posX, posY));
  _sprite->setTag(tag);
  _god = god;
  _lives = lives;
  _toDelete = false;
  _tag = tag;
  _playersPool = playersPool;
  if (tag == 0) //Player
    _weapon = new std::string("highLeftToRight");
  else if (tag == 1) //Enemy
    _weapon = new std::string("focusPlayer");
  else
    _weapon = new std::string("none");
  _visibleSize = CCDirector::sharedDirector()->getVisibleSize();
  _origin = CCDirector::sharedDirector()->getVisibleOrigin();
  _screenSize = CCDirector::sharedDirector()->getWinSize();
  _mapFPtr["leftToRight"] = &Unit::actionLeftToRight;
  _mapFPtr["rightToLeft"] = &Unit::actionRightToLeft;
  _mapFPtr["highLeftToRight"] = &Unit::actionHighLeftToRight;
  _mapFPtr["highRightToLeft"] = &Unit::actionHighRightToLeft;
  _mapFPtr["leftToRightRotate"] = &Unit::actionLeftToRightRotate;
  _mapFPtr["simpleFading"] = &Unit::actionSimpleFading;
  _mapFPtr["bezierUpDown"] = &Unit::actionBezierUpDown;
  _mapFPtr["spiralWeapon"] = &Unit::actionSpiralWeapon;
  _mapFPtr["focusPlayer"] = &Unit::actionFocusPlayer;
  _mapFPtr["touchBlink"] = &Unit::actionTouchBlink;
  _mapFPtr["rotateAste"] = &Unit::actionRotateAste;
  _mapFPtr["bounce"] = &Unit::actionBounce;
  _mapFPtr["elasticTop"] = &Unit::actionElasticTop;
  _mapFPtr["elasticBot"] = &Unit::actionElasticBot;
  initCCActions();
  runActions(motion);
}

Unit::~Unit() {

}

void			Unit::initCCActions() {

  _leftToRight = CCMoveBy::create(15.0f, ccp(_visibleSize.width * 2, 0));
  _leftToRight->retain();

  _rightToLeft = CCMoveBy::create(15.0f, ccp(-_visibleSize.width * 2, 0));
  _rightToLeft->retain();

  _highLeftToRight = CCMoveBy::create(2.0f, ccp(_visibleSize.width * 2, 0));
  _leftToRight->retain();

  _highRightToLeft = CCMoveBy::create(7.0f, ccp(-_visibleSize.width * 2, 0));
  _rightToLeft->retain();

  _rotate = CCRotateBy::create(2.0f, 180);
  _rotate->retain();

  _fadein = CCEaseIn::create(CCFadeIn::create(1.0f),2);
  _fadein->retain();

  _fadeout = CCEaseInOut::create(CCFadeOut::create(1.0f),2);
  _fadeout->retain();
  
  _blink = CCBlink::create(1.0f, 5);
  _blink->retain();

  _scaleup = CCScaleTo::create(1.0f,3.0f);
  _scaleup->retain();

  _bezierUpDown.controlPoint_1 = ccp(-50,
  				      -200);
  _bezierUpDown.controlPoint_2 = ccp(-100,
  				      200);
  _bezierUpDown.endPosition = ccp(-150,
				  0);

   _explosion = CCParticleSun::node();
  //std::cout << "OOPS" << std::endl;
  //_explosion->initWithTotalParticles(1);
  //std::cout << "OOPS" << std::endl;
  //_explosion->setAutoRemoveOnFinish(true);
  //_explosion->setStartSize(15.0f);
  //_explosion->setSpeed(15.0f);
  //_explosion->setAnchorPoint(ccp(0.5f,0.5f));
  //_explosion->setPosition(0, 0);
  //_explosion->setDuration(2.5f);
  //_explosion->retain();
}

void			Unit::update() {
  if (_sprite->getPositionX() < (0 - (_screenSize.width/2)) || _sprite->getPositionX() > (_screenSize.width * 2))
    _toDelete = true;
  if (_sprite->getPositionY() < 0 || _sprite->getPositionY() > _screenSize.height)
    _toDelete = true;
  _explosion->setPosition(_sprite->getPosition());
}

void			Unit::collideWith(std::vector<Unit*> objects) {
  
  CCRect		unitRect = CCRectMake( _sprite->getPosition().x - (_sprite->getContentSize().width/2)
					       , _sprite->getPosition().y - (_sprite->getContentSize().height/2)
					       , _sprite->getContentSize().width
					       , _sprite->getContentSize().height);
  for (int i = 0; i < objects.size(); i++)
    {
      CCRect		objectRect = CCRectMake( objects[i]->getSprite()->getPosition().x - (objects[i]->getSprite()->getContentSize().width/2)
						 , objects[i]->getSprite()->getPosition().y - (objects[i]->getSprite()->getContentSize().height/2)
						 , objects[i]->getSprite()->getContentSize().width
						 , objects[i]->getSprite()->getContentSize().height);
      if (unitRect.intersectsRect(objectRect))
	{
	  if (!this->_god)
	    this->_lives--;
	  if (!objects[i]->isGod())
	  objects[i]->setLives(objects[i]->getLives() - 1);
	  if (this->_lives <= 0)
	    this->_toDelete = true;
	  else
	    this->actionTouchBlink();
	  if (objects[i]->getLives() <= 0)
	    objects[i]->setDelete(true);
	  else
	    objects[i]->actionTouchBlink();
	}
    }
}

void			Unit::runActions(std::string *motion) {

  for (std::map<std::string, fPtr>::iterator it = _mapFPtr.begin(); it != _mapFPtr.end(); ++it)
    {
      if (it->first.compare(motion->c_str()) == 0) {
	if (it != _mapFPtr.end())
	  (this->*(it->second))();
      }
    }
}

void			Unit::actionLeftToRight() {
    _sprite->runAction((CCAction*)_leftToRight->copy()->autorelease());
}

void			Unit::actionRightToLeft() {
    _sprite->runAction((CCAction*)_rightToLeft->copy()->autorelease());
}

void			Unit::actionHighLeftToRight() {
    _sprite->runAction((CCAction*)_highLeftToRight->copy()->autorelease());
}

void			Unit::actionHighRightToLeft() {
    _sprite->runAction((CCAction*)_highRightToLeft->copy()->autorelease());
}

void			Unit::actionSimpleFading() {
  CCAction		*sequence = CCSequence::create(
						       CCDelayTime::create(1.0f),
  						       CCEaseInOut::create((CCActionInterval*)_fadeout, 2),
						       CCDelayTime::create(1.0f),
  						       CCEaseInOut::create((CCActionInterval*)_fadein, 2),
  							       NULL);
  _sprite->runAction((CCAction*)_rightToLeft->copy()->autorelease());
  _sprite->runAction((CCFiniteTimeAction*)sequence);
}

void			Unit::actionLeftToRightRotate() {
  _sprite->runAction((CCAction*)_leftToRight->copy()->autorelease());
  _sprite->runAction((CCAction*)_rotate->copy()->autorelease());
}

void			Unit::actionTouchBlink() {
  if (_tag == 0)
    _sprite->runAction((CCAction*)_blink->copy()->autorelease());
}

void			Unit::actionBezierUpDown() {
  CCActionInterval*	bezierTo1 = CCBezierBy::create(2.0f, _bezierUpDown);
  CCRepeatForever*	repeatMotion = CCRepeatForever::create(bezierTo1);
  _sprite->runAction(repeatMotion);
}

void			Unit::actionSpiralWeapon() {
}

void			Unit::actionFocusPlayer() {
  CCPoint		finalDest;
  CCPoint		subValue;
  CCPoint		playerPos;
  float			length;
  float			bulletSpeed = 1.5;
  float			duration;

  for (int i = 0; i < _playersPool.size(); i++)
    {
      playerPos = _playersPool[i]->getSprite()->getPosition();
    }
  subValue = ccpSub(_sprite->getPosition(), playerPos);
  finalDest = ccpNormalize(subValue);
  length = ccpDistance(playerPos, _sprite->getPosition());
  duration = length/bulletSpeed;
  finalDest = ccpMult(finalDest, -length - (length*300));
  _sprite->runAction(CCMoveBy::create(duration, finalDest));
}

void			Unit::actionRotateAste() {

  CCRepeatForever*	repeatMotion = CCRepeatForever::create((CCActionInterval*) _rotate);
  _sprite->runAction((CCAction*)_rightToLeft->copy()->autorelease());
  _sprite->runAction(repeatMotion);
}

void			Unit::actionElasticTop() {
  CCActionInterval*	move = CCMoveTo::create(10.0f, ccp(-100, -100));	
  CCEaseElasticOut*	elastic = CCEaseElasticOut::create((CCActionInterval*) move, 10.0f);
  _sprite->runAction(elastic);
}

void			Unit::actionElasticBot() {
  CCActionInterval*	move = CCMoveTo::create(10.0f, ccp(-100, _screenSize.height + 100));	
  CCEaseElasticOut*	elastic = CCEaseElasticOut::create((CCActionInterval*) move, 10.0f);
  _sprite->runAction(elastic);
}

void			Unit::actionBounce() {

  CCActionInterval* move = CCMoveBy::create(3, ccp(0 - 530, 0));
  CCActionInterval* move_back = move->reverse();
  
  CCActionInterval* move_ease = CCEaseBounceInOut::create((CCActionInterval*)(move->copy()->autorelease()) );
  CCActionInterval* move_ease_back = move_ease->reverse();

  CCDelayTime *delay = CCDelayTime::create(0.25f);
  
  CCFiniteTimeAction* seq2 = CCSequence::create(move_ease, CCCA(delay), move_ease_back, CCCA(delay), NULL);
  
  _sprite->runAction( CCRepeatForever::create((CCActionInterval*)seq2));
}

//GETTERS
CCSprite*		Unit::getSprite() {
  return _sprite;
}

CCParticleSun*		Unit::getExplosion() {
  return _explosion;
}

bool			Unit::isGod() {
  return _god;
}

bool			Unit::toDelete() {
  return _toDelete;
}

int			Unit::getTag() {
  return _tag;
}

int			Unit::getLives() {
  return _lives;
}

std::string*		Unit::getWeapon() {
  return _weapon;
}

//SETTERS

void			Unit::setDelete(bool value) {
  _toDelete = value;
}

void			Unit::setLives(int value) {
  _lives = value;
}
