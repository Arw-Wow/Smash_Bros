#include "GameScene.h"

//���볡��

void GameScene::onEnter()
{
    // ����״̬
    is_game_over = false;
    is_cursor_display = true;
    is_win_img_slide = false;

    mciSendString("play bgm_game repeat from 0", NULL, 0, NULL);

    player_1->setPosition(200, 100);
    player_2->setPosition(getwidth() - 200 - player_2->getSize().x, 100);
    player_1->setFacingleft(false);
    player_2->setFacingleft(true);

    //������ʾ��ͼƬ�ȴ����Դ�
    pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
    pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

    pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
    pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

    pos_render_large_platform.x = 122;
    pos_render_large_platform.y = 455;

    pos_render_small_platform_1.x = 175;
    pos_render_small_platform_1.y = 360;

    pos_render_small_platform_2.x = 855;
    pos_render_small_platform_2.y = 360;

    pos_render_small_platform_3.x = 515;
    pos_render_small_platform_3.y = 225;

    pos_img_winner_bar.x = -img_winner_bar.getwidth();
    pos_img_winner_bar.y = getheight() / 2 - img_winner_bar.getheight() / 2;

    pos_img_1P_winner.x = pos_img_winner_bar.x + img_winner_bar.getwidth() / 2 - img_1P_winner.getwidth() / 2;
    pos_img_1P_winner.y = getheight() / 2 - img_1P_winner.getheight() / 2;

    pos_img_2P_winner.x = pos_img_winner_bar.x + img_winner_bar.getwidth() / 2 - img_2P_winner.getwidth() / 2;
    pos_img_2P_winner.y = getheight() / 2 - img_2P_winner.getheight() / 2;


    platform_list.clear();
    platform_list.resize(4);

    Platform& large_platform = platform_list[0];
    large_platform.setImage(&img_platform_large);
    large_platform.setRenderPosition(pos_render_large_platform.x, pos_render_large_platform.y);
    large_platform.setTouchPosition(pos_render_large_platform.y + 60,
        pos_render_large_platform.x + 30, pos_render_large_platform.x + img_platform_large.getwidth() - 30);

    Platform& small_platform_1 = platform_list[1];
    small_platform_1.setImage(&img_platform_small);
    small_platform_1.setRenderPosition(pos_render_small_platform_1.x, pos_render_small_platform_1.y);
    small_platform_1.setTouchPosition(pos_render_small_platform_1.y + img_platform_small.getheight() / 2,
        pos_render_small_platform_1.x + 40, pos_render_small_platform_1.x + img_platform_small.getwidth() - 40);

    Platform& small_platform_2 = platform_list[2];
    small_platform_2.setImage(&img_platform_small);
    small_platform_2.setRenderPosition(pos_render_small_platform_2.x, pos_render_small_platform_2.y);
    small_platform_2.setTouchPosition(pos_render_small_platform_2.y + img_platform_small.getheight() / 2,
        pos_render_small_platform_2.x + 40, pos_render_small_platform_2.x + img_platform_small.getwidth() - 40);

    Platform& small_platform_3 = platform_list[3];
    small_platform_3.setImage(&img_platform_small);
    small_platform_3.setRenderPosition(pos_render_small_platform_3.x, pos_render_small_platform_3.y);
    small_platform_3.setTouchPosition(pos_render_small_platform_3.y + img_platform_small.getheight() / 2,
        pos_render_small_platform_3.x + 40, pos_render_small_platform_3.x + img_platform_small.getwidth() - 40);

    timer_cursor_display.setWaitTime(1500);
    timer_cursor_display.setOneShot(true);
    timer_cursor_display.setShotCallback(
        [&]() {
            is_cursor_display = false;
        }
    );
    timer_cursor_display.restart();

    timer_win_img_stay.setWaitTime(3000);
    timer_win_img_stay.setOneShot(true);
    timer_win_img_stay.setShotCallback(
        [&]() {
            scene_manager->switchTo(SceneManager::SceneType::Menu);
        }
    );
    timer_win_img_stay.restart();

    // ����p1ͷ��
    switch (player_1->getType())
    {
    case PlayerType::PeaShooter:
        status_bar_p1.set_avatar(&img_avatar_peashooter);
        break;
    case PlayerType::SunFlower:
        status_bar_p1.set_avatar(&img_avatar_sunflower);
        break;
	case PlayerType::GloomShroom:
		status_bar_p1.set_avatar(&img_avatar_gloomshroom);
		break;
	case PlayerType::Nut:
		status_bar_p1.set_avatar(&img_avatar_nut);
		break;
    }

    // ����p2ͷ��
    switch (player_2->getType())
    {
    case PlayerType::PeaShooter:
        status_bar_p2.set_avatar(&img_avatar_peashooter);
        break;
    case PlayerType::SunFlower:
        status_bar_p2.set_avatar(&img_avatar_sunflower);
        break;
    }

    status_bar_p1.set_position(235, 625);
    status_bar_p2.set_position(675, 625);
}

//��������

