#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window{{480, 480}, "Window 2"};
    window.setActive();
    sf::Event event;

    while (window.isOpen()) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        window.display();


    }
}