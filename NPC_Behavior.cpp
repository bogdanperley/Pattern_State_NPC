#include "NPC_Behavior.h"
#include<thread>
constexpr int small_enemy{ 2 };
constexpr int big_enemy{ 5 };
constexpr int NPC_Wounded{ 1 };
constexpr int NPC_wounded_enemy{ 5 };
constexpr int NPC_DIED{ 2 };
constexpr int NPC_could_run{ 4 };
constexpr int not_possible_to_restore_energy{ 1 };

bool NPC::has_energy() { return energy_ > 50; }

void NPC::Run() { state_ = new On_guard(); } // TO DO


void NPC::On_guard() {
    auto random{ rand() % 5 };
    while (random != small_enemy && random != big_enemy) {
        std::cout << "NPC On guard!" << std::endl;
        random = rand() % 5;
    }
    if (random == small_enemy) {
        std::thread th{ [this]() {
           state_->see_small_enemy();
        } };
        th.detach();
        return;
    }
    std::thread th{ [this]() {
    state_->see_big_enemy();
    } };
    th.detach();
}

void NPC::Fight() {
    auto random{ rand() % 6 };

    while (random != NPC_Wounded) {
        if (random == NPC_wounded_enemy) {
            std::cout << "NPC wounded the enemy!" << std::endl;
            break;
        }
        std::cout << "NPC and enemy missed!" << std::endl;
        random = rand() % 6;
    }
    if (random == NPC_Wounded) {
        std::cout << "NPC Wounded!" << std::endl;
        energy_ -= 50;
        if (has_energy()) {
            std::thread th{ [this]() {
                state_->energy_Ok();
            } };
            th.detach();
            return;
        }
        std::thread th{ [this]() {
            state_->losing_fight();
        } };
        th.detach();
    }
}

void NPC::Run_away() {
    auto random{ rand() % 5 };
    while (random != NPC_DIED && random != NPC_could_run) {
        std::cout << " NPC running! " << std::endl;
        random = rand() % 5;
    }
    if (random == NPC_DIED) {
        std::cout << "NPC could not escape from a big enemy, NPC DIED!"
            << std::endl;
        std::thread th{ [this]() {
            state_->died();
        } };
        th.detach();
        return;
    }
    std::cout << " Ran away from the big enemy " << std::endl;
    std::thread th{ [this]() {
        state_->escaped();
    } };
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
    auto state_died = Game_->get_State_Died();
    state_died->died();
    state_died->call_Next_NPC();
    delete NPC_;
}

Pool_NPC::Pool_NPC(int countNPC) {
    for (int i{}; i < countNPC; ++i) {
        poollNPC.push_back(new NPC{});
    }
}

NPC* Pool_NPC::getNextNPC() {
    auto npc{ poollNPC.back() };
    poollNPC.pop_back();
    return npc;
}

void Game::Run_NPCs() { poollNpc.getNextNPC()->Run(); }

State* Game::get_State_Died()
{
    return state_died;
}

void Died::call_Next_NPC() { Game_->Run_NPCs(); }
