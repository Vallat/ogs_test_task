#include "SlotRow.h"

SlotRow::SlotRow(){}


SlotRow::SlotRow(float row_width_, float row_height_)
{
	SlotRow::row_width = row_width_;
	SlotRow::row_height = row_height_;
}
	

void SlotRow::generate_symbols()
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol *symbol_to_add = new SlotSymbol(textures_list[iterator], sprites_scale);
		SlotRow::symbols[iterator] = *symbol_to_add;
	}
	SlotRow::initial_position_symbols();
}


void SlotRow::initial_position_symbols()
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol symbol = SlotRow::symbols[iterator];
		float y_position = SlotRow::row_height / LINES_AMOUNT * (static_cast<float>(iterator) - 1);
		symbol.set_position(sf::Vector2f(0, y_position));
	}
}


void SlotRow::display_symbols(sf::RenderTexture *texture)
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol symbol = SlotRow::symbols[iterator];
		texture->draw(*symbol.get_sprite());
	}
}


void SlotRow::do_spin(size_t stop_at_index)
{
	float screen_offset = SlotRow::row_height / LINES_AMOUNT;
	float bottom_border = SlotRow::row_height + screen_offset;
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol symbol = SlotRow::symbols[iterator];
		symbol.do_move(sf::Vector2f(0.0f, SlotRow::spin_speed));
		sf::Vector2f symbol_pos = symbol.get_position();
		if (symbol_pos.y > bottom_border)
		{
			symbol.set_position(sf::Vector2f(0, -screen_offset));
		}
	}
}
