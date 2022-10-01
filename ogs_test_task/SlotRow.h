#pragma once

#include <SFML/Graphics.hpp>
#include "SlotSymbol.h"
#include "Globals.h"

size_t get_real_index_offset(size_t index, size_t max_value, int offset);

class SlotRow
{
public:
	SlotRow();
	SlotRow(float row_height_, float row_width);

	void set_symbol(SlotSymbol* symbol_, size_t index);
	SlotSymbol* get_symbol(size_t index);

	void generate_symbols();
	void initial_position_symbols();
	void display_symbols(sf::RenderTexture *texture);

	void start_spinning(float spin_speed_, size_t max_spins_, size_t win_index_);
	bool do_spin();

	void set_middle_symbol_index(size_t middle_symbol_index_);
	size_t get_middle_symbol_index();

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
	bool is_spinning = false;
	SlotSymbol *symbols[SYMBOLS_AMOUNT];
	float row_height;
	float row_width;
	float spin_speed = 2.0f;
	float real_spin_speed = 0;

	size_t middle_symbol_index = SYMBOLS_AMOUNT;
	size_t spins_done = 0;
	size_t max_spins = 100;
	size_t win_index = 0;
};

