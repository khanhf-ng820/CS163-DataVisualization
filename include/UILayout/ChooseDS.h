#pragma once
#include "Program.h"
#include "utils/utils.h"

#define ALL_DS_TYPE_LIST { "Lists - Singly Linked List", "Hash Table - Linear Probing", "Trees - AVL Tree", "Trees - Trie", "Graphs - Minimum Spanning Tree (Prim\'s algorithm)", "Graphs - Shortest Path (Dijkstra\'s algorithm)" }


const std::vector<std::string> ALL_DS_LIST = ALL_DS_TYPE_LIST;


enum class DSType {
	SINGLY_LINKED_LIST,
	HASH_TABLE,
	AVL_TREE,
	TRIE_TREE,
	MST_PRIM_GRAPH,
	DIJKSTRA_GRAPH,
	DEFAULT // Error value, must avoid
};

enum DataInitOption {
	DATA_INIT_EMPTY,
	DATA_INIT_RANDOMIZED,
	DATA_INIT_CUSTOM,
	DATA_INIT_FROM_FILE,
	DATA_INIT_CONTINUE
	// Must avoid other values
};



DSType strToDSType(std::string str);
std::string getDataFileName(std::string ds_selection_str);

std::string getLongestDS_Str();
