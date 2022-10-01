#pragma once

#include "AwaitingInput.h"
#include "SlotSpinning.h"
#include "ResultDisplay.h"
#include "Renderer.h"

enum class States
{
	AWAITING_INPUT,
	SLOT_SPINNING,
	DISPLAYING_RESULT,
};

class StateMachine
{
public:
	StateMachine(Renderer* renderer);
	void process();
	void set_state(States new_state);

	bool awaiting_input_process();
	bool slot_spinning_process();
	bool result_display_process();

private:
	States current_state = States::AWAITING_INPUT;

	AwaitingInput* awaiting_input = nullptr;
	SlotSpinning* slot_spinning = nullptr;
	ResultDisplay* result_display = nullptr;
};

