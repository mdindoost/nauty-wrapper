#ifndef NAUTY_WRAPPER_HPP
#define NAUTY_WRAPPER_HPP

#include <vector>
#include <cstdint>

namespace nauty {

class Graph {
public:
    Graph(size_t n);
    void addEdge(size_t from, size_t to);
    void removeEdge(size_t from, size_t to);
    bool isomorphicTo(const Graph& other);
    std::vector<std::vector<size_t>> getAutomorphisms();

private:
    size_t n_;
    std::vector<std::vector<bool>> adj_matrix_;
};

} // namespace nauty

#endif // NAUTY_WRAPPER_HPP