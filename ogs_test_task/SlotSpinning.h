#pragma once
#include "GameState.h"
#include "SlotRow.h"
#include "Globals.h"


class SlotSpinning :
	public GameState
{
public:
	SlotSpinning(Renderer* renderer_);
	bool process() override;
	void on_wait() override;
	void on_state_change() override;

private:
	SlotRow* rows_array[SYMBOLS_AMOUNT];
};

