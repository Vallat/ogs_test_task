#include <SFML/Graphics.hpp>
#include "SlotRow.h"

const size_t ROWS_AMOUNT = 3;
const unsigned int WINDOW_HEIGHT = 600;
const unsigned int WINDOW_WIDTH = 500;
const float ROW_HEIGHT = 500;
const float ROW_WIDTH = 100;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "test task");

	SlotRow rows[ROWS_AMOUNT];
	for (size_t iterator = 0; iterator < ROWS_AMOUNT; ++iterator)
	{
		SlotRow* slot_row = new SlotRow(ROW_WIDTH, ROW_HEIGHT);
		slot_row->generate_symbols();
		rows[iterator] = *slot_row;
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();

		for (size_t iterator = 0; iterator < ROWS_AMOUNT; ++iterator)
		{
			SlotRow* slot_row = &rows[iterator];
			sf::RenderTexture rows_texture;
			rows_texture.create(ROW_WIDTH * 1.5f, ROW_HEIGHT);

			rows_texture.clear();
			slot_row->do_spin(1);
			slot_row->display_symbols(&rows_texture);
			rows_texture.display();

			sf::Sprite rows_sprite(rows_texture.getTexture());
			rows_sprite.setPosition(sf::Vector2f(50.0f + ROW_WIDTH * 1.25f * iterator, (WINDOW_HEIGHT - ROW_HEIGHT) / 2));
			window.draw(rows_sprite);
		}
		window.display();
	}

	return 0;
}