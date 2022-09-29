#pragma once

#include <SFML/Graphics.hpp>

class SlotSymbol
{
public:
	SlotSymbol();
	SlotSymbol(const std::string& texture_path, sf::Vector2f scale);
	sf::Sprite *get_sprite();
	void set_position(sf::Vector2f position);
	sf::Vector2f get_position();
	void do_move(sf::Vector2f offset);

private:
	sf::Texture *texture;
	sf::Sprite *sprite;
};

