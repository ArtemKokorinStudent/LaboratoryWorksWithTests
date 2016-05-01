#include <BinarySearchTree.hpp>
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
SCENARIO("BinarySearchTree init", "[init]") {
	GIVEN("File name"){
		WHEN("Create instansce of BinarySearchTree from file") {
			BinarySearchTree<int> tree;
			tree.FileFill("input_tree");
			THEN("Nothing breaks") {
				REQUIRE(true);
			}
		}
	}
}
