#include "SlotColumn.h"
#include "SlotSymbol.h"


SlotColumn::SlotColumn() {}


void SlotColumn::set_symbol(SlotSymbol* symbol_, size_t index)
{
	if (index > (SYMBOLS_AMOUNT - 1))
	{
		throw std::invalid_argument("SlotRow: Out of bounds trying to put new symbol into the symbols array");
	}
	symbols[index] = symbol_;
}

SlotSymbol* SlotColumn::get_symbol(size_t index)
{
	if (index > (SYMBOLS_AMOUNT - 1))
	{
		throw std::invalid_argument("SlotRow:: Out of bound trying to get symbol from the symbols array");
	}
	return symbols[index];
}


void SlotColumn::generate_symbols()
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol *symbol_to_add = new SlotSymbol(SYMBOLS_TEXTURES[iterator], SPRITES_SCALE, (iterator + 1) * BASE_VALUE_MULTIPLIER, iterator);
		set_symbol(symbol_to_add, iterator);
	}
	std::random_shuffle(&symbols[0], &symbols[SYMBOLS_AMOUNT - 1]);
	SlotColumn::initial_position_symbols();
}


void SlotColumn::initial_position_symbols()
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol *symbol = get_symbol(iterator);
		float y_position = COLUMN_HEIGHT / LINES_AMOUNT * (static_cast<float>(iterator) - 1);
		symbol->set_position(sf::Vector2f(0, y_position));
		symbol->set_current_index(iterator);
	}
}


void SlotColumn::display_symbols(sf::RenderTexture *texture)
{
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol *symbol = get_symbol(iterator);
		texture->draw(*symbol->get_sprite());
	}
}


void SlotColumn::start_spinning(float spin_speed_, size_t max_spins_, size_t win_index_)
{
	set_spin_speed(spin_speed_);
	set_real_spin_speed(get_spin_speed() * START_SPIN_SPEED_MULTIPLIER);
	set_done_spins(0);
	set_max_spins(max_spins_);
	set_win_index(win_index_);
	is_spinning = true;
}


bool SlotColumn::do_spin()
{
	if (!is_spinning)
	{
		return true;
	}
	float line_height = COLUMN_HEIGHT / LINES_AMOUNT;

	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		SlotSymbol* symbol = get_symbol(iterator);

		// getting the next position we want to move the symbol to
		size_t next_position_symbol_index = get_real_index_offset(symbol->get_current_index(), SYMBOLS_AMOUNT, 1);
		sf::Vector2f position_to_move(0.0f, line_height * (static_cast<float>(next_position_symbol_index) - 1.0f));
	
		// didn't manage to move means symbol reached the destination
		if (!symbol->move_sprite_to(position_to_move, sf::Vector2f(0.0f, get_real_spin_speed())))
		{
			if (next_position_symbol_index == static_cast<size_t>(SYMBOLS_AMOUNT / 2))
			{
				if (symbol->get_id() == get_win_index() && get_done_spins() >= get_max_spins())
				{
					symbol->set_position(sf::Vector2f(0.0f, line_height));
					is_spinning = false;
				}

			}
			symbol->set_current_index(next_position_symbol_index);
		}

		size_t symbol_current_index = symbol->get_current_index();
		if (symbol_current_index != (SYMBOLS_AMOUNT))
		{
			continue;
		}

		// reached the end of the row, lets move back to the beginning
		symbol->set_position(sf::Vector2f(0, -line_height));

		float lreal_spin_speed = get_real_spin_speed();
		float lspin_speed = get_spin_speed();

		if (get_done_spins() >= get_max_spins() - 1)
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


void SlotColumn::set_spin_speed(float spin_speed_)
{
	spin_speed = spin_speed_;
}

float SlotColumn::get_spin_speed()
{
	return spin_speed;
}


void SlotColumn::set_real_spin_speed(float real_spin_speed_)
{
	real_spin_speed = real_spin_speed_;
}

float SlotColumn::get_real_spin_speed()
{
	return real_spin_speed;
}


size_t get_real_index_offset(size_t index, size_t max_value, int offset)
{
	int real_value = static_cast<int> (index) + offset;
	if (real_value > max_value)
	{
		real_value = real_value - static_cast<int> (max_value) - 1;
	}
	else if (real_value < 0)
	{
		real_value = static_cast<int> (max_value) + real_value + 1;
	}
	return static_cast<size_t> (real_value);
}


void SlotColumn::set_done_spins(size_t spins_done_)
{
	spins_done = spins_done_;
}

size_t SlotColumn::get_done_spins()
{
	return SlotColumn::spins_done;
}


void SlotColumn::set_max_spins(size_t max_spins_)
{
	max_spins = max_spins_;
}

size_t SlotColumn::get_max_spins()
{
	return max_spins;
}


void SlotColumn::set_win_index(size_t win_index_)
{
	if (win_index_ >= SYMBOLS_AMOUNT)
	{
		throw std::logic_error("SlotRow: win index can't be bigger than amount of symbols minus one!");
	}
	win_index = win_index_;
}

size_t SlotColumn::get_win_index()
{
	return win_index;
}
