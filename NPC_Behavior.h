#pragma once 
#include<vector>
#include<iostream>

class NPC 
{
public:
	NPC();
	void change_state(State* state) 
	{	delete state_;
		state_ = state;
	};
	void On_guard();
	void Run_away();
	void Fight();
	bool has_energy();
	void call_energy_ok();
private:
	State* state_{ nullptr };
	int energy_{ 100 };
};
class State {
public:
	State(NPC* npc) : NPC_{ npc } {}
	virtual void see_small_enemy() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
	virtual void see_big_enemy() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
	virtual void losing_fight() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
	virtual void escaped() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
	virtual void set_Npc() { std::cout << "NOT IMPLEMENTED!" << std::endl; }
protected:
	NPC* NPC_{ nullptr };
};

class On_guard : public State {
public:
	using State::State; //On_guard(NPC* npc):State(npc){ }
	void see_small_enemy() override;
	void see_big_enemy() override;
};

class Fight : public State{
public:
	using State::State; //Fight(NPC* npc) :State(npc) { }
	void losing_fight() override;
	void energy_Ok();
};

class Run_away : public State {
public:
	using State::State; //Run_away(NPC* npc) :State(npc) { }
	void escaped() override;
	void died();
};