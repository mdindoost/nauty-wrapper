#include <cassert>
#include "nauty_wrapper.hpp"

int main() {
    nauty_wrap::Graph g1(3);  // Changed from nauty::Graph to nauty_wrap::Graph
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    
    nauty_wrap::Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    
    assert(g1.isomorphicTo(g2));
    
    return 0;
}