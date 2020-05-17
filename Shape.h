#pragma once

#include <string>
#include <iostream>  
#include <sstream>
#include <cmath>
#include <iterator>

#include "Base.h"

const double P_PI = 3.14;


enum ERRORS_List { ERROR_memory_allocation_is_not_possible, ERROR_empty_list, ERROR_iterator_have_moved_outside_list };

enum ERRORS_of_Shape { ERROR_parameters_for_circle_are_wrong, ERROR_parameters_for_rect_are_wrong, ERROR_parameters_for_square_are_wrong };



//„тобы определени€ шаблонов увидели реализацию

template <class Type>
class Cont_Iter;

template <class Type>
struct List_element
{
public:
	List_element(Type const& el, List_element<Type> *n) : p_element(el), p_next(n)
	{
	}

	Type p_element;
	List_element<Type>* p_next;
};



template <class Type>
class Cont_list
{
public:
	Cont_list() :p_number(0), p_first(NULL), p_last(NULL)
	{
	}

	Cont_list(Cont_list<Type> const& orig) :p_number(0), p_first(NULL), p_last(NULL) 
	{
		if (orig.is_empty())
			return;
		Cont_Iter<Type> i = orig.get_beginning();
		while (i != orig.get_ending())
		{
			add_in_ending(*i);
			i++;
		}
		add_in_ending(*i);
	}

	~Cont_list()
	{
		clear_list();
	}

	Cont_Iter<Type> get_beginning() const
	{
		return Cont_Iter<Type>(p_first);
	}

	Cont_Iter<Type> get_ending() const
	{
		return Cont_Iter<Type>(p_last);
	}

	void add_in_beginning(Type const& element) 

	{
		if (p_number == 0)
			p_first = p_last = new List_element<Type>(element, NULL);
		else
			p_first = new List_element<Type>(element, p_first);
		p_number++;
	}


	void add_in_ending(Type const& element) 

	{
		if (p_number == 0)
			p_first = p_last = new List_element<Type>(element, NULL);
		else
		{
			p_last->p_next = new List_element<Type>(element, NULL);
			p_last = p_last->p_next;
		}
		p_number++;
	}


	void delete_first() throw(ERRORS_List)
	{
		if (p_number == 0)
			throw ERROR_empty_list;
		else if (p_number == 1)
		{
			delete p_first;
			p_first = p_last = NULL;
		}
		else
		{
			List_element<Type> *temp = p_first->p_next;
			delete p_first;
			p_first = temp;
		}
		p_number--;
	}

	void delete_last() throw(ERRORS_List)
	{
		if (p_number == 0)
			throw ERROR_empty_list;
		else if (p_number == 1)
		{
			delete p_first;
			p_first = p_last = NULL;
			p_number = 0;
		}
		else
		{
			//поиск предпоследнего

			List_element<Type>* a = p_first;
			while (a->p_next != p_last)//пока следующий за текущим не последний 
				a = a->p_next;
			delete p_last;
			p_last = a;
			p_last->p_next = NULL;
			p_number--;
		}
	}

	void clear_list()
	{
		List_element<Type> *temp;
		while (p_first != NULL)//ѕока не пуст, можно удал€ть
		{
			temp = p_first;
			p_first = p_first->p_next;
			delete temp;
		}
		p_number = 0;
	}

	bool is_empty() const
	{
		return p_number == 0;
	}

	int get_element_number() const
	{
		return p_number;
	}
private:
	int p_number;
	List_element<Type> *p_first, *p_last;
};



template <class Type>
class Cont_Iter : public std::iterator<std::forward_iterator_tag, Type>
{
	friend class Cont_list<Type>;
public:
	Cont_Iter(const Cont_Iter &it) : p_ptr(it.p_ptr)
	{
	}

	Cont_Iter operator=(Cont_Iter const& other)
	{
		p_ptr = other.p_ptr;
		return *this;
	}

	bool operator==(Cont_Iter const& other) const
	{
		return p_ptr == other.p_ptr;
	}
	bool operator!=(Cont_Iter const& other) const
	{
		return p_ptr != other.p_ptr;
	}

	typename Cont_Iter::reference operator*() const throw(ERRORS_List) //јналогии дл€ получени€ константы
	{
		if (p_ptr == NULL)
			throw(ERROR_empty_list);
		return p_ptr->p_element;
	}

	operator Type*() const throw(ERRORS_List)
	{
		if (p_ptr == NULL)
			throw(ERROR_empty_list);
		return &(p_ptr->p_element);
	}

