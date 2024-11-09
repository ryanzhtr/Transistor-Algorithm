#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Create a shape
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
}