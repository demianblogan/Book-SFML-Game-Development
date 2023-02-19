#include <iostream>

#include "Application/Application.h"

int main()
{
	try
	{
		Application application;
		application.Run();
	}
	catch (const std::exception& exception)
	{
		std::cout << "EXCEPTION: " << exception.what() << std::endl;
	}

	return 0;
}