	Cont_Iter& operator++() throw(ERRORS_List)//++a
	{
		if (p_ptr->p_next == NULL)
			throw ERROR_iterator_have_moved_outside_list;
		List_element<Type>* temp = p_ptr;
		p_ptr = p_ptr->p_next;
		return *temp;
	}

	Cont_Iter& operator++(int) throw(ERRORS_List)//a++ 
	{
		if (p_ptr->p_next == NULL)
			throw ERROR_iterator_have_moved_outside_list;
		p_ptr = p_ptr->p_next;
		return *this;
	}

protected:
	Cont_Iter(List_element<Type>* p) : p_ptr(p)
	{
	}
private:
	List_element<Type>* p_ptr;
};




class Shape : public Printable
{
public:

	virtual ~Shape()
	{
		sm_counter--;
	}

	virtual std::string get_info() const = 0;

	static int get_counter()
	{
		return sm_counter;
	}


protected:
	Shape()
	{
		sm_counter++;
	}
private:
	static int sm_counter;//=0
};


class Point : public Shape, public Named
{
public:
	Point(double _x, double _y) : Named("Point"), p_x(_x), p_y(_y)
	{
	}

	Point(Point const& orig) : Named("Point"), p_x(orig.p_x), p_y(orig.p_y)
	{
	}

	virtual std::string get_info() const
	{
		std::stringstream ss;
		ss << get_name() << "\nCoordinates: (" << p_x << ", " << p_y << ")\n";
		return ss.str();
	}

	double get_x() const
	{
		return p_x;
	}

	double get_y() const
	{
		return p_y;
	}

	friend double get_dist(Point const& a, Point const& b)
	{
		return sqrt((a.p_x - b.p_x)*(a.p_x - b.p_x) + (a.p_y - b.p_y)*(a.p_y - b.p_y));
	}

	friend std::ostream& operator << (std::ostream &s, Point const &a)
	{
		return s << a.get_info();
	}
private:
	double p_x, p_y;
};

class Circle : public Shape, public Named
{
public:
	Circle(Point const& c, double _r) throw(ERRORS_of_Shape) : Named("Circle"), p_cen(c), p_r(_r)
	{
		if (p_r <= 0)
			throw ERROR_parameters_for_circle_are_wrong;
	}

	virtual std::string get_info() const
	{
		std::stringstream ss;
		ss << get_name() << "\nCenter coordinates: (" << p_cen.get_x() << ", " << p_cen.get_y() << ")\nR=" << p_r << "\nL=" << 2 * P_PI*p_r << "\nS=" << P_PI*p_r*p_r << "\n";
		return ss.str();
	}
	friend std::ostream& operator << (std::ostream &s, Circle const &a)
	{
		return s << a.get_info();
	}
private:
	Point p_cen;
	double p_r;
};

class Rect : public Shape, public Named
{
public:
	Rect(Point const& _a, Point const& _b) throw(ERRORS_of_Shape) : Named("Rect"), p_a(_a), p_b(_b)
	{
		if (p_a.get_x() == p_b.get_x() || p_a.get_y() == p_b.get_y())
			throw ERROR_parameters_for_rect_are_wrong;
	}

	virtual std::string get_info() const//вывести b, d
	{
		std::stringstream ss;
		ss << get_name() << "\nCoordinates s: a=(" << p_a.get_x() << ", " << p_a.get_y() << "), c=(" << p_b.get_x() << ", " << p_b.get_y() << ")\n";
		ss << "L=" << 2 * fabs(p_a.get_x() - p_b.get_x()) + 2 * fabs(p_a.get_y() - p_b.get_y()) << "\n";
		ss << "S=" << fabs((p_a.get_x() - p_b.get_x())*(p_a.get_y() - p_b.get_y())) << "\n";
		return ss.str();
	}

	friend std::ostream& operator << (std::ostream &s, Rect const &a)
	{
		return s << a.get_info();
	}
private:
	Point p_a, p_b;
};

class Square : public Shape, public Named
{
public:
	Square(Point const& _a, Point const& _b) throw(ERRORS_of_Shape) : Named("Square"), p_a(_a), p_b(_b)
	{
		if (p_a.get_x() == p_b.get_x() && p_a.get_y() == p_b.get_y())
			throw ERROR_parameters_for_square_are_wrong;
	}

