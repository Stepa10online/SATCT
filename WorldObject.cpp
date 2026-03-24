#include "WorldObject.h"


WorldObject::WorldObject(Color color, float x, float y, float Radius)
{
	// Rect
	RectObject.setSize(Vector2f(x, y));
	RectObject.setOrigin(RectObject.getGlobalBounds().width/2,  RectObject.getGlobalBounds().height/2);
	RectObject.setFillColor(color);
	// Circle
	CircleObject.setRadius(Radius);
	CircleObject.setOrigin(CircleObject.getGlobalBounds().width / 2, CircleObject.getGlobalBounds().height/2);
	CircleObject.setFillColor(color);
	// Complex
	

	if (this->ShapeType == "box") {}
	else if (this->ShapeType == "circle") {}
}

void WorldObject::setRectSize(float x, float y)
{
	RectObject.setSize(Vector2f(x, y));
	updateRectOrigin(x, y);
}

void WorldObject::updateRectOrigin(float x, float y)
{
	RectObject.setOrigin(x / 2, y / 2);
}

void WorldObject::calculateAllVerticesPos(vector<Vector2f>& Vertices)
{
	for (int i = 0; i < Vertices.size(); i++)
	{
		this->Vertices.push_back(Vertices[i]);
	}
}

void WorldObject::calculateVerticesPos()
{
	sf::FloatRect spriteBounds = RectObject.getLocalBounds();
	
	topLeftCorner = RectObject.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top));
	topRightCorner = RectObject.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top));
	bottomRightCorner = RectObject.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top + spriteBounds.height));
	bottomLeftCorner = RectObject.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top + spriteBounds.height));
}
//void WorldObject::showCollisionArea(WorldObject obj)
//{
//	collisionArea = new VertexArray(LineStrip, obj.getVerteces().size());
//
//	for (int i = 0; i < 5; i++)
//	{
//		(*collisionArea)[i].position = obj.getVerteces()[i];
//	}
//}
//
//void WorldObject::showCollisionArea()
//{
//	Vertex points[5] = { {topLeftCorner.X,topLeftCorner.Y}, {topRightCorner.X,topRightCorner.X},
//		{bottomRightCorner.X,bottomRightCorner.Y}, bottomLeftCorner, {topLeftCorner.X,topLeftCorner.Y} };
//	collisionArea = new VertexArray(LineStrip, 5);
//
//	for (int i = 0; i < 5; i++)
//	{
//		(*collisionArea)[i].position = points[i].position;
//	}
//}
