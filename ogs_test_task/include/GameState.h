#pragma once

#include "Renderer.h"
#include "Globals.h"

/// <summary>
/// default class of all StateMachine states
/// </summary>
class GameState
{
public:
	GameState(Renderer* renderer_);
	/// <summary>
	/// runs every tick when the StateMachine is switched to it
	/// </summary>
	virtual bool process() = 0;

	/// <summary>
	/// runs every tick no matter of the StateMachine state
	/// </summary>
	virtual void on_wait() = 0;

	/// <summary>
	/// called when the StateMachine changes its state on/from this state
	/// </summary>
	virtual void on_state_change() = 0;

	/// <summary>
	/// checks if the StateMachine currently uses this state
	/// </summary>
	bool is_active();

	/// <summary>
	/// use to access and give the pointer to the current main Renderer object
	/// </summary>
	Renderer* access_renderer();

	/// <summary>
	/// use to check if user pressed enter key
	/// </summary>
	bool user_pressed_enter();

private:
	bool active = false;
	Renderer* renderer = nullptr;
};	

