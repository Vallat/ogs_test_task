#include "SlotRow.h"

SlotRow::SlotRow()
{
	SlotRow::row_height = 0;
	SlotRow::row_width = 0;
}


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


void SlotRow::start_spinning(float spin_speed_)
{
	SlotRow::spin_speed = spin_speed_;
	SlotRow::real_spin_speed = SlotRow::spin_speed * 0.2f;
	SlotRow::spins_done = 0;
	SlotRow::middle_symbol_index = static_cast<size_t>(SYMBOLS_AMOUNT / 2);
}


bool SlotRow::do_spin(size_t stop_at_index, size_t max_spins)
{
	if (middle_symbol_index == stop_at_index && spins_done == max_spins)
	{
		return true;
	}

	float screen_offset = SlotRow::row_height / LINES_AMOUNT;
	float bottom_border = SlotRow::row_height + screen_offset;
	float middle_border = screen_offset;

	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol symbol = SlotRow::symbols[iterator];

		symbol.do_move(sf::Vector2f(0.0f, real_spin_speed));
		sf::Vector2f symbol_pos = symbol.get_position();
		if (symbol_pos.y > middle_border && symbol_pos.y < middle_border + screen_offset)
		{
			middle_symbol_index = iterator;
		}

		if (symbol_pos.y < bottom_border)
		{
			continue;
		}
		symbol.set_position(sf::Vector2f(0, -screen_offset));

		if (spins_done >= max_spins - 1)
		{
			SlotRow::real_spin_speed = std::max<float>(SlotRow::real_spin_speed - SlotRow::spin_speed * SLOWDOWN_MULTIPLIER, SlotRow::spin_speed * 0.25f);
		}
		else if (SlotRow::real_spin_speed != SlotRow::spin_speed)
		{
			SlotRow::real_spin_speed = std::min<float>(SlotRow::real_spin_speed + SlotRow::spin_speed * ACCELERATION_MULTIPLIER, SlotRow::spin_speed);
		}
	
		if (middle_symbol_index == (SYMBOLS_AMOUNT - 1))
		{
			++spins_done;
		}
		
	}
	return false;
}


size_t SlotRow::get_middle_symbol_index()
{
	return SlotRow::middle_symbol_index;
}