	virtual std::string get_info() const
	{
		std::stringstream ss;
         //јн.геом

		ss << get_name() << "\nCoordinates s: a=(" << p_a.get_x() << ", " << p_a.get_y() <<
			"), b=(" << (p_a.get_x() + p_b.get_x()) / 2 + (p_a.get_y() - p_b.get_y()) / 2 << ", " << (p_a.get_y() + p_b.get_y()) / 2 - (p_a.get_x() - p_b.get_x()) / 2 <<
			"), c=(" << p_b.get_x() << ", " << p_b.get_y() <<
			"), d=(" << (p_a.get_x() + p_b.get_x()) / 2 - (p_a.get_y() - p_b.get_y()) / 2 << ", " << (p_a.get_y() + p_b.get_y()) / 2 + (p_a.get_x() - p_b.get_x()) / 2 << ")\n";//восстанавливаем еще 2 точки 

		ss << "L=" << 2.0 / sqrt(0.5)*sqrt(fabs((p_a.get_x() - p_b.get_x())*(p_a.get_x() - p_b.get_x()) + (p_a.get_y() - p_b.get_y())*(p_a.get_y() - p_b.get_y()))) << "\n";
		ss << "S=" << 0.5*((p_a.get_x() - p_b.get_x())*(p_a.get_x() - p_b.get_x()) + (p_a.get_y() - p_b.get_y())*(p_a.get_y() - p_b.get_y())) << "\n";
		return ss.str();
	}
	friend std::ostream& operator << (std::ostream &s, Square const &a)
	{
		return s << a.get_info();
	}
private:
	Point p_a, p_b;
};

class Polyline : public Shape, public Named
{
public:
	Polyline() : Named("Polyline"), p_points()
	{
	}

	Polyline(Cont_list<Point> const &l) : Named("Polyline"), p_points(l)
	{
	}

	virtual std::string get_info() const
	{
		std::stringstream ss;
		ss << get_name() << '\n';
		if (p_points.is_empty())
		{
			ss << "Vershin net\nL=0\n";
		}
		else if (p_points.get_element_number() == 1)
		{
			ss << "Vershini:\n(" << (*p_points.get_beginning()).get_x() << ',' << (*p_points.get_beginning()).get_y() << ')' << "\nL=0\n";
		}
		else
		{
			ss << "Vershini:\n";
			Cont_Iter<Point> i = p_points.get_beginning(), j = p_points.get_beginning()++;
			double len = 0;
			while (j != p_points.get_ending())
			{
				ss << '(' << (*i).get_x() << ',' << (*i).get_y() << ')' << '\n';
				i++;
				j++;
				len += get_dist(*i, *j);
			}
			ss << '(' << (*i).get_x() << ',' << (*i).get_y() << ')' << '\n';
			ss << "L=" << len << '\n';
		}
		return ss.str();
	}
	friend std::ostream& operator << (std::ostream &s, Polyline const &a)
	{
		return s << a.get_info();
	}

	void add_point(Point const& p)
	{
		p_points.add_in_ending(p);
	}
private:
	Cont_list<Point> p_points;
};

class Polygon : public Shape, public Named
{
public:
	Polygon(Cont_list<Point> const &l) : Named("Polygon"), p_points(l)
	{
	}

	virtual std::string get_info() const
	{
		std::stringstream ss;
		ss << get_name() << '\n';
		if (p_points.is_empty())
		{
			ss << "Vershin net\nL=0\n";
		}
		else if (p_points.get_element_number() == 1)
		{
			ss << "Vershini:\n(" << (*p_points.get_beginning()).get_x() << ',' << (*p_points.get_beginning()).get_y() << ')' << "\nL=0\n";
		}
		else
		{
			ss << "Vershini:\n";
			Cont_Iter<Point> i = p_points.get_beginning(), j = p_points.get_beginning()++;
			double len = 0;
			while (j != p_points.get_ending())
			{
				ss << '(' << (*i).get_x() << ',' << (*i).get_y() << ')' << '\n';
				i++;
				j++;
				len += get_dist(*i, *j);
			}
			len += get_dist(*p_points.get_beginning(), *p_points.get_ending());
			ss << '(' << (*i).get_x() << ',' << (*i).get_y() << ')' << '\n';
			ss << "L=" << len << '\n';
		}
		return ss.str();
	}
	friend std::ostream& operator << (std::ostream &s, Polygon const &a)
	{
		return s << a.get_info();
	}
private:
	Cont_list<Point> p_points;
};


