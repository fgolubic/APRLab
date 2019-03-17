#include"Common.h"
#include<iostream>
#include<fstream>
#include<string>

Result::Result(double T, double TMax):T(T),TMax(TMax)
{
}

bool toFile(std::vector<Result> result, std::string fileName)
{

	std::ofstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return false;
	}

	std::cout << "File opened: " << fileName << std::endl;


	std::cout << "File opened: " << fileName << std::endl;

	file << result[0].T;
	file << " ";
	file << result[0].TMax;
	file << std::endl;

	for (const auto& i : result) {

		for (unsigned int j = 0; j < i.point.size(); j++) {
			file << i.point[j];
			file << "  ";
		}
		file << "\n";
	}

	std::cout << "Closing file: " << fileName << std::endl;
	file.close();

	return true;
}
