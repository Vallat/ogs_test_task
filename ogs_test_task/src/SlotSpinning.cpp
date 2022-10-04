#include <random>
#include "SlotSpinning.h"
#include "SlotColumn.h"
#include "SlotSymbol.h"
#include "Button.h"


SlotSpinning::SlotSpinning(Renderer* renderer_) : GameState::GameState(renderer_)
{
	for (size_t iterator = 0; iterator < COLUMNS_AMOUNT; ++iterator)
	{
		SlotColumn* slot_column = new SlotColumn();
		put_column_in_array(slot_column, iterator);
	}
	stop_button = new Button("Resources/button_stop.png", SPRITES_SCALE);
	stop_button->set_position(sf::Vector2f(STOP_BUTTON_POSITION_X, STOP_BUTTON_POSITION_Y));
}


void SlotSpinning::put_column_in_array(SlotColumn* row_to_put, size_t index)
{
	if (index > (COLUMNS_AMOUNT - 1))
	{
		throw std::runtime_error("SlotSpinning: Out of bounds trying to put new row into the array.");
	}
	columns_array[index] = row_to_put;
}

SlotColumn* SlotSpinning::get_column_from_array(size_t index)
{
	if (index > (COLUMNS_AMOUNT - 1))
	{
		throw std::runtime_error("SlotSpinning: Out of bounds trying to get row from the array.");
	}
	return columns_array[index];
}


bool SlotSpinning::process()
{
	if (!GameState::is_active())
	{
		return false;
	}

	if (!can_stop)
	{
		can_stop = true;
		for (size_t iterator = 0; iterator < COLUMNS_AMOUNT; ++iterator)
		{
			SlotColumn* slot_column = get_column_from_array(iterator);
			// we don't want to stop too early
			if (slot_column->get_done_spins() < MIN_SPINS_BEFORE_STOP)
			{
				can_stop = false;
				break;
			}
		}
	}

	sf::Vector2f mouse_position(sf::Mouse::getPosition(*GameState::access_renderer()->get_window()));
	if (can_stop && (GameState::user_pressed_enter() || stop_button->is_clicked(mouse_position)))
	{
		for (size_t iterator = 0; iterator < COLUMNS_AMOUNT; ++iterator)
		{
			SlotColumn* slot_column = get_column_from_array(iterator);
			slot_column->set_max_spins(2);
			slot_column->set_done_spins(0);
		}
		can_stop = false;
	}

	bool all_spins_done = true;
	for (size_t iterator = 0; iterator < COLUMNS_AMOUNT; ++iterator)
	{
		SlotColumn* slot_column = get_column_from_array(iterator);
		if (!slot_column->do_spin())
		{
			all_spins_done = false;
		}
	}

	if (all_spins_done)
	{
		return false;
	}
	return true;
}


void SlotSpinning::on_wait()
{
	for (size_t iterator = 0; iterator < COLUMNS_AMOUNT; ++iterator)
	{
		SlotColumn* slot_column = get_column_from_array(iterator);
		sf::RenderTexture column_texture;
		column_texture.create(static_cast<unsigned int>(COLUMN_WIDTH * 1.5), COLUMN_HEIGHT);
		column_texture.clear();

		slot_column->display_symbols(&column_texture);
		column_texture.display();

		sf::Texture sprite_texture = column_texture.getTexture();
		sf::Sprite column_sprite(sprite_texture);
		column_sprite.setPosition(sf::Vector2f(50.0f + COLUMN_WIDTH * 1.25f * iterator, (WINDOW_HEIGHT - COLUMN_HEIGHT) / 2));
		GameState::access_renderer()->window_draw(column_sprite);
	}

	if (!can_stop)
	{
		stop_button->get_sprite()->setColor(sf::Color(120, 120, 120));
	}
	else
	{
		stop_button->get_sprite()->setColor(sf::Color(255, 255, 255));
	}

	sf::Sprite button_sprite = *stop_button->get_sprite();
	GameState::access_renderer()->window_draw(button_sprite);

}


void SlotSpinning::on_state_change()
{
	can_stop = false;
	GameState::on_state_change();

	if (!GameState::is_active())
	{
		return;
	}

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> speed_dist(SPIN_SPEED * 0.8f, SPIN_SPEED * 1.2f);
	std::uniform_int_distribution<size_t> spins_dist(SPINS_BOTTOM_LIMIT, SPINS_UPPER_LIMIT);
	std::uniform_int_distribution<size_t> win_index_dist(0, SYMBOLS_AMOUNT - 1);

	for (size_t iterator = 0; iterator < COLUMNS_AMOUNT; ++iterator)
	{
		SlotColumn* slot_column = get_column_from_array(iterator);
		slot_column->start_spinning(speed_dist(mt), spins_dist(mt), win_index_dist(mt));
	}
}


size_t SlotSpinning::calculate_win_size()
{
	size_t symbols_amount[SYMBOLS_AMOUNT];
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; ++iterator)
	{
		symbols_amount[iterator] = 0;
	}

	for (size_t iterator = 0; iterator < COLUMNS_AMOUNT; ++iterator)
	{
		SlotColumn* slot_column = get_column_from_array(iterator);
		++symbols_amount[slot_column->get_win_index()];
	}

	size_t win_amount = 0;
	SlotColumn* reference_column = get_column_from_array(0);
	for (size_t iterator = 0; iterator < SYMBOLS_AMOUNT; iterator++)
	{
		if (symbols_amount[iterator] == 3)
		{
			win_amount = reference_column->get_symbol(iterator)->get_value() * 3 * THREE_IN_LINE_MULTIPLIER;
			break;
		}
		else if (symbols_amount[iterator] == 2)
		{
			win_amount = reference_column->get_symbol(iterator)->get_value() * 2 * TWO_IN_LINE_MULTIPLIER;
			break;
		}
	}
	return win_amount;

}

