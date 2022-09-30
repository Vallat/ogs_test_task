#include "AwaitingInput.h"

AwaitingInput::AwaitingInput(Renderer* renderer_) : GameState::GameState(renderer_) {}


bool AwaitingInput::process()
{
	if (GameState::user_pressed_enter())
	{
		return false;
	}
	return true;
}


void AwaitingInput::on_wait() { return; }


void AwaitingInput::on_state_change()
{
	GameState::on_state_change();
}

