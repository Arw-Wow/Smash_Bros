#include "MenuScene.h"

//���볡��

void MenuScene::onEnter()
{
    mciSendString("play bgm_menu repeat from 0", NULL, 0, NULL);
}

//��������

void MenuScene::onUpdate(int delta)
{
}

//��Ⱦ��ͼ

void MenuScene::onDraw(const Camera& camera)
{
    putimage(0, 0, &img_menu_background);

}

//��������

void MenuScene::onInput(const ExMessage& msg)
{
    if (msg.message == WM_KEYUP)
    {
        mciSendString("play ui_confirm from 0", NULL, 0, NULL);
        scene_manager->switchTo(SceneManager::SceneType::Selector);
    }
}

//�˳�����

void MenuScene::onExit()
{
    mciSendString("stop bgm_menu", NULL, 0, NULL);
}
