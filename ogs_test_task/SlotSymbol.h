#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

class SlotSymbol
{
public:
	SlotSymbol();
	SlotSymbol(const std::string& texture_path, sf::Vector2f scale, size_t value_, size_t id_);
	sf::Sprite *get_sprite();

	void set_position(sf::Vector2f position);
	sf::Vector2f get_position();

	void do_move(sf::Vector2f offset);
	bool move_sprite_to(sf::Vector2f new_position, sf::Vector2f move_speed);

	void set_current_index(size_t current_index_);
	size_t get_current_index();
	
	void set_value(size_t value_);
	size_t get_value();

	void set_id(size_t id_);
	size_t get_id();

private:
	size_t current_index = 0;
	sf::Texture *texture;
	sf::Sprite *sprite;
	size_t value = 10;
	size_t id = 0;
};

