#include "Renderer.h"

Renderer::Renderer(unsigned int window_width_, unsigned int window_height_)
{
	Renderer::window_width = window_width_;
	Renderer::window_height = window_height_;

	Renderer::display_window = new sf::RenderWindow(sf::VideoMode(Renderer::window_width, Renderer::window_height), "test task");
}


sf::RenderWindow* Renderer::get_window()
{
	return Renderer::display_window;
}


void Renderer::window_clear()
{
	Renderer::get_window()->clear();
}


void Renderer::window_draw(sf::Sprite sprite_to_draw)
{
	Renderer::get_window()->draw(sprite_to_draw);
}


void Renderer::window_display()
{
	Renderer::get_window()->display();
}

