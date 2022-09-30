#include "ResultDisplay.h"

ResultDisplay::ResultDisplay(Renderer* renderer_) : GameState::GameState(renderer_){}


bool ResultDisplay::process()
{
	return false;
}


void ResultDisplay::on_wait()
{
}


void ResultDisplay::on_state_change()
{
	GameState::on_state_change();
}
