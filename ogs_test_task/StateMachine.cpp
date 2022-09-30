#include "StateMachine.h"


StateMachine::StateMachine(Renderer* renderer)
{
	awaiting_input = new AwaitingInput(renderer);
	slot_spinning = new SlotSpinning(renderer);
	result_display = new ResultDisplay(renderer);
	awaiting_input->on_state_change();
}


void StateMachine::process()
{
	awaiting_input->on_wait();
	slot_spinning->on_wait();
	result_display->on_wait();

	switch (StateMachine::current_state)
	{
	case States::AWAITING_INPUT:
		if (!StateMachine::awaiting_input_process())
		{
			StateMachine::set_state(States::SLOT_SPINNING);
		}
		break;
	case States::SLOT_SPINNING:
		if (!StateMachine::slot_spinning_process())
		{
			StateMachine::set_state(States::DISPLAYING_RESULT);
		}
		break;
	case States::DISPLAYING_RESULT:
		if (!StateMachine::result_display_process())
		{
			StateMachine::set_state(States::AWAITING_INPUT);
		}
		break;
	default:
		break;
	}
}


void StateMachine::set_state(States new_state)
{
	current_state = new_state;
	switch (current_state)
	{
	case States::AWAITING_INPUT:
		/// deactivate
		StateMachine::result_display->on_state_change();
		/// activate
		StateMachine::awaiting_input->on_state_change();
		break;
	case States::SLOT_SPINNING:
		StateMachine::awaiting_input->on_state_change();
		StateMachine::slot_spinning->on_state_change();
		break;
	case States::DISPLAYING_RESULT:
		StateMachine::slot_spinning->on_state_change();
		StateMachine::result_display->on_state_change();
		break;
	default:
		break;
	}
}


bool StateMachine::awaiting_input_process()
{
	return StateMachine::awaiting_input->process();
}


bool StateMachine::slot_spinning_process()
{
	return StateMachine::slot_spinning->process();
}


bool StateMachine::result_display_process()
{
	return StateMachine::result_display->process();
}
