#include "SlotSymbol.h"

SlotSymbol::SlotSymbol()
{
	texture = nullptr;
	sprite = new sf::Sprite;
}


SlotSymbol::SlotSymbol(const std::string &texture_path, sf::Vector2f scale, size_t value_, size_t id_)
{
	texture = new sf::Texture;
	texture->loadFromFile(texture_path);
	texture->setSmooth(false);
	sprite = new sf::Sprite;
	sprite->setTexture(*SlotSymbol::texture);
	sprite->setScale(scale);

	set_value(value_);
	set_id(id_);
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


void SlotSymbol::set_value(size_t value_)
{
	value = value_;
}

size_t SlotSymbol::get_value()
{
	return value;
}


void SlotSymbol::set_id(size_t id_)
{
	id = id_;
}

size_t SlotSymbol::get_id()
{
	return id;
}
