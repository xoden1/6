#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct address {
	std::string street;
	int house;
	int appartment;
};

struct person {
	std::string name;
	address address;
	char gender;
	int age;
};

std::vector<person> cocktail(std::vector<person> database) {
	if (database.size() < 2) return database;
	bool swap = true;
	while (swap) {
		swap = false;
		for (int i = 0; i <= database.size() - 2; i++) {
			if ((database[i].name) > (database[i + 1].name)) {
				swap = true;
				std::swap(database[i], database[i + 1]);
			}
		}
		for (int i = database.size() - 2; i > 0; i--) {
			if ((database[i].name) < (database[i - 1].name)) {
				swap = true;
				std::swap(database[i], database[i - 1]);
			}
		}
	}
	std::cout << "Sorted!" << std::endl;
	return database;
}

std::ostream& operator<<(std::ostream& out, const std::vector<person>& database)
{
	out << database.size() << std::endl;
	for (int i = 0; i < database.size(); i++) {
		out << database[i].name << std::endl;
		out << database[i].address.street << std::endl;
		out << database[i].address.house << std::endl;
		out << database[i].address.appartment << std::endl;
		out << database[i].gender << std::endl;
		out << database[i].age << std::endl;
	}
	return out;
}

std::istream& operator>>(std::istream& in, std::vector<person>& database)
{
	int size;
	in >> size;
	database.resize(size);
	for (int i = 0; i < size; i++) {
		in.ignore();
		std::getline(in, database[i].name);
		std::getline(in, database[i].address.street);
		in >> database[i].address.house;
		in >> database[i].address.appartment;
		in >> database[i].gender;
		in >> database[i].age;
	}
	return in;
}

int write(std::vector<person> database) {
	std::ofstream stream("database.txt");
	stream << database;
	stream.close();
	std::cout << "Saved!" << std::endl;
	return 0;
}

std::vector<person> read() {
	std::vector<person> database;
	std::ifstream stream("database.txt");
	stream >> database;
	stream.close();
	std::cout << "Loaded!" << std::endl;
	return database;
}

int write_binary(std::vector<person> database) {
	std::ofstream stream("database_binary.txt", std::ios::binary);
	int size = database.size();
	stream.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (int i = 0; i < database.size(); i++) {
		int sizestr = database[i].name.size();
		stream.write(reinterpret_cast<char*>(&sizestr), sizeof(sizestr));
		for (int j = 0; j < sizestr; j++) {
			stream.write(reinterpret_cast<char*>(&database[i].name[j]), sizeof(database[i].name[j]));
		}
		size = database[i].address.street.size();
		stream.write(reinterpret_cast<char*>(&size), sizeof(size));
		for (int j = 0; j < size; j++) {
			stream.write(reinterpret_cast<char*>(&database[i].address.street[j]), sizeof(database[i].address.street[j]));
		}
		stream.write(reinterpret_cast<char*>(&database[i].address.house), sizeof(database[i].address.house));
		stream.write(reinterpret_cast<char*>(&database[i].address.appartment), sizeof(database[i].address.appartment));
		stream.write(reinterpret_cast<char*>(&database[i].gender), sizeof(database[i].gender));
		stream.write(reinterpret_cast<char*>(&database[i].age), sizeof(database[i].age));
	}
	stream.close();
	std::cout << "Saved! (binary)" << std::endl;
	return 0;
}

std::vector<person> read_binary() {
	std::ifstream stream("database_binary.txt", std::ios::binary);
	int size = 0;
	stream.read(reinterpret_cast<char*>(&size), sizeof(size));
	std::vector<person> database;
	database.resize(size);
	for (int i = 0; i < size; i++) {
		int sizestr = 0;
		stream.read(reinterpret_cast<char*>(&sizestr), sizeof(sizestr));
		for (int j = 0; j < sizestr; j++) {
			char temp;
			stream.read(reinterpret_cast<char*>(&temp), sizeof(temp));
			database[i].name.push_back(temp);
		}
		stream.read(reinterpret_cast<char*>(&sizestr), sizeof(sizestr));
		for (int j = 0; j < sizestr; j++) {
			char temp;
			stream.read(reinterpret_cast<char*>(&temp), sizeof(temp));
			database[i].address.street.push_back(temp);
		}
		stream.read(reinterpret_cast<char*>(&database[i].address.house), sizeof(database[i].address.house));
		stream.read(reinterpret_cast<char*>(&database[i].address.appartment), sizeof(database[i].address.appartment));
		stream.read(reinterpret_cast<char*>(&database[i].gender), sizeof(database[i].gender));
		stream.read(reinterpret_cast<char*>(&database[i].age), sizeof(database[i].age));
	}
	stream.close();
	std::cout << "Loaded! (binary)" << std::endl;
	return database;
}

