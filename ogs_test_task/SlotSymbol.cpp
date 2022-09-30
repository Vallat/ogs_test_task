#include "SlotSymbol.h"

SlotSymbol::SlotSymbol()
{
	SlotSymbol::texture = nullptr;
	SlotSymbol::sprite = new sf::Sprite;
}


SlotSymbol::SlotSymbol(const std::string &texture_path, sf::Vector2f scale)
{
	SlotSymbol::texture = new sf::Texture;
	SlotSymbol::texture->loadFromFile(texture_path);
	SlotSymbol::texture->setSmooth(false);
	SlotSymbol::sprite = new sf::Sprite;
	SlotSymbol::sprite->setTexture(*SlotSymbol::texture);
	SlotSymbol::sprite->setScale(scale);
}


sf::Sprite *SlotSymbol::get_sprite()
{
	return SlotSymbol::sprite;
}


void SlotSymbol::set_position(sf::Vector2f position)
{
	SlotSymbol::get_sprite()->setPosition(position);
}


sf::Vector2f SlotSymbol::get_position()
{
	return SlotSymbol::get_sprite()->getPosition();
}


void SlotSymbol::do_move(sf::Vector2f offset)
{
	SlotSymbol::get_sprite()->move(offset);
}


bool SlotSymbol::move_sprite_to(sf::Vector2f new_position, sf::Vector2f move_speed)
{
	sf::Vector2f move_offset(new_position - SlotSymbol::get_position());
	if (!move_offset.y)
	{
		return false;
	}

	if (move_offset.y > move_speed.y)
	{
		move_offset = move_speed;
	}
	else
		move_offset = move_offset;;
	SlotSymbol::do_move(move_offset);
	return true;
}


void SlotSymbol::set_current_index(size_t current_index_)
{
	current_index = current_index_;
}


size_t SlotSymbol::get_current_index()
{
	return current_index;
}

