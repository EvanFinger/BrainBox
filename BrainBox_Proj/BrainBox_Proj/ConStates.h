#ifndef CON_STATE_H
#define CON_STATE_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <tuple>
#include <map> 

enum alignment
{
	LEFT = 0,
	CENTER,
	RIGHT,
	TOP,
	BOTTOM
};

struct printable_struct
{
	std::vector<std::string> printable;
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

	printable_struct() {};

	void add_text(std::vector<std::string> _txt_obj)
	{
		for (auto& layer : _txt_obj)
		{
			this->printable.push_back(layer);
		}
	}

	void add_text(std::string _txt)
	{
		this->printable.push_back(_txt);
	}

	void print()
	{
		for (auto& _string : this->printable)
		{
				std::cout << _string << "\n";
		}
	}
};

struct string_struct
	:printable_struct
{
	
	string_struct()
	{
	}

};

struct box_struct
	:printable_struct
{
	
	string_struct box_text;
	unsigned short width, height;

	box_struct(unsigned short width, unsigned short height)
	{
		this->width = width;
		this->height = height;

		for (int i = 0; i < this->height; i++)
		{

			this->printable.push_back("");
			for (int j = 0; j < this->width; j++)
			{
				if (i == 0 || i == this->height - 1)
				{
					this->printable.back().append("-");
				}
				else if (j == 0 || j == this->width - 1)
				{
					this->printable.back().append("|");
				}
				else
				{
					this->printable.back().append(" ");
				}
			}
		}
	}
	
	void format_row(alignment horizontal, unsigned short row_num)
	{
		unsigned short row_num_txt = row_num - 1;
		unsigned short char_num = 0;
		unsigned short text_size = NULL;
		if (this->box_text.printable.size() > row_num_txt )
		{
			 text_size = this->box_text.printable[row_num_txt].size();
		}
		switch (horizontal)
		{
		case LEFT:
			for (size_t i = 0; i < this->width; i++)
			{
				if (i == 0 || i == this->width - 1)
				{
					this->printable[row_num].append("|");
				}
				else if (i <= text_size)
				{
					
					this->printable[row_num].push_back(this->box_text.printable[row_num_txt][char_num]);
					char_num++;
				}
				else
				{
					this->printable[row_num].append(" ");
				}
			}
			break;
		case CENTER:
			for (size_t i = 0; i < this->width; i++)
			{
				
				if (i == 0 || i == this->width - 1)
				{
					this->printable[row_num].append("|");
				}
				else if (i >= ((this->width - text_size) / 2)  && i < ((this->width - text_size) / 2)  + text_size)
				{
					this->printable[row_num].push_back(this->box_text.printable[row_num_txt][char_num]);
					char_num++;
				}
				else
				{
					this->printable[row_num].append(" ");
				}
			}
		}
	}
	void format_box(alignment vertical, alignment horizontal)
	{
		//Check Boundings
		for (auto& string : this->box_text.printable)
		{
			if (string.size() > this->width - 2)
			{
				throw "EXEMPTION IN BOX STRUCT: STRING LEAVES BOUNDS";
			}
		}
		if (this->box_text.printable.size() > this->height - 2)
		{
			throw "EXEMPTION IN BOX STRUCT: TEXT PRINTABLE LEAVES BOUNDS";
		}

		if (vertical == TOP)
		{
			for (int i = 1; i < this->printable.size() - 1; i++)
			{
				this->printable[i] = "";
				this->format_row(horizontal, i);
			}
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
	box_struct* con_text;

private:
	

};

class MainMenu
	:ConState
{
public:
	MainMenu();
	~MainMenu();
	void print()
	{
		this->con_text->print();
	}
protected:

private:

};
#endif