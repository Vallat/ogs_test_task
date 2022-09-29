#pragma once

#include <SFML/Graphics.hpp>
#include "SlotSymbol.h"

const size_t ROW_LINES = 3;
const std::string textures_list[] = {"resources/shape_1.png", "resources/shape_2.png" , "resources/shape_3.png" , "resources/shape_4.png" , "resources/shape_5.png" };
const sf::Vector2f sprites_scale = sf::Vector2f(4.f, 4.f);


class SlotRow
{
public:
	SlotRow(float row_height_, float row_width);
	void generate_symbols();
	void initial_position_symbols();
	void display_symbols(sf::RenderWindow *window);

private:
	SlotSymbol symbols[ROW_LINES];
	float row_height;
	float row_width;
};

