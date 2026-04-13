#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in pseudocode
// -- PRIM'S ALGORITHM --
inline const std::vector<std::string> MST_PRIM_PSEUDOCODE = {
	" 1 function PRIM(G, start):",
	" 2     for each vertex v in G:",
	" 3         visited[v] := false",
	" 4         cost[v] := +INF",
	" 5         parent[v] := NULL",
	" 6     cost[start] := 0",
	" 7     Q := new MinHeap()",   // stores (vertex, cost)
	" 8     INSERT(Q, (start, cost[start]))",
	" 9     while Q is not empty:",
	"10         (u, w) := EXTRACT-MIN(Q)",
	"11         if visited[u] = true:",
	"12             continue",
	"13         visited[u] := true",
	"14         for each (v, weight) in adjacency list of u:",
	"15             if visited[v] = false AND weight < cost[v]:",
	"16                 cost[v] := weight",
	"17                 parent[v] := u",
	"18                 INSERT(Q, (v, cost[v]))",
	"19     MST := empty set",     // Build MST from parent[]
	"20     for each vertex v in G:",
	"21         if parent[v] != NULL:",
	"22             MST.add_edge(parent[v], v)",
	"23     return MST"
};



// Line 8     = Push start node
// Line 10    = Extract min (highlight heap pop)
// Line 11–12 = Skip visited node (very important!)
// Line 13    = Mark node as visited
// Line 14    = Explore neighbors
// Line 15    = Key comparison (decision point)
// Line 16    = Update cost
// Line 17    = Update parent (edge selection moment)
// Line 18    = Push into heap

