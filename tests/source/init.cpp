#include <catch.hpp>

#include <Matrix.hpp>
#include <fstream>

SCENARIO("Matrix init", "[init]") {
	GIVEN("The number of lines and columns") {
		auto lines = 36;
		auto columns = 39;

		WHEN("Create instansce of Matrix") {
			Matrix<int> matrix(lines, columns);
			THEN("The number of lines and columns must be preserved") {
				REQUIRE(matrix.GetNumberOfLines() == lines);
				REQUIRE(matrix.GetNumberOfColumns() == columns);
			}
		}
	}
}

SCENARIO("Matrix InitFromFile", "[fill]") {
	Matrix<int> C(3, 1);
	C.InitFromFile("C3x1.txt");
	REQUIRE( C[0][0] == 1 );
	REQUIRE( C[1][0] == 2 );
	REQUIRE( C[2][0] == 0 );
}
SCENARIO("Matrix Output", "[output]") {
	Matrix<int> A(5, 4);
	A.InitFromRandom();
	std::cout << A;
}
SCENARIO("Matrix =", "assignment") {
	Matrix<int> A(3, 3);
	A.InitFromFile("A3x3.txt");
	Matrix<int> B(4, 2);
	B = A;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			REQUIRE( A[i][j] == B[i][j] );
		}
	}
}
SCENARIO("Matrix +", "[addition]") {
	Matrix<int> A(3, 3);
	A.InitFromFile("A3x3.txt");
	Matrix<int> B(3, 3);
	B.InitFromFile("B3x3.txt");
	Matrix<int> expected = Matrix<int>(3, 3);
	expected.InitFromFile("(A3x3)+(B3x3).txt");

	Matrix<int> result = A + B;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			REQUIRE(result[i][j] == expected[i][j]);
		}
	}
}
SCENARIO("Matrix *", "[multiplication]") {
	Matrix<int> A = Matrix<int>(3, 3);
	A.InitFromFile("A3x3.txt");
	Matrix<int> C = Matrix<int>(3, 1);
	C.InitFromFile("C3x1.txt");
	Matrix<int> expected = Matrix<int>(3, 1);
	expected.InitFromFile("(A3x3)(C3x1).txt");

	Matrix<int> result = A * C;
	for (int i = 0; i < 3; i++){
		REQUIRE(result[i][0] == expected[i][0]);
	}
}
SCENARIO("Matrix ==", "[comparsion]"){
	Matrix<int> A = Matrix<int>(3, 3);
	A.InitFromFile("A3x3.txt");
	Matrix<int> C = Matrix<int>(3, 1);
	C.InitFromFile("C3x1.txt");
	
	REQUIRE(A != C);
	REQUIRE(A == A);
}
SCENARIO("Bad Matrix *", "[badmultiplication]") {
	Matrix<int> A = Matrix<int>(3, 3);
	A.InitFromFile("A3x3.txt");
	Matrix<int> C = Matrix<int>(3, 1);
	C.InitFromFile("C3x1.txt");
	bool exception_flag = false;
	try{
		C * A;
	} catch (...){
		exception_flag = true;
	}
	REQUIRE(exception_flag);
}
SCENARIO("Bad Matrix +", "[badplus") {
	Matrix<int> A = Matrix<int>(3, 3);
	A.InitFromFile("A3x3.txt");
	Matrix<int> C = Matrix<int>(3, 1);
	C.InitFromFile("C3x1.txt");
	bool exception_flag = false;
	try{
		A + C;
	} catch (...){
		exception_flag = true;
	}
	REQUIRE(exception_flag);
}
SCENARIO("Bad matrix InitFromFile", "[fill]"){
	std::cout << "Bad >>";
	Matrix<int> C(4, 5);
	bool exception_flag = false;
	try{
		C.InitFromFile("A8x3.txt");
	} catch (...){
		exception_flag = true;
	}
	REQUIRE(exception_flag);
}

SCENARIO("Bad []", "[badindex]") {
	Matrix<int> C(3, 1);
	bool exception_flag = false;
	try{
		C[1000];
	} catch (...){
		exception_flag = true;
	}
	REQUIRE(exception_flag);
}

