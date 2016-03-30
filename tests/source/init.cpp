#include <Matrix.hpp>
#include <catch.hpp>
#include <fstream>

SCENARIO("Matrix init", "[init]") {
	GIVEN("The number of lines and columns") {
		auto lines = 36;
		auto columns = 39;

		WHEN("Create instansce of Matrix") {
			Matrix matrix(lines, columns);
			THEN("The number of lines and columns must be preserved") {
				REQUIRE(matrix.GetNumberOfLines() == lines);
				REQUIRE(matrix.GetNumberOfColumns() == columns);
			}
		}
	}
}
SCENARIO("Matrix InitFromFile", "[fill]") {
	Matrix C(3, 1);
	A.InitFromFile("C3x1.txt");
	REQUIRE( A[0][0] == 1 );
	REQUIRE( A[0][1] == 2 );
	REQUIRE( A[0][2] == 0 );
}
SCENARIO("Matrix +", "[addition]") {
	Matrix A(3, 3);
	A.InitFromFile("A3x3.txt");
	Matrix B(3, 3);
	B.InitFromFile("B3x3.txt");
	Matrix expected = Matrix(3, 3);
	expected.InitFromFile("(A3x3)+(B3x3).txt");

	Matrix result = A + B;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			REQUIRE(result[i][j] == expected[i][j]);
		}
	}
}
SCENARIO("Matrix *", "[multiplication]") {
	Matrix A = Matrix(3, 3);
	A.InitFromFile("A3x3.txt");
	Matrix C = Matrix(3, 1);
	C.InitFromFile("C3x1.txt");
	Matrix expected = Matrix(3, 1);
	expected.InitFromFile("(A3x3)(C3x1).txt");

	Matrix result = A * C;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			REQUIRE(result[i][j] == expected[i][j]);
		}
	}
}
