#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in pseudocode
// -- SEARCH --
inline const std::vector<std::string> TRIE_CODE_SEARCH = {
	"1 for 0 <= i < word.length:",
	"2     if node->children[word[i]] = nullptr:",
	"3         return nullptr",
	"4     node := node->children[word[i]]",
	"5 return node->value"
};


// -- INSERT --
inline const std::vector<std::string> TRIE_CODE_INSERT = {
	" 1 for 0 <= i < key.length:",
	" 2 	if node->children[key[i]] = nullptr:",
	" 3 		node->children[key[i]] := Create-New-Node()",
	" 4 	node := node->children[key[i]]",
	" 5 node->value := value"
};


// -- REMOVE --
inline const std::vector<std::string> TRIE_CODE_REMOVE = {
	" 1 func Trie-Delete(word, key):",
	" 2 	 if word = nullptr:",
	" 3 	 	 return nullptr",
	" 4 	 else if key = \"\":",
	" 5 	 	 word->value := nullptr",
	" 6 	 else",
	" 7 	 	 word->children[key[0]] := Trie-Delete(word->children[key[0]], key[1:])",
	" 8 	 if word->value != nullptr:",
	" 9 	 	 return word",
	"10 	 for 0 ≤ i < word->children.length:",
	"11 	 	 if word->children[i] != nullptr:",
	"12 	 		 return word",
	"13 	 return nullptr"
};


// -- UPDATE --
inline const std::vector<std::string> TRIE_CODE_UPDATE = {
	" 1 func Trie-Insert(word, key):",
	" 2     for 0 <= i < key.length:",
	" 3     	if node->children[key[i]] = nullptr:",
	" 4     		node->children[key[i]] := Create-New-Node()",
	" 5     	node := node->children[key[i]]",
	" 6     node->value := value",
	" 7 func Trie-Delete(word, key):",
	" 8 	 if word = nullptr:",
	" 9 	 	 return nullptr",
	"10 	 else if key = \"\":",
	"11 	 	 word->value := nullptr",
	"12 	 else",
	"13 	 	 word->children[key[0]] := Trie-Delete(word->children[key[0]], key[1:])",
	"14 	 if word->value != nullptr:",
	"15 	 	 return word",
	"16 	 for 0 ≤ i < word->children.length:",
	"17 	 	 if word->children[i] != nullptr:",
	"18 	 		 return word",
	"19 	 return nullptr"
};
