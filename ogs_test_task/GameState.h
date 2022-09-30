#pragma once

#include "Renderer.h"

class GameState
{
public:
	GameState(Renderer* renderer_);
	virtual bool process() = 0;
	virtual void on_wait() = 0;
	virtual void on_state_change() = 0;
	bool is_active();
	Renderer* access_renderer();

private:
	bool active = false;
	Renderer* renderer = nullptr;
};	

