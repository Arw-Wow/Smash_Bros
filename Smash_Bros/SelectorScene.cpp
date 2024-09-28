#include "SelectorScene.h"

//进入场景（类似init函数，不构造但要初始化）

void SelectorScene::onEnter()
{
    // 重置状态
    bool is_btn_1P_left_down = false;
    bool is_btn_1P_right_down = false;
    bool is_btn_2P_left_down = false;
    bool is_btn_2P_right_down = false;

    mciSendString("play bgm_selector repeat from 0", NULL, 0, NULL);

    animation_1P_peashooter.setAtlas(&atlas_peashooter_idle_right);
    animation_1P_sunflower.setAtlas(&atlas_sunflower_idle_right);
	animation_1P_gloomshroom.setAtlas(&atlas_gloomshroom_idle_right);
	animation_1P_nut.setAtlas(&atlas_nut_idle_right);
    animation_1P_peashooter.setInterval(100);
    animation_1P_sunflower.setInterval(100);
	animation_1P_gloomshroom.setInterval(100);
	animation_1P_nut.setInterval(100);

    animation_2P_peashooter.setAtlas(&atlas_peashooter_idle_left);
    animation_2P_sunflower.setAtlas(&atlas_sunflower_idle_left);
	animation_2P_gloomshroom.setAtlas(&atlas_gloomshroom_idle_left);
	animation_2P_nut.setAtlas(&atlas_nut_idle_left);
    animation_2P_peashooter.setInterval(100);
    animation_2P_sunflower.setInterval(100);
	animation_2P_gloomshroom.setInterval(100);
	animation_2P_nut.setInterval(100);


    static constexpr int OFFSET_X = 50;

    pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
    pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;

    pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
    pos_img_tip.y = getheight() - 125;

    pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
    pos_img_1P.y = 35;
    pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
    pos_img_2P.y = pos_img_1P.y;

    pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
    pos_img_1P_desc.y = getheight() - 150;
    pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
    pos_img_2P_desc.y = pos_img_1P_desc.y;

    pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
    pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
    pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
    pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;

    pos_animation_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right.getImage(0)->getwidth()) / 2 - OFFSET_X;
    pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
    pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.getImage(0)->getwidth()) / 2 + OFFSET_X;
    pos_animation_2P.y = pos_animation_1P.y;

    pos_img_1P_name.y = pos_animation_1P.y + 155;
    pos_img_2P_name.y = pos_img_1P_name.y;

    pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
    pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
    pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
    pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;

    pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
    pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
    pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
    pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;

}

//处理数据

void SelectorScene::onUpdate(int delta)
{
    animation_1P_peashooter.onUpdate(delta);
    animation_1P_sunflower.onUpdate(delta);
	animation_1P_gloomshroom.onUpdate(delta);
	animation_1P_nut.onUpdate(delta);

    animation_2P_peashooter.onUpdate(delta);
    animation_2P_sunflower.onUpdate(delta);
	animation_2P_gloomshroom.onUpdate(delta);
	animation_2P_nut.onUpdate(delta);

    selector_background_scorll_offset_x += 5;
    if (selector_background_scorll_offset_x >= img_peashooter_selector_background_left.getwidth())
        selector_background_scorll_offset_x = 0;
}

//渲染绘图

void SelectorScene::onDraw(const Camera& camera)
{
    IMAGE* img_p1_selector_background = nullptr;
    IMAGE* img_p2_selector_background = nullptr;

    switch (player_type_1)
    {
    case PlayerType::PeaShooter:
        img_p1_selector_background = &img_peashooter_selector_background_right;
        break;
    case PlayerType::SunFlower:
        img_p1_selector_background = &img_sunflower_selector_background_right;
        break;
	case PlayerType::GloomShroom:
		img_p1_selector_background = &img_gloomshroom_selector_background_right;
		break;
	case PlayerType::Nut:
		img_p1_selector_background = &img_nut_selector_background_right;
		break;
    default:
        img_p1_selector_background = &img_peashooter_selector_background_right;
        break;
    }

    switch (player_type_2)
    {
    case PlayerType::PeaShooter:
        img_p2_selector_background = &img_peashooter_selector_background_left;
        break;
    case PlayerType::SunFlower:
        img_p2_selector_background = &img_sunflower_selector_background_left;
        break;
	case PlayerType::GloomShroom:
		img_p2_selector_background = &img_gloomshroom_selector_background_left;
		break;
	case PlayerType::Nut:
		img_p2_selector_background = &img_nut_selector_background_left;
		break;
    case PlayerType::Invalid:
        break;
    default:
        img_p2_selector_background = &img_sunflower_selector_background_left;
        break;
    }

    putimage(0, 0, &img_selector_background);

    putimage_alpha(selector_background_scorll_offset_x - img_p1_selector_background->getwidth(), 0, img_p1_selector_background);	//左图片，动态向右
    putimage_alpha(selector_background_scorll_offset_x, 0,
        img_p1_selector_background->getwidth() - selector_background_scorll_offset_x, img_p1_selector_background->getheight(),
        img_p1_selector_background,
        0, 0);	//右图片，动态向右并且缩小右边界

    putimage_alpha(getwidth() - selector_background_scorll_offset_x, 0, img_p2_selector_background);
    putimage_alpha(getwidth() - img_p2_selector_background->getwidth(), 0,
        img_p2_selector_background->getwidth() - selector_background_scorll_offset_x, img_p2_selector_background->getheight(),
        img_p2_selector_background,
        selector_background_scorll_offset_x, 0);

    putimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);

    putimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
    putimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);
    putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
    putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);

    switch (player_type_1)
    {
    case PlayerType::PeaShooter:
        animation_1P_peashooter.onDraw(camera, pos_animation_1P.x, pos_animation_1P.y);
        pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;	//在这里设置位置是为了根据文本长度动态设置，以保证文本居中
        outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
        break;
    case PlayerType::SunFlower:
        animation_1P_sunflower.onDraw(camera, pos_animation_1P.x, pos_animation_1P.y);
        pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
        outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
        break;
	case PlayerType::GloomShroom:
		animation_1P_gloomshroom.onDraw(camera, pos_animation_1P.x, pos_animation_1P.y);
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_gloomshroom_name)) / 2;
		outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_gloomshroom_name);
		break;
	case PlayerType::Nut:
		animation_1P_nut.onDraw(camera, pos_animation_1P.x, pos_animation_1P.y);
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_nut_name)) / 2;
		outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_nut_name);
		break;
    case PlayerType::Invalid:
        break;
    }

    switch (player_type_2)
    {
    case PlayerType::PeaShooter:
        animation_2P_peashooter.onDraw(camera, pos_animation_2P.x, pos_animation_2P.y);
        pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
        outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
        break;
    case PlayerType::SunFlower:
        animation_2P_sunflower.onDraw(camera, pos_animation_2P.x, pos_animation_2P.y);
        pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
        outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
        break;
	case PlayerType::GloomShroom:
		animation_2P_gloomshroom.onDraw(camera, pos_animation_2P.x, pos_animation_2P.y);
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_gloomshroom_name)) / 2;
		outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_gloomshroom_name);
		break;
	case PlayerType::Nut:
		animation_2P_nut.onDraw(camera, pos_animation_2P.x, pos_animation_2P.y);
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_nut_name)) / 2;
		outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_nut_name);
		break;
    case PlayerType::Invalid:
        break;
    }

    putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y,
        is_btn_1P_left_down ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
    putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y,
        is_btn_1P_right_down ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
    putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y,
        is_btn_2P_left_down ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
    putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y,
        is_btn_2P_right_down ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);

    putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
    putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

    putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);

}

