#include "ConStates.h"

// MAIN MENU

MainMenu::MainMenu()
	:ConState("grade_books\\")
{	

	this->initGradeBooksDirectory();
	this->initGreetingDirections();
	this->initGradebookList();
	

	this->file_mangaer->create_directory("test_dir");
	this->file_mangaer->create_directory("test_dir2");

	
	

	
}

MainMenu::~MainMenu()
{
	
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
	this->printables.first["SS1"] = new string_struct();
	for (auto& filename : this->file_mangaer->read_directory())
	{
		this->printables.first["SS1"]->add_text
		(
			this->color["CYAN"] + filename + this->color["RESET"]
		);
	}

}
