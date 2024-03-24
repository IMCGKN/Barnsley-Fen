#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <math.h>
#include <cmath>

#define width 980
#define height 720

sf::Image img;

float x, y;

void Draw(float b)
{
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float nextX, nextY;

    if (r < 0.01) {
        nextY = 0.16 * y;
        nextX = 0;
    } else if (r < 0.86) {
        nextX = 0.85 * x + b * y;
        nextY = -b * x + 0.85 * y + 1.6;
    } else if (r < 0.93) {
        nextX = 0.2 * x + -0.26 * y;
        nextY = 0.23 * x + 0.22 * y + 1.6;
    } else {
        nextX = -0.15 * x + 0.28 * y;
        nextY = 0.26 * x + 0.24 * y + 0.4;
    }

    x = nextX;
    y = nextY;

    if(img.getPixel(x * 70 + width / 2 - 50, y * 70).r == 0)
    {
        img.setPixel(x * 70 + width / 2 - 50, y * 70, sf::Color::White);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Barnsley Fern", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(false);
    window.setPosition(sf::Vector2i(500, 250));
    sf::Event ev;

    sf::View view(window.getDefaultView());
    view.setRotation(180.0f);
    window.setView(view);

    sf::Sprite sp;
    img.create(width, height);
    sf::Texture tex;
    tex.create(width, height);
    sp.setScale(1, 1);

    while(window.isOpen())
    {
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)
                window.close();
            if(ev.type == sf::Event::KeyPressed)
                if(ev.key.code == sf::Keyboard::Escape)
                    window.close();
        }

        for(int i = 0; i < 1000; i++)
        {
            Draw(0.04);
        }
        tex.update(img.getPixelsPtr());
        sp.setTexture(tex);

        window.clear(sf::Color::Black);
        window.draw(sp);
        window.display();
    }
}