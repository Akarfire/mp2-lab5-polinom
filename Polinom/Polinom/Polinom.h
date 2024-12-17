#pragma once
#include <string>
#include <stdexcept>

class Polinom
{
	// Monom Node Structure
	struct Monom
	{
		double A; // - coefficient
		int Power; // pX * 100 + pY * 10 + pZ

		Monom* pNext; // pointer to the next monom ()

		// Constructor
		Monom(double InA = 0, int InPower = 0, Monom* InNext = nullptr) : A(InA), Power(InPower), pNext(InNext) {}

		Monom(double InA, int InXpower, int InYpower, int InZpower, Monom* InNext = nullptr) : A(InA), pNext(InNext)
		{
			Power = InXpower * 100 + InYpower * 10 + InZpower;
		}

		// Copy constructor
		Monom(const Monom& InMonom)
		{
			A = InMonom.A;
			Power = InMonom.Power;

		}

		double Calculate(double InX, double InY, double InZ)
		{
			return A * pow(InX, Power / 100) * pow(InY, (Power % 100) / 10) * pow(InZ, Power % 10);
		}
	};

	Monom* pFirst;

private:
	
	// Deletes all Monoms of the Polinom
	void DeletePolinom();

	/* Reads monom from a notation
		1) A*x^a*y^b*z^c
		2) Axaybzc
	*/
	bool ReadMonomNotation(std::string InNotation, double& OutA, int& OutPower);

	// Creates a new monom from the notation
	Monom* CreateMonomFromNotation(std::string InMonomNotation)
	{
		double A;
		int Power;

		if (!ReadMonomNotation(InMonomNotation, A, Power))
			throw(std::runtime_error("Incorrect Monom Notation: " + InMonomNotation));

		Monom* NewMonom = new Monom(A, Power);

		return NewMonom;
	}

	// Inserts a monom into the polinom (does addition if necessary)
	void InsertMonom(Monom* InMonom, double Multiplier = 1.0);

public:

	// Defalt constructor;
	Polinom(): pFirst(nullptr) {}

	/* Constructor - converts polinom notation to Monom List
	* Possible Notations:
	*	1) A*x^a*y^b - B*z^c
	*	2) Axayb - Bzc
	*/
	Polinom(std::string InPolinomNotation);

	// Copy constructor
	Polinom(const Polinom& InPolinom);

	// Move constructor
	Polinom(Polinom&& InMovingPolinom) noexcept : pFirst(InMovingPolinom.pFirst) { InMovingPolinom.pFirst = nullptr; }

	// Destructor
	~Polinom() { DeletePolinom; }


	// Calculates the value of the Polinom in (X, Y, Z)
	double Calculate(double InX, double InY, double InZ);

	// Derivatives
	Polinom DerivativeX();
	Polinom DerivativeY();
	Polinom DerivativeZ();

	// Assigment operators
	const Polinom& operator=(const Polinom& InPolinom);
	const Polinom& operator=(Polinom&& InMovingPolinom);

	// Polinom-to-Polinom math operations
	Polinom operator+(const Polinom& InPolinom) const;
	Polinom operator-(const Polinom& InPolinom) const;

	// Multiplication by constant
	Polinom operator*(double InConst) const;
	friend Polinom operator*(double InConst, const Polinom& InPolinom) { return InPolinom * InConst; }

	// Modify existing Polinom
	const Polinom& operator+=(const Polinom& InPolinom);
	const Polinom& operator-=(const Polinom& InPolinom);
	const Polinom& operator*=(double InConst);
};