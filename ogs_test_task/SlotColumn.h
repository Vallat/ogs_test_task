#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"


class SlotSymbol;

size_t get_real_index_offset(size_t index, size_t max_value, int offset);

class SlotColumn
{
public:
	SlotColumn();

	void set_symbol(SlotSymbol* symbol_, size_t index);
	SlotSymbol* get_symbol(size_t index);

	/// <summary>
	/// Is used for fill this column with SlotSymbol objects
	/// </summary>
	void generate_symbols();
	
	/// <summary>
	/// Is used for positioning SlotSymbol objects on the screen and give them their real index (position number on the screen)
	/// </summary>
	void initial_position_symbols();

	/// <summary>
	/// Is used for drawing on given RenderTexture all SlotSymbols in the current column
	/// </summary>
	void display_symbols(sf::RenderTexture *texture);

	/// <summary>
	/// Is used for setting up new spin process cycle with given arguments
	/// </summary>
	void start_spinning(float spin_speed_, size_t max_spins_, size_t win_index_);

	/// <summary>
	/// Moves each SlotSymbol in the current column by real_spin_speed, translating them from bottom to top
	/// </summary>
	/// <returns>
	/// Returns true if no SlotSymbol was moved, otherwise returns false
	/// </returns>
	bool do_spin();

	void set_spin_speed(float spin_speed_);
	float get_spin_speed();

	void set_real_spin_speed(float real_spin_speed_);
	float get_real_spin_speed();

	void set_done_spins(size_t spins_done_);
	size_t get_done_spins();

	void set_max_spins(size_t max_spins_);
	size_t get_max_spins();

	void set_win_index(size_t win_index_);
	size_t get_win_index();

private:
	/// <summary>
	/// indicates if this column is in spin process right now or not
	/// </summary>
	bool is_spinning = false;

	/// <summary>
	/// array of all SlotSymbol objects belonging to this column
	/// </summary>
	SlotSymbol *symbols[SYMBOLS_AMOUNT];

	/// <summary>
	/// Target and max spin speed
	/// </summary>
	float spin_speed = 2.0f;

	/// <summary>
	/// real spin speed that changes over time
	/// </summary>
	float real_spin_speed = 0;

	/// <summary>
	/// the number of full spins done from the start of the spin
	/// </summary>
	size_t spins_done = 0;

	/// <summary>
	/// max amount of spins that will be done before stopping spin process
	/// </summary>
	size_t max_spins = 100;

	/// <summary>
	/// ID of SlotSymbol marked as winning
	/// </summary>
	size_t win_index = 0;
};

