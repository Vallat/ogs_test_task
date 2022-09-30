#pragma once
#include "GameState.h"
#include "SlotRow.h"
#include <random>
#include "Button.h"


class SlotSpinning :
	public GameState
{
public:
	SlotSpinning(Renderer* renderer_);
	bool process() override;
	void on_wait() override;
	void on_state_change() override;
	size_t calculate_win_size();

private:
	SlotRow* rows_array[ROWS_AMOUNT];
	Button* stop_button;
	bool can_stop = false;
};

