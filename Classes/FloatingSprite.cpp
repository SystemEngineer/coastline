//
//  FloatingSprite.cpp
//  coastline
//
//  Created by 荣徽 贺 on 14-8-6.
//
//

#include "FloatingSprite.h"
#include "HelloWorldScene.h"    //This is nessesary because we use HelloWorld layer

USING_NS_CC;

#define TAG_FOR_MOVING 1

PathStep::PathStep():
_Position(Point::ZERO),
_GScore(0),
_HScore(0),
_Parent(nullptr)
{
    
}

PathStep::~PathStep()
{
    
}

PathStep* PathStep::createWithPosition(Point pos)
{
    PathStep* pPathStepObj = new PathStep();
    if(pPathStepObj && pPathStepObj->initWithPosition(pos)){
        pPathStepObj->autorelease();
        return pPathStepObj;
    }
    CC_SAFE_DELETE(pPathStepObj);
    return nullptr;
}

bool PathStep::initWithPosition(Point pos)
{
    bool bRet = false;
    do{
        this->setPosition(pos);
        bRet = true;
    }while(0);
    
    return bRet;
}

int PathStep::getFScore() const
{
    return this->getGScore() + this->getHScore();
}

bool PathStep::isEqual(const PathStep* other_ps) const
{
    return this->getPosition() == other_ps->getPosition();
}

std::string PathStep::getDescription() const
{
    __String* sTemp = __String::createWithFormat("pos = [%.0f, %.0f], g=%d, h=%d, f=%d",
                                                this->getPosition().x, this->getPosition().y,
                                                this->getGScore(),this->getHScore(),this->getFScore());
    
    return sTemp->_string;
}


FloatingSprite::FloatingSprite():
_HelloLayer(nullptr)
{
    
}

FloatingSprite::~FloatingSprite()
{
    
}

FloatingSprite* FloatingSprite::createWithFileAndLayer(const char *filename, HelloWorld* layer)
{
    FloatingSprite* FloatingSpriteObj = new FloatingSprite();
    if(FloatingSpriteObj && FloatingSpriteObj->initWithFile(filename) && FloatingSpriteObj->initWithLayer(layer))
    {
        FloatingSpriteObj->autorelease();
        return FloatingSpriteObj;
    }
    CC_SAFE_DELETE(FloatingSpriteObj);
    return NULL;
}

