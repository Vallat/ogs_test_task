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

	void set_win_size(size_t win_size_);
	size_t get_win_size();

	void set_time_result_recieved(std::time_t time_result_recieved_);
	std::time_t get_time_result_recieved();

private:
	size_t win_size = 0;
	std::time_t time_result_recieved = NULL;
	sf::Font loaded_font;
};

