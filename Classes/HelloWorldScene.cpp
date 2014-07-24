#include "HelloWorldScene.h"
#include "PortPopupLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto pPopupLayer = PortPopupLayer::create();
    // add layer as a child to scene
    // Attention: tag is the 3rd argument!
    scene->addChild(pPopupLayer,100,POPUP_LAYER_TAG);
    
    auto layer = HelloWorld::create();
    scene->addChild(layer,0,BACKGROUND_LAYER_TAG);
   
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
/*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
*/
    
    //Create tile map with file in Resource directory
    std::string file = "MyTileMap1.tmx";
    auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
    _TileMap = TMXTiledMap::createWithXML(str->getCString(), "");
    //Load background layer in tile map
    _Background = _TileMap->layerNamed("Background");
    _Land = _TileMap->layerNamed("LandLayer");
    
    _Land->setVisible(false);
    addChild(_TileMap,-1);

    //Load player object layer in tile map, get the position of object
    TMXObjectGroup *objects = _TileMap->getObjectGroup("PlayerLayer");
    CCASSERT(NULL != objects, "'PlayerLayer' object group not found");
    auto player_start_point = objects->getObject("PlayerStartPoint");
    CCASSERT(!player_start_point.empty(), "player_start_point object not found");
    
    int start_x = player_start_point["x"].asInt();
    int start_y = player_start_point["y"].asInt();
    
    //Create player sprite and put it to center
    _Player = Sprite::create("ship1.png");
    _Player->setPosition(start_x,start_y);
    
    addChild(_Player);
    setViewPointCenter(_Player->getPosition());
    
    //Create listener for touch (left-click in osx)
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};   //Note: object-c ?
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded,this);  //Note: what the purpose of the 4 kind of CC_CALLBACK?
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //Note: what this mean?
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::setViewPointCenter(Point posCenter)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    //handle the pos in 4 cornors, winSize always from 0 to window width or height
    int x = MAX(posCenter.x, winSize.width/2);
    int y = MAX(posCenter.y, winSize.height/2);
    x = MIN(x,(_TileMap->getMapSize().width*_TileMap->getTileSize().width) - winSize.width/2);
    y = MIN(y,(_TileMap->getMapSize().height * _TileMap->getTileSize().height) - winSize.height/2);
    
    //Calc view point: the positon of current FOV ((0,0) is bottom-left)
    auto acturalPos = Point(x,y);
    auto centerOfView = Point(winSize.width/2, winSize.height/2);
    auto viewPoint = centerOfView - acturalPos;
    this->setPosition(viewPoint);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    auto actionTo1 = RotateTo::create(0, 0, 180);
    auto actionTo2 = RotateTo::create(0, 0, 0);
    auto touchLocation = touch->getLocation();
    
    touchLocation = this->convertToNodeSpace(touchLocation);
    
    auto playerPos = _Player->getPosition();
    auto diff = touchLocation - playerPos;
    if (abs(diff.x) > abs(diff.y)) {
        if (diff.x > 0) {
            //Move half of the tile block size each touch
            playerPos.x += _TileMap->getTileSize().width ;
            //Player may be fliped according its directory
            _Player->runAction(actionTo2);
        }
        else {
            playerPos.x -= _TileMap->getTileSize().width ;
            _Player->runAction(actionTo1);
        }
    }
    else {
        if (diff.y > 0) {
            playerPos.y += _TileMap->getTileSize().height ;
        }
        else {
            playerPos.y -= _TileMap->getTileSize().height ;
        }
    }
    
    if (playerPos.x <= (_TileMap->getMapSize().width * _TileMap->getTileSize().width) &&
        playerPos.y <= (_TileMap->getMapSize().height * _TileMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0)
    {
        this->setPlayerPosition(playerPos);
        
    }
    
    this->setViewPointCenter(_Player->getPosition());
}

void HelloWorld::setPlayerPosition(Point position)
{
    Point tileCoord = this->getTileCoordForPosition(position);
    int tileGID = _Land->getTileGIDAt(tileCoord);
    if (tileGID) {
        //Check if it is a blockage area. If so, ship cannot pass, move disabled.
        auto properties = _TileMap->getPropertiesForGID(tileGID).asValueMap();
        if (!properties.empty()) {
            //Properties and values are defined in tiled map
            //All attributes lies in the "LandLayer"
            auto collision = properties["Blockage"].asString();
            auto dockable = properties["Port"].asString();
            if ("True" == collision) {
                return;
            }
            else if ("True" == dockable) {
                //Show the port sub image
                PortPopupLayer* pPopupLayer = (PortPopupLayer*)Director::getInstance()->getRunningScene()->getChildByTag(POPUP_LAYER_TAG);
                //Attention to the position coord.
                auto winSize = Director::getInstance()->getWinSize();
                //Get port name by coord
                CCString* tmp_str = CCString::createWithFormat("%d:%d",int(tileCoord.x),int(tileCoord.y));
                pPopupLayer->createBgSprite(tmp_str->getCString(), Point(winSize.width/2, winSize.height/2));
                
            }
        }
    }
    _Player->setPosition(position);
}

Point HelloWorld::getTileCoordForPosition(Point position)
{
    int x = position.x/_TileMap->getTileSize().width;
    int y = ((_TileMap->getMapSize().height*_TileMap->getTileSize().height) - position.y)/_TileMap->getTileSize().height;
    return Point(x,y);
}
