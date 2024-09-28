#pragma once

#include "Player.h"

class Nut :
    public Player
{
public:

	Nut();

	~Nut() = default;

	void onAttack() override;

	void onAttack_ex() override;

	void onUpdate(int delta) override;

};

