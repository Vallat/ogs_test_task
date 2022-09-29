#include <SFML/Graphics.hpp>
#include "SlotRow.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 600), "SFML works!");

    //sf::Texture texture;
    //texture.loadFromFile("resources/shape_1.png");

    //sf::Sprite sprite;
    //sprite.setTexture(texture);
    //sprite.setScale(sf::Vector2f(4.f, 4.f));

    //SlotSymbol *symbol = new SlotSymbol(sprite, sf::Vector2f(70.f, 50.f));

    SlotRow* slot_row = new SlotRow(100, 600);
    slot_row->generate_symbols();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        slot_row->display_symbols(&window);
        window.display();
    }

    return 0;
}