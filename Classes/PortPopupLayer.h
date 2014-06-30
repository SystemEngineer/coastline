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

class PortPopupLayer : public cocos2d::Layer
{
public:
    PortPopupLayer();
    ~PortPopupLayer();
    
    virtual bool init();
    CREATE_FUNC(PortPopupLayer);
    
    void createBgSprite(const char* bg_image,cocos2d::Point posCenter);
    void destoryBgSprite();
    cocos2d::CCLabelTTF* createTitle(const char* title, int fontzise = 20);
    bool addButton(const char* normal_img, const char* click_img, const char* title, int tag = 0);

private:
    cocos2d::Sprite *_m_BgSprite;
};

#endif
