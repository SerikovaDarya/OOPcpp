#pragma once

#include <string>
// Базовый класс - Printable и наследник - Named
class Printable
{
public:
	virtual std::string get_info() const = 0;
protected:
	Printable()
	{
	}
};

class Named : public Printable
{
public:
	Named(std::string const& name_str) : p_name(name_str)
	{
	}

	virtual std::string get_info() const
	{
		return p_name;
	}

	std::string const& get_name() const
	{
		return p_name;
	}
private:
	std::string const p_name;
};

