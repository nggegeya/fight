//
//  Player.cpp
//  arrowGame
//
//  Created by work on 15/7/4.
//
//

#include "Player.h"
Player::Player(){
    
}
Player::~Player(){
    
}

Player * Player::create(Vec2 playerPos)
{
    Player *pRet  = new Player();
    
    if (pRet && pRet->init(playerPos))
    {
        pRet->autorelease();
        return pRet;
    }else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool Player::init(Vec2 playerPos)
{
    if (!Sprite::init())
    {
        return false;
    }
    this->playerPos = playerPos;
    
    createPlayer();        // 创建角色
    createPlayerHpBar();   // 创建角色血量条
    scheduleUpdate();
  
    return true;
}

void Player::createPlayer()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist", "texture.pvr.ccz");
    playerbody = Sprite::createWithSpriteFrameName("playerbody.png");
    playerSize = Size(playerbody->getContentSize().width/2, playerbody->getContentSize().height / 3*2);  // 设置Player的尺寸，大小略小于playerbody的尺寸，这样利于我们后面更准确的进行碰撞设置。
    playerbody->setAnchorPoint(Vec2(0.7f, 0.4f));
    playerbody->setPosition(Vec2(111, 111));//暂时的,因为GameManager没有
    this->addChild(playerbody);
//    this->setPosition(Vec2(playerPos.x+ GameManager::getInstance()->getObjectPosOffX(), playerPos.y + playerSize.height * 0.4f));
    
    playerarrow = Sprite::createWithSpriteFrameName("playerarrow.png");
    playerarrow->setPosition(Vec2(111, 111));
    playerarrow->setAnchorPoint(Vec2(0.3f, 0.5f));
    this->addChild(playerarrow);
}

void Player::createPlayerHpBar()
{
    // 创建血条底，即进度条的底背景
    hPBgSprite = Sprite::createWithSpriteFrameName("hpbg.png");
    hPBgSprite->setPosition(Vec2(playerbody->getContentSize().width / 2, playerbody->getContentSize().height));
    playerbody->addChild(hPBgSprite);
    // 创建血条
    hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));
    hpBar->setType(ProgressTimer::Type::BAR); // 设置进度条样式（条形或环形）
    hpBar->setMidpoint(Vec2(0, 0.5f));        // 设置进度条的起始点，（0，y）表示最左边，（1，y）表示最右边，（x，1）表示最上面，（x，0）表示最下面。
    hpBar->setBarChangeRate(Vec2(1, 0));      //横方向 设置进度条变化方向，（1,0）表示横方向，（0,1）表示纵方向。
    hpBar->setPercentage(100);                // 设置当前进度条的进度
    hpBar->setPosition(Vec2(hPBgSprite->getContentSize().width / 2, hPBgSprite->getContentSize().height / 2 ));
    hPBgSprite->addChild(hpBar);
    hPBgSprite->setVisible(true);   // 设置整个血条不可见，我们将在Player 遭受攻击的时候再显示血条。
}

/*
获取角色弓箭在游戏场景中位置；
计算弓箭的旋转角度。
这里利用三角正切函数来计算，原理如下图所示：

vector（offX，offY） 是触摸点到弓箭之间的向量，通过 getAngle 方法，我们可以得到 vector 向量与X轴之间的弧度。
再者，我们需要把弧度 rotateRadians 转化为角度，CC_RADIANS_TO_DEGREES就是能把弧度转化为角度的宏。转化时乘 -1 是因为Cocos2d-x中规定顺时针方向为正，这与我们计算出的角度方向相反，所以转化的时候需要把角度a变为-a。
控制旋转角度的范围，即只让它在角色右半边内旋转。
计算弓箭旋转时间。
speed表示炮塔旋转的速度，0.5 / M_PI其实就是 1 / 2PI，它表示1秒钟旋转1个圆。
rotateDuration表示旋转特定的角度需要的时间，计算它用弧度乘以速度。
让弓箭执行旋转动作。*/
void Player::rotateArrow(Point touchPoint)
{
    // 1
    auto playerPos = this->getPosition();
    auto pos = playerPos + playerarrow->getPosition();
    // 2
    Point vector = touchPoint - pos;
    auto rotateRadians = vector.getAngle();
    auto rotateDegrees = CC_RADIANS_TO_DEGREES( -1 * rotateRadians);
    // 3
    if (rotateDegrees >= -180 && rotateDegrees <= -90){
        rotateDegrees = -90;
    }
    else if (rotateDegrees >= 90 && rotateDegrees <= 180){
        rotateDegrees = 90;
    }
    // 4
    auto speed = 1 / M_PI;
    auto rotateDuration = fabs(rotateRadians * speed);
    // 5
    playerarrow->runAction( RotateTo::create(rotateDuration, rotateDegrees));
}


void Player::createAndShootArrow( Point touchPoint)
{
    // 1
    isRunAction = true;
    // 2
    auto animation = AnimationCache::getInstance()->getAnimation("player");
    auto animate = Animate::create(animation);
    // 3
    auto funcall1= CallFunc::create(CC_CALLBACK_0(Player::shootArrow, this));
    // 4
    auto delayTime = DelayTime::create(0.5f);
    // 5
    auto funcall2= CallFunc::create(CC_CALLBACK_0(Player::finishRunAction, this));
    // 6
    playerbody->runAction(Sequence::create(animate, funcall1, delayTime, funcall2, NULL));
}

void Player::shootArrow()
{
    // 创建箭
    Sprite* arrow = Sprite::createWithSpriteFrameName("arrow1.png");
    arrow->setPosition(Vec2(playerarrow->getPosition().x, playerarrow->getPosition().y));

    this->addChild(arrow);
    // 以下将写射出箭的代码
    // .................
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Vec2(100, 200);
    bezier.controlPoint_2 = Vec2(200, 200);
    bezier.endPosition = Vec2(300, 0);
    auto action = BezierTo::create(2, bezier);
    arrow->runAction(action);
    
}
void Player::finishRunAction()
{
    isRunAction = false;
}