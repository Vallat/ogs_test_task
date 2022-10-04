#pragma once
#include "GameState.h"

/// <summary>
/// This state of StateMachine handles the display of the result player got by spin process
/// </summary>
class ResultDisplay :
	public GameState
{
public:
	ResultDisplay(Renderer* renderer_);

	/// <summary>
	/// Manages rendering of win/lose text
	/// </summary>
	bool process() override;

	void on_wait() override;
	void on_state_change() override;

	void set_player_win_amount(size_t player_win_amount_);
	size_t get_player_win_amount();

private:
	/// <summary>
	/// last win amount user got
	/// </summary>
	size_t player_win_amount = 0;

	/// <summary>
	/// last time user got spinning result, in global seconds
	/// Is used for automatical hiding the result message
	/// </summary>
	sf::Clock* timer = nullptr;

	sf::Font loaded_font;
};

