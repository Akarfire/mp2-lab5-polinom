#include "Polinom.h"


Polinom::Polinom(std::string InPolinomNotation)
{
	pFirst = nullptr;

	// Funning Parsing
	std::string CurrentLexeme;
	float Multiplier = 1.f;

	for (int i = 0; i < InPolinomNotation.size(); i++)
	{
		char c = InPolinomNotation[i];
		if (c == ' ' && i != InPolinomNotation.size() - 1)
			continue;

		if (std::string("+-").find(c) != std::string::npos || i == InPolinomNotation.size() - 1)
		{
			if (i == InPolinomNotation.size() - 1)
				CurrentLexeme += c;

			// End of current lexeme (current monom)

			InsertMonom(CreateMonomFromNotation(CurrentLexeme += " "), Multiplier);

			Multiplier = 1.f;
			if (c == '-')
				Multiplier = -1.f;

			CurrentLexeme = "";
		}

		else
			CurrentLexeme += c;
	}
	InsertMonom(CreateMonomFromNotation("0"), 1.f);
}

Polinom::Polinom(const Polinom& InPolinom)
{
	Monom* OriginalMonom = InPolinom.pFirst;
	Monom* Last = nullptr;

	pFirst = nullptr;

	while (OriginalMonom)
	{
		Monom* NewMonom = new Monom(*OriginalMonom);

		if (Last)
			Last->pNext = NewMonom;

		else
			pFirst = NewMonom;

		Last = NewMonom;
		OriginalMonom = OriginalMonom->pNext;
	}
}


bool Polinom::ReadMonomNotation(std::string InNotation, double& OutA, int& OutPower)
{
	char LastVar = '-';
	std::string CurrentLexeme;

	OutPower = 0;

	for (int i = 0; i < InNotation.size(); i++)
	{
		char c = InNotation[i];

		bool IsVar = std::string("xyz").find(c) != std::string::npos;
		if (IsVar || i == InNotation.size() - 1)
		{

			if (LastVar == '-')
			{
				try
				{
					if (CurrentLexeme.size() > 0)
						OutA = std::stod(CurrentLexeme);
					else if (i != InNotation.size() - 1)
						OutA = 1;
					else
						OutA = 0;
				}
				catch (std::invalid_argument exception) { return false; }
			}

			else
			{				

				try
				{
					int Power = 1;

					if (CurrentLexeme.size() > 0)
						Power = std::stoi(CurrentLexeme);

					if (Power >= 10)
						return false;

					switch (LastVar)
					{
					case 'x':
						OutPower += 100 * Power;
						break;

					case 'y':
						OutPower += 10 * Power;
						break;

					case 'z':
						OutPower += Power;
						break;

					default:
						break;
					}
				}
				catch (std::invalid_argument exception) { return false; }
			}

			CurrentLexeme = "";
			LastVar = c;
		}

		else if (std::string("*^ ").find(c) != std::string::npos)
			continue;

		else
			CurrentLexeme += c;
	}

	return true;
}


void Polinom::InsertMonom(Monom* InMonom, double Multiplier)
{
	Monom* P = pFirst;
	Monom* Prp = nullptr;
	while (P != nullptr && P->Power > InMonom->Power)
	{
		Prp = P;
		P = P->pNext;
	}

	if (P && P->Power == InMonom->Power)
		P->A += InMonom->A * Multiplier;

	else
	{
		Monom* NewMonom = new Monom(*InMonom);
		NewMonom->A *= Multiplier;

		if (!Prp)
		{
			NewMonom->pNext = pFirst;
			pFirst = NewMonom;
		}

		else
		{
			Prp->pNext = NewMonom;
			NewMonom->pNext = P;
		}
	}
}


void Polinom::DeletePolinom()
{
	Monom* Next = nullptr;
	while (pFirst)
	{
		Next = pFirst->pNext;

		delete pFirst;

		pFirst = Next;
	}

	pFirst = nullptr;
}


double Polinom::Calculate(double InX, double InY, double InZ)
{
	double Result = 0;

	Monom* P = pFirst;
	while (P)
	{
		Result += P->Calculate(InX, InY, InZ);
		P = P->pNext;
	}

	return Result;
}

