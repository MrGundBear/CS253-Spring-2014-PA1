/*! \file main.cpp: main function for complex number calculator */
#include <Image.h>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
#include <fstream>

int main(int argc, char* argv[])
{

	Image img;
	int result = img.parseFile(argv[1]);	
	//img.printImage();
	//cout << "returning " << result;
	return result;
}


