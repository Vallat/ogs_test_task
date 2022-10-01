#include "ResultDisplay.h"
#include <iostream>

ResultDisplay::ResultDisplay(Renderer* renderer_) : GameState::GameState(renderer_)
{
	if (!loaded_font.loadFromFile("Resources/Roboto-Black.ttf"))
	{
		throw std::runtime_error("ResultDisplay: Didn't manage to load font file!");
	}
}


bool ResultDisplay::process()
{
	if ((static_cast<std::time_t>(get_time_result_recieved() + SECONDS_TO_DISPLAY_RESULT) < std::time(nullptr)))
	{
		return false;
	}

	sf::Text text_to_display;
	text_to_display.setFont(loaded_font);
	text_to_display.setCharacterSize(48);
	if (player_win_amount)
	{
		text_to_display.setString("You won " + std::to_string(player_win_amount) + " credits!");
	}
	else
	{
		text_to_display.setString("You lose! :(");
	}

	sf::FloatRect text_rect = text_to_display.getLocalBounds();
	text_to_display.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height);
	text_to_display.setPosition(GameState::access_renderer()->get_window()->getView().getCenter());

	GameState::access_renderer()->window_draw(text_to_display);

	return true;
}


void ResultDisplay::on_wait() {}


void ResultDisplay::on_state_change()
{
	GameState::on_state_change();
}


void ResultDisplay::set_player_win_amount(size_t player_win_amount_)
{
	player_win_amount = player_win_amount_;
	set_time_result_recieved(std::time(nullptr));
}

size_t ResultDisplay::get_player_win_amount()
{
	return player_win_amount;
}


void ResultDisplay::set_time_result_recieved(std::time_t time_result_recieved_)
{
	time_result_recieved = time_result_recieved_;
}

std::time_t ResultDisplay::get_time_result_recieved()
{
	return time_result_recieved;
}

