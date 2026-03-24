#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
using namespace std;

struct tData
{
	int ID;
	string name;
	bool drawable;
};

class Text_class
{
private:
	float Character_size;
	Vector2f Position;
	Color color;
	Text text;

	string String;
	bool ishovered;
	bool ispressed;

	RectangleShape rect_text;
	
	tData data;
public:
	Text_class(int ID = 0, string name = "", float Character_size = 10.f, Vector2f pos = { 0.f,0.f }, Color color = Color::White, string str = "Enter text", bool drawable = true)
	{
		this->data.ID = ID;
		this->data.name = name;
		this->data.drawable = drawable;
		this->Character_size = Character_size;
		this->Position = pos;
		this->String = str;
		this->color = color;
	}

	bool update()
	{
		text.setString(this->String);
		return true;
	}

	// Getters
	float get_text_character_size()
	{
		return this->Character_size;
	}

	string get_text_string()
	{
		return this->String;
	}

	Color get_text_color()
	{
		return this->color;
	}

	Vector2f get_text_position()
	{
		return this->Position;
	}

	int get_text_id()
	{
		return this->data.ID;
	}

	bool get_drawable_parametr()
	{
		return this->data.drawable;
	}

	// Setters
	void set_text_string(string str)
	{
		this->String = str;
	}
	void set_drawable_parametr(bool drawable)
	{
		this->data.drawable = drawable;
	}
	void set_button_data(int ID, string name, bool drawable)
	{
		this->data.ID = ID;
		this->data.name = name;
		this->data.drawable = drawable;
	}
};