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

    _m_pPortConfHelper = new PortConfigHelper();
    _m_pPortConfHelper->Init("Port.xml");
    log("Port name is %s, Port image is %s, Port Intro is %s",_m_pPortConfHelper->GetPortNameByCoord("9:6")
        ,_m_pPortConfHelper->GetPortImgStrByCoord("9:6"),_m_pPortConfHelper->GetPortIntroByCoord("9:6"));

    
    return true;
}
/*
bool PortPopupLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    return true;
}

void PortPopupLayer::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    this->destoryBgSprite();
}
*/
//Create background image sprite
void PortPopupLayer::createBgSprite(const char* csCoordString,Point position)
{
    char* port_image = NULL;
    char* port_name = NULL;
    char* port_intro = NULL;
    port_name = (char *)_m_pPortConfHelper->GetPortNameByCoord(csCoordString);
    port_image = (char *)_m_pPortConfHelper->GetPortImgStrByCoord(csCoordString);
    port_intro = (char *)_m_pPortConfHelper->GetPortIntroByCoord(csCoordString);
    
    if((!_m_BgSprite)&&(port_image)){
        _m_BgSprite = Sprite::create(port_image);
        if(!_m_BgSprite){
            return;
        }
        _m_BgSprite->setPosition(position);
        this->addChild(_m_BgSprite, 100);
        
        //Create touch event handler and swallow the event of the hello layer
        _m_pListener = EventListenerTouchOneByOne::create();
        _m_pListener->setSwallowTouches(true);
        _m_pListener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};
        _m_pListener->onTouchEnded = [=](Touch *touch, Event *unused_event){};
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_m_pListener, this);
        
    }else{
        return;
    }

    Point titlePoint;
    Size spriteSize = _m_BgSprite->getContentSize();

    if(!_m_TitleLable){
        titlePoint.x = position.x;
        titlePoint.y = position.y + spriteSize.height/2;
        createTitle(port_name, 20, titlePoint);
    }
    if(!_m_IntroLable){
        titlePoint.x = position.x + spriteSize.width/4;
        titlePoint.y = position.y + spriteSize.height/4;
        createIntro(port_intro, 12, titlePoint);
    }
    if(!_m_CloseButton){
        titlePoint.x = position.x + spriteSize.width/2;
        titlePoint.y = position.y + spriteSize.height/2;
        createCloseButton(titlePoint);
    }
}

void PortPopupLayer::destoryBgSprite()
{
    log("get into touch ended event");
    this->removeAllChildren();
    this->_eventDispatcher->removeEventListener(_m_pListener);
    _m_BgSprite = NULL;
    _m_TitleLable = NULL;
    _m_IntroLable = NULL;
    _m_CloseButton = NULL;
}

void PortPopupLayer::createTitle(const char* title_name, int title_font, Point position)
{
    _m_TitleLable =LabelTTF::create(title_name,"Arial", title_font);
    if(_m_TitleLable){
        _m_TitleLable->setPosition(position);
        this->addChild(_m_TitleLable,200);
    }
}

void PortPopupLayer::createIntro(const char *intro_name, int intro_font, Point position)
{
    _m_IntroLable =LabelTTF::create(intro_name,"Arial", intro_font);
    if(_m_IntroLable){
        _m_IntroLable->setPosition(position);
        _m_IntroLable->setDimensions(Size(100,100));
        _m_IntroLable->setHorizontalAlignment(TextHAlignment::LEFT);
        this->addChild(_m_IntroLable,199);
    }
}

void PortPopupLayer::createCloseButton(Point position)
{
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(PortPopupLayer::buttonCloseCallback, this));
    
	closeItem->setPosition(position);
    
    // create menu, it's an autorelease object
    _m_CloseButton = Menu::create(closeItem, NULL);
    _m_CloseButton->setPosition(Vec2::ZERO);
    this->addChild(_m_CloseButton, 200);
}

void PortPopupLayer::buttonCloseCallback(Ref *pSender)
{
    this->destoryBgSprite();
}



