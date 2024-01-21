#pragma once
#include <limits>
#include <map>
#include <string>
#include <cassert>
#include "graph.h"

namespace pf {
class GraphBuilder {
  Graph& graph_;
public:
  explicit GraphBuilder(Graph& graph) : graph_{graph} {}

  void Link(NodeId from, NodeId to, CostType cost) {
    auto& nodes = graph_.nodes_;
    assert(nodes.find(from) != nodes.end() &&
           nodes.find(to) != nodes.end());
    graph_.adjacencies_.emplace(from, std::make_pair(to, pf::EdgeProperties{cost}));
  };
  void Node(NodeId id, std::string name="") {
    auto& nodes = graph_.nodes_;
    assert(nodes.find(id) == nodes.end());
    nodes.emplace(id, pf::NodeProperties{name});
  }
};

}  // namespace pf