#pragma once
#include "Program.h"

#define ALL_DS_TYPE_LIST { "Lists - Singly Linked List", "Hash Table - Linear Probing", "Trees - AVL Tree", "Trees - Trie", "Graphs - Minimum Spanning Tree", "Graphs - Shortest Path (Dijkstra\'s algorithm)" }



enum class DSType {
	SINGLY_LINKED_LIST,
	HASH_TABLE_LINEAR,
	AVL_TREE,
	TRIE_TREE,
	MST_GRAPH,
	DIJKSTRA_GRAPH,
	DEFAULT // Error value, must avoid
};

enum DataInitOption {
	DATA_INIT_EMPTY,
	DATA_INIT_RANDOMIZED,
	DATA_INIT_FROM_FILE,
	DATA_INIT_DEFAULT // Error value, must avoid
};



DSType strToDSType(std::string str);
std::string getDataFileName(std::string ds_selection_str);
