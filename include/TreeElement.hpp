#pragma once
#include "BinarySearchTreeException.hpp"

template<class DataT>
class TreeElement {
public:
	TreeElement *left_children, *right_children, *parent;
	DataT data;
	TreeElement() : left_children(nullptr), right_children(nullptr), parent(nullptr) {};
	TreeElement(DataT _data) 
		: data(_data), left_children(nullptr), right_children(nullptr), parent(nullptr) {};
	void OutputSubtree(std::ostream &stream) const throw (StreamException){
		if (left_children != nullptr) left_children->OutputSubtree(stream);
		if (!(stream << data << " ")) throw StreamException();
		if (right_children != nullptr) right_children->OutputSubtree(stream);
	}
};
