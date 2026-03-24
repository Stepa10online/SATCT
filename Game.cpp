#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "WorldObject.h"
#include "Constructor.h"
#include "Collisions.h"
#include "Save_manager_class.h"

#include"imgui/imgui.h"
#include"imgui/imconfig-SFML.h"

#include "Global variables.h"

using namespace sf;
using namespace std;

void updateConvexShape(ConvexShape& convex, Vector2f pos, Vector2f size, IntRect trect);

Vector2f Movement()
{
	/*if (Keyboard::isKeyPressed(Keyboard::A))
	{
		return { -1 * speed, 0 };
		//player.getObjShape().move(-1 * speed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		return { 1 * speed, 0 };
		//player.getObjShape().move(1 * speed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		return { 0, -1 * speed };
		//player.getObjShape().move(0, -1 * speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		return { 0, 1 * speed };
		//player.getObjShape().move(0, 1 * speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		player.getObjShape().rotate(1);
	}*/
	if (gravity_mode)
	{
		velY += gravity_strength * 0.2;
	}
	else
		velY = 0;

	//ImGui::IsKeyPressed(ImGuiKey_Space)* speed;

	
	//cout << collision_dirY << endl;
	if (collision_dirY > 0)
	{
		collision_dirY = -1;
		velY = 1;
		if (collision_dirX > 0) cout << "Right";
		if (collision_dirX < 0) cout << "Left";
		velY -= Keyboard::isKeyPressed(Keyboard::W) * jump_strength;
		//cout << "STOP velY " << velY  << " | collision dir " << collision_dirY << endl;
	}
	if(gravity_mode)
		return { float((Keyboard::isKeyPressed(Keyboard::D) - Keyboard::isKeyPressed(Keyboard::A)) * speed),
			float(velY) };
	return { float((Keyboard::isKeyPressed(Keyboard::D) - Keyboard::isKeyPressed(Keyboard::A)) * speed),
		float((Keyboard::isKeyPressed(Keyboard::S) - Keyboard::isKeyPressed(Keyboard::W)) * speed + velY) };
}

void ConvertAllVerticesToConvexShapes(vector<VertexArray> AllVertices, vector<ConvexShape>&CovexShapes, float* color)
{
	ConvexShape CS;
	
	for (int i = 0; i < AllVertices.size(); i++)
	{
		Color shape_color{
		(Uint8)(color[0]*255),
		(Uint8)(color[1]*255),
		(Uint8)(color[2]*255),
		(Uint8)(color[3]*255),
		};

		cout << "Vertice Number " << i << endl;
		for (int j = 0; j < AllVertices[i].getVertexCount(); j++)
		{
			CS.setPointCount(AllVertices[i].getVertexCount());
			CS.setFillColor(shape_color);
			cout << 1;
			CS.setPoint(j,AllVertices[i][j].position);
			
		}
		CovexShapes.push_back(CS);
	}
}

void ConvertVerticesToConvexShapes(VertexArray Vertices, vector<ConvexShape>& CovexShapes, float* color)
{
	ConvexShape CS;

	Color shape_color{
	(Uint8)(color[0] * 255),
	(Uint8)(color[1] * 255),
	(Uint8)(color[2] * 255),
	(Uint8)(color[3] * 255),
	};

	for (int j = 0; j < Vertices.getVertexCount(); j++)
	{
		CS.setPointCount(Vertices.getVertexCount());
		CS.setFillColor(shape_color);
		cout << 1;
		CS.setPoint(j, Vertices[j].position);

	}
	CovexShapes.push_back(CS);
}

void save_list(const vector<WorldObject>& objs, string filename)
{
	ofstream file("saves/" + filename);

	if (!file.is_open()) // вызов метода is_open()
		cout << "Файл не открыт!\n\n" << endl;

	string s;
	WorldObject obj;

	for (int i = 0; i < objs.size(); i++)
	{


		file << s;
	}
}

void load_list(string filename)
{
	ifstream file("saves/" + filename);

	if (!file.is_open()) // вызов метода is_open()
		cout << "Файл не открыт!\n\n" << endl;

	string s;
	file >> s;

	for (int i = 0; i < s.size(); i++)
	{
		file >> s;
		if (s[i] == '\n') continue;
		cout << s[i] << ',';

	}
	cout << endl;
}

