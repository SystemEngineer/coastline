//
//  FloatingSprite.h
//  coastline
//
//  Created by 荣徽 贺 on 14-8-6.
//  For floating sprites such as ships
//  A floating sprite has the ability of A-star path finding
//

#ifndef __coastline__FloatingSprite__
#define __coastline__FloatingSprite__

#include "cocos2d.h"

class HelloWorld;   //Path-finding need tile map info

//Here is the step object for A-star
class PathStep : public cocos2d::Ref
{
public:
    PathStep();
    ~PathStep();
    
    static PathStep *createWithPosition(const cocos2d::Point pos);
    bool initWithPosition(const cocos2d::Point pos);
    
    int getFScore() const;
    bool isEqual(const PathStep* other_ps) const;
    std::string getDescription() const;
    
    CC_SYNTHESIZE(cocos2d::Point, _Position, Position);
    CC_SYNTHESIZE(int, _GScore, GScore);
    CC_SYNTHESIZE(int, _HScore, HScore);
    CC_SYNTHESIZE(PathStep*, _Parent, Parent);
};

class FloatingSprite : public cocos2d::Sprite
{
public:
    FloatingSprite();
    ~FloatingSprite();
    
    static FloatingSprite* createWithFileAndLayer(const char* filename, HelloWorld* layer);
    bool initWithLayer(HelloWorld* layer);
    
    CC_SYNTHESIZE(cocos2d::Layer*, _ParentLayer, ParentLayer);
    
    //members for A-Star
    void moveTowardTarget(const cocos2d::Point &target);
    void insertInOpenSteps(PathStep *step);
    ssize_t getStepIndex(const cocos2d::Vector<PathStep*> &stepVec, PathStep* step);
    int calcHScoreFromCoordToCoord(const cocos2d::Point &from, const cocos2d::Point &to);
    int calcCostFromStepToAdjacent(const PathStep *from, const PathStep *to);
    void buildFoundedPathSteps(PathStep *step);
    void moveStepByStep();
    
private:
    HelloWorld* _HelloLayer;
    //members for A-star
    cocos2d::Vector<PathStep*> _OpenSteps;
    cocos2d::Vector<PathStep*> _ClosedSteps;
    cocos2d::Vector<PathStep*> _FoundedPathSteps;
};

#endif /* defined(__coastline__FloatingSprite__) */
