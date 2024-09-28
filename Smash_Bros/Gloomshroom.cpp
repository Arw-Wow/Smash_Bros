#include "Gloomshroom.h"

Gloomshroom::Gloomshroom()
{
	Type = PlayerType::GloomShroom;

	// ��current animation����ֵ
	animation_current = &animation_idle_right;

	animation_idle_left.setAtlas(&atlas_gloomshroom_idle_left);
	animation_idle_left.setInterval(100);
	animation_idle_left.setLoop(true);

	animation_idle_right.setAtlas(&atlas_gloomshroom_idle_right);
	animation_idle_right.setInterval(100);
	animation_idle_right.setLoop(true);

	animation_run_left.setAtlas(&atlas_gloomshroom_run_left);
	animation_run_left.setInterval(100);
	animation_run_left.setLoop(true);

	animation_run_right.setAtlas(&atlas_gloomshroom_run_right);
	animation_run_right.setInterval(100);
	animation_run_right.setLoop(true);

	animation_die_left.setAtlas(&atlas_gloomshroom_die_left);
	animation_die_left.setInterval(100);
	animation_die_left.setLoop(false);

	animation_die_right.setAtlas(&atlas_gloomshroom_die_right);
	animation_die_right.setInterval(100);
	animation_die_right.setLoop(false);

	animation_attack_ex_left.setAtlas(&atlas_gloomshroom_attack_ex_left);
	animation_attack_ex_left.setInterval(75);
	animation_attack_ex_left.setLoop(true);

	animation_attack_ex_right.setAtlas(&atlas_gloomshroom_attack_ex_right);
	animation_attack_ex_right.setInterval(75);
	animation_attack_ex_right.setLoop(true);


	timer_attack_ex.setOneShot(true);
	timer_attack_ex.setWaitTime(attack_ex_duration);
	timer_attack_ex.setShotCallback(
		[&]() {
			is_attacking_ex = false;
		}
	);

	timer_bubbles_ex.setOneShot(false);
	timer_bubbles_ex.setWaitTime(250);	// ���⹥��ʱ�ӵ����ɼ��
	timer_bubbles_ex.setShotCallback(
		[&]() {
			spawn_bubbles_bullet_ex();
		}
	);

	attack_cd = 400;
	timer_attack_cd.setWaitTime(attack_cd);
}

void Gloomshroom::onAttack()
{
	spawn_bubbles_bullet();
}

void Gloomshroom::onAttack_ex()
{
	is_attacking_ex = true;
	timer_attack_ex.restart();

	animation_attack_ex_left.reset();
	animation_attack_ex_right.reset();
}

void Gloomshroom::onUpdate(int delta)
{
	Player::onUpdate(delta);
	
	for (Bullet* bullet : bullet_list)
	{
		if (bullet->getType() == BulletType::BubblesBullet_ || bullet->getType() == BulletType::BubblesBullet_ex_)
		{
			BubblesBullet* b = (BubblesBullet*)bullet;
			bullet->setPosition(this->position.x + b->getRenderOffset().x, this->position.y + b->getRenderOffset().y);
		}
	}

	if (is_attacking_ex)
	{
		timer_attack_ex.onUpdate(delta);
		timer_bubbles_ex.onUpdate(delta);

		main_camera.shake(5, 100);
	}
}

void Gloomshroom::spawn_bubbles_bullet()
{
	Bullet* bullet = new BubblesBullet();
	bullet->setType(BulletType::BubblesBullet_);

	bullet->setTarget(ID == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
	bullet->setTouchCallback(
		[&]() {
			mp += 25;
		}
	);

	bullet_list.push_back(bullet);

}

void Gloomshroom::spawn_bubbles_bullet_ex()
{
	Bullet* bullet = new BubblesBullet_ex();
	bullet->setType(BulletType::BubblesBullet_ex_);

	// ���ڲ�֪��ԭ�򣨿����ǲ��Ŷ�����һ֡ʱ��δupdate����ex������һ֡������ڽ�ɫ��ʼ��Ӧλ�ö����ǽ�ɫ��ǰ��Ӧλ�á�
	// ����仰���������ʹ��һ֡����ƫ�ơ�
	bullet->setPosition(this->position.x + ((BubblesBullet_ex*)bullet)->getRenderOffset().x,
						this->position.y + ((BubblesBullet_ex*)bullet)->getRenderOffset().y);

	bullet->setTarget(ID == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
	bullet->setTouchCallback(
		[&]() {
			mp += 25;
		}
	);

	bullet_list.push_back(bullet);
}

void Gloomshroom::onRun(double distance)
{
	position.x += distance;
	timer_run_effect_generation.resume();
}

void Gloomshroom::onJump()
{
	if (velocity.y != 0)	//��ֹ�ظ���Ծ
		return;

	is_jump_effect_visible = true;
	animation_jump_effect.reset();

	IMAGE* effect_frame = animation_jump_effect.getCurrentFrame();

	position_jump_effect.x = position.x + size.x / 2 - effect_frame->getwidth() / 2;
	position_jump_effect.y = position.y + size.y - effect_frame->getheight();

	velocity += jump_velocity;
}

