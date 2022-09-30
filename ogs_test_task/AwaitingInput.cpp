#include "AwaitingInput.h"

AwaitingInput::AwaitingInput(Renderer* renderer_) : GameState::GameState(renderer_) {}


bool AwaitingInput::process()
{
	if (AwaitingInput::handle_keyboard_input())
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


bool AwaitingInput::handle_keyboard_input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		return true;
	}
	return false;
}
