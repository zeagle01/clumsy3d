
#include "gmock/gmock.h"

import clumsy.matrix;

using namespace clumsy;

namespace matrix_test
{


	template<typename M>
	void matrix_equals_expect(const M& act, const M& exp)
	{
		for (int ri = 0; ri < act.row_num(); ri++)
		{
			for (int ci = 0; ci < act.column_num(); ci++)
			{
				EXPECT_THAT(act(ri, ci), exp(ri, ci));
			}
		}
	}


	TEST(matrix_test, add0)
	{
		mat2f a
		{
			1.f,2.f,
			3.f,4.f
		};

		mat2f b
		{
			1.f,1.f,
			1.f,1.f
		};

		auto c = static_cast<mat2f> (a + b);

		matrix_equals_expect(c, 
		mat2f
			{
				2,3,
				4,5
			}
		);
	}

	TEST(matrix_test, add1)
	{
		mat2f a
		{
			1.f,2.f,
			3.f,4.f
		};

		mat2f b
		{
			1.f,1.f,
			1.f,1.f
		};

		auto c = static_cast<mat2f> (a + b + b);

		matrix_equals_expect(c, 
		mat2f
			{
				3,4,
				5,6
			}
		);
	}

	TEST(matrix_test, multiply)
	{
		mat2f a
		{
			1.f,2.f,
			3.f,4.f
		};

		mat2f b
		{
			1.f,0,
			0,1.f
		};

		auto c = static_cast<mat2f> (a * b);

		matrix_equals_expect(c, 
		mat2f
			{
				1,2,
				3,4
			}
		);
	}

	TEST(matrix_test, multiply1)
	{
		mat2f a
		{
			1.f,2.f,
			3.f,4.f
		};

		vec2f b
		{
			1.f,
			1.f,
		};

		auto c = static_cast<vec2f> (a * b);

		matrix_equals_expect(c,
			vec2f
			{
				3,
				7
			}
		);
	}

	TEST(matrix_test, column0)
	{
		mat2f a
		{
			1.f,2.f,
			3.f,4.f
		};

		auto c = static_cast<vec2f> (column(a, 0));

		matrix_equals_expect(c,
			vec2f
			{
				1,
				3
			}
		);
	}

	TEST(matrix_test, column1)
	{
		mat2f a
		{
			1.f,2.f,
			3.f,4.f
		};

		column(a, 0) = vec2f{ 42,42 };

		matrix_equals_expect(a,
			mat2f
			{
				42,2,
				42,4	
			}
		);
	}


	TEST(matrix_test, transpose0)
	{
		mat2f a
		{
			1.f,2.f,
			3.f,4.f
		};

		auto c = static_cast<mat2f> (transpose(a));

		matrix_equals_expect(c,
			mat2f
			{
				1,3,
				2,4
			}
		);
	}

	TEST(matrix_test, transpose1)
	{
		mat2f a;

		transpose(a) = mat2f
		{
			1,3,
			2,4,
		};

		matrix_equals_expect(a,
			mat2f
			{
				1,2,
				3,4
			}
		);
	}



}