static void UI()
{
	

	///////////////////////////////////////////////////// Constructor //////////////////////////////////////////////////////

	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowBgAlpha(window_alpha);
	ImGui::Begin("Constructor", NULL, 8);
	ImGui::Text("< Constructor >");

	ImGui::InputInt("Shape index", &convex_shape_index);

	ImGui::InputFloat("Pos X", &temp_trect1);
	ImGui::InputFloat("Pos Y", &temp_trect2);
	if(textures.size()>0)
		if (ImGui::InputFloat("Texture rect 1", &trect1)
			|| ImGui::SliderFloat("Slider trect 1", &trect1, 0, textures[texture_index].getSize().x)
			|| ImGui::InputFloat("Texture rect 2", &trect2)
			|| ImGui::SliderFloat("Slider trect 2", &trect2, 0, textures[texture_index].getSize().y))
		{
			updateConvexShape(ConvexShapes[convex_shape_index], { temp_trect1,temp_trect2 }, { temp_trect_size1,temp_trect_size2 },
				{ int(trect1),int(trect2),int(trect3),int(trect4) });
		}
	
	

	ImGui::InputFloat("Texture rect 3", &trect3);
	ImGui::InputFloat("Texture rect 4", &trect4);

	ImGui::InputFloat("Texture size X", &temp_trect_size1);
	ImGui::InputFloat("Texture size Y", &temp_trect_size2);


	if (ImGui::Button("Set Shape", { NULL, 25}))
	{
		if (shape_setting == true) shape_setting = false;
		else shape_setting = true;
		if (vertices.getVertexCount() == 2)
		{
			lines.push_back(vertices[0]);
			lines.push_back(vertices[1]);
		}

		if (vertices.getVertexCount() > 2)
		{

			WorldObject temp_obj;
			temp_obj.getObjShape().setFillColor({
			(Uint8)(object_color[0] * 255),
			(Uint8)(object_color[1] * 255),
			(Uint8)(object_color[2] * 255),
			(Uint8)(object_color[3] * 255),
				});
			temp_obj.setShapeType("polygon");
			temp_obj.setVertices(vertices);
			temp_obj.setStaticParametr(is_obj_static);
			obj.push_back(temp_obj);

			AllVertices.push_back(vertices);
			for (int i = 0; i < vertices.getVertexCount(); i++)
			{
				//cout << object_color[0] * 255 << endl;
				AllVertices[AllVertices.size() - 1][i].color.r = object_color[0] * 255;
				AllVertices[AllVertices.size() - 1][i].color.g = object_color[1] * 255;
				AllVertices[AllVertices.size() - 1][i].color.b = object_color[2] * 255;
				AllVertices[AllVertices.size() - 1][i].color.a = object_color[3] * 255;
			}
		}

		vertices.clear();
		c_clock.restart();
	}
	if (ImGui::IsItemHovered()) ImGui::SetTooltip("Set shape\nif clicked - set shape\nif clicked second time - shape done");
	ImGui::Checkbox("Is Object static", &is_obj_static);
	ImGui::ShowStackToolWindow();
	ImGui::ColorEdit3("Object\nColor", object_color);
	ImGui::BeginDisabled(!(obj.size() > 1)); // Если есть созданные или загруженнеы объекты

	ImGui::BeginChild("Convert editor", { NULL,300 }, 1);
	ImGui::Text("< Convertor >");

	string ss = "Convert " + to_string(changable_obj_index) + " obj\nto convex shapes";
	char cs[100];
	for (int i = 0; i < ss.size(); i++)
	{
		cs[i] = ss[i];
	}
	//setStaticParametr
	if (ImGui::Button(cs))
	{
		ConvertVerticesToConvexShapes(obj[changable_obj_index].getVertexShape(), ConvexShapes, object_color);
	}
	if (ImGui::IsItemHovered()) ImGui::SetTooltip("Convert shape to\nobj with color\n-----------------------------\n<!> CAUTION CONTAINS BUGS <!>\n-----------------------------");


	//ImGui::BeginListBox("List");




	//for (int i = 1; i < obj.size(); i++)
	//{
	//	string str = to_string(i) + ". <" + to_string(obj[i].getVertexShape().getVertexCount()) + ">";

	//	const char* c = str.c_str();
	//	if (ImGui::Selectable(c, sellected))load_list("room-test_room-0.txt"); // loads list of rooms (Example: "room/<name_of_room>/<number>/<additional information>")

	//}

	//ImGui::EndListBox();



	ImGui::SliderInt("Choose obj", &changable_obj_index, 1, obj.size() - (obj.size() > 1));
	ImGui::EndChild();
	ImGui::EndDisabled();

	ImGui::ColorEdit3("Screen\nColor", color_screen_clear);
	if (ImGui::IsItemHovered()) ImGui::SetTooltip("Edit background screen color");
	ImGui::Checkbox("Grid mode", &grid_mode);
	if (ImGui::IsItemHovered()) ImGui::SetTooltip("Enables the binding of the mouse\nto the global grid to create shapes");
	if (grid_mode) ImGui::SliderInt("Grid", &grid_size, 1 * 10, 5 * 10);

	ImGui::Checkbox("Enable collision\n& movement", &collision_enabled);

	ImGui::BeginChild("TextureRect", { NULL,150 }, 1);

	ImGui::Button("Set Texture", { NULL,30 });
	if (ImGui::IsItemHovered()) ImGui::SetTooltip("Set texture\nto object");

	ImGui::EndChild();

	ImGui::SliderFloat("Window alpha:", &window_alpha,0.001,1.00);

	ImGui::End();
	
	///////////////////////////////////////////////// Player Settings //////////////////////////////////////////////////////

	//cout << temp_obj_pos.x << endl;
	ImGui::Begin("Player Settings", NULL, 0);
	if (ImGui::Button("Box"))
	{
		is_shape_is_box = true;
	}
	if (ImGui::Button("Circle"))
	{
		is_shape_is_box = false;
	}
	ImGui::SliderInt("Speed", &speed, 1, 5);
	ImGui::SliderInt("Jump strength", &jump_strength, 1, 15);
	if (ImGui::Checkbox("Gravity enable", &gravity_mode)) gravity_strength = 1;
	if (gravity_mode) ImGui::SliderFloat("Gravity", &gravity_strength, 1, 5);
	else gravity_strength = 0;
	ImGui::End();
	
	//////////////////////////////////////// Box & Cirlce Settings /////////////////////////////////////////////////////////

	//cout << "OBJ SIZE: " << obj.size() << endl;

	if (is_shape_is_box)
	{
		ImGui::Begin("Box Settings", NULL, 6); // 6
		ImGui::InputFloat("Size", &box_size);
		ImGui::ColorEdit4("Color", box_color);
		ImGui::End();
		obj[0].getObjShape().setFillColor({
			(Uint8)(box_color[0] * 255),
			(Uint8)(box_color[1] * 255),
			(Uint8)(box_color[2] * 255),
			(Uint8)(box_color[3] * 255),
			});
		obj[0].setRectSize(box_size, box_size);
		obj[0].setPosition(obj[0].getObjShape().getPosition());
		obj[0].setShapeType("box");
	}
	else
	{
		ImGui::Begin("Circle Settings", NULL, 6); // 6
		ImGui::InputFloat("Size", &circle_radius);
		ImGui::ColorEdit4("Color", circle_color);
		ImGui::End();
		obj[0].getObjShape().setFillColor({
			(Uint8)(circle_color[0] * 255),
			(Uint8)(circle_color[1] * 255),
			(Uint8)(circle_color[2] * 255),
			(Uint8)(circle_color[3] * 255),
			});
		obj[0].setRadius(circle_radius);
		obj[0].getObjShape().setOrigin(circle_radius, circle_radius);
		obj[0].setPosition(obj[0].getObjShape().getPosition());
		obj[0].setShapeType("circle");
	}
	
	///////////////////////////////////////// Save Manager ////////////////////////////////////////////////////////////////

	// Проверка нажатой кнопки "Создать фигуры/форму"
	ImGui::Begin("Save Manager", NULL, 0);
	if (ImGui::Button("Save") && obj.size() - 1 > 0)
	{
		save_list(obj, "room-test_room-0.txt");

	}
	ImGui::End();
	
	///////////////////////////////////////////Is Any item Hovered ////////////////////////////////////////////////////////

	if (!ImGui::IsAnyItemHovered()) // Убрать баг с лишней вершиной при клике на "Set Shape"
	{
		// Задача сложной фигуры / часть конструктора
		if (ImGui::IsMouseClicked(0) && timer >= 0.2 && shape_setting == true)
		{
			Vertex point;
			point.position = { float(mposX), float(mposY) };
			point.color = Color{
			(Uint8)(object_color[0] * 255),
			(Uint8)(object_color[1] * 255),
			(Uint8)(object_color[2] * 255),
			(Uint8)(object_color[3] * 255),
			};
			vertices.append(point);
			c_clock.restart();
		}
	}

}



