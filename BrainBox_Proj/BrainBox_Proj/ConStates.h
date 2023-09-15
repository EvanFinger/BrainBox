#ifndef CON_STATE_H
#define CON_STATE_H

#include "FileMan.h"


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
	
	void format_row(alignment horizontal, unsigned short row_num, unsigned short row_num_txt)
	{
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
			break;
		case RIGHT:
			for (size_t i = 0; i < this->width; i++)
			{
				if (i == 0 || i == this->width - 1)
				{
					this->printable[row_num].append("|");
				}
				else if (i < this->width - text_size - 1)
				{
					this->printable[row_num].append(" ");
				}
				else
				{
					this->printable[row_num].push_back(this->box_text.printable[row_num_txt][char_num]);
					char_num++;
				}
			}
			break;
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
				this->format_row(horizontal, i, i - 1);
			}
		}
		else if (vertical == CENTER)
		{
			unsigned short top_offset = (this->height - 1 - this->box_text.printable.size()) / 2 + 1;
			for (int i = top_offset; i < this->printable.size() - 1; i++)
			{
				this->printable[i] = "";
				this->format_row(horizontal, i, i - top_offset);
			}
		}
		else if (vertical == BOTTOM)
		{
			unsigned short top_offset = this->height - 1 - this->box_text.printable.size();
			for (int i = top_offset; i < this->printable.size() - 1; i++)
			{
				this->printable[i] = "";
				this->format_row(horizontal, i, i - top_offset);
			}
		}
	}

};

class ConState
{
public:
	ConState(std::string working_dir, std::stack<ConState*>* console_states)
	{
		this->console_states = console_states;
		this->file_mangaer = new FileMan(working_dir);
	}
	~ConState()
	{
		delete this->file_mangaer;
		for (auto& printable : printables.first)
		{
			delete printable.second;
		}
		for (auto& printable : printables.second)
		{
			delete printable.second;
		}
		delete this->file_mangaer;
	}

	virtual void read_user_input() = 0;
	virtual void refresh_state() = 0;

	void print()
	{
		system("cls");
		for (auto& printable : printables.second)
		{
			printable.second->print();
		}
		for (auto& printable : printables.first)
		{
			printable.second->print();
		}
	}
	
protected:
	// ptr to console state stack (different screens / menus)
	std::stack<ConState*>* console_states;
	//First = string struct, Second = box struct
	std::pair<std::map<std::string, string_struct*>, std::map<std::string, box_struct*>> printables;
	
	

	FileMan* file_mangaer;   

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
	
	void EXIT()
	{
		std::cout << "---";
		this->console_states->pop();
		
	}

private:
	

};

class MainMenu
	:public ConState
{
public:
	MainMenu(std::stack<ConState*>* console_states);
	~MainMenu();

	virtual void read_user_input();
	virtual void refresh_state();
protected:

private:
	std::vector<std::string> gradebookList;

	void initGradeBooksDirectory();
	void initGreetingDirections();
	void initGradebookList();
	void initMiscOptions();


	void createNewGradebook();
	void deleteExistingGradebook();
	void selectGradebook(std::string dir_path);
	

};

class CreateNewGradeook
	:public ConState
{
public:
	CreateNewGradeook(std::stack<ConState*>* console_states);
	~CreateNewGradeook();

	virtual void read_user_input();
	virtual void refresh_state();

private:
	std::string gradebook_name;
	void initDirections();
};

class DeleteExistingGradebook
	:public ConState
{
public:
	DeleteExistingGradebook(std::stack<ConState*>* console_states);
	~DeleteExistingGradebook();

	virtual void read_user_input();
	virtual void refresh_state();

private:
	std::vector<std::string> gradebookList;

	void initDirections();
	void initGradebook();
};
#endif