#include "Renderer.h"

Renderer::Renderer(unsigned int window_width_, unsigned int window_height_)
{
	window_width = window_width_;
	window_height = window_height_;

	display_window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), WINDOW_NAME);
}


sf::RenderWindow* Renderer::get_window()
{
	if (display_window == nullptr)
	{
		throw std::runtime_error("Renderer: Display window was not initialized!");
	}
	return display_window;
}


void Renderer::window_clear()
{
	sf::RenderWindow* game_window = get_window();
	game_window->clear();
}


void Renderer::window_draw(sf::Sprite sprite_to_draw)
{
	sf::RenderWindow* game_window = get_window();
	game_window->draw(sprite_to_draw);
}


void Renderer::window_draw(sf::Text text_to_draw)
{
	sf::RenderWindow* game_window = get_window();
	game_window->draw(text_to_draw);
}


void Renderer::window_display()
{
	sf::RenderWindow* game_window = get_window();
	game_window->display();
}
