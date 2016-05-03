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
SCENARIO("BinarySearchTree file init", "[file init]") {
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
SCENARIO("FileOutput", "[file output]") {
	GIVEN("File name"){
		WHEN("Output in file") {
			BinarySearchTree<int> tree;
			tree.FileFill("input_tree");
			tree.FileOut("output");
			THEN("Nothing breaks") {
				REQUIRE(true);
			}
		}
	}
}
SCENARIO("Add", "[add]"){
	BinarySearchTree<int> tree;
	for (int i = 0; i < 5; i++){
		tree.add(4);
	}
	REQUIRE(true);
}
SCENARIO("Search", "[search]") {
	BinarySearchTree<int> tree;
	tree.add(3);
	REQUIRE(tree.search(3));
	REQUIRE(!tree.search(2));
}

SCENARIO("FileSearch","[file search]"){
	BinarySearchTree<int> tree;
	tree.FileFill("input_tree");
	REQUIRE(tree.search(98));
	REQUIRE(!tree.search(97));
}
