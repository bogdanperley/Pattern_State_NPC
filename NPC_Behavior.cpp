#include "NPC_Behavior.h"
constexpr int small_enemy{ 2 };
constexpr int big_enemy{ 5 };
constexpr int NPC_Wounded{ 1 };
constexpr int NPC_wounded_enemy{5};
constexpr int NPC_DIED{ 2 };
constexpr int NPC_could_run{ 4 };
constexpr int not_possible_to_restore_energy{ 1 };

NPC::NPC() : state_{ new On_guard(state_) } {}

bool NPC::has_energy() { return energy_ > 50; }

void NPC::Run()
{
    state_ = new On_guard();
}

void NPC::On_guard() {
    auto random{ rand() % 5 };
    while (random != small_enemy && random != big_enemy) {
        std::cout << "NPC On guard!" << std::endl;
    }
    if (random == small_enemy) {
        state_->see_small_enemy();
        return;
    }
    state_->see_big_enemy();
}

void NPC::Fight() {
    auto random{ rand() % 6 };

    while (random != NPC_Wounded && random != NPC_wounded_enemy) {
        std::cout << "NPC Fight!" << std::endl;
    }
    if (random == NPC_wounded_enemy) {
        std::cout << "NPC wounded the enemy!" << std::endl;
    }
    if (random == NPC_Wounded) {
        std::cout << "NPC Wounded!" << std::endl;
        energy_ -= 50;
        if (has_energy()) {
            state_->energy_Ok();
            return;
        }
        state_->losing_fight();
    }
}

void NPC::Run_away() {
    if (has_energy()) {
        auto random{ rand() % 5 };
        while (random != NPC_DIED && random != NPC_could_run) {
            std::cout << " NPC running! " << std::endl;
        }
            if (random == NPC_DIED) {
                std::cout << "NPC could not escape from a big enemy, NPC DIED!"
                    << std::endl;
                state_->died();
                return;
            }
            if (random == NPC_could_run) {
                std::cout << " Ran away from the big enemy " << std::endl;
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

void Fight::energy_Ok() { NPC_->Fight(); }

void Run_away::escaped() {
    NPC_->change_state(new On_guard(NPC_));
    NPC_->On_guard();
}

void Run_away::died() {
    std::cout << " NPC object died!" << std::endl;
   
}

Pool_NPC::Pool_NPC(int countNPC)
{
    for (int i{}; i < countNPC; ++i) {
        poollNPC.push_back(new NPC{});
    }
}

NPC* Pool_NPC::getNextNPC()
{
    auto npc{ poollNPC.back() };
    poollNPC.pop_back();
    return npc;
}

void Game::Run_NPCs()
{

}
