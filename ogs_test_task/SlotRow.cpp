#include "SlotRow.h"

SlotRow::SlotRow(float row_width_, float row_height_)
{
	SlotRow::row_width = row_width_;
	SlotRow::row_height = row_height_;
}
	

void SlotRow::generate_symbols()
{
	for (size_t iterator = 0; iterator < ROW_LINES; ++iterator)
	{
		//sf::Texture sprite_texture;
		//sprite_texture.loadFromFile(textures_list[iterator]);

		SlotSymbol *symbol_to_add = new SlotSymbol(textures_list[iterator], sprites_scale);
		SlotRow::symbols[iterator] = *symbol_to_add;
	}
	SlotRow::initial_position_symbols();
}


void SlotRow::initial_position_symbols()
{
	float x_position = SlotRow::row_width / 2;
	for (size_t iterator = 0; iterator < 3; ++iterator)
	{
		SlotSymbol symbol = SlotRow::symbols[iterator];
		float y_position = (SlotRow::row_height - SlotRow::row_height * 0.1f) / 3 * iterator + SlotRow::row_height * 0.1f;
		symbol.set_position(sf::Vector2f(x_position, y_position));
	}
}


void SlotRow::display_symbols(sf::RenderWindow *window)
{
	float x_position = SlotRow::row_width / 2;
	for (size_t iterator = 0; iterator < 3; ++iterator)
	{
		SlotSymbol symbol = SlotRow::symbols[iterator];
		window->draw(*symbol.get_sprite());
	}
}
