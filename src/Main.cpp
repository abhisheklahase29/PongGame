
#include <SFML/Graphics.hpp>
#include <ball.h>
#include <bat.h>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;
int main()
{
	int Width = 1024;
	int Height = 768;
	VideoMode vm(Width, Height);
	RenderWindow window(vm, "PinGPonG");
	bool paused = true;
	int score = 0;
	int lives = 3;

	Bat bat(Width / 2, Height - 20);

	Ball ball(Height / 2, 1);

	Text hud;
	Font font;
	font.loadFromFile("graphicss/text.ttf");
	hud.setFont(font);
	hud.setCharacterSize(30);
	hud.setFillColor(Color::White);

	Text msgText;
	msgText.setFont(font);
	msgText.setString("Press ENTER to START!!!");
	msgText.setCharacterSize(50);
	msgText.setFillColor(Color::White);
	FloatRect textRect = msgText.getLocalBounds();
	msgText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	msgText.setPosition(sf::Vector2f(Width / 2.0f, Height / 2.0f));

	auto image = Image();
	image.loadFromFile("graphicss/icon.png");
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			bat.moveUp();
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			bat.moveDown();
		}
		if (!paused)
		{

			if (ball.getPosition().top > Height)
			{
				ball.hitBottom();
				lives--;
				if (lives < 1)
				{
					paused = true;
					score = 0;
					lives = 3;
				}
			}
			if (ball.getPosition().top < 0)
			{
				ball.reboundBatOrTop();
				score++;
			}
			if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > Width)
			{
				ball.reboundSides();
			}
			if (ball.getPosition().intersects(bat.getPosition()))
			{
				ball.reboundBatOrTop();
			}
			ball.update();
			bat.update();

			stringstream ss;
			ss << "SCORE :- " << score << "   LIVES:- " << lives;
			hud.setString(ss.str());
		}
		window.clear();
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.draw(hud);
		if (paused)
		{
			window.draw(msgText);
		}

		window.display();
	}
}