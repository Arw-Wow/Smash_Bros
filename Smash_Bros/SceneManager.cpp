#include "SceneManager.h"

// 设置当前场景（并调用onEnter）（一般在main中调用，且只在第一次调用）

void SceneManager::setCurrentScene(Scene* scene)
{
    if (current_scene)
        current_scene->onExit();
    current_scene = scene;
    current_scene->onEnter();
}

// 跳转场景 
// 由于switch方法一般在各个场景子类中调用，为了避免子类相互引用，传入参数设为SceneType枚举类
// 写manager类也是为了集中封装，避免相互引用以及方便同意调用

void SceneManager::switchTo(SceneType type)
{
    if (current_scene)
        current_scene->onExit();
    switch (type)
    {
    case SceneManager::Menu:
        current_scene = menu_scene;
        break;
    case SceneManager::Selector:
        current_scene = selector_scene;
        break;
    case SceneManager::Game:
        current_scene = game_scene;
        break;
    }
    current_scene->onEnter();
}

void SceneManager::onUpdate(int delta)
{
    current_scene->onUpdate(delta);
}

void SceneManager::onDraw(const Camera& camera)
{
    current_scene->onDraw(camera);
}

void SceneManager::onInput(const ExMessage& msg)
{
    current_scene->onInput(msg);
}
