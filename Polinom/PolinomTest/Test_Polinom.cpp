#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "Polinom.h"
#include <gtest.h>

TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW( Polinom A("5x2y3 + 3x3z1 - 5z") );
}

TEST(Polinom, equal_polinoms_are_equal)
{
	Polinom A("5x2y3 + 3x3z1 - 5z");
	Polinom B("5x2 y3 + 3x3z 1 - 5z ");

	bool Result = false;
	ASSERT_NO_THROW(Result = A == B);

	EXPECT_EQ(true, Result);
}

TEST(Polinom, can_calculate_simple_polinom)
{
	Polinom A("5x3yz3");

	double Result = 0;
	ASSERT_NO_THROW(Result = A.Calculate(1, 2, 3));

	EXPECT_EQ(270, Result);
}

TEST(Polinom, can_calculate_complex_polinom)
{
	Polinom A("5x2y3 + 3x3z1 - 5z + 5");

	double Result = 0;
	ASSERT_NO_THROW(Result = A.Calculate(1, 2, 3));

	EXPECT_EQ(39, Result);
}

TEST(Polinom, can_add_simple_polinoms)
{
	Polinom A("5x2y3 + 3x3z1 - 5z");
	Polinom B("-5x");
	Polinom C("5x2y3 + 3x3z1 - 5z - 5x");

	Polinom Result;
	ASSERT_NO_THROW(Result = A + B);

	bool Eq = Result == C;

	EXPECT_EQ(true, Eq);
}

TEST(Polinom, can_add_intersecting_polinoms)
{
	Polinom A("5x2y3 + 3x3z1 - 5z");
	Polinom B("3x2y3 -5x - 3");
	Polinom C("8x2y3 + 3x3z1 - 5z - 5x - 3");

	Polinom Result;
	ASSERT_NO_THROW(Result = A + B);

	bool Eq = Result == C;

	EXPECT_EQ(true, Eq);
}

TEST(Polinom, can_subtract_simple_polinoms)
{
	Polinom A("5x2y3 + 3x3z1 - 5z");
	Polinom B("-5x");
	Polinom C("5x2y3 + 3x3z1 - 5z + 5x");

	Polinom Result;
	ASSERT_NO_THROW(Result = A - B);

	bool Eq = Result == C;

	EXPECT_EQ(true, Eq);
}

TEST(Polinom, can_subtract_intersecting_polinoms)
{
	Polinom A("5x2y3 + 3x3z1 - 5z");
	Polinom B("3x2y3 -5x - 3");
	Polinom C("2x2y3 + 3x3z1 - 5z + 5x + 3");

	Polinom Result;
	ASSERT_NO_THROW(Result = A - B);

	bool Eq = Result == C;

	EXPECT_EQ(true, Eq);
}

TEST(Polinom, can_multiply_polinoms_by_const)
{
	Polinom A("5x2y3 + 3x3z1 - 5z");
	Polinom B("10x2y3 + 6x3z1 - 10z");

	Polinom Result;
	ASSERT_NO_THROW(Result = A * 2);

	bool Eq = Result == B;

	EXPECT_EQ(true, Eq);
}

TEST(Polinom, can_get_polinom_derivative_over_x)
{
	Polinom A("5xyz + 3x2z");
	Polinom B("5yz + 6xz");

	Polinom Result;
	ASSERT_NO_THROW(Result = A.DerivativeX());

	bool Eq = Result == B;

	EXPECT_EQ(true, Eq);
}

TEST(Polinom, can_get_polinom_derivative_over_y)
{
	Polinom A("5xyz + 3x2z");
	Polinom B("5xz");

	Polinom Result;
	ASSERT_NO_THROW(Result = A.DerivativeY());

	bool Eq = Result == B;

	EXPECT_EQ(true, Eq);
}

TEST(Polinom, can_get_polinom_derivative_over_z)
{
	Polinom A("5xyz + 3x2z");
	Polinom B("5xy + 3x2");

	Polinom Result;
	ASSERT_NO_THROW(Result = A.DerivativeZ());

	bool Eq = Result == B;

	EXPECT_EQ(true, Eq);
}