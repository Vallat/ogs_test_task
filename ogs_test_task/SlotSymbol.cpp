#include "SlotSymbol.h"

SlotSymbol::SlotSymbol()
{
	SlotSymbol::sprite = new sf::Sprite;
}

SlotSymbol::SlotSymbol(const std::string &texture_path, sf::Vector2f scale)
{
	SlotSymbol::texture = new sf::Texture;
	SlotSymbol::texture->loadFromFile(texture_path);
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
	SlotSymbol::sprite->setPosition(position);
}