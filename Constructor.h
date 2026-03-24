#include<SFML/Graphics.hpp>
#include <fstream>
#include<iostream>

using namespace sf;
using namespace std;

class Consturtor
{
private:
	ofstream out;
	Clock clk;
	float timer;
public:
	Consturtor() {}

	/*Vector2f setPoint(Vector2i m_pos)
	{
		return 
	}*/

	void Run(RenderWindow& window)
	{
		VertexArray points(TriangleFan);
		timer = clk.getElapsedTime().asSeconds();
		points.append(Vertex({ 0,0 }));
		out.open("points.txt");

		

		window.draw(points);
	}

};