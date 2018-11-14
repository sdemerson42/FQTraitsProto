#include <conio.h>

#include "SimState.h"

int main()
{
	std::unique_ptr<SimState> state = std::make_unique<SimState>();

	_getch();
	return 0;
}