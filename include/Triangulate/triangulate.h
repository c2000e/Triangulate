#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include "Triangulate/mesh.h"

#include <queue>
#include <set>

auto compare_edge_queue = [](HalfEdge* a, HalfEdge* b)                    
{                                                                         
    return below(*a->origin, *b->origin);               
};
typedef std::priority_queue<HalfEdge*, std::vector<HalfEdge*>,            
    decltype(compare_edge_queue)> EdgeQueue;      

auto compare_edge_set = [](HalfEdge* a, HalfEdge* b)                      
{                                                                         
    return std::min(a->origin->x, a->twin->origin->x)
        < std::min(b->origin->x, b->twin->origin->x);
};                                                                        
typedef std::set<HalfEdge*, decltype(compare_edge_set)> EdgeSet;

void makeMonotone(const Face* f, Mesh& m);
void handleVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m);
void handleStartVertex(HalfEdge* e, EdgeSet& edge_set);
void handleEndVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m);
void handleSplitVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m);
void handleMergeVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m);
void handleRegularVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m);

#endif
