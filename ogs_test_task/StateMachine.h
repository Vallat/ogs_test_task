#pragma once

class AwaitingInput;
class SlotSpinning;
class ResultDisplay;
class Renderer;

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

	/// <summary>
	/// Calls process() of the AwaitingInput object, returns its result
	/// </summary>
	bool awaiting_input_process();

	/// <summary>
	/// Calls process() of the SlotSpinning object, returns its result
	/// </summary>
	bool slot_spinning_process();

	/// <summary>
	/// Calls process() of the ReslutDisplay object, returns its result
	/// </summary>
	bool result_display_process();

private:
	States current_state = States::AWAITING_INPUT;

	AwaitingInput* awaiting_input = nullptr;
	SlotSpinning* slot_spinning = nullptr;
	ResultDisplay* result_display = nullptr;
};

