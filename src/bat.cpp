#include <bat.h>
using namespace sf;
Bat::Bat(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	batShape.setSize(Vector2f(50, 5));
	batShape.setPosition(position);
}
FloatRect Bat::getPosition()
{
	return batShape.getGlobalBounds();
}
RectangleShape Bat::getShape()
{
	return batShape;
}
void Bat::moveLeft()
{
	position.x -= batSpeed;
}
void Bat::moveRight()
{
	position.x += batSpeed;
}
void Bat::moveDown()
{
	position.y += batSpeed;
}
void Bat::moveUp()
{
	position.y -= batSpeed;
}
void Bat::update()
{
	batShape.setPosition(position);
}