#pragma once
#include "GameState.h"
#include "Globals.h"

class ResultDisplay :
	public GameState
{
public:
	ResultDisplay(Renderer* renderer_);
	bool process() override;
	void on_wait() override;
	void on_state_change() override;

	void set_player_win_amount(size_t player_win_amount_);
	size_t get_player_win_amount();

	void set_time_result_recieved(std::time_t time_result_recieved_);
	std::time_t get_time_result_recieved();

private:
	size_t player_win_amount = 0;
	std::time_t time_result_recieved = NULL;
	sf::Font loaded_font;
};

