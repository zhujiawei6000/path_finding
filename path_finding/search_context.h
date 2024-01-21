
#include "graph.h"
#include <vector>
#include <set>
#include <queue>
namespace pf {

struct Transition {
    NodeId curr_node;
    NodeId prev_node;
    CostType cost;
    bool operator<(const Transition& rhs) const {
        return cost < rhs.cost;
    }
    bool operator>(const Transition& rhs) const {
        return cost > rhs.cost;
    }
};

class SearchContext {
    NodeId goal_;
    std::map<NodeId, NodeId> visited_;
    std::priority_queue<Transition, std::vector<Transition>, std::greater<Transition>> transitions_;
public:
    void Reset(NodeId s, NodeId e) {
        goal_ = e;
        visited_.clear();
        while (!transitions_.empty()) transitions_.pop();
        //  Mark the starting vertex with a distance of zero. Designate this vertex as current.
        Enqueue(s, s, 0);
    }
    void MarkVisited(NodeId from, NodeId to) {
        visited_.emplace(to, from);
    }
    NodeId Predecessor(NodeId n) const {
        if (auto find = visited_.find(n); find == end(visited_)) {
            return n;
        } else {
            return find->second;
        }
    }
    void Enqueue(NodeId curr, NodeId prev, CostType cost) {
        transitions_.emplace(curr, prev, cost);
    }
    bool IsTerminal(NodeId n) const noexcept {
        return n == goal_;
    }
    Transition Dequeue() {
        auto t = transitions_.top();
        transitions_.pop();
        return t;
    }
    bool QueueIsNotEmpty() const noexcept {
        return !transitions_.empty();
    }
    bool IsVisited(NodeId n) const noexcept {
        return visited_.find(n) != visited_.end(); 
    }
};

}  // namespace pf