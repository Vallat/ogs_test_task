#include "SlotSpinning.h"

SlotSpinning::SlotSpinning(Renderer* renderer_) : GameState::GameState(renderer_)
{
	for (size_t iterator = 0; iterator < ROWS_AMOUNT; ++iterator)
	{
		SlotRow* slot_row = new SlotRow(ROW_WIDTH, ROW_HEIGHT);
		slot_row->generate_symbols();
		SlotSpinning::rows_array[iterator] = slot_row;
	}
}


bool SlotSpinning::process()
{
	if (!GameState::is_active())
	{
		return false;
	}

	bool all_spins_done = true;
	for (size_t iterator = 0; iterator < ROWS_AMOUNT; ++iterator)
	{
		SlotRow* slot_row = SlotSpinning::rows_array[iterator];
		if (!slot_row->do_spin(iterator, 6))
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
	for (size_t iterator = 0; iterator < ROWS_AMOUNT; ++iterator)
	{
		SlotRow* slot_row = SlotSpinning::rows_array[iterator];
		sf::RenderTexture rows_texture;
		rows_texture.create(static_cast<unsigned int>(ROW_WIDTH * 1.5), ROW_HEIGHT);
		rows_texture.clear();

		slot_row->display_symbols(&rows_texture);
		rows_texture.display();

		sf::Texture sprite_texture = rows_texture.getTexture();
		sf::Sprite rows_sprite(sprite_texture);
		rows_sprite.setPosition(sf::Vector2f(50.0f + ROW_WIDTH * 1.25f * iterator, (WINDOW_HEIGHT - ROW_HEIGHT) / 2));
		GameState::access_renderer()->window_draw(rows_sprite);
	}
}


void SlotSpinning::on_state_change()
{
	GameState::on_state_change();
	for (size_t iterator = 0; iterator < ROWS_AMOUNT; ++iterator)
	{
		SlotRow* slot_row = SlotSpinning::rows_array[iterator];
		slot_row->start_spinning(SPIN_SPEED);
	}
}
