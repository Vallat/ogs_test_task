#pragma once
#include "GameState.h"

class AwaitingInput :
	public GameState
{
public:
	AwaitingInput(Renderer* renderer_);
	bool process() override;
	void on_wait() override;
	void on_state_change() override;
	bool handle_keyboard_input();
};

