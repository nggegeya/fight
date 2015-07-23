//
//  CCDefine.h
//  arrowGame
//
//  Created by work on 15/7/4.
//
//

#ifndef __arrowGame__CCDefine__
#define __arrowGame__CCDefine__

#include <stdio.h>

#define SCENE_FUNC(__TYPE__)\
static cocos2d::Scene* scene(){\
cocos2d::Scene *scene = cocos2d::Scene::create();\
__TYPE__ *layer = __TYPE__::create();\
scene->addChild(layer);\
return scene;\
}

#endif /* defined(__arrowGame__CCDefine__) */
