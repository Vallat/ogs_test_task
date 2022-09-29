#include "StateMachine.h"


StateMachine::StateMachine()
{
	awaiting_input = new AwaitingInput();
}


void StateMachine::process()
{
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
