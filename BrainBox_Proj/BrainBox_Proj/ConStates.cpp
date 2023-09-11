#include "ConStates.h"

// MAIN MENU

MainMenu::MainMenu()
{
	this->con_text.add_layer
	(
		std::vector<std::string>
		{
			"Welcome to the Grade Manager!",
				this->con_text.color["BLUE"] + 
			"  Select an existing file, or create a new one..."
		}
	);
}