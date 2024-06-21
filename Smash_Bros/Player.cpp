#include "Player.h"

Player::Player()
{
    timer_attack_cd.setWaitTime(attack_cd);
    timer_attack_cd.setOneShot(true);
    timer_attack_cd.setShotCallback(
        [&]() {
            can_attack = true;
        }
    );

    timer_invulnerable.setWaitTime(750);
    timer_invulnerable.setOneShot(true);
    timer_invulnerable.setShotCallback(
        [&]() {
            is_invulnerable = false;
        }
    );

    timer_invulnerable_blink.setWaitTime(75);
    timer_invulnerable_blink.setOneShot(false);
    timer_invulnerable_blink.setShotCallback(
        [&]() {
            is_showing_white_frame = !is_showing_white_frame;
        }
    );

    timer_run_effect_generation.setWaitTime(75);
    timer_run_effect_generation.setOneShot(false);
    timer_run_effect_generation.setShotCallback(
        [&]() {
            Vector2 particle_position;
            IMAGE* frame = atlas_run_effect.getImage(0);
            particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
            particle_position.y = position.y + size.y - frame->getheight();
            particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
        }
    );

    timer_die_effect_generation.setWaitTime(35);
    timer_die_effect_generation.setOneShot(false);
    timer_die_effect_generation.setShotCallback(
        [&]() {
            Vector2 particle_position;
            IMAGE* frame = atlas_run_effect.getImage(0);
            particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
            particle_position.y = position.y + size.y - frame->getheight();
            particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
        }
    );

    animation_jump_effect.setAtlas(&atlas_jump_effect);
    animation_jump_effect.setInterval(25);
    animation_jump_effect.setLoop(false);
    animation_jump_effect.set_Callback(
        [&]() {
            is_jump_effect_visible = false;
        }
    );

    animation_land_effect.setAtlas(&atlas_land_effect);
    animation_land_effect.setInterval(50);
    animation_land_effect.setLoop(false);
    animation_land_effect.set_Callback(
        [&]() {
            is_land_effect_visible = false;
        }
    );
}

const Vector2& Player::getPosition() const
{
    return position;
}

const Vector2& Player::getSize() const
{
    return size;
}

void Player::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void Player::setID(PlayerID in_ID)
{
    ID = in_ID;
}

PlayerID Player::getID() const
{
    return ID;
}

void Player::setType(PlayerType in_Type)
{
    Type = in_Type;
}

PlayerType Player::getType() const
{
    return Type;
}

void Player::setFacingleft(bool in)
{
    is_facing_left = in;
}

int Player::get_hp() const
{
    return hp;
}

void Player::set_hp(int val)
{
    hp = val;
}

int Player::get_mp() const
{
    return mp;
}

bool Player::check_die() const
{
    return is_die;
}

void Player::set_velocity_die(double x, double y)
{
    Vector2 velocity_input(x, y);
    velocity_die += velocity_input.normalize();
}

void Player::onUpdate(int delta)
{
    int direction = is_right_btn_down - is_left_btn_down;

    if (direction != 0)
    {
        if (!is_attacking_ex)
            is_facing_left = (direction < 0);

        if (direction < 0)
        {
            animation_current = &animation_run_left;
        }
        else
        {
            animation_current = &animation_run_right;
        }

        double distance = direction * run_velocity * delta;
        onRun(distance);
    }
    else //direction == 0
    {
        animation_current = is_facing_left ? &animation_idle_left : &animation_idle_right;
        timer_run_effect_generation.pause();	// 不动就不产生粒子
    }

    if (is_attacking_ex)
    {
        animation_current = is_facing_left ? &animation_attack_ex_left : &animation_attack_ex_right;
    }

    animation_current->onUpdate(delta);
    animation_jump_effect.onUpdate(delta);
    animation_land_effect.onUpdate(delta);

    moveAndTouch(delta);

    timer_attack_cd.onUpdate(delta);
    timer_invulnerable.onUpdate(delta);
    timer_invulnerable_blink.onUpdate(delta);
    timer_run_effect_generation.onUpdate(delta);

    if (hp <= 0)
    {
        timer_die_effect_generation.onUpdate(delta);
    }

    for (int i = 0; i < particle_list.size(); i++)
    {
        if (!(particle_list[i].check_valid()))
        {
            std::swap(particle_list[i], particle_list.back());
            particle_list.pop_back();
        }
        else
        {
            particle_list[i].on_update(delta);
        }
    }

    if (is_showing_white_frame)
    {
        white_image(animation_current->getCurrentFrame(), &img_white);
    }

    if (hp <= 0 && !is_die)
    {
        is_die = true;
        onDie();
    }

}

void Player::onDraw(const Camera& camera)
{
    if (is_jump_effect_visible)
    {
        animation_jump_effect.onDraw(camera, position_jump_effect.x, position_jump_effect.y);
    }
    if (is_land_effect_visible)
    {
        animation_land_effect.onDraw(camera, position_land_effect.x, position_land_effect.y);
    }

    for (const Particle& particle : particle_list)
    {
        particle.on_draw(camera);
    }

    if (is_invulnerable && is_showing_white_frame)
    {
        putimage_alpha(camera, position.x, position.y, &img_white);
    }
    else
    {
        animation_current->onDraw(camera, (int)position.x, (int)position.y);
    }

    if (is_debug)
    {
        setlinecolor(YELLOW);
        line_alpha(camera, position.x, position.y, position.x + size.x, position.y);
        line_alpha(camera, position.x, position.y, position.x, position.y + size.y);
        line_alpha(camera, position.x + size.x, position.y, position.x + size.x, position.y + size.y);
        line_alpha(camera, position.x, position.y + size.y, position.x + size.x, position.y + size.y);
    }
}

