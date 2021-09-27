#include "Graphics.h"

Graphics::Graphics() {}

Graphics::Graphics(sf::RenderWindow* pwindow){
    pWindow = pwindow;
}

void Graphics::drawCircle(float x, float y, float radius, sf::Color color){
    sf::CircleShape circle(radius);
    circle.setPosition(x, y);
    circle.setFillColor(color);
    pWindow->draw(circle);
}

void Graphics::drawRect(float x, float y, float w, float h, sf::Color color) {
    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(color);
    pWindow->draw(rect);
}

void Graphics::clearScreen(sf::Color color){
    pWindow->clear(color);
}

void Graphics::setUseCamera(bool _useCamera) {
    useCamera = _useCamera;
}
