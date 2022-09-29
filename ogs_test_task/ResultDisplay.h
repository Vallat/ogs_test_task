#pragma once
#include "GameState.h"
class ResultDisplay :
	public GameState
{
public:
	ResultDisplay();
	bool process() override;
};

