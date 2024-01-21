#pragma once
#include <limits>
#include <map>

namespace pf {
using NodeId = int;
struct NodeProperties {
  std::string name;
};
using CostType = int;
struct EdgeProperties {
  CostType cost;
};

static constexpr const CostType InfiniteCost =
    std::numeric_limits<CostType>::max();

using Edge = std::pair<NodeId, EdgeProperties>;

class Graph {
 private:
  friend class GraphBuilder;
  std::multimap<NodeId, Edge> adjacencies_;
  std::map<NodeId, NodeProperties> nodes_;

 public:
  template <typename EdgeVisitorT>
  void ForEachEdge(NodeId key, EdgeVisitorT&& visitor) const {
    auto range = adjacencies_.equal_range(key);
    std::for_each(range.first, range.second,
                  [visitor](const auto& parent_and_edge) mutable {
                    std::apply(visitor, parent_and_edge.second);
                  });
  }
  const NodeProperties& Node(NodeId nid) const { return nodes_.at(nid); }
};
}  // namespace pf