#include <algorithm>

#include "graph.h"
#include "search_context.h"

namespace pf {

std::vector<NodeId> Dijkstra(const Graph& graph, NodeId start,
                                        NodeId end) {
  SearchContext context;
  // Mark the ending vertex with a distance of zero.
  context.Reset(start, end);
  bool solved = false;
  while (context.QueueIsNotEmpty()) {
    // Designate this vertex as current.
    auto [curr_node, prev_node, cost] = context.Dequeue();
    if (context.IsVisited(curr_node)) {
        continue;
    }
    context.MarkVisited(prev_node, curr_node);
    if (context.IsTerminal(curr_node)) {
      solved = true;
      break;
    }
    graph.ForEachEdge(curr_node, [&context, curr_node, cost](
                                     NodeId nid, const EdgeProperties& props) {
      // Don’t record this distance if it is longer than a previously recorded
      // distance.
      if (!context.IsVisited(nid)) {
        context.Enqueue(nid,               // curr node
                        curr_node,         // prev
                        props.cost + cost  // cost
        );
      }
    });
  }

  
  std::vector<NodeId> result;
  if (solved) {
    result.push_back(end);
    auto prev = context.Predecessor(result.back());
    while (prev != result.back()) {
        result.push_back(prev);
        prev = context.Predecessor(result.back());
    }
  }
  return result;
}

}  // namespace pf