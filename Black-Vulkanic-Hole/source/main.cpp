#include "GraphicThings/FirstApp.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
	engine::FirstApp BlackHole{};

	try
	{
		BlackHole.run();
	}
	catch (const std::exception& E)
	{
		std::cerr << E.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}