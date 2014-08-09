#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "FloatingSprite.h"

#define BACKGROUND_LAYER_TAG  1
#define SHIP_LAYER_TAG        2
#define MASK_LAYER_TAG        3
#define POPUP_LAYER_TAG       4
#define PORT_SPRITE_TAG       100

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void setViewPointCenter(cocos2d::Point posCenter);    
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void setPlayerPosition(cocos2d::Point position);
    cocos2d::Point getTileCoordForPosition(cocos2d::Point point);
    cocos2d::Point getPositionForTileCoord(cocos2d::Point tileCoord);
    bool isBlockageTile(cocos2d::Point point);
    bool isValidTile(cocos2d::Point tileCoord);
    cocos2d::PointArray* accessibleTilesAdjacentToTileCoord(const cocos2d::Point &curCoord);
    
private:
    cocos2d::TMXTiledMap *_TileMap;
    cocos2d::TMXLayer *_Background;
    cocos2d::TMXLayer *_Land;
    FloatingSprite *_Player;
    cocos2d::Scene *_RunningScene;
};

#endif // __HELLOWORLD_SCENE_H__
