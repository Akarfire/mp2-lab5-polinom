#include "Polinom.h"
#include <iostream>
#include <map>

using namespace std;

void ClearCin()
{
	if (cin.fail())
		cin.clear();

	cin.ignore(INT_MAX, '\n');
}

int main()
{
	map<int, Polinom> PolinomStorage;

	cout << "Polinoms" << endl << "'Exit' to exit the program" << endl << endl;

	string Input = " ";

	while (true)
	{
		cout << "Choose operation: " << endl << "1. Enter polinom;" << endl << "2. View all polinoms;" << endl << "3. Add Polinoms;" << endl << "4. Subtract Polinoms;" << endl << "5. Get derivative over x;" << endl << "6. Get derivative over y;" << endl << "7. Get derivative over z;" << endl << "8. Multiply by constant;" << endl << endl;
		cout << "Enter operation number: ";

		int Attempt = 0;
		while (std::string("12345678").find(Input) == std::string::npos)
		{
			if (Attempt > 0)
				cout << "Invalid operation, retry: ";

			cin >> Input;
			ClearCin();

			if (Input == "Exit")
				return 0;

			if (Input.size() > 1)
			{
				Input = " ";
			}

			Attempt++;
		}
		
		int Operation = stod(Input);

		bool Added = false;
		bool Inputting = true;
		int Option1 = 0;
		int Option2 = 0;
		double C = 0;
		switch (Operation)
		{
		case 1:

			while (!Added)
			{
				cout << endl << "Enter Polinom: ";
				getline(cin, Input);
				

				try
				{
					Polinom P(Input);
					PolinomStorage[PolinomStorage.size()] = P;
					Added = true;
				}
				catch (exception e)
				{
					cout << endl << "ERROR: Invalid polinom notation!";
				}

			}
			break;
		
		case 2:

			for (auto p : PolinomStorage)
				cout << p.first << " : " << p.second.ToString() << ";" << endl;

			break;

		case 3:
			for (auto p : PolinomStorage)
				cout << p.first << " : " << p.second.ToString() << ";" << endl;

			cout << endl << "Choose polinom 1: ";

			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();
				
				try
				{
					Option1 = stoi(Input);
					
					if (Option1 >= 0 && Option1 < PolinomStorage.size())
						Inputting = false;
					else
						Inputting = true;
				}

				catch (exception e)
				{
					Inputting = true;
				}
				
				if (Inputting)
					cout << endl << "Invalid option, try again: ";
			}

			cout << endl << "Choose polinom 2: ";

			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();

				try
				{
					Option2 = stoi(Input);

					if (Option2 >= 0 && Option2 < PolinomStorage.size())
						Inputting = false;
					else
						Inputting = true;
				}

				catch (exception e)
				{
					Inputting = true;
				}

				if (Inputting)
					cout << endl << "Invalid option, try again: ";
			}

			if (true)
			{
				Polinom P = PolinomStorage[Option1] + PolinomStorage[Option2];
				PolinomStorage[PolinomStorage.size()] = P;
				cout << endl << "Result: " << P.ToString();
			}

			break;

		case 4:
			for (auto p : PolinomStorage)
				cout << p.first << " : " << p.second.ToString() << ";" << endl;

			cout << endl << "Choose polinom 1: ";

			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();

				try
				{
					Option1 = stoi(Input);

					if (Option1 >= 0 && Option1 < PolinomStorage.size())
						Inputting = false;
					else
						Inputting = true;
				}

				catch (exception e)
				{
					Inputting = true;
				}

				if (Inputting)
					cout << endl << "Invalid option, try again: ";
			}

			cout << endl << "Choose polinom 2: ";

			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();

				try
				{
					Option2 = stoi(Input);

					if (Option2 >= 0 && Option2 < PolinomStorage.size())
						Inputting = false;
					else
						Inputting = true;
				}

				catch (exception e)
				{
					Inputting = true;
				}

				if (Inputting)
					cout << endl << "Invalid option, try again: ";
			}

			if (true)
			{
				Polinom P = PolinomStorage[Option1] - PolinomStorage[Option2];
				PolinomStorage[PolinomStorage.size()] = P;
				cout << endl << "Result: " << P.ToString();
			}

			break;

		case 5:
			for (auto p : PolinomStorage)
				cout << p.first << " : " << p.second.ToString() << ";" << endl;

			cout << endl << "Choose polinom: ";

			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();

				try
				{
					Option1 = stoi(Input);

					if (Option1 >= 0 && Option1 < PolinomStorage.size())
						Inputting = false;
					else
						Inputting = true;
				}

				catch (exception e)
				{
					Inputting = true;
				}

				if (Inputting)
					cout << endl << "Invalid option, try again: ";
			}


			if (true)
			{
				Polinom P = PolinomStorage[Option1].DerivativeX();
				PolinomStorage[PolinomStorage.size()] = P;
				cout << endl << "Result: " << P.ToString();
			}

			break;

		case 6:
			for (auto p : PolinomStorage)
				cout << p.first << " : " << p.second.ToString() << ";" << endl;

			cout << endl << "Choose polinom: ";

			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();

				try
				{
					Option1 = stoi(Input);

					if (Option1 >= 0 && Option1 < PolinomStorage.size())
						Inputting = false;
					else
						Inputting = true;
				}

				catch (exception e)
				{
					Inputting = true;
				}

				if (Inputting)
					cout << endl << "Invalid option, try again: ";
			}


			if (true)
			{
				Polinom P = PolinomStorage[Option1].DerivativeY();
				PolinomStorage[PolinomStorage.size()] = P;
				cout << endl << "Result: " << P.ToString();
			}

			break;

		case 7:
			for (auto p : PolinomStorage)
				cout << p.first << " : " << p.second.ToString() << ";" << endl;

			cout << endl << "Choose polinom: ";

			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();

				try
				{
					Option1 = stoi(Input);

					if (Option1 >= 0 && Option1 < PolinomStorage.size())
						Inputting = false;
					else
						Inputting = true;
				}

				catch (exception e)
				{
					Inputting = true;
				}

				if (Inputting)
					cout << endl << "Invalid option, try again: ";
			}


			if (true)
			{
				Polinom P = PolinomStorage[Option1].DerivativeZ();
				PolinomStorage[PolinomStorage.size()] = P;
				cout << endl << "Result: " << P.ToString();
			}

			break;

		case 8:
			for (auto p : PolinomStorage)
				cout << p.first << " : " << p.second.ToString() << ";" << endl;

			cout << endl << "Choose polinom: ";

			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();

				try
				{
					Option1 = stoi(Input);

					if (Option1 >= 0 && Option1 < PolinomStorage.size())
						Inputting = false;
					else
						Inputting = true;
				}

				catch (exception e)
				{
					Inputting = true;
				}

				if (Inputting)
					cout << endl << "Invalid option, try again: ";
			}

			cout << endl << "Choose const: ";
			Inputting = true;
			while (Inputting)
			{
				cin >> Input;
				ClearCin();

				try
				{
					C = stod(Input);
					Inputting = false;
				}
				catch (exception e)
				{
					cout << endl << "Invalid constanst, try again: ";
					Inputting = true;
				}
			}

			if (true)
			{
				Polinom P = PolinomStorage[Option1] * C;
				PolinomStorage[PolinomStorage.size()] = P;
				cout << endl << "Result: " << P.ToString();
			}

			break;

		default:
			break;
		}

		cout << endl << endl;
		Input = " ";
	}

	return 0;
}

