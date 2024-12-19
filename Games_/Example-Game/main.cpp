#include <SFML/Graphics.hpp>


// SIMPLE SFML PROJECT IT IS JUST AN EXAMPLE
int main() {
    sf::RenderWindow window(sf::VideoMode(800,480), {"Example Game"});

    sf::RectangleShape shape(sf::Vector2f(50,50));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            window.clear();

            window.draw(shape);

            window.display();
        }
    }
}