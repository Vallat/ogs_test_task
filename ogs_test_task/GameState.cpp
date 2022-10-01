#include "GameState.h"


GameState::GameState(Renderer* renderer_)
{
	if (renderer == nullptr)
	{
		throw std::runtime_error("GameStateL Tried to initialize one of game states without renderer!");
	}
	renderer = renderer_;
}


void GameState::on_state_change()
{
	active = !active;
}


bool GameState::is_active()
{
	return active;
}


Renderer* GameState::access_renderer()
{
	if (renderer == nullptr)
	{
		throw std::runtime_error("GameState: Renderer was not initialized!");
	}
	return renderer;
}


bool GameState::user_pressed_enter()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		return true;
	}
	return false;
}
