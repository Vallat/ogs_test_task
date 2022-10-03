#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "Globals.h"
#include "Renderer.h"

/// <summary>
/// Main function, firstly, it initializes "Renderer" and "StateMachine" and if something goes wrong it terminates the application
/// Secondly, it runs the main windows loop, telling to the renderer to clear application window first
/// Then it tells to State Machine to process its logic. It includes telling the renderer what to draw.
/// After that, renderer displays everything it got and the loop starts again
/// </summary>
/// <returns>
/// "1" if the application was terminated by closing the window
/// "0" if the application was terminated by unexpected runtime error
/// </returns>

int main()
{
	Renderer* renderer = nullptr;
	StateMachine* state_machine = nullptr;
	try
	{
		renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
		state_machine = new StateMachine(renderer);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 0;
	}

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

	return 1;
}