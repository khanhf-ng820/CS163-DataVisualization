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






inline char SLL_EXAMPLE[] = "36 67 -69 18 1 -5";
inline char HASH_TABLE_EXAMPLE[] = "N 56 N 36 N N N -4 N N N";
inline char AVL_EXAMPLE[] = "36 67 -69 18 1 -5";
inline char TRIE_EXAMPLE[] = "abc abcd abd bcd";
inline char GRAPH_ADJ_MATRIX_EXAMPLE[] = " 0  6 10  0  0  0  0  0  0  0 \n 6  0 12 11 14  0  0  0  0  0 \n10 12  0 12  0  0  8 16  0  0 \n 0 11 12  0  0  6  3  0  0  0 \n 0 14  0  0  0  4  0  0  6  0 \n 0  0  0  6  4  0  0  0 12  0 \n 0  0  8  3  0  0  0  0 16  6 \n 0  0 16  0  0  0  0  0  0  8 \n 0  0  0  0  6 12 16  0  0 13 \n 0  0  0  0  0  0  6  8 13  0";
inline char GRAPH_ADJ_LIST_EXAMPLE[] = "10\n1 6 2 10 \n0 6 2 12 3 11 4 14  \n0 10 1 12 3 12 6 8 7 16\n1 11 2 12 5 6 6 3   \n1 14 5 4 8 6     \n3 6 4 4 8 12     \n2 8 3 3 8 16 9 6    \n2 16 9 8      \n4 6 5 12 6 16 9 13  \n6 6 7 8 8 13";
inline char GRAPH_EDGE_LIST_EXAMPLE[] = "10\n0 1 6\n0 2 10\n1 2 12\n1 3 11\n1 4 14\n2 3 12\n2 6 8\n2 7 16\n3 5 6\n3 6 3\n4 5 4\n4 8 6\n5 8 12\n6 8 16\n6 9 6\n7 9 8\n8 9 13";




