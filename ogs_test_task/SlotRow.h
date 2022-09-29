#pragma once

#include <SFML/Graphics.hpp>
#include "SlotSymbol.h"

const size_t LINES_AMOUNT = 3;
const float SCREEN_BORDER_OFFSET = 0.1f;
const std::string textures_list[] = {"resources/shape_1.png", "resources/shape_2.png" , "resources/shape_3.png" , "resources/shape_4.png" , "resources/shape_5.png" };
constexpr size_t SYMBOLS_AMOUNT = _countof(textures_list);
const sf::Vector2f sprites_scale = sf::Vector2f(4.f, 4.f);


class SlotRow
{
public:
	SlotRow();
	SlotRow(float row_height_, float row_width);
	void generate_symbols();
	void initial_position_symbols();
	void display_symbols(sf::RenderTexture *texture);
	void do_spin(size_t stop_at_index);

private:
	SlotSymbol symbols[SYMBOLS_AMOUNT];
	float row_height;
	float row_width;
	float spin_speed = 2.0f;
};