bool FloatingSprite::initWithLayer(HelloWorld *layer)
{
    if(!layer){
        return false;
    }
    _HelloLayer = layer;
    return true;
}
//This is the function for A-star pathfinding and moving
void FloatingSprite::moveTowardTarget(const Point &target)
{
    if(!_HelloLayer){
        return;
    }
    //Stop current movint action and start a new pathfinding
    this->stopActionByTag(TAG_FOR_MOVING);
    Point fromTileCoord = _HelloLayer->getTileCoordForPosition(this->getPosition());
    Point toTileCoord = _HelloLayer->getTileCoordForPosition(target);
    if(fromTileCoord == toTileCoord){
        log("It's already there");
        return;
    }
    if((_HelloLayer->isBlockageTile(toTileCoord)) || !(_HelloLayer->isValidTile(toTileCoord))){
        log("Target [%f,%f] is unaccessible",toTileCoord.x, toTileCoord.y);
        return;
    }
    log("From: %f, %f", fromTileCoord.x, fromTileCoord.y);
    log("To: %f, %f", toTileCoord.x, toTileCoord.y);
    
    _OpenSteps.clear();
    _ClosedSteps.clear();
    _FoundPathSteps.clear();
    //Add current position(start position)
    this->insertInOpenSteps(PathStep::createWithPosition(fromTileCoord));
    do{
        //1. get the top step in open steps array, push it to close steps array, then check the step
        PathStep* currentStep = _OpenSteps.at(0);
        _ClosedSteps.pushBack(currentStep);
        _OpenSteps.erase(0);
        
        //current step is the target to move, finished
        //log("%s",currentStep->getDescription().c_str());
        if(currentStep->getPosition() == toTileCoord){
            PathStep* tmpStep = currentStep;
            log("Path found");
            //Got the path, start moving to the target point
            buildFoundedPathSteps(tmpStep);
            moveStepByStep();
            
            _OpenSteps.clear();
            _ClosedSteps.clear();
            break;
        }
        //Check all adjacent tiles, put it into open steps array according to the F score
        PointArray* adjSteps = _HelloLayer->accessibleTilesAdjacentToTileCoord(currentStep->getPosition());
        for(ssize_t i = 0; i < adjSteps->count(); i++){
            PathStep* step = PathStep::createWithPosition(adjSteps->getControlPointAtIndex(i));
            //log("%s",step->getDescription().c_str());
            if(this->getStepIndex(_ClosedSteps,step) != -1){
                //the step is already in the closed steps, ignore
                continue;
            }
            int moveCost = this->calcCostFromStepToAdjacent(currentStep, step);
            ssize_t openIndex = this->getStepIndex(_OpenSteps, step);
            if(openIndex == -1){
                //this step is not in the open steps array, calc scores and put it into the array
                step->setParent(currentStep);
                step->setGScore(currentStep->getGScore() + moveCost);
                step->setHScore(this->calcHScoreFromCoordToCoord(step->getPosition(), toTileCoord));
                this->insertInOpenSteps(step);
            }else{
                step = _OpenSteps.at(openIndex);
                //this step is already in the open steps array ,recalc scores and refine the score and parent
                if((currentStep->getGScore() + moveCost) < step->getGScore()){
                    //Fix me: why not set parent?
                    step->setParent(currentStep);
                    step->setGScore(currentStep->getGScore() + moveCost);
                    step->retain();
                    _OpenSteps.erase(openIndex);
                    this->insertInOpenSteps(step);
                    step->release();
                }
            }
        }
    }while(_OpenSteps.size() > 0);
    
    if(_FoundPathSteps.empty()){
        log("Cannot find a path to the destination");
    }
}

void FloatingSprite::insertInOpenSteps(PathStep *step)
{
    //Make sure the insertion is ordered!
    int stepFScore = step->getFScore();
    ssize_t count = _OpenSteps.size();
    ssize_t i = 0;
    for(; i < count; i++){
        if(stepFScore <= _OpenSteps.at(i)->getFScore()){
            break;
        }
    }
    _OpenSteps.insert(i,step);
}
ssize_t FloatingSprite::getStepIndex(const cocos2d::Vector<PathStep*> &stepVec, PathStep* step)
{
    for(ssize_t i = 0; i < stepVec.size(); i++){
        if(stepVec.at(i)->isEqual(step)){
            return i;
        }
    }
    return -1;
}

int FloatingSprite::calcHScoreFromCoordToCoord(const Point &from, const Point &to)
{
    return abs(to.y - from.y)+abs(to.x - from.x);
}

int FloatingSprite::calcCostFromStepToAdjacent(const PathStep *from, const PathStep *to)
{
    return 1;
}

void FloatingSprite::buildFoundedPathSteps(PathStep *step)
{
    _FoundPathSteps.clear();
    
    do{
        if(step->getParent()){
            _FoundPathSteps.insert(0, step);
        }
        step = step->getParent();
    }while(step);
    
    for(const PathStep *s : _FoundPathSteps){
        log("%s",s->getDescription().c_str());
    }
}

void FloatingSprite::moveStepByStep()
{
    if(_FoundPathSteps.empty()){
        return;
    }
    PathStep* step = _FoundPathSteps.at(0);
    Point stepPos = _HelloLayer->getPositionForTileCoord(step->getPosition());
    MoveTo* moveAction = MoveTo::create(0.3f, stepPos);
    CallFunc* moveCallback = CallFunc::create(CC_CALLBACK_0(FloatingSprite::moveStepByStep, this));
    
    _FoundPathSteps.erase(0);
    Sequence* moveSeq = Sequence::create(moveAction,moveCallback, NULL);
    moveSeq->setTag(TAG_FOR_MOVING);
    this->runAction(moveSeq);
    if(_FoundPathSteps.empty()){
        _HelloLayer->setPlayerPosition(stepPos);
        _HelloLayer->setViewPointCenter(stepPos);
    }
}
