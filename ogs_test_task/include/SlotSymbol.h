#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

class SlotSymbol
{
public:
	SlotSymbol();
	SlotSymbol(sf::Texture* texture_, sf::Vector2f scale, size_t value_, size_t id_);

	void set_sprite(sf::Sprite* sprite_);
	sf::Sprite *get_sprite();

	void set_position(sf::Vector2f position);
	sf::Vector2f get_position();

	/// <summary>
	/// Moves sprite by the offset
	/// </summary>
	void do_move(sf::Vector2f offset);

	/// <summary>
	/// Moves sprite to the new_position (and no further) by the move_speed
	/// </summary>
	/// <returns>
	/// Returns true if the move was successfull, otherwise returns fall (means that the sprite is already on the given positon)
	/// </returns>
	bool move_sprite_to(sf::Vector2f new_position, sf::Vector2f move_speed);

	void set_current_index(size_t current_index_);
	size_t get_current_index();
	
	void set_value(size_t value_);
	size_t get_value();

	void set_id(size_t id_);
	size_t get_id();

private:
	/// <summary>
	/// Object index on the screen (number of line it is positioned on)
	/// </summary>
	size_t current_index = 0;
	sf::Texture *texture;
	sf::Sprite *sprite;

	/// <summary>
	/// Object value (affects the amount of winnings)
	/// </summary>
	size_t value = 10;

	/// <summary>
	/// Object ID, used to determine winning combination
	/// </summary>
	size_t id = 0;
};

