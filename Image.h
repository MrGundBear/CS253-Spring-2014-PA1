#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

/*! \file Complex.h: Declares the Complex number class 
 */

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>



using std::istream;
using std::ostream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::cerr;


/*! \brief A numeric class for complex numbers with arithmetic operations.
 *
 * A class for instances of complex numbers, i.e. numbers with both real and
 * imaginary components. The class not only provides a representation for
 * complex numbers, it also defines simple arithmetic operations (+, -, *)
 * and I/O operations (<< and >>).
 */
class Image {
public:
	Image();
	int parseFile(string fileName);
	void printImage();
private:

	// mainData = all rows of int data, not including the PG
	vector<int> mainData;
	// width and height will correspond to the dimensions of image
	int width, height, maxPixelValue;
	bool debug;

	int max, min;
	double mean;

	
	bool isInteger(const string & s);
	int nextValidValue(ifstream& openFile);

};


#endif
