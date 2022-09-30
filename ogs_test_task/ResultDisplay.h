#pragma once
#include "GameState.h"
class ResultDisplay :
	public GameState
{
public:
	ResultDisplay(Renderer* renderer_);
	bool process() override;
	void on_wait() override;
	void on_state_change() override;
};

