#pragma once
#include <iostream>
#include <fstream>
#include "TreeElement.hpp"
#include "BinarySearchTreeException.hpp"

template <class DataT> class BinarySearchTree;
template <class DataT> std::istream& operator>> (std::istream &stream, BinarySearchTree<DataT> &tree) {
	tree.Fill(stream);
	return stream;
}
template <class DataT> std::ostream& operator<< (std::ostream &stream, const BinarySearchTree<DataT> &tree) {
	tree.Output();
	return stream;
}

template<class DataT>
class BinarySearchTree {
public:
	BinarySearchTree() : root(nullptr) {};
	
	void FileFill(const char *filename) throw (FileException, FileEndException);
	void InsertElement(DataT _data);
	TreeElement<DataT>* SearchElement(DataT _data) const;
	void Output(std::ostream &stream = std::cout) const { root->OutputSubtree(stream); }
	friend std::istream& operator>> <>(std::istream &stream, BinarySearchTree<DataT> &tree);
private:
	TreeElement<DataT> *root;
	TreeElement<DataT> * FindParent(DataT _data) const;
	void Fill(std::istream & stream) throw (FileException);
};
template <class DataT> TreeElement<DataT> * BinarySearchTree<DataT>::FindParent(DataT _data) const {
	TreeElement<DataT> *iterator = root;
	while (iterator != nullptr) {
		if (_data < iterator->data) {
			if (iterator->left_children == nullptr) {
				break;
			}
			iterator = iterator->left_children;
		}
		else {
			if (iterator->right_children == nullptr) {
				break;
			}
			iterator = iterator->right_children;
		}
	}
	return iterator;
}
template <class DataT> void BinarySearchTree<DataT>::Fill(std::istream & stream) throw (FileException) {
	int input_length;
	if (!(stream >> input_length)) throw FileException();

	DataT temp;
	for (int i = 0; i < input_length; i++) {
		if (stream >> temp) InsertElement(temp);
		else throw FileEndException();
	}
}
template <class DataT> void BinarySearchTree<DataT>::FileFill(const char *filename) throw (FileException, FileEndException){
	std::fstream stream(filename);
	Fill(stream);
}
template <class DataT> void BinarySearchTree<DataT>::InsertElement(DataT _data) {
	TreeElement<DataT> *new_element = new TreeElement<DataT>(_data);
	if (root == nullptr) {
		root = new_element;
	}
	else {
		TreeElement<DataT> *parent_of_new_element = FindParent(_data);
		new_element->parent = parent_of_new_element;
		if (_data < parent_of_new_element->data) parent_of_new_element->left_children = new_element;
		else parent_of_new_element->right_children = new_element;
	}
}
template <class DataT> TreeElement<DataT>* BinarySearchTree<DataT>::SearchElement(DataT _data) const  {
	TreeElement<DataT> *iterator = root;
	while (iterator != nullptr) {
		if (iterator->data == _data) return iterator;
		iterator = _data < iterator->data ? iterator->left_children : iterator->right_children;
	}
	iterator = nullptr;
	return iterator;
}
