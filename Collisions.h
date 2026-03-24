#pragma once

#include <SFML/Graphics.hpp>
#include "VectorMath.h"

using namespace sf;


void ProjectVertices(
	vector<Vector2f>vertices, Vector2f axis,
	float& min, float& max)
{
	min = INFINITY;
	max = -INFINITY;

	for (int i = 0; i < vertices.size(); i++)
	{
		Vector2f v = vertices[i];
		float proj = VectorMath::Dot(v, axis);

		if (proj < min) min = proj;
		if (proj > max) max = proj;
	}
}
void ProjectCircle(Vector2f center, float radius, Vector2f axis, float& min, float& max)
{
	Vector2f direction = VectorMath::Normalize(axis);
	Vector2f directionAndRadius = direction * radius;

	Vector2f p1 = center + directionAndRadius;
	Vector2f p2 = center - directionAndRadius;

	min = VectorMath::Dot(p1, axis);
	max = VectorMath::Dot(p2, axis);

	if (min > max)
	{
		float t = min;
		min = max;
		max = t;
	}
}

Vector2f FindArithmeticMean(vector<Vector2f> vertices)
{
	float sumx = 0;
	float sumy = 0;

	for (int i = 0; i < vertices.size(); i++)
	{
		Vector2f v = vertices[i];
		sumx += v.x;
		sumy += v.y;
	}

	return Vector2f(sumx / (float)vertices.size(), sumy / (float)vertices.size());
}

int FindClosestPointOnPolygon(Vector2f circleCenter, vector<Vector2f> vertices)
{
	int result = -1;
	float minDistance = INFINITY;

	for (int i = 0; i < vertices.size(); i++)
	{
		Vector2f v = vertices[i];
		float distance = VectorMath::Distance(v, circleCenter);
		if (distance < minDistance)
		{
			minDistance = distance;
			result = i;
		}
	}
	
	return result;
}

bool IntersectCirclePolygon(Vector2f circleCenter, float circleRadius,
	const vector<Vector2f>& vertices,
	Vector2f& normal, float& depth)
{
	normal = { 0,0 };
	depth = INFINITY;
	Vector2f axis = { 0,0 };
	float axisDepth = 0;
	float minA, maxA, minB, maxB;

	for (int i = 0; i < vertices.size(); i++)
	{
		Vector2f va = vertices[i];
		Vector2f vb = vertices[(i + 1) % vertices.size()];

		Vector2f edge = vb - va;
		axis = Vector2f(-edge.y, edge.x);
		axis = VectorMath::Normalize(axis);

		ProjectVertices(vertices, axis, minA, maxA);
		ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA)
		{
			return false;
		}

		axisDepth = min(maxB - minA, maxA - minB);
		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}
	int cpIndex = FindClosestPointOnPolygon(circleCenter, vertices);
	Vector2f cp = vertices[cpIndex];

	axis = cp - circleCenter;
	axis = VectorMath::Normalize(axis);

	ProjectVertices(vertices, axis, minA, maxA);
	ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);

	if (minA >= maxB || minB >= maxA)
	{
		return false;
	}

	axisDepth = min(maxB - minA, maxA - minB);
	if (axisDepth < depth)
	{
		depth = axisDepth;
		normal = axis;
	}

	// Get reid of if everything is OK
	//depth /= VectorMath::Length(normal);
	//normal = VectorMath::Normalize(normal);

	Vector2f polygonCenter = FindArithmeticMean(vertices);

	Vector2f direction = polygonCenter - circleCenter;

	if (VectorMath::Dot(direction, normal) < 0.0)
	{
		normal = -normal;
	}

	return true;
}

bool IntersectPolygons(vector<Vector2f> verticesA, vector<Vector2f> verticesB, Vector2f& normal, float& depth)
{
	normal = { 0,0 };
	depth = INFINITY;
	Vector2f axis;
	float minA, maxA, minB, maxB;

	for (int i = 0; i < verticesA.size(); i++)
	{
		Vector2f va = verticesA[i];
		Vector2f vb = verticesA[(i + 1) % verticesA.size()];

		Vector2f edge = vb - va;
		axis = Vector2f(-edge.y, edge.x);
		axis = VectorMath::Normalize(axis);

		ProjectVertices(verticesA, axis, minA, maxA);
		ProjectVertices(verticesB, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA)
		{
			return false;
		}

		float axisDepth = min(maxB - minA, maxA - minB);
		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}
	for (int i = 0; i < verticesB.size(); i++)
	{
		Vector2f va = verticesB[i];
		Vector2f vb = verticesB[(i + 1) % verticesB.size()];

		Vector2f edge = vb - va;
		axis = Vector2f(-edge.y, edge.x);
		axis = VectorMath::Normalize(axis);

		ProjectVertices(verticesA, axis, minA, maxA);
		ProjectVertices(verticesB, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA)
		{
			return false;
		}
		float axisDepth = min(maxB - minA, maxA - minB);
		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}

	// Get reid of if everything is OK
	//depth /= VectorMath::Length(normal);
	//normal = VectorMath::Normalize(normal);

	Vector2f centerA = FindArithmeticMean(verticesA);
	Vector2f centerB = FindArithmeticMean(verticesB);

	Vector2f direction = centerB - centerA;

	if (VectorMath::Dot(direction, normal) < 0.0)
	{
		normal = -normal;
	}

	return true;
}

