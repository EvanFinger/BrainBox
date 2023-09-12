#include "ConStates.h"

// MAIN MENU

MainMenu::MainMenu()
{
	this->con_text = new box_struct(17, 5);
	this->con_text->box_text.add_text("Hello World");
	this->con_text->format_box(TOP, CENTER);
	
}

MainMenu::~MainMenu()
{
	delete this->con_text;
}

