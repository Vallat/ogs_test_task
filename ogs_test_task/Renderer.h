#pragma once

#include <SFML/Graphics.hpp>

class Renderer
{
public:
	Renderer(unsigned int window_width_, unsigned int window_height_);
	sf::RenderWindow* get_window();
	void window_clear();
	void window_draw(sf::Sprite sprite_to_draw);
	void window_display();

private:
	unsigned int window_width;
	unsigned int window_height;

	sf::RenderWindow* display_window;
};

