#include <Image.h>


Image::Image(void)
{
	debug = false;
	if(debug) cout << "Image is being created" << endl;
}

// parseFile will read in the image file and
// 1. Parse through the header and get the height, width, maxValue
// 2. Catch any errors, return -1 if errors otherwise return 0
int Image::parseFile(string fileName)
{
	ifstream myFile;	
	myFile.open(fileName.c_str());
	string output = "";	
	if (myFile.is_open())
	{
		//First let us check that the header begins with "P2"
		myFile >> output;
		
		if(output.compare("P2") == 0)
		{
			if(debug) cout << "first element is P2!" << endl;
		}
		else
		{
			//cerr << "Error - first element is NOT P2, found value: " << output;
			return -1;
		}
		
		//Here is where we will read in and set the width, then height
		//The width and height
		//  - must be positive
		//  - must be integers
		int tempWidth, tempHeight, tempMaxPixelValue;

		tempWidth = nextValidValue(myFile);
		if(debug) cout << "tempWidth: " << tempWidth << endl;
		tempHeight = nextValidValue(myFile);
		if(debug) cout << "tempHeight: " << tempHeight << endl;
		if(tempHeight > 0 && tempWidth > 0)
		{
			width = tempWidth;
			height = tempHeight;
		}
		else
		{
			//cerr << "Error - height and width must be a positive integer!, found width: " << tempWidth << ", found height: " << tempHeight;
			return -1;
		}
		
		//Here we are going to look for the maxPixelValue
		//   - an integer between 0 - 256 (inclusive)
		tempMaxPixelValue = nextValidValue(myFile);
		if(debug) cout << "tempMaxPixelValue: " << tempMaxPixelValue << endl;
		if(tempMaxPixelValue >= 0 && tempMaxPixelValue <= 256)
		{
			maxPixelValue = tempMaxPixelValue;
		}
		else
		{
			//cerr << "Error - MaxPixelValue is invalid, found value: " << tempMaxPixelValue;
			return -1;
		}
		
		//currentLine is going to hold a list of all pixel values
		//Each pixel value must be:
		//   - a non-negative (0 - maxPixVal) (inclusive) integer
		//   - pixel values are seperated by white space
		//   - There must be width * height pixels, more or less is an error!
		vector<int> tempData;
		while (true)
		{
			// Here val is set to the read in pixel value			
			int val = nextValidValue(myFile);
			//Here I am doing a manual check to see if the next value is eof
			if(myFile.eof())
			{
				break;
			}
			// Checking if pixel value is integer and within range
			if(val < 0 || val > maxPixelValue)
			{
				//cerr << "Pixel value at position " << tempData.size()+1 << " is invalid with value: " << val << endl;
				return -1;
			}
			else
			{
				tempData.push_back(val);
				if(debug)
				{
					cout << val << "\t";
					if(tempData.size() % width == 0)
					{
						cout << endl;
					}
				}

			}
			
			
	 	}
		// Now that tempData is holding a vector of ints of size width * height
		unsigned int expectedSize = width * height;
		if(tempData.size() != expectedSize)
		{
			//cerr << "Invalid number of pixels provided, found: " << tempData.size() << ", am looking for " << width*height << " pixels";
			return -1;
		}

		//All pixels loaded into Image's mainData vector
		mainData = tempData;

		min = maxPixelValue, max = 0;
		mean = 0;
		for(unsigned int i = 0; i<mainData.size(); i++)
		{
			if(mainData.at(i) < min)
			{
				min = mainData.at(i);
			}
			if(mainData.at(i) > max)
			{
				max = mainData.at(i);
			}
			mean += mainData.at(i);
		}
		mean /= mainData.size();
		cout << min << " " << mean << " " << max << endl;

		
	}
	//else if myFile isnt open (something went wrong)
	else
	{
		return -1;
	}
	myFile.close();
	return 0;
}

bool Image::isInteger(const string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}


//This function will return a string representation of what the next value is
//Importantly, skip all values including COMMENTS
int Image::nextValidValue(ifstream& myFile)
{	
	// output is filled using the >> command, s is a string representation of output
	char output[100];

	if(myFile.is_open())
	{
		myFile >> output;
	}

	string s(output);
	string num = "";
	// Here I am checking to make sure no # character has been found,
	// the find function returns string::npos if no # char was found
	// If there is a # found, first check to see if there is a number proceeding '#'
	// This could be a valid value such as 32#Comment, which should return 32 pixel value
	// and still parse for the comment
	if(s.find('#') !=  string::npos)
	{
		//This case gets run if the comment does not begin with a #
		// Could be 32# which is valid		
		
		string n = s.substr(0, s.find('#'));
		if(output[0] != '#')
		{
			if(debug) cout << "number found before Comment!" << n << endl;
			s = s.substr(s.find('#'));
			// Now we have the number before the comment
			// Now let us skip through the rest of the comment until we hit newline
			
		}		
		//This code is the same whether we see such as 32# or #comment
	
		string fullComment = s;
		getline(myFile, s);
		//This is not a newline so keep going

		fullComment += s;
		
		if(debug) cout << "found full comment: " << fullComment << endl;	
		if(n.size() > 0)
		{
			return atoi(n.c_str());
		}
		else 
		{
			return nextValidValue(myFile);
		}
		
		//Now we are at the point where the comment has finished
		// Here we will return the number 
		//myFile >> output;
		
	}
	if(isInteger(output) == false)
	{

		return -7531;
	}
	return atoi(output);
}

void Image::printImage()
{
	cout << endl;
	for(unsigned int i = 0; i<mainData.size(); i++)
	{
		//Then I will print the darkest value
		if(mainData.at(i) > maxPixelValue * 0.8)
		{
			cout << "â–ˆ" ;
			
		}
		else if(mainData.at(i) > maxPixelValue * 0.6)
		{
			cout << "â–“" ;	
		}
		else if(mainData.at(i) > maxPixelValue * 0.4)
		{
			cout << "â–’" ;	
		}
		else if(mainData.at(i) > 0)
		{
			cout << "â–‘" ;	
		}
		else 
		{
			cout << " " ;	
		}

		if(i % width == 0)
		{
			cout << endl;
		}
	}
	cout << endl;
}




