#include "SceneManager.h"

// ���õ�ǰ������������onEnter����һ����main�е��ã���ֻ�ڵ�һ�ε��ã�

void SceneManager::setCurrentScene(Scene* scene)
{
    if (current_scene)
        current_scene->onExit();
    current_scene = scene;
    current_scene->onEnter();
}

// ��ת���� 
// ����switch����һ���ڸ������������е��ã�Ϊ�˱��������໥���ã����������ΪSceneTypeö����
// дmanager��Ҳ��Ϊ�˼��з�װ�������໥�����Լ�����ͬ�����

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
