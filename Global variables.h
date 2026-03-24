#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct nTexture : public Texture { string path; };

const Vector2i windowSize = Vector2i(1024, 768);

int speed = 2;
int jump_strength = 5;
float gravity_strength = 0.0001;
int number_of_objects = 1;
int grid_size = 25;

float window_alpha = 0.5; // 0.99

float mposX = 0; // Global mouse X pos 
float mposY = 0; // Global mouse Y pos

float offsetX = 0;
float offsetY = 0;

float velX = 0;
float velY = 0;

float collision_dirX = 1;
float collision_dirY = -1;

float trect1=0, trect2 = 0, trect3 = 126, trect4 = 126, trectp1 = 0, trectp2=0 ;
int trects1 = 100, trects2 = 100, trects3 = 100, trects4 = 100;
float timer;

float temp_trect1 = 600, temp_trect2 = 256, temp_trect_size1 = 0, temp_trect_size2 = 0;

float color_screen_clear[3] = {
	(float)79 / 255,
	(float)79 / 255,
	(float)134 / 255,
};

float box_size = 40;
float box_color[4] = {
	(float)255 / 255,
	(float)255 / 255,
	(float)255 / 255,
	(float)255 / 255,
};

float circle_radius = 10;
float circle_color[4] = {
	(float)255 / 255,
	(float)255 / 255,
	(float)255 / 255,
	(float)255 / 255,
};


float object_color[4] = {
	(float)255 / 255,
	(float)255 / 255,
	(float)255 / 255,
	(float)255 / 255,
};

bool shape_setting = false;
bool grid_mode = false;
bool gravity_mode = false;
bool saved = false;
bool collision_enabled = true;
bool is_shape_is_box = true;
bool sellected = false;
bool is_obj_static = false;

int changable_obj_index = 1;

int convex_shape_index = 0;
ConvexShape convex;

char texture_path[256] = "additional files/textures/";
int texture_index;
Texture current_texture;
Texture texture1;
Texture texture2;

vector<nTexture> textures;

Texture textures_[2]{texture1,texture2};

Clock c_clock;
vector<ConvexShape> ConvexShapes;
vector<VertexArray> AllVertices;
VertexArray vertices(TriangleFan);
vector<WorldObject> obj;
vector<Vertex> lines;