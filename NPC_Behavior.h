#pragma once
#include <iostream>
#include <vector>

class Pool_NPC {
public:
    Pool_NPC() = default;
    Pool_NPC(int countNPC);
    NPC* getNextNPC(); 

private:
    std::vector<NPC*> poollNPC;
};

class Game {
public:
    Game() : state_died{ new Died(this) } { }
    Game(int countNPC) : poollNpn{ countNPC } {};
    void Run_NPCs();
    State* get_State_Died();

private:
    State* state_died;
    Pool_NPC poollNpn;
};

class NPC {
public:
    NPC() = default;
    void change_state(State* state) {
        delete state_;
        state_ = state;
    };
    void On_guard();
    void Run_away();
    void Fight();
    bool has_energy();
    void Run();

private:
    State* state_{ nullptr };
    int energy_{ 100 };
};
class State {
public:
    State(NPC* npc) : NPC_{ npc } {}
    State(Game* game) : Game_{ game } {}
    virtual void see_small_enemy() {
        std::cout << "NOT IMPLEMENTED!" << std::endl;
    }
    virtual void see_big_enemy() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
    virtual void losing_fight() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
    virtual void escaped() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
    virtual void set_Npc(State* state) {
        std::cout << "NOT IMPLEMENTED!" << std::endl;
    }
    virtual void died() { std::cout << "NOT IMPLEMENTED!" << std::endl; };
    virtual void energy_Ok() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
    virtual void call_Next_NPC() {
        std::cout << "NOT IMPLEMENTED!" << std::endl;
    };

protected:
    NPC* NPC_{ nullptr };
    Game* Game_{ nullptr };
};

class On_guard : public State {
public:
    using State::State;
    void see_small_enemy() override;
    void see_big_enemy() override;
};

class Fight : public State {
public:
    using State::State;
    void losing_fight() override;
    void energy_Ok() override;
};

class Run_away : public State {
public:
    using State::State;
    void escaped() override;
    void died() override;
};
class Died : public State {
public:
    using State::State;
    void call_Next_NPC() override;
};
