
#include <algorithm>
#include <iostream>

#include "path_finding/algorithm.hpp"
#include "path_finding/graph_builder.h"

struct Problem {
  pf::Graph graph;
  pf::NodeId start_node;
  pf::NodeId end_node;
};

Problem Problem1() {
  Problem problem;
  auto& graph = problem.graph;
  auto builder = pf::GraphBuilder(graph);
  for (auto i : {0, 1, 2, 3, 4, 5, 6}) {
    builder.Node(i);
  }
  builder.Link(0, 1, 2);
  builder.Link(0, 2, 6);
  builder.Link(1, 3, 5);
  builder.Link(2, 3, 8);
  builder.Link(3, 5, 15);
  builder.Link(3, 4, 10);
  builder.Link(4, 5, 6);
  builder.Link(4, 6, 2);
  builder.Link(6, 5, 6);
  problem.start_node = 0;
  problem.end_node = 5;
  return problem;
};

int main() {
  auto [graph, s, e] = Problem1();

  // search path
  auto shortest_path = pf::Dijkstra(graph, s, e);

  // output result
  std::copy(begin(shortest_path), end(shortest_path),
            std::ostream_iterator<pf::NodeId>(std::cout, " "));

  return 0;
}