#include <Matrix.hpp>
#include <catch.hpp>
#include <fstream>

SCENARIO("BinarySearchTree init", "[init]") {
	WHEN("Create instansce of BinarySearchTree") {
		BinarySearchTree<int> tree;
		THEN("Nothing breaks") {
			REQUIRE(true);
		}
	}
}
