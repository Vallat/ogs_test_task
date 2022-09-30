#pragma once
#include "GameState.h"
#include "SlotRow.h"
#include "Globals.h"
#include <random>


class SlotSpinning :
	public GameState
{
public:
	SlotSpinning(Renderer* renderer_);
	bool process() override;
	void on_wait() override;
	void on_state_change() override;
	bool handle_keyboard_input();

private:
	SlotRow* rows_array[ROWS_AMOUNT];
};

