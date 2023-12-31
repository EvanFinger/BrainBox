#include "ConStates.h"


void init_lib();
void change_color(WORD color_id);



int main()
{
	init_lib();
	std::stack<ConState*> console_states;

	console_states.push(new MainMenu(&console_states));
	while (console_states.size() > 0)
	{	
		console_states.top()->refresh_state();
		console_states.top()->print();
		console_states.top()->read_user_input();
	}
	
	
}

void init_lib()
{
	std::vector< std::tuple< float, float, float > > GPA_Point_Scale_Number =
		{
			{94.f, 100.f, 4.f},
			{90.f, 93.f, 3.7},
			{87.f, 89.f, 3.3},
			{84.f, 86.f, 3.f},
			{80.f, 83.f, 2.7},
			{77.f, 79.f, 2.3},
			{74.f, 76.f, 2.f},
			{70.f, 73.f, 1.7},
			{67.f, 69.f, 1.3},
			{64.f, 66.f, 1.f},
			{60.f, 63.f, 0.7},
			{0.f, 59.f, 0.f}
		};
	std::vector< std::pair< std::string, float > > GPA_Point_Scale_Letter =
		{
			{"A", 4.f},
			{"A-", 3.7},
			{"B+", 3.3},
			{"B", 3.f},
			{"B-", 2.7},
			{"C+", 2.3},
			{"C", 2.f},
			{"C-", 1.7},
			{"D+", 1.3},
			{"D", 1.f},
			{"D-", 0.7},
			{"F", 0.f}
		};
}

void change_color(WORD color_id)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color_id);
}



