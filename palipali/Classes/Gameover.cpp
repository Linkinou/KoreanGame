#include "Gameover.h"
#include "BackgroundLayer.h"
USING_NS_CC;


CCScene* Gameover::scene()
{
    CCScene *scene = CCScene::create();
    Gameover *layer = Gameover::create();
    scene->addChild(layer);
    return scene;
}

bool Gameover::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    _screenSize = CCDirector::sharedDirector()->getWinSize();    
    _state = 0;
    _background = CCSprite::create("gameover_bg.jpg");
    _background->setAnchorPoint(ccp(0,0));
    _gameoverText = CCSprite::create("gameover_text.png");
    _gameoverText->setPosition(ccp(_screenSize.width * 0.7, _screenSize.height + 100));
    _tryagainText = CCSprite::create("tryagain.png");
    _bap = CCSprite::create("character.png");

    //GameOver Text
    CCActionInterval* move = CCMoveTo::create(2, ccp(_screenSize.width * 0.7, _screenSize.height - 100));
    CCActionInterval* move_ease_out = CCEaseBounceOut::create((CCActionInterval*)(move->copy()->autorelease()) );
    CCDelayTime *delay = CCDelayTime::create(0.10f);
    CCFiniteTimeAction* seq3 = CCSequence::create(move_ease_out, CCCA(delay), NULL);
    CCActionInterval* scale = CCScaleTo::create(1.0f, 1.2f);
    CCActionInterval* scale_rev = CCScaleTo::create(1.0f, 1.0f);
    CCFiniteTimeAction* seqBap = CCSequence::create(scale, CCCA(delay), scale_rev, NULL);
    CCActionInterval* waves = CCWaves3D::create(13,50,ccg(10,5),5);
    _tryagainText->runAction(CCHide::create());
    _gameoverText->runAction((CCActionInterval*)seq3);
    _tryagainText->setPosition(ccp(_screenSize.width / 2, _screenSize.height / 1.9));
    _tryagainText->runAction(CCRepeatForever::create(waves));
    _bap->setPosition(ccp(_screenSize.width * 0.8, _screenSize.height / 5));
    _bap->runAction(CCRepeatForever::create((CCActionInterval*)seqBap));
    setTouchEnabled(true);
    this->addChild(_background, 0);
    this->addChild(_gameoverText, 1);
    this->addChild(_tryagainText, 1);
    this->addChild(_bap, 1);

    return true;
}

Gameover::~Gameover() {

}

void Gameover::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
  CCScene	*menuScene = Menu::scene();
  if (_state == 0) {
    _tryagainText->runAction(CCShow::create());
    _state++;
  }
  else if (_state == 1) {
    CCDirector::sharedDirector()->replaceScene(menuScene);
  }
}

void Gameover::ccTouchesMoved(CCSet* touches, CCEvent* event)
{

}

void  Gameover::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

}
