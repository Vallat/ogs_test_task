#pragma once

#include <SFML/Graphics.hpp>

class SlotSymbol
{
public:
	SlotSymbol();
	SlotSymbol(const std::string& texture_path, sf::Vector2f scale);
	sf::Sprite *get_sprite();
	void set_position(sf::Vector2f position);

private:
	sf::Texture *texture;
	sf::Sprite *sprite;
};

