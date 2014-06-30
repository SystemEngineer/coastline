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
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}

//Create background image sprite
void PortPopupLayer::createBgSprite(const char* bg_image,Point position)
{
    if (!_m_BgSprite){
        _m_BgSprite = Sprite::create(bg_image);
        _m_BgSprite->setPosition(position);
        this->addChild(_m_BgSprite, 100);
    }
}

void PortPopupLayer::destoryBgSprite()
{
    if(_m_BgSprite != NULL){
        this->removeChild(_m_BgSprite);
        _m_BgSprite = NULL;
    }
}

CCLabelTTF* PortPopupLayer::createTitle(const char* title_name, int title_font)
{
    CCLabelTTF *lbl_title =CCLabelTTF::create(title_name,"", title_font);
}



