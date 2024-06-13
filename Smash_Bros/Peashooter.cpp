#include "Peashooter.h"

Peashooter::Peashooter()
{
    Type = PlayerType::PeaShooter;

    // 给current animation赋初值
    animation_current = &animation_idle_right;

    animation_idle_left.setAtlas(&atlas_peashooter_idle_left);
    animation_idle_left.setInterval(100);
    animation_idle_left.setLoop(true);

    animation_idle_right.setAtlas(&atlas_peashooter_idle_right);
    animation_idle_right.setInterval(100);
    animation_idle_right.setLoop(true);

    animation_run_left.setAtlas(&atlas_peashooter_run_left);
    animation_run_left.setInterval(100);
    animation_run_left.setLoop(true);

    animation_run_right.setAtlas(&atlas_peashooter_run_right);
    animation_run_right.setInterval(100);
    animation_run_right.setLoop(true);

    animation_die_left.setAtlas(&atlas_peashooter_die_left);
    animation_die_left.setInterval(100);
    animation_die_left.setLoop(false);

    animation_die_right.setAtlas(&atlas_peashooter_die_right);
    animation_die_right.setInterval(100);
    animation_die_right.setLoop(false);

    animation_attack_ex_left.setAtlas(&atlas_peashooter_attack_ex_left);
    animation_attack_ex_left.setInterval(75);
    animation_attack_ex_left.setLoop(true);

    animation_attack_ex_right.setAtlas(&atlas_peashooter_attack_ex_right);
    animation_attack_ex_right.setInterval(75);
    animation_attack_ex_right.setLoop(true);



    timer_attack_ex.setOneShot(true);
    timer_attack_ex.setWaitTime(attack_ex_duration);
    timer_attack_ex.setShotCallback(
        [&]() {
            is_attacking_ex = false;
        }
    );

    timer_spawn_pea_ex.setOneShot(false);
    timer_spawn_pea_ex.setWaitTime(100);	// 特殊攻击时子弹生成间隔
    timer_spawn_pea_ex.setShotCallback(
        [&]() {
            spawn_pea_bullet(speed_pea_ex);
        }
    );

    attack_cd = 200;
    timer_attack_cd.setWaitTime(attack_cd);
}

void Peashooter::onAttack()
{
    spawn_pea_bullet(speed_pea);
}

void Peashooter::onAttack_ex()
{
    is_attacking_ex = true;
    timer_attack_ex.restart();

    animation_attack_ex_left.reset();
    animation_attack_ex_right.reset();

    // mciSendString("play pea_shoot_ex from 0", NULL, 0, NULL);

}

void Peashooter::onUpdate(int delta)
{
    Player::onUpdate(delta);

    if (is_attacking_ex)
    {
        timer_attack_ex.onUpdate(delta);

        timer_spawn_pea_ex.onUpdate(delta);

        main_camera.shake(5, 100);
    }
}

void Peashooter::spawn_pea_bullet(double speed)	//生成子弹（生成子弹与攻击分成两个函数，是因为特殊与普通攻击都要生成子弹，且子弹都一样，所以生成子弹单独封装成函数。sunflower就不是这样了）
{
    Bullet* bullet = new PeaBullet();

    Vector2 bullet_velocity, bullet_position;

    const Vector2& bullet_size = bullet->getSize();

    bullet_position.y = position.y;
    bullet_velocity.y = 0;

    if (is_facing_left)
    {
        bullet_position.x = position.x - bullet_size.x / 2;
        bullet_velocity.x = -speed;
    }
    else
    {
        bullet_position.x = position.x + size.x - bullet_size.x / 2;
        bullet_velocity.x = speed;
    }

    bullet->setPosition(bullet_position.x, bullet_position.y);
    bullet->setVelocity(bullet_velocity.x, bullet_velocity.y);

    bullet->setTarget(ID == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
    bullet->setTouchCallback(
        [&]() {
            mp += 25;
        }
    );

    bullet_list.push_back(bullet);

    switch (rand() % 2)
    {
    case 0:
        mciSendString("play pea_shoot_1 from 0", NULL, 0, NULL);
        break;
    case 1:
        mciSendString("play pea_shoot_2 from 0", NULL, 0, NULL);
        break;
    }

}