//处理输入

void SelectorScene::onInput(const ExMessage& msg)
{
    int temp_p1_type = player_type_1;
    int temp_p2_type = player_type_2;

    switch (msg.message)
    {
    case WM_KEYDOWN:
        switch (msg.vkcode)
        {
        case 0x41:		// 'A'
            is_btn_1P_left_down = true;
            break;
        case 0x44:		// 'D'
            is_btn_1P_right_down = true;
            break;
        case VK_LEFT:	// '←'
            is_btn_2P_left_down = true;
            break;
        case VK_RIGHT:	// '→'
            is_btn_2P_right_down = true;
            break;
        }
        break;

    case WM_KEYUP:
        switch (msg.vkcode)
        {
        case 0x41:		// 'A'
            is_btn_1P_left_down = false;

            // 由于枚举类型不能直接加减，故要转换成int类型操作，再转回枚举类型
            temp_p1_type = player_type_1;
            temp_p1_type++;
            if (temp_p1_type >= (int)PlayerType::Invalid)	temp_p1_type = 0;
            player_type_1 = PlayerType(temp_p1_type);

            mciSendString("play ui_switch from 0", NULL, 0, NULL);

            break;

        case 0x44:		// 'D'
            is_btn_1P_right_down = false;

            temp_p1_type = player_type_1;
            temp_p1_type++;
            if (temp_p1_type >= (int)PlayerType::Invalid)	temp_p1_type = 0;
            player_type_1 = PlayerType(temp_p1_type);

            mciSendString("play ui_switch from 0", NULL, 0, NULL);

            break;

        case VK_LEFT:	// '←'
            is_btn_2P_left_down = false;

            temp_p2_type = player_type_2;
            temp_p2_type++;
            if (temp_p2_type >= (int)PlayerType::Invalid)	temp_p2_type = 0;
            player_type_2 = PlayerType(temp_p2_type);

            mciSendString("play ui_switch from 0", NULL, 0, NULL);

            break;

        case VK_RIGHT:	// '→'
            is_btn_2P_right_down = false;

            temp_p2_type = player_type_2;
            temp_p2_type++;
            if (temp_p2_type >= (int)PlayerType::Invalid)	temp_p2_type = 0;
            player_type_2 = PlayerType(temp_p2_type);

            mciSendString("play ui_switch from 0", NULL, 0, NULL);

            break;

        case VK_RETURN:	// 回车进入game scene
            scene_manager->switchTo(SceneManager::SceneType::Game);
            mciSendString("play ui_confirm from 0", NULL, 0, NULL);
            break;
        }
        break;

    }
}

//退出场景

void SelectorScene::onExit()
{
    switch (player_type_1)
    {
    case PlayerType::PeaShooter:
        player_1 = new Peashooter();
        break;
    case PlayerType::SunFlower:
        player_1 = new Sunflower();
        break;
	case PlayerType::GloomShroom:
		player_1 = new Gloomshroom();
		break;
	case PlayerType::Nut:
		// player_1 = new Nut();
		break;
    }
    player_1->setID(PlayerID::P1);

    switch (player_type_2)
    {
    case PlayerType::PeaShooter:
        player_2 = new Peashooter();
        break;
    case PlayerType::SunFlower:
        player_2 = new Sunflower();
        break;
	case PlayerType::GloomShroom:
		player_2 = new Gloomshroom();
		break;
	case PlayerType::Nut:
		// player_2 = new Nut();
		break;
    }
    player_2->setID(PlayerID::P2);

    mciSendString("stop bgm_selector", NULL, 0, NULL);
}
