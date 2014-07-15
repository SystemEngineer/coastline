//
//  PortPopupLayer.cpp
//  coastline
//
//  Created by 荣徽 贺 on 14-6-27.
//
//

#include "PortPopupLayer.h"

USING_NS_CC;

PortPopupLayer::PortPopupLayer()
{

}
PortPopupLayer::~PortPopupLayer()
{
    
}

bool PortPopupLayer::init()
{
    Color4B layer_color = {100,0,0,25};

    auto winSize = Director::getInstance()->getWinSize();
    if(!LayerColor::initWithColor(layer_color,winSize.width,winSize.height))
    {
        return false;
    }

    return true;
}

bool PortPopupLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    return true;
}

void PortPopupLayer::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    this->destoryBgSprite();
}

//Create background image sprite
void PortPopupLayer::createBgSprite(const char* bg_image,Point position)
{
    if (!_m_BgSprite){
        _m_BgSprite = Sprite::create(bg_image);
        _m_BgSprite->setPosition(position);
        this->addChild(_m_BgSprite, 100);
        //Create touch event handler and swallow the event of the hello layer
        _m_pListener = EventListenerTouchOneByOne::create();
        _m_pListener->setSwallowTouches(true);
        _m_pListener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};
        _m_pListener->onTouchEnded = [=](Touch *touch, Event *unused_event){this->destoryBgSprite();};
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_m_pListener, this);

    }
}

void PortPopupLayer::destoryBgSprite()
{
    log("get into touch ended event");
    if(_m_BgSprite != NULL){
        this->removeChild(_m_BgSprite);
        this->_eventDispatcher->removeEventListener(_m_pListener);
        _m_BgSprite = NULL;
    }
}

CCLabelTTF* PortPopupLayer::createTitle(const char* title_name, int title_font)
{
    CCLabelTTF *lbl_title =CCLabelTTF::create(title_name,"", title_font);
}



