#pragma once
#include "GameState.h"
class AwaitingInput :
	public GameState
{
public:
	AwaitingInput();
	bool process() override;
};

