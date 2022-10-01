#include "SlotRow.h"

SlotRow::SlotRow()
{
	row_height = 0;
	row_width = 0;
}


SlotRow::SlotRow(float row_width_, float row_height_)
{
	row_width = row_width_;
	row_height = row_height_;
}
	

void SlotRow::set_symbol(SlotSymbol* symbol_, size_t index)
{
	if (index > (SYMBOLS_AMOUNT - 1))
	{
		throw std::invalid_argument("SlotRow: Out of bounds trying to put new symbol into the symbols array");
	}
	symbols[index] = symbol_;
}

SlotSymbol* SlotRow::get_symbol(size_t index)
{
	if (index > (SYMBOLS_AMOUNT - 1))
	{
		throw std::invalid_argument("SlotRow:: Out of bound trying to get symbol from the symbols array");
	}
	return symbols[index];
}


void SlotRow::generate_symbols()
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol *symbol_to_add = new SlotSymbol(SYMBOLS_TEXTURES[iterator], SPRITES_SCALE, (iterator + 1) * 10, iterator);
		set_symbol(symbol_to_add, iterator);
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
	set_spin_speed(spin_speed_);
	set_real_spin_speed(get_spin_speed() * START_SPIN_SPEED_MULTIPLIER);
	set_done_spins(0);
	set_max_spins(max_spins_);
	set_win_index(win_index_);
	set_middle_symbol_index(static_cast<size_t>(SYMBOLS_AMOUNT / 2));
	is_spinning = true;
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
		sf::Vector2f position_to_move(0.0f, row_height / LINES_AMOUNT * (static_cast<float>(next_position_symbol_index) - 1.0f));
	
		// didn't manage to move - reached the destination
		if (!symbol->move_sprite_to(position_to_move, sf::Vector2f(0.0f, get_real_spin_speed())))
		{
			if (next_position_symbol_index == static_cast<size_t>(SYMBOLS_AMOUNT / 2))
			{
				SlotRow::set_middle_symbol_index(iterator);
				if (symbol->get_id() == get_win_index() && get_done_spins() >= get_max_spins())
				{
					symbol->set_position(sf::Vector2f(0.0f, screen_offset));
					is_spinning = false;
				}

			}
			symbol->set_current_index(next_position_symbol_index);
		}

		size_t symbol_current_index = next_position_symbol_index;
		if (symbol_current_index != (SYMBOLS_AMOUNT))
		{
			continue;
		}

		// reached the end of the row, lets move back to start
		symbol->set_position(sf::Vector2f(0, -screen_offset));

		float lreal_spin_speed = get_real_spin_speed();
		float lspin_speed = get_spin_speed();

		if (get_done_spins() >= max_spins - 1)
		{
			set_real_spin_speed(std::max<float>(lreal_spin_speed - lspin_speed * SLOWDOWN_MULTIPLIER, lspin_speed * 0.25f));
		}
		else if (lreal_spin_speed < lspin_speed)
		{
			set_real_spin_speed(std::min<float>(lreal_spin_speed + lspin_speed * ACCELERATION_MULTIPLIER, lspin_speed));
		}
	
		if (iterator == (SYMBOLS_AMOUNT - 1) && symbol_current_index == SYMBOLS_AMOUNT)
		{
			set_done_spins(get_done_spins() + 1);
		}
		
	}
	return !is_spinning;
}


void SlotRow::set_spin_speed(float spin_speed_)
{
	spin_speed = spin_speed_;
}

float SlotRow::get_spin_speed()
{
	return spin_speed;
}


void SlotRow::set_real_spin_speed(float real_spin_speed_)
{
	real_spin_speed = real_spin_speed_;
}

float SlotRow::get_real_spin_speed()
{
	return real_spin_speed;
}


size_t SlotRow::get_middle_symbol_index()
{
	return middle_symbol_index;
}

void SlotRow::set_middle_symbol_index(size_t middle_symbol_index_)
{
	if (middle_symbol_index_ > (SYMBOLS_AMOUNT - 1))
	{
		middle_symbol_index_ = 0;
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
		real_value = static_cast<int>(max_value) + real_value + 1;
	}
	return static_cast<size_t>(real_value);
}


void SlotRow::set_done_spins(size_t spins_done_)
{
	spins_done = spins_done_;
}

size_t SlotRow::get_done_spins()
{
	return SlotRow::spins_done;
}


void SlotRow::set_max_spins(size_t max_spins_)
{
	max_spins = max_spins_;
}

size_t SlotRow::get_max_spins()
{
	return max_spins;
}


void SlotRow::set_win_index(size_t win_index_)
{
	if (win_index_ >= SYMBOLS_AMOUNT)
	{
		throw std::logic_error("SlotRow: win index can't be bigger than amount of symbols minus one!");
	}
	win_index = win_index_;
}

size_t SlotRow::get_win_index()
{
	return win_index;
}
