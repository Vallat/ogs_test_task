#include "AwaitingInput.h"
#include "SlotSpinning.h"
#include "ResultDisplay.h"
#include "Renderer.h"
#include "StateMachine.h"

StateMachine::StateMachine(Renderer* renderer)
{
	try
	{
		awaiting_input = new AwaitingInput(renderer);
		slot_spinning = new SlotSpinning(renderer);
		result_display = new ResultDisplay(renderer);
	}
	catch (const std::exception&)
	{
		throw;
	}

	// by default we're waiting for user input
	awaiting_input->on_state_change();
}


void StateMachine::process()
{
	awaiting_input->on_wait();
	slot_spinning->on_wait();
	result_display->on_wait();

	switch (current_state)
	{
	case States::AWAITING_INPUT:
		if (!awaiting_input_process())
		{
			set_state(States::SLOT_SPINNING);
		}
		break;
	case States::SLOT_SPINNING:
		if (!slot_spinning_process())
		{
			result_display->set_player_win_amount(slot_spinning->calculate_win_size());
			set_state(States::DISPLAYING_RESULT);
		}
		break;
	case States::DISPLAYING_RESULT:
		if (!result_display_process() || !awaiting_input_process())
		{
			set_state(States::AWAITING_INPUT);
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
		result_display->on_state_change();
		/// activate
		awaiting_input->on_state_change();
		break;
	case States::SLOT_SPINNING:
		awaiting_input->on_state_change();
		slot_spinning->on_state_change();
		break;
	case States::DISPLAYING_RESULT:
		slot_spinning->on_state_change();
		result_display->on_state_change();
		break;
	default:
		break;
	}
}


bool StateMachine::awaiting_input_process()
{
	return awaiting_input->process();
}


bool StateMachine::slot_spinning_process()
{
	return slot_spinning->process();
}


bool StateMachine::result_display_process()
{
	return result_display->process();
}
