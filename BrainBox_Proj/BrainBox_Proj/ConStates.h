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
		{"RESET", "\033[0m"},
		{"BLACK", "\033[30m"},
		{"RED", "\033[31m"},
		{"GREEN", "\033[32m"},
		{"YELLOW", "\033[33m"},
		{"BLUE", "\033[34m"},
		{"PURPLE", "\033[35m"},
		{"CYAN", "\033[36m"},
	};
	
	string_struct()
	{
	}

	void add_layer(std::string layer_text)
	{
		this->text.push_back(layer_text);
	}

	void add_layer(std::vector<std::string> layers)
	{
		for (auto& str : layers)
		{
			this->text.push_back(str);
		}
	}

	void delete_layer(int layer)
	{
		this->text[layer].erase();
	}

	void print()
	{
		for (auto& layer : text)
		{
			std::cout << layer << "\n";
		}
	}
};

class ConState
{
public:
	ConState()
	{

	}
	~ConState()
	{

	}
	
protected:
	string_struct con_text;

private:
	

};

class MainMenu
	:ConState
{
public:
	MainMenu();
	void print()
	{
		this->con_text.print();
	}
protected:

private:

};
#endif