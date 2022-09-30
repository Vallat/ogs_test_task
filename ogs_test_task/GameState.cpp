#include "GameState.h"


GameState::GameState(Renderer* renderer_)
{
	GameState::renderer = renderer_;
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
	return renderer;
}
