#include "ConStates.h"

// MAIN MENU

MainMenu::MainMenu(std::stack<ConState*>* console_states)
	:ConState("grade_books\\", console_states)
{	

	this->initGradeBooksDirectory();
	this->initGreetingDirections();
	this->initGradebookList();
	this->initMiscOptions();
	

	this->file_mangaer->create_directory("test_dir");
	this->file_mangaer->create_directory("test_dir2");
	this->file_mangaer->create_directory("test_dir3");
	this->file_mangaer->create_directory("test_dir4");
	this->file_mangaer->create_directory("test_dir5");

	
	

	
}

MainMenu::~MainMenu()
{
	
}

void MainMenu::read_user_input()
{
	std::string input;
	std::cout << "Selection->  ";
	std::cin >> input;

	if (input == "+")
		this->createNewGradebook();
	else if (input == "-")
		this->deleteExistingGradebook();
	else if (input == "X")
		this->EXIT();
	else if (stoi(input) < this->gradebookList.size())
	{
		this->selectGradebook(this->gradebookList[stoi(input)]);
	}
}

void MainMenu::refresh_state()
{
	this->printables.first["SS1"]->printable.erase
	(
		this->printables.first["SS1"]->printable.begin(), 
		this->printables.first["SS1"]->printable.end()
	);
	this->initGradebookList();
	this->print();
}

void MainMenu::initGradeBooksDirectory()
{
	if (!_mkdir("grade_books"))
	{
	}
}

void MainMenu::initGreetingDirections()
{
	this->printables.second["BOX1"] = new box_struct(60, 6);
	this->printables.second["BOX1"]->box_text.add_text("Welcome to the BrainBox gradebook!");
	this->printables.second["BOX1"]->box_text.add_text("Select an existing gradebook, or create a new one.");
	this->printables.second["BOX1"]->format_box(CENTER, CENTER);
}

void MainMenu::initGradebookList()
{
	this->gradebookList = this->file_mangaer->read_directory();
	this->printables.first["SS1"] = new string_struct();
	unsigned short option_label = 0;
	for (auto& filename : this->gradebookList)
	{
		this->printables.first["SS1"]->add_text
		(
			this->color["CYAN"] + "[" + std::to_string(option_label) + "] " + 
			filename.substr(12) + this->color["RESET"]
		);
		option_label++;
	}

}

void MainMenu::initMiscOptions()
{
	this->printables.first["SS2"] = new string_struct();
	this->printables.first["SS2"]->add_text
	(
		this->color["GREEN"] + "[" + "+" + "] " +
		"CREATE a NEW Gradebook"
	);
	this->printables.first["SS2"]->add_text
	(
		this->color["RED"] + "[" + "-" + "] " +
		"DELETE an EXISTING Gradebook" + this->color["RESET"]
	);
	this->printables.first["SS2"]->add_text
	(
		this->color["YELLOW"] + "[" + "X" + "] " +
		"EXIT" + this->color["RESET"]
	);
}

// MENU OPTIONS

void MainMenu::createNewGradebook()
{
	this->console_states->push(new CreateNewGradeook(this->console_states));
}

void MainMenu::deleteExistingGradebook()
{
	this->console_states->push(new DeleteExistingGradebook(this->console_states));
}

void MainMenu::selectGradebook(std::string dir_path)
{
}


/*
//////////////////////////////////////////////////////////////////////////////////

		CreateNewGradeBook (Class)<--(ConState)
	+ Console state meant for creating new gradebook directories
	+ INHERITS ConState class

//////////////////////////////////////////////////////////////////////////////////
*/



CreateNewGradeook::CreateNewGradeook(std::stack<ConState*>* console_states)
	:ConState("grade_books\\", console_states)
{
	this->initDirections();
}

CreateNewGradeook::~CreateNewGradeook()
{
	
}

void CreateNewGradeook::refresh_state()
{

}

void CreateNewGradeook::read_user_input()
{	
	while (true)
	{
		std::string input, name;

		std::cout << "Name the Gradebook (" << 
			this->color["RED"] << "\\x to CANCEL" << 
			this->color["RESET"] << "):  " << 
			this->color["CYAN"];
		std::cin >> std::ws;
		std::getline(std::cin, name);
		std::cout << this->color["RESET"];
		if (input == "\\x")
		{
			this->EXIT();
		}
		else
		{
			std::cout << "Gradebook Name:  " << this->color["CYAN"] << name << "\n";
			std::cout << this->color["YELLOW"];

			std::cout << "Correct?"<< 
				this->color["RESET"] << "[" <<
				this->color["GREEN"] <<  "Y" << 
				this->color["RESET"] <<  "/" << 
				this->color["RED"] << "N" << 
				this->color["RESET"] << "]";

			std::cin >> input;
			
			if (input == "Y")
			{
				this->gradebook_name = name;
				std::string dir_name = this->file_mangaer->get_wdir() + name;
				if (!_mkdir(dir_name.c_str())) {};
				this->console_states->pop();
				break;
			}
			else if (input == "N")
			{
				this->print();
			}
		}
	}
	
}

void CreateNewGradeook::initDirections()
{
	this->printables.second["BOX1"] = new box_struct(60, 6);
	this->printables.second["BOX1"]->box_text.add_text("|  To CREATE a New Gradebook  |");
	this->printables.second["BOX1"]->box_text.add_text("V Follow the Directions Below V");
	this->printables.second["BOX1"]->format_box(CENTER, CENTER);
}

/*
//////////////////////////////////////////////////////////////////////////////////

		DeleteExistingGradebook (Class)<--(ConState)
	+ Console state meant for creating new gradebook directories
	+ INHERITS ConState class

//////////////////////////////////////////////////////////////////////////////////
*/

DeleteExistingGradebook::DeleteExistingGradebook(std::stack<ConState*>* console_states)
	:ConState("grade_books\\", console_states)
{
	this->initDirections();
	this->initGradebook();
}

DeleteExistingGradebook::~DeleteExistingGradebook()
{
}

void DeleteExistingGradebook::read_user_input()
{
	std::string input;
	std::cin>>input;
}

void DeleteExistingGradebook::refresh_state()
{
}

void DeleteExistingGradebook::initDirections()
{
	this->printables.second["BOX1"] = new box_struct(60, 6);
	this->printables.second["BOX1"]->box_text.add_text("|  To DELETE an EXISTING Gradebook  |");
	this->printables.second["BOX1"]->box_text.add_text("V    Follow the Directions Below    V");
	this->printables.second["BOX1"]->format_box(CENTER, CENTER);
}

void DeleteExistingGradebook::initGradebook()
{
	this->gradebookList = this->file_mangaer->read_directory();
	this->printables.first["SS1"] = new string_struct();
	unsigned short option_label = 0;
	for (auto& filename : this->gradebookList)
	{
		this->printables.first["SS1"]->add_text
		(
			this->color["CYAN"] + "[" + std::to_string(option_label) + "] " +
			filename.substr(12) + this->color["RESET"]
		);
		option_label++;
	}
}
