#include "Triangulate/triangulate.h"

#include "Triangulate/mesh.h"


void makeMonotone(const Face* f, Mesh& m)
{
    EdgeQueue edge_queue(compare_edge_queue);
    edge_queue.push(f->edge);
    HalfEdge* e = f->edge->next;
    while (e != f->edge)
    {
        edge_queue.push(e);
        e = e->next;
    }
    
    EdgeSet edge_set(compare_edge_set);
    while (!edge_queue.empty())
    {
        handleVertex(edge_queue.top(), edge_set, m);
        edge_queue.pop();
    }
}

void handleVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m)
{
    double t = angle(*e->next->origin - *e->origin,
            *e->prev->origin - *e->origin);

    if (below(*e->prev->origin, *e->origin)
            && below(*e->next->origin, *e->origin))
    {
        if (t < 3.1415)
        {
            handleStartVertex(e, edge_set);
        }
        else
        {
            handleSplitVertex(e, edge_set, m);
        }
    }
    else if (above(*e->prev->origin, *e->origin)
            && above(*e->next->origin, *e->origin))
    {
        if (t > 3.1415)
        {
            e->origin->merge = true;
            handleMergeVertex(e, edge_set, m);
        }
        else
        {
            handleEndVertex(e, edge_set, m);
        }
    }
    else
    {
        handleRegularVertex(e, edge_set, m);
    }
}

void handleStartVertex(HalfEdge* e, EdgeSet& edge_set)
{
    edge_set.insert(e);
    e->helper = e->origin;
}

void handleEndVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m)
{
    if (e->prev->helper->merge)
    {
        m.addEdge(e->origin, e->prev->helper);
    }
    edge_set.erase(e->prev);
}

void handleSplitVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m)
{
    HalfEdge* neighbor = e->leftNeighbor(edge_set.begin(), edge_set.end());
    m.addEdge(e->origin, neighbor->helper);
    neighbor->helper = e->origin;
    edge_set.insert(e);
    e->helper = e->origin;
}

void handleMergeVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m)
{
    if (e->prev->helper->merge)
    {
        m.addEdge(e->origin, e->prev->helper);
    }
    edge_set.erase(e->prev);

    HalfEdge* neighbor = e->leftNeighbor(edge_set.begin(), edge_set.end());
    if (neighbor->helper->merge)
    {
        m.addEdge(e->origin, neighbor->helper);
    }
    neighbor->helper = e->origin;
}

void handleRegularVertex(HalfEdge* e, EdgeSet& edge_set, Mesh& m)
{
    if (e->left())
    {
        if (e->prev->helper->merge)
        {
            m.addEdge(e->origin, e->prev->helper);
        }
        edge_set.erase(e->prev);
        edge_set.insert(e);
        e->helper = e->origin;
    }
    else
    {
        HalfEdge* neighbor = e->leftNeighbor(edge_set.begin(),
                edge_set.end());
        if (neighbor->helper->merge)
        {
            m.addEdge(e->origin, neighbor->helper);
        }
        neighbor->helper = e->origin;
    }
}

