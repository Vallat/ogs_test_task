#pragma once

#include <SFML/Graphics.hpp>
#include "SlotSymbol.h"

const size_t LINES_AMOUNT = 3;
const std::string textures_list[] = {"resources/shape_1.png", "resources/shape_2.png" , "resources/shape_3.png" , "resources/shape_4.png" , "resources/shape_5.png" };
constexpr size_t SYMBOLS_AMOUNT = _countof(textures_list);
const sf::Vector2f sprites_scale = sf::Vector2f(4.f, 4.f);

const float ACCELERATION_MULTIPLIER = 0.05f;
const float SLOWDOWN_MULTIPLIER = 0.1f;

size_t get_real_index_offset(size_t index, size_t max_value, int offset);

class SlotRow
{
public:
	SlotRow();
	SlotRow(float row_height_, float row_width);

	void set_symbol(size_t index, SlotSymbol* symbol_);
	SlotSymbol* get_symbol(size_t index);

	void generate_symbols();
	void initial_position_symbols();
	void display_symbols(sf::RenderTexture *texture);

	void start_spinning(float spin_speed_, size_t max_spins_, size_t win_index_);
	bool do_spin();

	void set_middle_symbol_index(size_t middle_symbol_index_);
	size_t get_middle_symbol_index();

	size_t get_done_spins();

	void set_max_spins(size_t max_spins_);

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

