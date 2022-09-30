#pragma once
#include "GameState.h"
#include "Button.h"

class AwaitingInput :
	public GameState
{
public:
	AwaitingInput(Renderer* renderer_);
	bool process() override;
	void on_wait() override;
	void on_state_change() override;

private:
	Button* start_button;
};