bool checkTexture(string texture_path)
{
	Texture tx;
	if (!(texture_path.find(".png") || texture_path.find(".jpg") || texture_path.find(".jpeg")))
	{
		cout << "CANNOT LOAD FILE WOTHOUT \".png\" or \".jpg\" or etc..." << endl;
		return false;
	}
	if (!tx.loadFromFile(texture_path))
		return false;
	else
	{
		nTexture temp_ntx;
		temp_ntx.path = texture_path;
		textures.push_back(temp_ntx);
		return true;
	}
	return false;
}

void updateConvexShape(ConvexShape &convex, Vector2f pos, Vector2f size, IntRect trect)
{
	convex.setPosition(pos);
	//if(textures.size()>0)
	//	convex.setTexture(&texture1);
	
	convex.setTexture(&textures_[texture_index]);

	// {0,0}
	// {0,*}
	// {*,*}

	for (int i = 1; i < convex.getPointCount(); i++)
	{
		convex.setPoint(i, { convex.getPoint(i).x + 1 * size.x,convex.getPoint(i).y + 1 * size.y });
		//cout << size.x << ' ' << size.y << endl;
	}
}

ConvexShape SetConvex(int point_count, Vector2f* points,
	float positionX, float positionY,
	IntRect trect)
{
	ConvexShape temp_convex;
	temp_convex.setPosition(positionX, positionY);
	temp_convex.setPointCount(point_count);
	temp_convex.setTexture(&textures[texture_index]);
	for (int i = 0; i < point_count; i++)
	{
		temp_convex.setPoint(i, points[i]);
	}
	temp_convex.setTextureRect({
		int(trect.left),
		int(trect.top),
		int(trect.width),
		int(trect.height)
		});
	return temp_convex;
}


