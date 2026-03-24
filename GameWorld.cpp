#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


namespace GameWorld
{
	class GameWorld
	{
	public:
		float MinBodySize = 0.01f * 0.01f;
		float MaxBodySize = 64.f * 64.f;

		float MinDencity = 0.5f;
		float MaxDencity = 21.4f;
		GameWorld();
	private:
		float gravity;
		vector<Vector2f> obj_;
		
		
		

	};

	GameWorld::GameWorld()
	{

	}

}