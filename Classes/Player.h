//
//  Player.h
//  arrowGame
//
//  Created by work on 15/7/4.
//
//

#ifndef __arrowGame__Player__
#define __arrowGame__Player__

#include "cocos2d.h"
USING_NS_CC;

class Player: public Sprite
{
public:
    Player();
    virtual ~Player();
    
    bool init(Vec2 playerPos);
    static Player* create(Vec2 playerPos);
    
    void createPlayer();
    void createPlayerHpBar();
    void rotateArrow(Point touchPoint);
    void createAndShootArrow( Point touchPoint);
    void shootArrow();
    void finishRunAction();
//    void update(float dt);
    
    CC_SYNTHESIZE(int, playerHp, PlayerHp);        // 玩家血量值
    CC_SYNTHESIZE(bool, startDraw, StartDraw);     // 是否开始画红色的路径线
    CC_SYNTHESIZE(bool, isRunAction, IsRunAction); // 玩家是否正在执行射箭动画
    

    
private:
    Vec2 playerPos;            // 角色在 tmx 地图上的位置
    Size playerSize;           // 角色尺寸
    Size winSize;              // 屏幕窗口尺寸
    Sprite* playerbody;        // 角色身体
    Sprite* playerarrow;       // 角色的弓箭，也就是会随触摸点旋转的弓和箭部分
    Sprite* hPBgSprite;        // 角色血条背景精灵
    ProgressTimer* hpBar;      // 角色血条
//    ccQuadBezierConfig bezier; // 路径贝赛尔

    DrawNode* drawNode;        // 这里表示我们的线条对象
    
    
    
};
#endif /* defined(__arrowGame__Player__) */
