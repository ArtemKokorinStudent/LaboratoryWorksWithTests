#include <Matrix.hpp>
#include <catch.hpp>
#include <fstream>

SCENARIO("Matrix init", "[init]") {

	GIVEN("The number of rows and columns") {

		auto rows = 3;
		auto columns = 3;

		WHEN("Create instansce of Matrix") {

			Matrix<int> matrix(rows, columns);

			THEN("The number of rows and columns must be preserved") {

				REQUIRE(matrix.rows() == rows);
				REQUIRE(matrix.columns() == columns);
			}
		}
	}
}

SCENARIO("Matrix >>", "[fill]") {
	std::ifstream input("A2x2.txt");
	Matrix<int> A = Matrix<int>(2, 2);
	REQUIRE( input >> A );
	REQUIRE( A[0][0] == 1 );
	REQUIRE( A[0][1] == 1 );
	REQUIRE( A[1][0] == 2 );
	REQUIRE( A[1][1] == 2 );
}

SCENARIO("Matrix +", "[addition]") {
	Matrix<int> A = Matrix<int>(2, 2);
	std::ifstream("A2x2.txt") >> A;
	Matrix<int> B = Matrix<int>(2, 2);
	std::ifstream("B2x2.txt") >> B;
	Matrix<int> expected = Matrix<int>(2, 2);
	std::ifstream("A+B2x2.txt") >> expected;

	Matrix<int> result = A + B;
	REQUIRE(result == expected);
}

SCENARIO("Matrix *", "[multiplication]") {
	Matrix<int> A = Matrix<int>(2, 2);
	std::ifstream("A2x2.txt") >> A;
	Matrix<int> B = Matrix<int>(2, 2);
	std::ifstream("B2x2.txt") >> B;
	Matrix<int> expected = Matrix<int>(2, 2);
	std::ifstream("A*B2x2.txt") >> expected;

	Matrix<int> result = A * B;
	REQUIRE(result == expected);
}
