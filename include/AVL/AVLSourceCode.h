#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in pseudocode
// -- SEARCH --
inline const std::vector<std::string> AVL_CODE_SEARCH = {
	" 1  function Search(root, key):",
	" 2      if root == NULL:",
	" 3          return NULL",
	" 4      if key == root.key:",
	" 5          return root",
	" 6      else if key < root.key:",
	" 7          return Search(root.left, key)",
	" 8      else:",
	" 9          return Search(root.right, key)"
};


// -- INSERT --
inline const std::vector<std::string> AVL_CODE_INSERT = {
	" 1  function Insert(root, key):",
	" 2      if root == NULL:",
	" 3          return NewNode(key)",
	" 4      if key < root.key:",
	" 5          root.left = Insert(root.left, key)",
	" 6      else if key > root.key:",
	" 7          root.right = Insert(root.right, key)",
	" 8      else:",
	" 9          return root   // Duplicate keys not allowed",
	"10      root.height = 1 + max(Height(root.left), Height(root.right))",
	"11      balance = Height(root.left) - Height(root.right)",
	"12      if balance > 1 AND key < root.left.key:",
	"13          return RightRotate(root)",
	"14      if balance < -1 AND key > root.right.key:",
	"15          return LeftRotate(root)",
	"16      if balance > 1 AND key > root.left.key:",
	"17          root.left = LeftRotate(root.left)",
	"18          return RightRotate(root)",
	"19      if balance < -1 AND key < root.right.key:",
	"20          root.right = RightRotate(root.right)",
	"21          return LeftRotate(root)",
	"22      return root"
};


// -- DELETE --
inline const std::vector<std::string> AVL_CODE_DELETE = {
	" 1  function Delete(root, key):",
	" 2      if root == NULL:",
	" 3          return root",
	" 4      if key < root.key:",
	" 5          root.left = Delete(root.left, key)",
	" 6      else if key > root.key:",
	" 7          root.right = Delete(root.right, key)",
	" 8      else:",
	" 9          if root.left == NULL:",
	"10              temp = root.right",
	"11              DELETE root",
	"12              return temp",
	"13          else if root.right == NULL:",
	"14              temp = root.left",
	"15              DELETE root",
	"16              return temp",
	"17          temp = MinValueNode(root.right)",
	"18          root.key = temp.key",
	"19          root.right = Delete(root.right, temp.key)",
	"20      root.height = 1 + max(Height(root.left), Height(root.right))",
	"21      balance = Height(root.left) - Height(root.right)",
	"22      if balance > 1 AND BalanceFactor(root.left) >= 0:",
	"23          return RightRotate(root)",
	"24      if balance > 1 AND BalanceFactor(root.left) < 0:",
	"25          root.left = LeftRotate(root.left)",
	"26          return RightRotate(root)",
	"27      if balance < -1 AND BalanceFactor(root.right) <= 0:",
	"28          return LeftRotate(root)",
	"29      if balance < -1 AND BalanceFactor(root.right) > 0:",
	"30          root.right = RightRotate(root.right)",
	"31          return LeftRotate(root)",
	"32      return root"
};


// // -- UPDATE --
// inline const std::vector<std::string> AVL_CODE_UPDATE = {
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
