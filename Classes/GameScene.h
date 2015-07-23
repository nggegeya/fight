#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "Player.h"
#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Layer
{
public:
//    GameScene();
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void addGameBg();
    Player *player;
    CREATE_FUNC(GameScene);
    
    Point preTouchPoint;      // 上一个触摸点
    Point currTouchPoint;     // 当前触摸点
    
private:
    Size winSize;                  // 窗口尺寸
    TMXTiledMap *map;              // 地图背景对象
    TMXObjectGroup * objectGroup;  // 对象组对象
    float objectPosOffX;           // 对象组X方向上的偏移值
    
    Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);  // 开始触摸屏幕时响应
    virtual void onTouchMoved(Touch *touch, Event *unused_event);  // 触摸屏幕并在屏幕上滑动时响应
    virtual void onTouchEnded(Touch *touch, Event *unused_event);  // 触摸结束时
};

#endif // __HELLOWORLD_SCENE_H__