void GameScene::onUpdate(int delta)
{
    player_1->onUpdate(delta);
    player_2->onUpdate(delta);

    main_camera.onUpdate(delta);

    // ɾ����ɾ�����ӵ�������erase����Ϊ��new�����ı���Ҫdelete����ָ�룩�����ڴ�й¶��
    for (int i = 0; i < bullet_list.size(); i++)
    {
        if (bullet_list[i]->checkCanRemove())
        {
            delete bullet_list[i];
            std::swap(bullet_list[i], bullet_list.back());
            bullet_list.pop_back();
        }
    }

    for (Bullet* bullet : bullet_list)
    {
        bullet->onUpdate(delta);
    }

    timer_cursor_display.onUpdate(delta);

    // ������Ļ������Ѫ��
    if (player_1->getPosition().y > getheight())
        player_1->set_hp(0);
    if (player_2->getPosition().y > getheight())
        player_2->set_hp(0);

    status_bar_p1.set_hp(player_1->get_hp());
    status_bar_p1.set_mp(player_1->get_mp());
    status_bar_p2.set_hp(player_2->get_hp());
    status_bar_p2.set_mp(player_2->get_mp());

    if (player_1->check_die() || player_2->check_die())
    {
        if (is_game_over == false)	// ������ж���Ϊ�˷�ֹ�ظ��ж���Ϸ����
        {
            mciSendString("stop bgm_game", NULL, 0, NULL);
            mciSendString("play ui_win from 0", NULL, 0, NULL);
            is_game_over = true;
            is_win_img_slide = true;
            id_winner = (player_1->check_die()) ? PlayerID::P2 : PlayerID::P1;
        }
    }

    if (is_game_over)
    {
        // ʤ��ͼƬ�����ұ߽�Ͳ��ٻ���
        if (pos_img_winner_bar.x + img_winner_bar.getwidth() >= getwidth())
        {
            is_win_img_slide = false;
        }

        if (is_win_img_slide)
        {
            pos_img_winner_bar.x += win_img_slide_speed * delta;
            switch (id_winner)
            {
            case P1:
                pos_img_1P_winner.x += win_img_slide_speed * delta;
                break;
            case P2:
                pos_img_2P_winner.x += win_img_slide_speed * delta;
                break;
            default:
                break;
            }
        }
        else
        {
            timer_win_img_stay.onUpdate(delta);
        }
    }

}

//��Ⱦ��ͼ

void GameScene::onDraw(const Camera& camera)
{
    putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
    putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);
    putimage_alpha(camera, pos_render_large_platform.x, pos_render_large_platform.y, &img_platform_large);

    for (Platform& platform : platform_list)
    {
        platform.onDraw(camera);
    }

    if (is_debug)
    {
        settextcolor(RED);
        outtextxy(15, 15, "����ģʽ�ѿ�������'Q'���ر�");
    }

    player_1->onDraw(camera);
    player_2->onDraw(camera);

    if (is_cursor_display)
    {
        POINT position_p1_cursor, position_p2_cursor;
        position_p1_cursor.x = player_1->getPosition().x + player_1->getSize().x / 2 - img_1P_cursor.getwidth() / 2;
        position_p1_cursor.y = player_1->getPosition().y - img_1P_cursor.getheight();
        position_p2_cursor.x = player_2->getPosition().x + player_2->getSize().x / 2 - img_2P_cursor.getwidth() / 2;
        position_p2_cursor.y = player_2->getPosition().y - img_2P_cursor.getheight();

        putimage_alpha(camera, position_p1_cursor.x, position_p1_cursor.y, &img_1P_cursor);
        putimage_alpha(camera, position_p2_cursor.x, position_p2_cursor.y, &img_2P_cursor);
    }

    for (Bullet* bullet : bullet_list)
    {
        bullet->onDraw(camera);
		if (bullet->getType() == BulletType::BubblesBullet_ex_)
		{
			std::cout << "(" << bullet->getPosition().x << "," << bullet->getPosition().y << ")" << std::endl;
		}
    }
    if (is_game_over)
    {
        putimage_alpha(camera, pos_img_winner_bar.x, pos_img_winner_bar.y, &img_winner_bar);
        switch (id_winner)
        {
        case P1:
            putimage_alpha(camera, pos_img_1P_winner.x, pos_img_1P_winner.y, &img_1P_winner);
            break;
        case P2:
            putimage_alpha(camera, pos_img_2P_winner.x, pos_img_2P_winner.y, &img_2P_winner);
            break;
        default:
            break;
        }
    }
    else
    {
        status_bar_p1.on_draw();
        status_bar_p2.on_draw();
    }
}

//��������

void GameScene::onInput(const ExMessage& msg)
{
    player_1->onInput(msg);
    player_2->onInput(msg);

    switch (msg.message)
    {
    case WM_KEYUP:
        switch (msg.vkcode)
        {
        case 0x51:	//'Q' ����or�رյ���ģʽ
            is_debug = !is_debug;
            break;
        }
        break;

    default:
        break;
    }

}

//�˳�����

void GameScene::onExit()
{
    mciSendString("stop bgm_game", NULL, 0, NULL);

    is_debug = false;

    delete player_1;	player_1 = nullptr;
    delete player_2;	player_2 = nullptr;

    for (Bullet* bullet : bullet_list)
        delete bullet;
    bullet_list.clear();

    main_camera.reset();
}
