#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in pseudocode
// -- DIJKSTRA'S ALGORITHM --
inline const std::vector<std::string> DIJKSTRA_PSEUDOCODE = {
	"1  function Dijkstra(Graph, source):", // 0
	"2      dist[] := +INF",
	"3      parent[] := -1",
	"4      dist[source] := 0",
	"5      pq := empty-min-priority-queue()",
	"6      pq.push( (0, source) )",
	"7      while pq is not empty:",        // 6
	"8          (d, u) := pq.pop()",
	"9          if d > dist[u]:",
	"10             continue",
	"11         for each (v, weight) in Graph[u]:",
	"12             if dist[u] + weight < dist[v]:",
	"13                 dist[v] := dist[u] + weight",
	"14                 parent[v] := u",
	"15                 pq.push( (dist[v], v) )",
	"16     return dist[], parent[]"
};

// Line 5 = highlight when inserting source
// Line 7 = selecting next node (current min)
// Line 8–9 = skipping outdated queue entries
// Line 10 = exploring neighbors
// Line 11–13 = relaxation step (key animation)

// function getPath(parent, target):
// 	path := empty list
// 	while target != -1:
// 		path.push_front(target)
// 		target := parent[target]
// 	return path
