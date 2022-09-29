#pragma once
#include "GameState.h"
class SlotSpinning :
	public GameState
{
public:
	SlotSpinning();
	bool process() override;
};

