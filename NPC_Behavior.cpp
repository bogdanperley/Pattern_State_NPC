#include "NPC_Behavior.h"


NPC::NPC() : state_{new On_guard(state_)} {}

bool NPC::has_energy() { return this->energy_ > 50;}

void NPC::call_energy_ok()
{
	Fight::energy_Ok;
}

void NPC::On_guard()
{	auto random{ rand() % 5 };
	if (random < 2) {
		state_->see_small_enemy();
		return;
	}
	state_->see_big_enemy();
}

void NPC::Fight()
{
	auto random{ rand() % 2 };
	if (random == 2) {
		std::cout << "NPC Wounded!" << std::endl;
		this->energy_ -= 50;
	}
	else {
		std::cout << "NPC wounded the enemy!" << std::endl;
	}
	if (has_energy() == true) {
		this->call_energy_ok();
		return;
	}
	state_->losing_fight();
}
	

void NPC::Run_away()
{
	if (has_energy() == true) {
		auto random{ rand() % 3 };
		if (random == 2) {
			std::cout << "NPC could not escape from a big enemy, NPC DIED!" << std::endl;
			state_ = nullptr;
			return;
		}
		else
		{
			std::cout << " Ran away from the big enemy " << std::endl;
			state_->escaped();
		}
	}
	else
	{
		auto random{ rand() % 2 };
		if (random == 1) {
			std::cout << "It was not possible to restore energy, NPC DIED " << std::endl;
			state_ = nullptr;
		}
		else
		{
			std::cout << "Energy recovered " << std::endl;
			energy_ += 50;
			state_->escaped();
		}
	}
}


void On_guard::see_small_enemy()
{
	NPC_->change_state(new Fight(NPC_));
	NPC_->Fight();
}

void On_guard::see_big_enemy()
{
	NPC_->change_state(new Run_away(NPC_));
	NPC_->Run_away();
}



void Fight::losing_fight()
{
	NPC_->change_state(new Run_away(NPC_));
	NPC_->Run_away();
}

void Fight::energy_Ok()
{
	NPC_->Fight();
}


void Run_away::escaped()
{
	NPC_->change_state(new On_guard (NPC_));
	NPC_->On_guard();
}

void Run_away::died()
{
	NPC_->change_state(new On_guard(NPC_));
	NPC_->On_guard();
}

