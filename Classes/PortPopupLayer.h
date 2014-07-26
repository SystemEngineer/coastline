//
//  PortPopupLayer.h
//  coastline
//
//  Created by 荣徽 贺 on 14-6-27.
//
//

#ifndef coastline_PortPopupLayer_h
#define coastline_PortPopupLayer_h

#include "cocos2d.h"
#include "PortConfigHelper.h"

class PortPopupLayer : public cocos2d::LayerColor
{
public:
    PortPopupLayer();
    ~PortPopupLayer();
    
    virtual bool init();
    CREATE_FUNC(PortPopupLayer);
    
    void createBgSprite(const char* csCoordString,cocos2d::Point posCenter);
    void destoryBgSprite();
    void createTitle(const char* title, int fontzise, cocos2d::Point position);
    void createIntro(const char* intro, int fontzise, cocos2d::Point position);
    void createCloseButton(cocos2d::Point position);
    
    //virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    cocos2d::EventListenerTouchOneByOne *_m_pListener;
    void buttonCloseCallback(cocos2d::Ref* pSender);

private:
    cocos2d::Sprite *_m_BgSprite;
    cocos2d::LabelTTF *_m_TitleLable;
    cocos2d::LabelTTF *_m_IntroLable;
    PortConfigHelper *_m_pPortConfHelper;
    cocos2d::Menu *_m_CloseButton;
};

#endif
