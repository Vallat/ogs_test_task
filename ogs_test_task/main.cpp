#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "Globals.h"
#include "Renderer.h"

int main()
{
	Renderer* renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	StateMachine* state_machine = new StateMachine(renderer);

	while (renderer->get_window()->isOpen())
	{
		sf::Event event;
		while (renderer->get_window()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderer->get_window()->close();
		}
		renderer->window_clear();
		state_machine->process();
		renderer->window_display();
	}

	//sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "test task");

	//SlotRow *rows[ROWS_AMOUNT];
	//for (size_t iterator = 0; iterator < ROWS_AMOUNT; ++iterator)
	//{
	//	SlotRow* slot_row = new SlotRow(ROW_WIDTH, ROW_HEIGHT);
	//	slot_row->generate_symbols();
	//	rows[iterator] = slot_row;
	//	slot_row->start_spinning(5.0f);
	//}


	//while (window.isOpen())
	//{
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//	}
	//	
	//	window.clear();

	//	bool all_spins_done = true;
	//	for (size_t iterator = 0; iterator < ROWS_AMOUNT; ++iterator)
	//	{
	//		SlotRow* slot_row = rows[iterator];
	//		sf::RenderTexture rows_texture;
	//		rows_texture.create(static_cast<unsigned int>(ROW_WIDTH * 1.5), ROW_HEIGHT);

	//		rows_texture.clear();
	//		if (!slot_row->do_spin(iterator, 6))
	//		{
	//			all_spins_done = false;
	//		}
	//		slot_row->display_symbols(&rows_texture);
	//		rows_texture.display();

	//		sf::Sprite rows_sprite(rows_texture.getTexture());
	//		rows_sprite.setPosition(sf::Vector2f(50.0f + ROW_WIDTH * 1.25f * iterator, (WINDOW_HEIGHT - ROW_HEIGHT) / 2));
	//		window.draw(rows_sprite);
	//	}
	//	window.display();

	//	if (all_spins_done)
	//	{
	//		std::cout << "all spins done" << std::endl;
	//	}
	//}

	return 0;
}