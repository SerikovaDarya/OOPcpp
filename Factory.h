#pragma once

#include "Shape.h"
#include <random>


Shape* random_factory(const std::string &type)
{
	static std::random_device rd;
	std::uniform_int_distribution<int> gen_coord(0, 1000), gen_r(1, 100), gen_num(0, 12);

	if (type == std::string("Point"))
		return new Point(gen_coord(rd), gen_coord(rd));
	else if (type == std::string("Circle"))
		return new Circle(Point(gen_coord(rd), gen_coord(rd)), gen_r(rd));//Circle 
	else if (type == std::string("Rect"))
	{
		int x1 = gen_coord(rd), y1 = gen_coord(rd), x2, y2;
		do
		{
			x2 = gen_coord(rd);
		} while (x1 == x2);
		do
		{
			y2 = gen_coord(rd);
		} while (y1 == y2);
		return new Rect(Point(x1, y1), Point(x2, y2));//Rect 
	}
	else if (type == std::string("Square"))
	{
		int x1 = gen_coord(rd), y1 = gen_coord(rd), x2, y2;
		do
		{
			x2 = gen_coord(rd);
			y2 = gen_coord(rd);
		} while (x1 == x2 && y1 == y2);
		return new Square(Point(x1, y1), Point(x2, y2));//Square 
	}
	else if (type == std::string("Polyline"))
	{
		Cont_list<Point> a = Cont_list<Point>();
		int n = gen_num(rd);
		for (int i = 0; i<n; i++)
			a.add_in_beginning(Point(gen_coord(rd), gen_coord(rd)));
		return new Polyline(a);
	}
	else if (type == std::string("Polygon"))
	{
		Cont_list<Point> a = Cont_list<Point>();
		int n = gen_num(rd);
		for (int i = 0; i<n; i++)
			a.add_in_beginning(Point(gen_coord(rd), gen_coord(rd)));
		return new Polygon(a);
	}
	else
		return NULL;
}
