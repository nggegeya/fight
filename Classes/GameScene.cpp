#include "GameScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CCDefine.h"
USING_NS_CC;

using namespace cocostudio::timeline;
//SCENE_FUNC(GameScene);
Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    winSize = Director::getInstance()->getWinSize();
    this->addGameBg();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist", "texture.pvr.ccz");
    player = Player::create(Vec2(winSize.width / 4, winSize.height/5));
    this->addChild(player);
    
    // 获取事件分发器
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    // 创建单点触摸监听器
    auto listener = EventListenerTouchOneByOne::create();
    // 让监听器绑定事件处理函数
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    // 将事件监听器添加到事件调度器
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    
    Animation* animation = createAnimation("player", 8, 0.06f);
    AnimationCache::getInstance()->addAnimation(animation, "player");
    
//    auto rootNode = CSLoader::createNode("MainScene.csb");
//
//    addChild(rootNode);

    return true;
}

void GameScene::addGameBg(){
    Sprite* spGameBg = Sprite::create("bg1.jpg");
    Vec2 center = Vec2 (winSize.width/2,winSize.height/2);
    spGameBg->setPosition(center);
    this->addChild(spGameBg,-1);
    
    map = TMXTiledMap::create("map1.tmx");
    map->setAnchorPoint(Vec2(0.5f,0.5f));
    map->setPosition(center);
    this->addChild(map,-1);
    
    objectGroup = map->getObjectGroup("object");
    objectPosOffX = -(map->getContentSize().width - winSize.width) / 2;
}

Animation* GameScene::createAnimation(std::string prefixName, int framesNum, float delay)
{
    // 1
    Vector<SpriteFrame*> animFrames;
    // 2
    for (int i = 1; i <= framesNum; i++)
    {
        char buffer[20] = { 0 };
        sprintf(buffer, "%i.png",  i);
        std::string str =  prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    // 3
    return Animation::createWithSpriteFrames(animFrames, delay);
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    currTouchPoint = touch->getLocation();
//    if( !currTouchPoint.equals(preTouchPoint)){
//        player->rotateArrow(currTouchPoint);
//    }
    preTouchPoint = currTouchPoint;
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
    currTouchPoint = touch->getLocation();
    if( !currTouchPoint.equals(preTouchPoint)){
        player->rotateArrow(currTouchPoint);
    }
    preTouchPoint = currTouchPoint;
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
    // 射箭，下章内容
    currTouchPoint = touch->getLocation();
    player->createAndShootArrow(currTouchPoint);
}
