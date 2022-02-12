#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Employee
{
	int num; 
	char name[10];
	double hours;
};

bool IsInteger(char* value) {

	for (int i = 0; i < strlen(value); i++) {
		if (isdigit(value[i]) == false) {
			return false;
		}
	}
	return true;
}

bool CompareEmployees(Employee lhs, Employee rhs) {
	return lhs.hours > rhs.hours;
}

int main(int argc, char** argv)
{
    if(argc != 4) {
        std::cerr << "Invalid number of arguments!\nProcess terminated...\n";
        return 1;
    }

    char* sourceFilename = argv[1];
    char* reportFileName = argv[2];

	if (!IsInteger(argv[3])) {
		std::cerr << "Invalid 'hourly wage' argument.\nProcess terminated...\n";
		return 1;
	}

    int wagePerHour = std::atoi(argv[3]);

	if (strcmp(sourceFilename, reportFileName) == 0)
	{
		std::cerr << "Source file name and report file name is equal.\nProcess terminated...\n";
		return 1;
	}

	std::ifstream in;		
	Employee employee;
	unsigned i;

	std::ofstream reportOut;

	in.open(sourceFilename);
	if (!in)
	{
		std::cerr << "Open source file failed.\nProcess terminated...\n";
		return 1;
	}

	reportOut.open(reportFileName);

	if (!reportOut.is_open()) 
	{
		std::cerr << "Open/Create report file failed.\nProcess terminated...\n";
		return 1;
	}

	std::vector<Employee> vectorOfEmployees;

	while (!in.eof())
	{
		in.read((char*)&employee, sizeof(Employee));

		if (in.eof()) {
			break;
		}

		if (!in.good())
		{
			std::cerr << "Error ocurred while reading file.\nProcess terminated...\n";
			return 1;	
		}

		vectorOfEmployees.push_back(employee);
	}
	std::cout << "Report generated.\n";

	in.close();

	sort(vectorOfEmployees.begin(), vectorOfEmployees.end(), CompareEmployees);

	reportOut << "Report for file: " << sourceFilename << std::endl;

	for (size_t i = 0; i < vectorOfEmployees.size(); i++)
	{
		reportOut << "id = " << vectorOfEmployees[i].num
			<< " name = " << vectorOfEmployees[i].name
			<< " hours = " << vectorOfEmployees[i].hours
			<< " salary = " << vectorOfEmployees[i].hours * wagePerHour << std::endl;

	}

	reportOut.close();
	return 0;
}
