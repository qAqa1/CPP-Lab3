#include <iostream>
#include <string>
#include <map>
#include <Windows.h>

using namespace std;

map<string, string>directory;

void CHANGE_CAPITAL(string country, string new_capital) // Ч изменение столицы страны country на new_capital, либо добавление такой страны с такой столицей, если раньше еЄ не было.
{
	auto it = directory.find(country);
	if (it == directory.end())
	{
		directory.emplace(country, new_capital);
		cout << "Introduce new country " << country << " with capital " << new_capital;
	}
	else
	{
		if (it->first == country && it->second == new_capital)
		{
			cout << "Country " << country << " hasn't changed its capital";
		}
		else
		{
			cout << "Country " << country << " has changed its capital from " << it->second << " to " << new_capital;
			it->second = new_capital;
		}
	}
}

void RENAME(string old_country_name, string new_country_name) // Ч переименование страны из old_country_name в new_country_name.
{
	if (old_country_name._Equal(new_country_name) || directory.find(new_country_name) != directory.end())
	{
		cout << "Incorrect rename";
		return;
	}

	auto it = directory.find(old_country_name);

	if (it == directory.end())
	{
		cout <<"—трана "<< old_country_name << " не существует";
	}
	else
	{
		if (it->first == new_country_name)
		{
			cout << "Incorrect rename";
			
		}
		else
		{
			cout << "Country " << old_country_name <<" with capital "<< it->second << " has been renamed to " << new_country_name;
			directory.emplace(new_country_name, it->second);
			directory.erase(old_country_name);
		}
	}
}

void ABOUT(string country) // Ч вывод столицы страны country
{
	auto it = directory.find(country);
	if (it == directory.end())
	{
		cout << "Country " << country << " doesn't exist";
	}
	else
	{
		cout << "Country " << country << " has capital " << it->second;
	}
}

void DUMP() // Ч вывод столиц всех стран.
{
	if (directory.empty())
	{
		cout << "There are no countries in the world";
	}
	else
	{
		for (auto it = directory.begin(); it != directory.end(); ++it)
		{
			cout << it->first << " / " << it->second << endl;
		}
	}
}

void HELP()
{
	cout << "HELP - вывод всех команд на экран";
	cout << endl << "EXIT - закрыть программу";
	cout << endl << "CHANGE_CAPITAL country new_capital Ч изменение столицы страны country на new_capital, либо добавление такой страны с такой столицей, если раньше еЄ не было.";
	cout << endl << "RENAME old_country_name new_country_name Ч переименование страны из old_country_name в new_country_name.";
	cout << endl << "ABOUT country Ч вывод столицы страны country.";
	cout << endl << "DUMP Ч вывод столиц всех стран.";
}

int find_space_second_index(string input)
{
	bool first_index = false;
	for (int x = 0; x < input.length(); x++)
	{
		if (input[x] == 32)
		{
			if (first_index == false)
			{
				first_index = true;
			}
			else
			{
				return(x);
			}
		}
	}

	return (-1);
}

void Execute_Command(string input)
{
	if (strstr(input.c_str(), "  "))
	{
		cout << "¬вод не корректен";
		return;
	}

	if (input == "HELP")
	{
		HELP();
		return;
	}

	if (input == "DUMP")
	{
		DUMP();
		return;
	}

	if (input == "EXIT")
	{
		exit(1);
	}

	if (input.substr(0, 6) == "ABOUT ")
	{
		const int command_len = 6;
		string country = input.substr(command_len, input.length() - command_len);

		ABOUT(country);
		return;
	}

	if (input.substr(0, 7) == "RENAME ")
	{
		const int command_len = 7;
		int second_space_index = find_space_second_index(input);
		if (second_space_index == -1)
		{
			cout << "¬вод не корректен";
			return;
		}
		else
		{
			string old_country_name = input.substr(command_len, input.length() - command_len - (input.length() - second_space_index));
			string new_country_name = input.substr(second_space_index + 1, input.length() - second_space_index);

			if (new_country_name == "")
			{
				cout << "¬вод не корректен!";
				return;
			}

			RENAME(old_country_name, new_country_name);
		}
		return;
	}

	if (input.substr(0, 15) == "CHANGE_CAPITAL ")
	{
		const int command_len = 15;
		int second_space_index = find_space_second_index(input);
		if (second_space_index == -1)
		{
			cout << "¬вод не корректен";
			return;
		}
		else
		{
			string country = input.substr(command_len, input.length() - command_len - (input.length() - second_space_index));
			string new_capital = input.substr(second_space_index + 1, input.length() - second_space_index);

			if (new_capital == "")
			{
				cout << "¬вод не корректен!";
				return;
			}
		
			CHANGE_CAPITAL(country, new_capital);
		}
		return;
	}
	cout << "¬ведЄнной вами команды не существует!";
}


void main()
{
	//setlocale(LC_ALL, "russian");
	SetConsoleCP(1251); //установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); //установка кодовой страницы win-cp 1251 в поток 

	while (true)
	{
		cout << endl << endl << "(¬ведите HELP дл€ просмотра списка команд)"<<endl<<"¬ведите команду: ";
		string input;
		getline(cin, input);
		cout << endl;
		Execute_Command(input);
	}
}