int main()
{

	Save_Manager sv;
	CircleShape cursor;
	cursor.setFillColor(Color::Cyan);
	cursor.setRadius(4);
	cursor.setOrigin(2, 2);

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Main Window
	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "SAT game engine", Style::Default, settings);
	ImGui::SFML::Init(window);
	window.setFramerateLimit(60);
	Clock deltaClock;

	Consturtor c;
	
	if (!texture1.loadFromFile("additional files/textures/stone brick wall.jpg"))
		cout << "ERROR 1" << endl;
	if (!texture2.loadFromFile("additional files/textures/wood.png"))
		cout << "ERROR 2" << endl;

	srand(time(NULL));

	RectangleShape bounds;
	float posx = 100, posy = 100;
	// Определение(spawn) объектов
	for (int i = 0; i < number_of_objects; i++)
	{
		WorldObject temp_obj;
		if (rand() % 2 == 1) // circle
		{
			temp_obj.setRadius(12.5);
			temp_obj.setShapeType("circle");
		}
		else
		{
			temp_obj.setRectSize(box_size, box_size);
			temp_obj.setShapeType("box");
		}
		temp_obj.getObjShape().setPosition(Vector2f{ rand() % 30 * 25.0f + 25.0f,rand() % 20 * 25.0f + 25.0f });
		obj.push_back(temp_obj);
	}
	
	// Задаем параметры игрока
	obj[0].setShapeType("box");
	obj[0].setRectSize(40, 40);
	obj[0].getObjShape().setPosition(windowSize.x / 2, windowSize.y / 2);

	// Параметры колизии (вынесены за цикл, чтобы не переопределялись)
	float depth = 0;
	Vector2f normal;

	while (window.isOpen())
	{
		timer = c_clock.getElapsedTime().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		
		if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::Z) && timer >= 0.3)
		{
			if (vertices.getVertexCount() > 0)
			{
				vertices.resize(vertices.getVertexCount() - 1);
				cout << "CTRL + Z" << endl;
				c_clock.restart();
			}
		}

		//collision_dirY = temp_var;


		// Grid
		if (grid_mode)
		{
			mposX = (int)((Mouse::getPosition(window).x + 0.01 * grid_size) / grid_size + 0.5) * grid_size;
			mposY = (int)((Mouse::getPosition(window).y + 0.01 * grid_size) / grid_size + 0.5) * grid_size;
		}
		else
		{
			mposX = Mouse::getPosition(window).x;
			mposY = Mouse::getPosition(window).y;
		}
		cursor.setPosition(mposX, mposY);

		int j = 0;

		for (int i = 0; i < AllVertices.size(); i++)
		{
			if (AllVertices[i].getVertexCount() == 2)
			{
				lines[j] = AllVertices[i][0].position + Movement();
				j++;
				lines[j] = AllVertices[i][1].position + Movement();
				j++;
			}
		}

		ImGui::Begin("Texture loader");

		ImGui::InputText("Texture Path", texture_path,256);
		if (ImGui::Button("Load"))
		{
			cout << texture_path << endl;
			checkTexture(texture_path);
			strcpy_s(texture_path, "additional files/textures/");
		}
		ImGui::InputInt("Texture index", &texture_index);
		if(ImGui::Button("Set Convex Shape"))
		{
			int point_count = 3;
			float positionX = trectp1, positionY = trectp2;
			cout << "textures size:" << textures.size() << '\t' << "texture path:" << textures[texture_index].path << endl;
			IntRect trect = { int(trect1),int(trect2),int(trect3),int(trect4) };
			Vector2f points[] = { {0,0},{0,float(trects1)},{float(trects2),float(trects3)} };
			ConvexShapes.push_back(SetConvex(point_count, points, positionX, positionY, trect));
		}
		if (ImGui::Button("Update convex Shapes"))
		{
			for (int i = 0; i < ConvexShapes.size(); i++)
			{
				updateConvexShape(ConvexShapes[i], { temp_trect1,temp_trect2}, { temp_trect_size1,temp_trect_size2 },
					{ int(trect1),int(trect2),int(trect3),int(trect4)});
			}
		}

		ImGui::End();



		// Подсчет положения игрока / переделать для сложных фигур
		obj[0].calculateVerticesPos();



		// Колизии
		if(collision_enabled)
		for (int i = 0; i < obj.size() - 1; i++)
		{
			for (int j = i + 1; j < obj.size(); j++)
			{
				UpdateCollisions(obj[i], obj[j], normal, depth, obj[j].getStaticParametr(),collision_dirX, collision_dirY);
			}
				if (obj[i+1].getShapeType() == "polygon") 
					obj[i+1].moveVertices({ -offsetX, -offsetY});
			
		}

		obj[0].getObjShape().move(Movement());
		offsetX = obj[0].getObjShape().getPosition().x - windowSize.x / 2;
		offsetY = obj[0].getObjShape().getPosition().y - windowSize.y / 2;

		obj[0].getObjShape().setPosition({
			obj[0].getRectPosition().x - offsetX,
			obj[0].getRectPosition().y - offsetY });
		UI();

		// Отрисовка
		window.clear(Color{
			(Uint8)(color_screen_clear[0] * 255),
			(Uint8)(color_screen_clear[1] * 255),
			(Uint8)(color_screen_clear[2] * 255)
			});

		for (int i = 1; i < AllVertices.size()+1; i++)
		{
			cursor.setFillColor(Color::Cyan);
			FloatRect temp_frect(obj[i].getFloatRect());
			temp_frect.left = obj[i].getObjShape().getPosition().x;
			temp_frect.top = obj[i].getObjShape().getPosition().y;
			if (temp_frect.intersects({mposX,mposY,1,1}))
			{
				bounds.setSize(
					Vector2f ( obj[i].getFloatRect().width, obj[i].getFloatRect().height )
				);
				bounds.setPosition(obj[i].getObjShape().getPosition().x, obj[i].getObjShape().getPosition().y);
				bounds.setFillColor(Color::Red);
				cursor.setFillColor(Color::Red);
				window.draw(bounds);
			}
		}

		for (int i = 0; i < obj.size(); i++)
		{
			window.draw(obj[i].getObjShape());
			window.draw(obj[i].getVertexShape());
		}
		for (int i = 0; i < ConvexShapes.size(); i++)
		{
			//cout << ":" << convex.getTexture() << endl;
			//cout << ConvexShapes[i].getTexture() << endl;
			window.draw(ConvexShapes[i]);
		}
		window.draw(vertices);
		if (lines.size() >= 1)
		{
			for (int i = 0; i < lines.size() - 1; i++)
			{
				Vertex line[]
				{
					Vertex(lines[i].position),
					Vertex(lines[i + 1].position)
				};

				window.draw(line, 2, Lines);
				i++;
			}
		}
		for (int i = 0; i < ConvexShapes.size(); i++)
		{
			window.draw(ConvexShapes[i]);
		}
		window.draw(cursor);
		window.draw(convex);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}