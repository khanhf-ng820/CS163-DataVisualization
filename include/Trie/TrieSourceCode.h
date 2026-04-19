#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in pseudocode
// -- SEARCH --
inline const std::vector<std::string> TRIE_CODE_SEARCH = {
	" 1  function Search(word):",
	" 2      node := root",
	" 3      for each character c in word:",
	" 4          if node.child[c] == NULL:",
	" 5              return false",
	" 6          node := node.child[c]",
	" 7      if node.isEndOfWord == true:",
	" 8          return true",
	" 9      else:",
	"10          return false"
};


// -- INSERT --
inline const std::vector<std::string> TRIE_CODE_INSERT = {
	"1  function Insert(word):",
	"2      node := root",
	"3      for each character c in word:",
	"4          if node.child[c] == NULL:",
	"5              node.child[c] := new TrieNode(c)",
	"6          node := node.child[c]",
	"7      node.isEndOfWord := true",
	"8      return node"
};


// -- DELETE --
inline const std::vector<std::string> TRIE_CODE_DELETE = {
	" 1  function Delete(node, word, depth):",
	" 2      if node == NULL:",
	" 3          return NULL",
	" 4      if depth == length(word):",
	" 5          node.isEndOfWord := false",
	" 6          if node != root AND node has no children:",
	" 7              DELETE node",
	" 8              return NULL",
	" 9          return node",
	"10      c := word[depth]",
	"11      node.child[c] := Delete(node.child[c], word, depth + 1)",
	"12      if node != root AND node has no children AND node.isEndOfWord == false:",
	"13          DELETE node",
	"14          return NULL",
	"15      return node"
};


// // -- UPDATE --
// inline const std::vector<std::string> TRIE_CODE_UPDATE = {
// 	" 1 func Trie-Insert(word, key):",
// 	" 2     for 0 <= i < key.length:",
// 	" 3     	if node->children[key[i]] = nullptr:",
// 	" 4     		node->children[key[i]] := Create-New-Node()",
// 	" 5     	node := node->children[key[i]]",
// 	" 6     node->value := value",
// 	" 7 func Trie-Delete(word, key):",
// 	" 8 	 if word = nullptr:",
// 	" 9 	 	 return nullptr",
// 	"10 	 else if key = \"\":",
// 	"11 	 	 word->value := nullptr",
// 	"12 	 else",
// 	"13 	 	 word->children[key[0]] := Trie-Delete(word->children[key[0]], key[1:])",
// 	"14 	 if word->value != nullptr:",
// 	"15 	 	 return word",
// 	"16 	 for 0 ≤ i < word->children.length:",
// 	"17 	 	 if word->children[i] != nullptr:",
// 	"18 	 		 return word",
// 	"19 	 return nullptr"
// };
