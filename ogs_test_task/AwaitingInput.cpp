#include "AwaitingInput.h"

AwaitingInput::AwaitingInput(Renderer* renderer_) : GameState::GameState(renderer_)
{
	start_button = new Button("Resources/button_start.png", SPRITES_SCALE);
	start_button->set_position(sf::Vector2f(START_BUTTON_POSITION_X, START_BUTTON_POSITION_Y));
}


bool AwaitingInput::process()
{
	sf::Vector2f mouse_position(sf::Mouse::getPosition(*GameState::access_renderer()->get_window()));
	if (GameState::user_pressed_enter() || start_button->is_clicked(mouse_position))
	{
		return false;
	}
	return true;
}


void AwaitingInput::on_wait()
{
	sf::Sprite button_sprite = *start_button->get_sprite();
	GameState::access_renderer()->window_draw(button_sprite);
}


void AwaitingInput::on_state_change()
{
	GameState::on_state_change();
}

