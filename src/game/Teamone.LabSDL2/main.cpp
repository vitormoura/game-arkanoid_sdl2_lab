#include "stdafx.h"
#include "game.h"

int main(int argc, char *args[])
{
	auto g = new game();
	
	if (!g->init("Laboratorio SDL2", 100, 100, 640, 480, false))
		return EXIT_FAILURE;
	
	g->run();
	g->clean();

	delete g;

	return EXIT_SUCCESS;
}
