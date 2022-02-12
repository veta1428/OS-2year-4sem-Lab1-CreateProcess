#include <iostream>
#include <fstream>
#include <string>


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

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Invalid number of arguments!\nProcess terminated...";
        return 1;
    }

	long recordsAmount;

	recordsAmount = std::atoi(argv[1]);

    if(recordsAmount <= 0 || !IsInteger(argv[1])) {
        std::cerr << "Invalid argument 'records amount'\nProcess terminated...";
        return 1;
    }

	std::ofstream out;

	out.open(argv[2], std::ofstream::binary);

	Employee employee;

	if (!out)
	{
		std::cerr << "Open&Create file failed.\n";
		return 1;
	}

	std::cout << "Input employee id, name and hours." << std::endl;

	char* tempNumber = new char[100];

	while (recordsAmount != 0)
	{
		std::cout << std::endl;

		//num
		std::cout << "ID (number) = ";
		std::cin >> tempNumber;

		if (!IsInteger(tempNumber)) {
			std::cerr << "Invalid number.\nThis employee record wouldn't be written.\nTry again...\n";
			continue;
		}

		employee.num = std::atoi(tempNumber);


		//name
		std::cout << "Name (shorter than 10 characters) = ";
		std::string temp;
		std::cin >> temp;
		
		if (temp.size() >= 10) {
			std::cerr << "Invalid length of name.\nThis employee record wouldn't be written.\nTry again...\n";
			continue;
		}
		
		strncpy_s(employee.name, temp.c_str(), temp.length() + 1);


		//hours
		std::cout << "Hours = ";
		std::cin >> tempNumber;

		if (!IsInteger(tempNumber)) {
			std::cerr << "Invalid number.\nThis employee record wouldn't be written.\nTry again...\n";
			continue;
		}

		employee.hours = std::atoi(tempNumber);



		std::cout << std::endl;

		out.write((const char*)&employee, sizeof(Employee));

		recordsAmount--;
	}
	// закрываем выходной поток
	out.close();

	std::cout << "Records were written.\n";

	return 0;
}