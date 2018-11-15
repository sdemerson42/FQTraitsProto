#include <conio.h>
#include <time.h>

#include "SimState.h"

int main()
{
	srand(time(NULL));

	std::unique_ptr<SimState> state = std::make_unique<SimState>();
	state->execute();

	_getch();
	return 0;
}