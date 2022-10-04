#include "SlotSymbol.h"

SlotSymbol::SlotSymbol()
{
	texture = nullptr;
	sprite = nullptr;
}


SlotSymbol::SlotSymbol(sf::Texture* texture_, sf::Vector2f scale, size_t value_, size_t id_)
{
	texture = texture_;

	sf::Sprite* current_sprite = new sf::Sprite;
	current_sprite->setTexture(*texture);
	current_sprite->setScale(scale);
	set_sprite(current_sprite);

	set_value(value_);
	set_id(id_);
}


void SlotSymbol::set_sprite(sf::Sprite* sprite_)
{
	sprite = sprite_;
}

sf::Sprite* SlotSymbol::get_sprite()
{
	return sprite;
}


void SlotSymbol::set_position(sf::Vector2f position)
{
	sf::Sprite* current_sprite = get_sprite();
	current_sprite->setPosition(position);
}


sf::Vector2f SlotSymbol::get_position()
{
	sf::Sprite* current_sprite = get_sprite();
	return current_sprite->getPosition();
}


void SlotSymbol::do_move(sf::Vector2f offset)
{
	sf::Sprite* current_sprite = get_sprite();
	current_sprite->move(offset);
}


bool SlotSymbol::move_sprite_to(sf::Vector2f new_position, sf::Vector2f move_speed)
{
	sf::Vector2f move_offset(new_position - get_position());
	if (!move_offset.y)
	{
		return false;
	}

	if (move_offset.y > move_speed.y)
	{
		move_offset = move_speed;
	}

	do_move(move_offset);

	return true;
}


void SlotSymbol::set_current_index(size_t current_index_)
{
	if (current_index_ > SYMBOLS_AMOUNT)
	{
		throw std::logic_error("SlotSymbol: current index can't be bigger than amount of symbols!");
	}
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
	if (id_ >= SYMBOLS_AMOUNT)
	{
		throw std::logic_error("SlotSymbol: id can't be bigger than amount of symbols minus one!");
	}
	id = id_;
}

size_t SlotSymbol::get_id()
{
	return id;
}
