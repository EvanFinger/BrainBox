#include "ConStates.h"

// MAIN MENU

MainMenu::MainMenu()
{
	this->printables.second["BOX1"] = new box_struct(17, 8);
	this->printables.second["BOX1"]->box_text.add_text("Hello");
	this->printables.second["BOX1"]->box_text.add_text("World");
	this->printables.second["BOX1"]->format_box(BOTTOM, CENTER);
	this->print();
	this->printables.second["BOX1"]->box_text.add_text("World");
	this->print();
	this->printables.second["BOX1"]->format_box(CENTER, CENTER);
	
}

MainMenu::~MainMenu()
{
	for (auto& printable : printables.first)
	{
		delete printable.second;
	}
	for (auto& printable : printables.second)
	{
		delete printable.second;
	}
}
