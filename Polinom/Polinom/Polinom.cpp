#include "Polinom.h"


Polinom::Polinom(std::string InPolinomNotation)
{
	// Funning Parsing
	std::string CurrentLexeme;

	for (char c : InPolinomNotation)
	{
		if (std::string("+-").find(c) != std::string::npos)
		{
			// End of current lexeme (current monom)
			if (size(CurrentLexeme) <= 0)
				throw(std::runtime_error("Empty Monom Notation!"));

			InsertMonom(CreateMonomFromNotation(CurrentLexeme));

			CurrentLexeme = "";
		}

		else
			CurrentLexeme += c;
	}

	if (size(CurrentLexeme) <= 0)
		throw(std::runtime_error("Empty Monom Notation!"));

	InsertMonom(CreateMonomFromNotation(CurrentLexeme));
}

Polinom::Polinom(const Polinom& InPolinom)
{
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
}


bool Polinom::ReadMonomNotation(std::string InNotation, double& OutA, int& OutPower)
{
	char LastVar = '-';
	std::string CurrentLexeme;
	for (char c : InNotation)
	{
		if (std::string("*^").find(c) != std::string::npos)
			continue;

		if (std::string("xyz").find(c) != std::string::npos)
		{
			if (LastVar == '-')
			{
				try
				{
					OutA = std::stod(CurrentLexeme);
				}
				catch (std::invalid_argument exception) { return false; }
			}

			else
			{				

				try
				{
					int Power = 0;

					if (CurrentLexeme.size() == 0)
						Power = 1;

					else
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

			LastVar = c;
		}
	}

	return true;
}


void Polinom::InsertMonom(Monom* InMonom, double Multiplier)
{
	Monom* P = pFirst;
	Monom* Prp = nullptr;
	while (P && P->Power > InMonom->Power)
	{
		Prp = P;
		P = P->pNext;
	}

	if (Prp->Power == InMonom->Power)
		Prp->A += InMonom->A * Multiplier;

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
	Polinom Result(*this);

	Monom* Prp = nullptr;
	Monom* P = Result.pFirst;
	while (P)
	{
		if (P->Power / 100 > 0)
		{
			P->A *= P->Power / 100;
			P->Power -= 100;

			Prp = P;
			P = P->pNext;
		}

		else
		{
			Prp->pNext = P->pNext;

			delete P;

			P = Prp->pNext;
		}
	}

	return Result;
}

Polinom Polinom::DerivativeY()
{
	Polinom Result(*this);

	Monom* Prp = nullptr;
	Monom* P = Result.pFirst;
	while (P)
	{
		if ((P->Power % 100) / 10 > 0)
		{
			P->A *= (P->Power % 100) / 10;
			P->Power -= 10;

			Prp = P;
			P = P->pNext;
		}

		else
		{
			Prp->pNext = P->pNext;

			delete P;

			P = Prp->pNext;
		}
	}

	return Result;
}

Polinom Polinom::DerivativeZ()
{
	Polinom Result(*this);

	Monom* Prp = nullptr;
	Monom* P = Result.pFirst;
	while (P)
	{
		if (P->Power % 10 > 0)
		{
			P->A *= P->Power % 10;
			P->Power -= 1;

			Prp = P;
			P = P->pNext;
		}

		else
		{
			Prp->pNext = P->pNext;

			delete P;

			P = Prp->pNext;
		}
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
}


const Polinom& Polinom::operator=(Polinom&& InMovingPolinom)
{
	DeletePolinom();

	pFirst = InMovingPolinom.pFirst;
	InMovingPolinom.pFirst = nullptr;
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

	Result *= (1 / Result.pFirst->A);

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

	operator*=(1 / pFirst->A);

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

	operator*=(1 / pFirst->A);

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
