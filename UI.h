#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

#include "Button_class.h"
#include "Text_class.h"

using namespace sf;
using namespace std;

class UI : protected Button
{
private:
	vector<Button> buttons;
	vector<Text_class> texts;

public:
	UI() {}

	void UpdateUI(RenderWindow& window)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].button_update(window);
		}
		for (int i = 0; i < texts.size(); i++)
		{
			texts[i].update();
		}
	}

	// Getters
	int Get_Pressed_Button_ID()
	{
		for (int i = 1; i < buttons.size() + 1; i++)
		{
			if (buttons[i - 1].get_pressed_state() == true)
			{
				return i;
			}
		}
		return 0;
	}
	int Get_Hovered_Button_ID()
	{
		for (int i = 1; i < buttons.size()+1; i++)
		{
			if (buttons[i-1].get_hover_state())
			{
				return i;
			}
		}
		return 0;
	}
	// Setters
	void Set_Text_String(int ID, string str)
	{
		this->texts[ID - 1].set_text_string(str);
	}
	void Set_Button_Drawable_Parametr(int ID, bool drawable)
	{
		buttons[ID - 1].set_drawable_parametr(drawable);
	}
	void Set_Text_Drawable_Parametr(int ID, bool drawable)
	{
		texts[ID - 1].set_drawable_parametr(drawable);
	}
	void Set_Button_Pressed_State(int ID, bool state)
	{
		buttons[ID - 1].button_set_pressed_state(state);
	}
	// Other methods
	void create_Button(int ID, string name, Vector2f size, float character_size, Vector2f pos, string str, bool drawable = true)
	{
		Button btn(ID, name, size, character_size, pos, str, drawable);
		buttons.push_back(btn);
	}
	void create_Text(int ID, string name, float character_size, Vector2f pos, Color color, string str, bool drawable = true)
	{
		Text_class txt(ID, name, character_size, pos, color, str, drawable);
		texts.push_back(txt);
	}

	void Draw_interface(RenderWindow&window)
	{
		Text text;
		Font font;
		if (!font.loadFromFile("Tablon-Regular.ttf"))
		{
			cout << "Text not loaded" << endl;
		}
		text.setFont(font);
		for (int i = 0; i < buttons.size(); i++)
		{
			if (!buttons[i].get_drawable_parametr()) continue;
			window.draw(buttons[i].get_rect_button());

			text.setPosition(buttons[i].get_rect_button().getPosition());
			text.setString(buttons[i].get_button_string());
			text.setFillColor(Color::White);
			text.setCharacterSize(buttons[i].get_text_character_size());
			
			window.draw(text);
		}
		for (int i = 0; i < texts.size(); i++)
		{
			if (!texts[i].get_drawable_parametr()) continue;
			text.setCharacterSize(texts[i].get_text_character_size());
			text.setPosition(texts[i].get_text_position());
			text.setString(texts[i].get_text_string());
			text.setFillColor(Color::White);
			/*text.setString("Enter text");
			text.setPosition({ 100,0 });*/
			
			window.draw(text);
		}
	}
	void Logic()
	// В планах перенести всю логику нажатия кнопок в эту логику
	// Проблемы в переменных: gravity_mode, grid_mode, ...
	// Вынести их в отдельную структуру
	{

	}
};