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
	

void SlotRow::set_symbol(size_t index, SlotSymbol* symbol_)
{
	if (index > SYMBOLS_AMOUNT - 1)
	{
		throw std::invalid_argument("set symbol index out of bounds");
	}
	symbols[index] = symbol_;
}

SlotSymbol* SlotRow::get_symbol(size_t index)
{
	if (index > SYMBOLS_AMOUNT - 1)
	{
		throw std::invalid_argument("get symbol index out of bounds");
	}
	return symbols[index];
}


void SlotRow::generate_symbols()
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol *symbol_to_add = new SlotSymbol(textures_list[iterator], sprites_scale);
		symbol_to_add->set_value(iterator * 10);
		symbol_to_add->set_id(iterator);
		set_symbol(iterator, symbol_to_add);
	}
	std::random_shuffle(&symbols[0], &symbols[SYMBOLS_AMOUNT - 1]);
	SlotRow::initial_position_symbols();
}


void SlotRow::initial_position_symbols()
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol *symbol = get_symbol(iterator);
		float y_position = SlotRow::row_height / LINES_AMOUNT * (static_cast<float>(iterator) - 1);
		symbol->set_position(sf::Vector2f(0, y_position));
		symbol->set_current_index(iterator);
	}
}


void SlotRow::display_symbols(sf::RenderTexture *texture)
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol *symbol = get_symbol(iterator);
		texture->draw(*symbol->get_sprite());
	}
}


void SlotRow::start_spinning(float spin_speed_, size_t max_spins_, size_t win_index_)
{
	SlotRow::spin_speed = spin_speed_;
	SlotRow::real_spin_speed = SlotRow::spin_speed * 0.2f;
	SlotRow::spins_done = 0;
	SlotRow::set_max_spins(max_spins_);
	SlotRow::win_index = win_index_;
	SlotRow::middle_symbol_index = static_cast<size_t>(SYMBOLS_AMOUNT / 2);
	SlotRow::is_spinning = true;
}


bool SlotRow::do_spin()
{
	if (!is_spinning)
	{
		return true;
	}
	float screen_offset = SlotRow::row_height / LINES_AMOUNT;

	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol* symbol = get_symbol(iterator);

		// getting next position we want to move the symbol
		size_t next_position_symbol_index = get_real_index_offset(symbol->get_current_index(), SYMBOLS_AMOUNT, 1);
		sf::Vector2f position_to_move(0.0f, SlotRow::row_height / LINES_AMOUNT * (static_cast<float>(next_position_symbol_index) - 1.0f));
	
		// didn't manage to move - reached the destination
		if (!symbol->move_sprite_to(position_to_move, sf::Vector2f(0.0f, SlotRow::real_spin_speed)))
		{
			if (next_position_symbol_index == static_cast<size_t>(SYMBOLS_AMOUNT / 2))
			{
				SlotRow::set_middle_symbol_index(iterator);
				if (middle_symbol_index == win_index && spins_done >= max_spins)
				{
					symbol->set_position(sf::Vector2f(0.0f, screen_offset));
					is_spinning = false;
				}

			}
			symbol->set_current_index(next_position_symbol_index);
		}

		if (symbol->get_current_index() != (SYMBOLS_AMOUNT))
		{
			continue;
		}

		// reached the end of the row, lets move back to start
		symbol->set_position(sf::Vector2f(0, -screen_offset));

		if (spins_done >= max_spins - 1)
		{
			SlotRow::real_spin_speed = std::max<float>(SlotRow::real_spin_speed - SlotRow::spin_speed * SLOWDOWN_MULTIPLIER, SlotRow::spin_speed * 0.25f);
		}
		else if (SlotRow::real_spin_speed < SlotRow::spin_speed)
		{
			SlotRow::real_spin_speed = std::min<float>(SlotRow::real_spin_speed + SlotRow::spin_speed * ACCELERATION_MULTIPLIER, SlotRow::spin_speed);
		}
	
		if (middle_symbol_index == (SYMBOLS_AMOUNT - 1))
		{
			++spins_done;
		}
		
	}
	return !is_spinning;
}


size_t SlotRow::get_middle_symbol_index()
{
	return SlotRow::middle_symbol_index;
}


void SlotRow::set_middle_symbol_index(size_t middle_symbol_index_)
{
	if (middle_symbol_index_ > (SYMBOLS_AMOUNT - 1))
	{
		SlotRow::middle_symbol_index = 0;
		return;
	}
	middle_symbol_index = middle_symbol_index_;
}


size_t get_real_index_offset(size_t index, size_t max_value, int offset)
{
	int real_value = static_cast<int>(index) + offset;
	if (real_value > max_value)
	{
		real_value = real_value - static_cast<int>(max_value) - 1;
	}
	else if (real_value < 0)
	{
		real_value = static_cast<int>(max_value) + real_value;
	}
	return static_cast<size_t>(real_value);
}


size_t SlotRow::get_done_spins()
{
	return SlotRow::spins_done;
}


void SlotRow::set_max_spins(size_t max_spins_)
{
	max_spins = max_spins_;
}


void SlotRow::set_win_index(size_t win_index_)
{
	win_index = win_index_;
}

size_t SlotRow::get_win_index()
{
	return win_index;
}