std::vector<person> input() {
	std::cout << "How many people are we entering? ";
	int num;
	std::cin >> num;
	std::vector<person> database(num);
	for (int i = 0; i < num; i++) {
		std::cout << "Enter information about a person #" << i + 1 << ":" << std::endl;
		std::cout << "Name: ";
		std::cin.ignore();
		std::getline(std::cin, database[i].name);
		std::cout << "Street: ";
		std::getline(std::cin, database[i].address.street);
		std::cout << "House: ";
		std::cin >> database[i].address.house;
		std::cout << "Appartment: ";
		std::cin >> database[i].address.appartment;
		std::cout << "Gender (M or F): ";
		std::cin >> database[i].gender;
		std::cout << "Age: ";
		std::cin >> database[i].age;
	}
	std::cout << "Input finished!" << std::endl;
	return database;
}

int output(std::vector<person> database) {
	if (database.size() == 0) {
		std::cout << "The database is empty!" << std::endl;
		return 0;
	}
	std::cout << "--------------------" << std::endl;
	for (int i = 0; i < database.size(); i++) {
		std::cout << "Information about a person #" << i + 1 << ":" << std::endl;
		std::cout << "Name: ";
		std::cout << database[i].name << std::endl;
		std::cout << "Street: ";
		std::cout << database[i].address.street << std::endl;
		std::cout << "House: ";
		std::cout << database[i].address.house << std::endl;
		std::cout << "Appartment: ";
		std::cout << database[i].address.appartment << std::endl;
		std::cout << "Gender (M or F): ";
		std::cout << database[i].gender << std::endl;
		std::cout << "Age: ";
		std::cout << database[i].age << std::endl;
		std::cout << "--------------------" << std::endl;
	}
	return 0;
}

int children(std::vector<person> database) {
	std::cout << "Enter the street name: ";
	std::string street_name;
	std::cin >> street_name;
	std::cout << "Enter the house number: ";
	int house_num;
	std::cin >> house_num;
	int cnt = 0;
	std::vector<person> database2;
	for (int i = 0; i < database.size(); i++) {
		if ((database[i].address.street == street_name) && (database[i].address.house == house_num) && (database[i].age >= 1) && (database[i].age <= 5)) {
			cnt++;
			database2.push_back(database[i]);
		}
	}
	std::cout << "There are " << cnt << " children aged between 1 and 5, living on " << street_name << " st., " << house_num << "." << std::endl << "List:" << std::endl;
	output(database2);
	return 0;
}

int main() {
	system("chcp 1251");
	std::cout << "Welcome! Available commands list:" << std::endl;
	std::cout << "input - Enter the database in the console" << std::endl;
	std::cout << "output - Shows the current database" << std::endl;
	std::cout << "sort - Sorts all people in the database by their names" << std::endl;
	std::cout << "children - Checks how many children aged between 1 and 5 live in a certain house" << std::endl;
	std::cout << "write - Saves the database in a txt format (database.txt)" << std::endl;
	std::cout << "read - Loads the database in a txt format (database.txt)" << std::endl;
	std::cout << "write_bin - Saves the database in a binary format (database_binary.txt)" << std::endl;
	std::cout << "read_bin - Loads the database in a binary format (database_binary.txt)" << std::endl;
	std::cout << "exit - Exits the program" << std::endl;
	std::vector<person> database;
	while (true) {
		std::string console_input;
		std::cin >> console_input;
		if (console_input == "input") database = input();
		else if (console_input == "output") output(database);
		else if (console_input == "sort") database = cocktail(database);
		else if (console_input == "children") children(database);
		else if (console_input == "write") write(database);
		else if (console_input == "read") database = read();
		else if (console_input == "write_bin") write_binary(database);
		else if (console_input == "read_bin") database = read_binary();
		else if (console_input == "exit") exit(0);
		else std::cout << "Unknown command" << std::endl;
	}
	return 0;
}