Polinom Polinom::DerivativeX()
{
	Polinom Result;

	Monom* P = pFirst;
	while (P)
	{
		double A = 0;
		int Power = 0;

		if (P->Power / 100 > 0)
		{
			A = P->A * (P->Power / 100);
			Power = P->Power - 100;
		}

		Monom* NewMonom = new Monom(A, Power);
		Result.InsertMonom(NewMonom);

		P = P->pNext;
	}

	return Result;
}

Polinom Polinom::DerivativeY()
{
	Polinom Result;

	Monom* P = pFirst;
	while (P)
	{
		double A = 0;
		int Power = 0;

		if ((P->Power % 100) / 10 > 0)
		{
			A = P->A * ((P->Power % 100) / 10);
			Power = P->Power - 10;
		}

		Monom* NewMonom = new Monom(A, Power);
		Result.InsertMonom(NewMonom);

		P = P->pNext;
	}

	return Result;
}

Polinom Polinom::DerivativeZ()
{
	Polinom Result;

	Monom* P = pFirst;
	while (P)
	{
		double A = 0;
		int Power = 0;

		if (P->Power % 10 > 0)
		{
			A = P->A * (P->Power % 10);
			Power = P->Power - 1;
		}

		Monom* NewMonom = new Monom(A, Power);
		Result.InsertMonom(NewMonom);

		P = P->pNext;
	}

	return Result;
}


const Polinom& Polinom::operator=(const Polinom& InPolinom)
{
	DeletePolinom();

	Monom* OriginalMonom = InPolinom.pFirst;
	Monom* Last = nullptr;
	while (OriginalMonom)
	{
		Monom* NewMonom = new Monom(*OriginalMonom);

		if (Last)
			Last->pNext = NewMonom;

		else
			pFirst = NewMonom;

		Last = NewMonom;
		OriginalMonom = OriginalMonom->pNext;
	}

	return *this;
}


const Polinom& Polinom::operator=(Polinom&& InMovingPolinom)
{
	DeletePolinom();

	pFirst = InMovingPolinom.pFirst;
	InMovingPolinom.pFirst = nullptr;

	return *this;
}


Polinom Polinom::operator+(const Polinom& InPolinom) const
{
	Polinom Result(*this);
	Monom* InP = InPolinom.pFirst;

	while (InP)
	{
		Result.InsertMonom(InP);

		InP = InP->pNext;
	}

	return Result;
}


Polinom Polinom::operator-(const Polinom& InPolinom) const
{
	Polinom Result(*this);
	Monom* InP = InPolinom.pFirst;

	while (InP)
	{
		Result.InsertMonom(InP, -1);

		InP = InP->pNext;
	}

	return Result;
}


const Polinom& Polinom::operator+=(const Polinom& InPolinom)
{
	Monom* InP = InPolinom.pFirst;

	while (InP)
	{
		InsertMonom(InP);

		InP = InP->pNext;
	}


	return *this;
}


const Polinom& Polinom::operator-=(const Polinom& InPolinom)
{
	Monom* InP = InPolinom.pFirst;

	while (InP)
	{
		InsertMonom(InP, -1);

		InP = InP->pNext;
	}


	return *this;
}


const Polinom& Polinom::operator*=(double InConst)
{
	Monom* P = pFirst;
	while (P)
	{
		P->A *= InConst;
		P = P->pNext;
	}

	return *this;
}

bool Polinom::operator==(const Polinom& InPolinom)
{
	Monom* P1 = pFirst;
	Monom* P2 = InPolinom.pFirst;
	while (P1)
	{
		if (!P2)
			return false;

		if (*P1 != *P2)
			return false;

		P1 = P1->pNext;
		P2 = P2->pNext;
	}

	return true;
}

std::string Polinom::ToString()
{
	std::string OutString;

	Monom* P = pFirst;

	while (P)
	{
		OutString += P->ToString();
		P = P->pNext;
		if (P)
			OutString += " ";
	}

	return OutString;
}


Polinom Polinom::operator*(double InConst) const
{
	Polinom Result(*this);

	Monom* P = Result.pFirst;
	while (P)
	{
		P->A *= InConst;
		P = P->pNext;
	}

	return Result;
}
