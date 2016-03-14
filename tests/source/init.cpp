#include <Matrix.hpp>
#include <catch.hpp>

SCENARIO("Matrix", "[init]") {

	GIVEN("The number of rows and columns") {

		auto rows = 3;
		auto columns = 3;

		WHEN("Create instansce of Matrix") {

			Matrix matrix(rows, columns);

			THEN("The number of rows and columns must be preserved") {

				REQUIRE(matrix.rows() == rows);
				REQUIRE(matrix.columns() == columns);
			}
		}
	}
}