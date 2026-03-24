#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include"WorldObject.h"

using namespace sf;
using namespace std;

class Save_Manager
{
public:
	Save_Manager(){}
	
	vector<WorldObject> Manager(const vector<WorldObject>& points)
	{
		setlocale(LC_ALL, "rus");

		cout << "Trying to save..." << endl;

		char ch='0';
		while (ch != 'q')
		{
			cout << "Выберите действие: [S - save L - load Q - quit]" << endl << ">";
			cin >> ch;
			
			if (ch == 's' || ch == 'S')
			{
				//Save(points);
			}
			if (ch == 'l', ch == 'L')
			{
				//Load(points);
			}
		}
		cout << "Saved succesfuly" << endl;
		return points;
	}

	void Save(const vector<WorldObject>& points)
	{
		setlocale(LC_ALL, "rus");

		Vertex a;

		ofstream file("test.txt");

		if (!file.is_open()) // вызов метода is_open()
			cout << "Файл не открыт!\n\n" << endl;
		
		for (auto t : points)
		{
			for (int i = 0; i < t.getAllVerteces().size(); i++)
			{
				cout << t.getAllVerteces()[i].x << endl;
			}
		}

		/*for (int i = 0; i < points.size(); i++)
		{
			string s = to_string(points[i].getPointCount());
			file << s;
			for (int point_cnt = 0; point_cnt < points[i].getPointCount(); point_cnt++)
			{
				s = ("|" + to_string(points[i].getPoint(point_cnt).x) + " " + to_string(points[i].getPoint(point_cnt).y));
				file << s;
			}
			file << "\n";
		}*/

		cout << "Записб прошла успешно!" << endl;
	}


	bool Load(const vector<ConvexShape>& points)
	{
		setlocale(LC_ALL, "rus");

		ifstream file("test.txt");

		if (!file.is_open()) // вызов метода is_open()
		{
			cout << "Файл не открыт!\n\n" << endl;
			return false;
		}

		for (int i = 0; i < points.size(); i++)
		{
			string s;
			file >> s;
			cout << s;
		}


		cout << "Чтение прошло успешно!" << endl;
		return true;
	}

private:

};