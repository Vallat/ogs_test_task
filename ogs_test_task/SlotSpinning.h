#pragma once
#include "GameState.h"

class SlotColumn;
class Button;

class SlotSpinning :
	public GameState
{
public:
	/// <summary>
	/// Initializes the COLUMNS_AMOUNT number of Slot Columns, populates them with slot symbols
	/// Creates stop_button
	/// </summary>
	SlotSpinning(Renderer* renderer_);

	/// <summary>
	/// Manages the spin in every slot column, the display of the stop button
	/// Takes input from the user to stop slot spinning
	/// </summary>
	bool process() override;

	/// <summary>
	/// Manages rendering of stop button and all Slot Columns on their own RenderTextures
	/// </summary>
	void on_wait() override;

	/// <summary>
	/// If current stage it active, sets up random values for max spin speed, spins amount and win index of slot symbol
	/// </summary>
	void on_state_change() override;

	void put_column_in_array(SlotColumn* row_to_put, size_t index);
	SlotColumn* get_column_from_array(size_t index);


	/// <summary>
	/// Is used for checking how many SlotSymbols with the same id are in the central line and their value
	/// automatically multiplies their value by win coefs
	/// </summary>
	/// <returns>
	/// returns the amount of credits player won
	size_t calculate_win_size();

private:
	/// <summary>
	/// the array of all slot columns presented on the screen
	/// </summary>
	SlotColumn* columns_array[COLUMNS_AMOUNT];
	Button* stop_button;
	bool can_stop = false;
};

