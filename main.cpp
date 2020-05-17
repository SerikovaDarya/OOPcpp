#include <cstdlib>
#include <iostream>
#include <random>


#include "Shape.h"
#include "Factory.h"

int Shape::sm_counter = 0;//

using namespace std;


typedef Cont_list<Shape*> list;
typedef Cont_Iter<Shape*> list_iterator;

int main(int argc, char** argv)
{
	std::random_device rd;
	std::uniform_int_distribution<int> gen_type(0, 5);

	try
	{
		list shapes_list;
		for (int i = 0; i<20; i++)
		{
			int job = gen_type(rd);
			if (job == 0)
				shapes_list.add_in_ending(random_factory(std::string("Point")));
			else if (job == 1)
				shapes_list.add_in_ending(random_factory(std::string("Circle")));
			else if (job == 2)
				shapes_list.add_in_ending(random_factory(std::string("Rect")));
			else if (job == 3)
				shapes_list.add_in_ending(random_factory(std::string("Square")));
			else if (job == 4)
				shapes_list.add_in_ending(random_factory(std::string("Polyline")));
			else //if(job == 5)
				shapes_list.add_in_ending(random_factory(std::string("Polygon")));
		}
		std::cout << "Shape::GetCount()=" << Shape::get_counter() << '\n' << "INFO\n";
		list_iterator i(shapes_list.get_beginning());
		while (i != shapes_list.get_ending())
		{
			std::cout << (*(i))->get_info() << '\n';
			i++;
		}
		std::cout << (*i)->get_info() << '\n';
		//вручную очищаем память  (т.к у нас список указателей)
		i = shapes_list.get_beginning();
		while (i != shapes_list.get_ending())
		{
			delete *i;
			i++;
		}
		delete *i;
		std::cout << "Shape::GetCount()=" << Shape::get_counter() << '\n';
	}
	catch (ERRORS_List err)
	{
		switch (err)
		{
		case ERROR_memory_allocation_is_not_possible:
			cout << "ERROR_memory_allocation_is_not_possible\n";
			return -1;
		case ERROR_empty_list:
			cout << "ERROR_empty_list\n";//доступ к элементу из пустого списка
			return -1;
		case ERROR_iterator_have_moved_outside_list:
			cout << "ERROR_iterator_have_moved_outside_list\n";
			return -1;
		}
	}
	catch (ERRORS_of_Shape err)
	{
		switch (err)
		{
		case ERROR_parameters_for_circle_are_wrong:
			cout << "ERROR_parameters_for_circle_are_wrong\n";
			return -1;
		case ERROR_parameters_for_rect_are_wrong:
			cout << "ERROR_parameters_for_rect_are_wrong\n";
			return -1;
		case ERROR_parameters_for_square_are_wrong:
			cout << "ERROR_parameters_for_square_are_wrong\n";
			return -1;
		}
	}
	system("pause");
	return 0;
}