#ifndef CON_STATE_H
#define CON_STATE_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <tuple>
#include <map> 

struct string_struct
{
	std::vector<std::string> text;
	std::map<std::string, std::string> color = 
	{
		{"RED", "\033[0m"},
		{"RED", "\033[31m"},
		{"ORANGE", "\033[32m"},
		{"YELLOW", "\033[33m"},
		{"GREEN", "\033[34m"},
		{"BLUE", "\033[35m"},
		{"BLUE", "\033[36m"},
	};
	WORD color_id = NULL;

	void add_layer(std::string layer_text)
	{
		this->text.push_back(layer_text);
	}

	void print()
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, this->color_id);
		for (auto& layer : text)
		{
			std::cout << layer << "\n";
		}
		SetConsoleTextAttribute(h, 0);
	}
};

class ConState
{
public:

protected:

private:

	

};

#endif