void Player::onInput(const ExMessage& msg)
{
    // 如果已死亡就不能操作
    if (is_die)
        return;

    switch (msg.message)
    {
    case WM_KEYDOWN:
        switch (ID)
        {
        case PlayerID::P1:
            switch (msg.vkcode)
            {
            case 0x41:	//'A'
                is_left_btn_down = true;
                break;
            case 0x44:	//'D'
                is_right_btn_down = true;
                break;
            case 0x57:	//'W'
                onJump();
                break;
            case 0x46:	//'F'
                if (can_attack)
                {
                    onAttack();
                    can_attack = false;
                    timer_attack_cd.restart();
                }
                break;
            case 0x47:	//'G'
                if (mp >= 100)
                {
                    onAttack_ex();
                    mp = 0;
                }
                break;
            }
            break;

        case PlayerID::P2:
            switch (msg.vkcode)
            {
            case VK_LEFT:	//'←'
                is_left_btn_down = true;
                break;
            case VK_RIGHT:	//'→'
                is_right_btn_down = true;
                break;
            case VK_UP:		//'↑'
                onJump();
                break;
            case VK_OEM_PERIOD:	//'.'
                if (can_attack)
                {
                    onAttack();
                    can_attack = false;
                    timer_attack_cd.restart();
                }
                break;
            case VK_OEM_2:	//'/'
                if (mp >= 100)
                {
                    onAttack_ex();
                    mp = 0;
                }
                break;

            }
            break;
        }
        break;

    case WM_KEYUP:
        switch (ID)
        {
        case PlayerID::P1:
            switch (msg.vkcode)
            {
            case 0x41:	//'A'
                is_left_btn_down = false;
                break;
            case 0x44:	//'D'
                is_right_btn_down = false;
                break;
            }
            break;

        case PlayerID::P2:
            switch (msg.vkcode)
            {
            case VK_LEFT:	//'←'
                is_left_btn_down = false;
                break;
            case VK_RIGHT:	//'→'
                is_right_btn_down = false;
                break;
            }
            break;
        }
        break;
    }
}

void Player::onRun(double distance)
{
    if (is_attacking_ex)
        return;

    position.x += distance;
    timer_run_effect_generation.resume();
}

void Player::onAttack()
{

}

void Player::onAttack_ex()
{

}

void Player::moveAndTouch(int delta)
{
    double last_y = position.y;
    double last_velocity_y = velocity.y;

    // 模拟重力
    velocity.y += gravity * delta;	//v = v0 + at
    position += velocity * (double)delta;	//y = y0 + vt
    //这里用向量运算而不是y方向的标量运算，这样可以在速度不垂直向下的时候依旧有效。（通用性）

    if (!is_die)	// 非死亡状态才能被平台碰撞
    {
        for (Platform& platform : platform_list)
        {
            int left = (int)platform.getLeft();
            int right = (int)platform.getRight();
            int y = (int)platform.getY();


            if (velocity.y > 0)	//玩家下坠时才判断
            {
                if (last_y + size.y <= y && position.x < right && position.x + size.x > left && position.y <= y && position.y + size.y >= y)
                {
                    // velocity = 0;
                    velocity.y = 0;	// 碰到平台，y速度置0
                    position.y = y - size.y;

                    if (last_velocity_y != 0)
                        onLand();

                    break;
                }
            }
        }
    }

    if (!is_invulnerable)	//非无敌状态才能被子弹碰撞
    {
        for (Bullet* bullet : bullet_list)
        {
            // 如果没失效或者子弹目标不是自己，就跳过
            if (!(bullet->getValid()) || bullet->getTarget() != ID)
                continue;

            if (bullet->checkTouch(position, size))
            {
                bullet->onTouch();
                bullet->setValid(false);
                hp -= bullet->getDamage();
                if (hp <= 0)
                {
                    POINT pos_player_center, pos_bullet_center;
                    pos_player_center.x = position.x + size.x / 2;
                    pos_player_center.y = position.y + size.y / 2;
                    pos_bullet_center.x = bullet->getPosition().x + bullet->getSize().x / 2;
                    pos_bullet_center.y = bullet->getPosition().y + bullet->getSize().y / 2;

                    set_velocity_die(pos_player_center.x - pos_bullet_center.x, pos_player_center.y - pos_bullet_center.y);
                }
                make_invulnerable();
            }
        }
    }
}

void Player::onJump()
{ 
	if (is_attacking_ex)	//特殊攻击禁止移动
        return;

    if (velocity.y != 0)	//防止重复跳跃
        return;

    is_jump_effect_visible = true;
    animation_jump_effect.reset();

    IMAGE* effect_frame = animation_jump_effect.getCurrentFrame();

    position_jump_effect.x = position.x + size.x / 2 - effect_frame->getwidth() / 2;
    position_jump_effect.y = position.y + size.y - effect_frame->getheight();

    velocity += jump_velocity;
}

void Player::onLand()
{
    is_land_effect_visible = true;
    animation_land_effect.reset();

    IMAGE* effect_frame = animation_land_effect.getCurrentFrame();

    position_land_effect.x = position.x + size.x / 2 - effect_frame->getwidth() / 2;
    position_land_effect.y = position.y + size.y - effect_frame->getheight();

}

void Player::make_invulnerable()
{
    is_invulnerable = true;
    timer_invulnerable.restart();
    // timer_invulnerable_blink.restart();	// 其实程序一直在加载闪白，只是通过is_showing布尔变量来控制是否显示处闪白效果而已
}

void Player::onDie()
{
    velocity += velocity_die;
    animation_current = velocity.x <= 0 ? &animation_die_left : &animation_die_right;
}
