#include "MenuScene.h"

//进入场景

void MenuScene::onEnter()
{
    mciSendString("play bgm_menu repeat from 0", NULL, 0, NULL);
}

//处理数据

void MenuScene::onUpdate(int delta)
{
}

//渲染绘图

void MenuScene::onDraw(const Camera& camera)
{
    putimage(0, 0, &img_menu_background);

}

//处理输入

void MenuScene::onInput(const ExMessage& msg)
{
    if (msg.message == WM_KEYUP)
    {
        mciSendString("play ui_confirm from 0", NULL, 0, NULL);
        scene_manager->switchTo(SceneManager::SceneType::Selector);
    }
}

//退出场景

void MenuScene::onExit()
{
    mciSendString("stop bgm_menu", NULL, 0, NULL);
}
