#pragma once
#ifndef WorldObject_H
#define WorldObject_H

#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;

class WorldObject
{
private:

	struct WObject
	{
		float x;
		float y;
		float width;
		float height;
		Color color;

	};

	WObject Object = {0,0,0,0};
	
	RectangleShape RectObject;/*
	Position {x,y}
	Shape {sizex, sizey}
	Color {r,g,b,a}
	Rotation {angle}
	*/
	CircleShape CircleObject;/*
	Position {x,y}
	Shape {radius}
	Color {r,g,b,a}
	Rotation {angle}
	*/

	Vector2f offset;/*
	Camera handle
	*/

	ConvexShape conv_shape; // if box -> NULL, if circle -> NULL
	/*
	Convex Shape
	*/
	vector<Vector2f> Vertices;

	Vector2f topLeftCorner;
	Vector2f topRightCorner;
	Vector2f bottomRightCorner;
	Vector2f bottomLeftCorner;

	string ShapeType;
	float Radius;

	bool IsStatic;

public:

	
	// Others

	WorldObject(Color color = Color::White,
		float x = 25.0f, float y = 25.0f,
		float Radius = 12.5
	);

	bool Update(Vector2f position, Vector2f size, Color color)
	{
		if (position.x == NULL && position.y == NULL) {}
		if (size.x == NULL && size.y == NULL) {}
		if (color == Color{NULL, NULL, NULL, NULL})



		//// Not for Complex Shape
		// update color 
		// update pos
		// update shape
		//// Based on shape:
		// update size {x,y} {radius} {points position}
		// update rotation
		// 
		//



		return 1; // Everything OK
	}

	void calculateAllVerticesPos(vector<Vector2f>&);
	void calculateVerticesPos();
	void loadConvexShape(ConvexShape conv_shape) { this->conv_shape = conv_shape; }

	// Updates functions
	void updateRectOrigin(float x, float y);
	
	// Getters
	inline Shape& getObjShape()
	{
		if (this->ShapeType == "box" || this->ShapeType == "polygon")
		{
			return RectObject;
		}
		return CircleObject;
	}
	inline VertexArray getVertexShape()
	{
		VertexArray temp(TriangleFan);
		for (int i = 0; i < Vertices.size(); i++)
		{
			Vertex temp_ver;
			temp_ver.position = { Vertices[i].x, Vertices[i].y };
			temp.append(temp_ver);
		}
		return temp;
	}
	inline ConvexShape getConvexShape() { return this->conv_shape; }
	
	bool getStaticParametr()			{ return this->IsStatic;															}
	Vector2f getRectPosition()			{ return { RectObject.getPosition().x,RectObject.getPosition().y };					}
	Vector2f getCirclePosition()		{ return { CircleObject.getPosition().x,CircleObject.getPosition().y };				}
	vector<Vector2f> getAllVerteces()	{ return Vertices;																	}
	vector<Vector2f> getRectVerteces()	{ return { topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner };	}
	Vector2f getRectSize()				{ return this->RectObject.getSize();												}
	float getRadius()					{ return this->Radius;																}
	string getShapeType()				{ return this->ShapeType;															}
	FloatRect getFloatRect()			{ return this->RectObject.getLocalBounds();											}


	// Setters

	//// Circle shapes
	void setRadius(float Radius) { this->Radius = Radius; CircleObject.setRadius(Radius); }
	
	//// Rect shapes
	void setRectSize(float x, float y);
	
	//// Complex shapes
	void setVertices(vector<Vector2f>& Vertices) { this->Vertices = Vertices; }
	void setVertices(VertexArray Vertices)
	{
		vector<Vector2f> VectorVertices;
		for (int i = 0; i < Vertices.getVertexCount(); i++)
		{
			VectorVertices.push_back({ Vertices[i].position.x, Vertices[i].position.y });
		}
		this->Vertices = VectorVertices;
	}
	// Regular parametr
	
	//// For shape
	void setShapeType(string ShapeType)				{ this->ShapeType = ShapeType;					}
	void setStaticParametr(bool static_parametr)	{ this->IsStatic = static_parametr;				}
	void setPosition(Vector2f position)				{ Object.x = position.x; Object.y = position.y; }
	void moveVertices(Vector2f pos)
	{
		for (int i = 0; i < Vertices.size(); i++)
		{
			Vertices[i].x += pos.x;
			Vertices[i].y += pos.y;
		}
	}
	void setVertecisPosition(Vector2f pos)
	{
		for (int i = 0; i < Vertices.size(); i++)
		{
			Vertices[i].x = pos.x;
			Vertices[i].y = pos.y;
		}
	}

};
#endif
