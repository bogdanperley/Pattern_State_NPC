#include "NPC_Behavior.h"
NPC::NPC() : state_{ new On_guard(state_) } {}

bool NPC::has_energy() { return energy_ > 50; }


void NPC::On_guard() {
    constexpr int see_small_enemy{ 2 };
    constexpr int see_big_enemy{ 5 };
    auto random{ rand() % 5 };
    while (random == see_small_enemy || random == see_big_enemy)
    {
        if (random == see_small_enemy) {
            state_->see_small_enemy();
            return;
        }
        if (random == see_big_enemy) {
            state_->see_big_enemy();
            return;
        }
      std::cout << "NPC On guard!" << std::endl;
    }
}

void NPC::call_energy_ok() { Fight(); } // TO DO

void NPC::Fight() {
    auto random{ rand() % 2 };
    constexpr int NPC_Wounded{ 2 };
    if (random == NPC_Wounded) {
        std::cout << "NPC Wounded!" << std::endl;
        energy_ -= 50;
    }
    else {
        std::cout << "NPC wounded the enemy!" << std::endl;
    }
    if (has_energy()) {
        this->call_energy_ok();
        return;
    }
    state_->losing_fight();
}

void NPC::Run_away() {
    if (has_energy()) {
        auto random{ rand() % 3 };
        constexpr int NPC_DIED{ 2 };
        if (random == NPC_DIED) {
            std::cout << "NPC could not escape from a big enemy, NPC DIED!"
                << std::endl;
            delete state_;
            return;
        }
        else {
            std::cout << " Ran away from the big enemy " << std::endl;
            state_->escaped();
        }
    }
    else {
        auto random{ rand() % 2 };
        constexpr int not_possible_to_restore_energy{ 1 };
        if (random == not_possible_to_restore_energy) {
            std::cout << "It was not possible to restore energy, NPC DIED "
                << std::endl;
            delete state_;
        }
        else {
            std::cout << "Energy recovered " << std::endl;
            energy_ += 50;
            state_->escaped();
        }
    }
}

void On_guard::see_small_enemy() {
    NPC_->change_state(new Fight(NPC_));
    NPC_->Fight();
}

void On_guard::see_big_enemy() {
    NPC_->change_state(new Run_away(NPC_));
    NPC_->Run_away();
}

void Fight::losing_fight() {
    NPC_->change_state(new Run_away(NPC_));
    NPC_->Run_away();
}

void Fight::energy_Ok() { NPC_->change_state( new Fight(NPC_)); }

void Run_away::escaped() {
    NPC_->change_state(new On_guard(NPC_));
    NPC_->On_guard();
}

void Run_away::died() {
    NPC_->change_state(new On_guard(NPC_));
    NPC_->On_guard();
}