bool IntersectCircles(
	Vector2f centerA, float radiusA,
	Vector2f centerB, float radiusB,
	Vector2f& normal, float& depth)
{
	normal = { 0.f,0.f };
	depth = 0.f;

	float distance = VectorMath::Distance(centerA, centerB);
	float radii = radiusA + radiusB;
	if (distance >= radii) return false;

	normal = VectorMath::Normalize(centerB - centerA);
	depth = radii - distance;

	return true;

}


bool UpdateCollisions(WorldObject& a, WorldObject& b, Vector2f normal, float depth, bool isstatic,
	float &collision_dirX,float &collision_dirY)
{
	a.calculateVerticesPos();
	b.calculateVerticesPos();

	// MOUSE && POLYGON

	// POLYGON && POLYGON
	if (a.getShapeType() == "polygon" && b.getShapeType() == "polygon")
	{
		if (IntersectPolygons(a.getAllVerteces(), b.getAllVerteces(), normal, depth))
		{
			if (isstatic)
				a.moveVertices({ -normal.x * depth / 2.0f, -normal.y * depth / 2.0f });
			else
			{
				a.moveVertices({ -normal.x * depth / 2.0f, -normal.y * depth / 2.0f });
				b.moveVertices({ normal.x * depth / 2.0f,normal.y * depth / 2.0f });
			}
		}
	}

	// BOX && POLYGON
	if (a.getShapeType() == "box" && b.getShapeType() == "polygon")
	{
		if (IntersectPolygons(a.getRectVerteces(), b.getAllVerteces(), normal, depth))
		{
			if (isstatic)
				a.getObjShape().move(-normal.x * depth / 2.0f, -normal.y * depth / 2.0f);
			else
			{
				a.getObjShape().move(-normal.x * depth / 2.0f, -normal.y * depth / 2.0f);
				b.moveVertices({ normal.x * depth / 2.0f,  normal.y * depth / 2.0f });
			}

			if (normal.x > 0) collision_dirX = 1;
			else if (normal.x < 0) collision_dirX = -1;
			else collision_dirX = 0;
 
			if (normal.y > 0) collision_dirY = 1;
			else if (normal.y < 0) collision_dirY = -1;
			else collision_dirY = 0;

			cout << collision_dirX << " " << collision_dirY << " | " << normal.x << " " << normal.y << endl;
		}
	}
	
	// BOX && BOX
	if (a.getShapeType() == "box" && b.getShapeType() == "box")
	{
		if (IntersectPolygons(a.getRectVerteces(), b.getRectVerteces(), normal, depth))
		{
			//cout << depth << endl;
			//a.getObjShape().move(-normal.x * depth / 2.0f, -normal.y * depth / 2.0f);
			b.getObjShape().move( normal.x * depth / 2.0f,  normal.y * depth / 2.0f);
		}
	}

	// BOX && CIRCLE
	if (a.getShapeType() == "box" && b.getShapeType() == "circle")
	{
		if (IntersectCirclePolygon(b.getCirclePosition(),
			b.getRadius(), a.getRectVerteces(), normal, depth))
		{
			a.getObjShape().move( normal.x * depth / 2.0f,  normal.y * depth / 2.0f);
			b.getObjShape().move( -normal.x * depth / 2.0f,  -normal.y * depth / 2.0f);
			
			//b.moveVertices({ normal.x * depth / 2.0f, normal.y * depth / 2.0f });
		}
	}


	// CIRCLE && BOX
	if (a.getShapeType() == "circle" && b.getShapeType() == "box")
	{
		if (IntersectCirclePolygon(a.getCirclePosition(),
			a.getRadius(), b.getRectVerteces(), normal, depth))
		{
			//a.getObjShape().move(-normal.x * depth / 2.0f, -normal.y * depth / 2.0f);
			b.getObjShape().move( normal.x * depth / 2.0f,  normal.y * depth / 2.0f);

			//b.moveVertices({ normal.x * depth / 2.0f, normal.y * depth / 2.0f });
		}
	}

	// POLYGON && CIRLE
	if (a.getShapeType() == "polygon" && b.getShapeType() == "circle")
	{
		if (IntersectCirclePolygon(b.getCirclePosition(),
			b.getRadius(), a.getAllVerteces(), normal, depth))
		{
			//return { normal.x * depth / 2.0f, normal.y * depth / 2.0f };
			//a.moveVertices({ normal.x * depth / 2.0f, normal.y * depth / 2.0f });
			b.getObjShape().move( -normal.x * depth / 2.0f,  -normal.y * depth / 2.0f);
		}
	}
	// CIRCLE && POLYGON
	if (a.getShapeType() == "circle" && b.getShapeType() == "polygon")
	{
		if (IntersectCirclePolygon(a.getCirclePosition(),
			a.getRadius(), b.getAllVerteces(), normal, depth))
		{
			
			//a.getObjShape().move(-normal.x * depth / 2.0f, -normal.y * depth / 2.0f);
			b.moveVertices({  normal.x * depth / 2.0f, normal.y * depth / 2.0f });
		}
	}

	// CIRCLE && CIRCLE
	if (IntersectCircles(a.getCirclePosition(), a.getRadius(),
						b.getCirclePosition(), b.getRadius(),
						normal, depth))
	{
		//a.getObjShape().move(-normal.x * depth / 2.0f, -normal.y * depth / 2.0f);
		b.getObjShape().move( normal.x * depth / 2.0f,  normal.y * depth / 2.0f);
	}
	return true;
}