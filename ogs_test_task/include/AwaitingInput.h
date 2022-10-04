#pragma once
#include "GameState.h"

class Renderer;
class Button;

/// <summary>
/// This state of StateMachine waits for user to press enter or click the start button
/// </summary>
class AwaitingInput :
	public GameState
{
public:
	AwaitingInput(Renderer* renderer_);
	/// <summary>
	/// Takes input from the user to start spinning
	/// </summary>
	bool process() override;

	/// <summary>
	/// Manages rendering of start button
	/// </summary>
	void on_wait() override;
	void on_state_change() override;

private:
	Button* start_button;
};

