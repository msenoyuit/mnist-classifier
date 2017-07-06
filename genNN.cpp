#include "net.hpp"
#include <iostream>
#include <fstream>

#include <vector>

std::string fillTo3(int inNum)
{
	std::string outStr = std::to_string(inNum);
	while (outStr.length() < 3)
	{
		outStr.insert(0, "0");
	}
	return outStr;
}


int main(int argc, char *argv[])
{
	std::ifstream inFile("C:\\\\Users\\MS4\\Documents\\hands\\mnist-classifier\\data\\train-images-idx3-ubyte", std::ios::binary);
	std::ifstream inLabel("C:\\\\Users\\MS4\\Documents\\hands\\mnist-classifier\\data\\train-labels-idx1-ubyte", std::ios::binary);
	if (inFile.is_open() && inLabel.is_open())
	{
		
		int magicNumber = 0;
		int numberOfItems = 0;
		int numberOfRows = 0;
		int numberOfColumns = 0;
		inFile.read((char*)&magicNumber, sizeof(magicNumber));
		inFile.read((char*)&numberOfItems, sizeof(numberOfItems));
		inFile.read((char*)&numberOfRows, sizeof(numberOfRows));
		inFile.read((char*)&numberOfColumns, sizeof(numberOfColumns));

		int magicNumbTwo = 0;
		int numberOfLabels = 0;
		inLabel.read((char*)&magicNumbTwo, sizeof(magicNumbTwo));
		inLabel.read((char*)&numberOfLabels, sizeof(numberOfLabels));
		
		std::cout << '\n';
		for(int k = 0; k < 10; k++)
		{
			for(int i = 0; i < 28; i++)
			{
				for (int j = 0; j < 28; j++)
				{
					std::cout << fillTo3(inFile.get()) << ' ';
				}
				std::cout << '\n';
			}
			std::cout << inLabel.get() << '\n';
		}
	}
	

}