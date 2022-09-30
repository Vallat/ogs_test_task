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
	bool move_sprite_to(sf::Vector2f new_position, sf::Vector2f move_speed);
	void set_current_index(size_t current_index_);
	size_t get_current_index();

private:
	size_t current_index = 0;
	sf::Texture *texture;
	sf::Sprite *sprite;
};

