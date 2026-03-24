#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
using namespace std;

struct bData
{
	int ID;
	string name;
	bool drawable;
};

class Button
{
private:
	float Character_size;
	Vector2f Size;
	Vector2f Position;
	Color color;
	Text text;

	string String;
	bool ispressed;
	bool ishovered;

	RectangleShape rect_Button;
	bData data;
public:
	/* Standart size
	   X = 50...
	   Y = 25
	Ch_S = 20
	*/
	Button(int ID = 0, string name = "", Vector2f size = { 50,25 }, float character_size = 20, Vector2f positon = { 20,20 }, string str = "Enter text", bool drawable = true, Color color = {45,45,45,255}/*{ 150,150,150,255 }*/, bool ispressed = false)
	{
		this->data.ID = ID;
		this->data.name = name;
		this->data.drawable = drawable;
		this->Size = size;
		this->Character_size = character_size;
		this->Position = positon;
		this->String = str;
		this->color = color;
		this->ispressed = ispressed;
	}
	
	bool button_update(RenderWindow&window)
	{
		check_mouse(window);
		if (this->ispressed == true)
		{
			//cout << data.ID << endl;
			float k = 0.5;
			rect_Button.setFillColor({ Uint8(150 * k),Uint8(150 * k),Uint8(150 * k),255 });
			return true;
		}
		if(this->ishovered == true)
		{
			float k = 0.9;
			rect_Button.setFillColor({ Uint8(150 * k),Uint8(150 * k),Uint8(150 * k),255 });
			return true;
		}
		rect_Button.setFillColor(color);
		return true;
	}

	bool get_drawable_parametr()
	{
		return this->data.drawable;
	}

	void set_drawable_parametr(bool drawable)
	{
		this->data.drawable = drawable;
	}

	RectangleShape get_rect_button()
	{
		rect_Button.setSize(this->Size);
		rect_Button.setPosition(this->Position);

		return rect_Button;
	}

	void set_button_data(int ID, string name, bool drawable)
	{
		this->data.ID = ID;
		this->data.name = name;
		this->data.drawable = drawable;
	}

	bData get_button_data()
	{
		return this->data;
	}

	Color get_button_color()
	{
		return this->color;
	}

	string get_button_string()
	{
		return this->String;
	}

	Text get_text_button()
	{
		return this->text;
	}

	bool get_pressed_state()
	{
		return this->ispressed;
	}

	bool get_hover_state()
	{
		return this->ishovered;
	}

	float get_text_character_size()
	{
		return this->Character_size;
	}

	void check_mouse(RenderWindow& window)
	{
		Mouse m;
		button_set_pressed_state(m.getPosition(window));
	}

	void button_set_pressed_state(bool state)
	{
		this->ispressed = state;
	}
	void button_set_pressed_state(Vector2i m_pos)
	{
		if (m_pos.x >= this->Position.x && m_pos.x <= this->Position.x + this->Size.x &&
			m_pos.y >= this->Position.y && m_pos.y <= this->Position.y + this->Size.y)
		{
			this->ishovered = true;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->ispressed = true;
			}
			else
			{
				this->ispressed = false;
			}
		}
		else
		{
			this->ishovered = false;
		}
	}
};