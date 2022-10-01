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

	return 0;
}