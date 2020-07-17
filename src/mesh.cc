#include "Triangulate/mesh.h"

#include <algorithm>
#include <iterator>

std::vector<HalfEdge*> Mesh::findEdges(const Vertex* v) const
{
    std::vector<HalfEdge*> v_edges; 
    if (v->edge)
    {
        v_edges.push_back(v->edge);
        HalfEdge* e = v->edge->twin->next;
        while (e != v->edge)
        {
            v_edges.push_back(e);
            e = e->twin->next;
        }
    }
    return v_edges;
}

void Mesh::mergeEdge(Vertex* v, HalfEdge* e) const
{
    std::vector<HalfEdge*> v_edges = findEdges(v);
    v_edges.push_back(e);
    if (v_edges.size() > 1)
    {
        sortEdgesCW(v_edges, v);
        for (int i = 0; i < v_edges.size() - 1; i++)
        {
            v_edges[i]->twin->next = v_edges[i + 1];
            v_edges[i + 1]->prev = v_edges[i]->twin;
        }
        v_edges[v_edges.size() - 1]->twin->next = v_edges[0];
        v_edges[0]->prev = v_edges[v_edges.size() - 1]->twin;
    }
    else
    {
        e->twin->next = e;
        e->prev = e->twin;
    }
    v->edge = v_edges[0];
}

Vertex* Mesh::addVertex(int x, int y)
{
    Vertex v(x, y);

    // check if vertex already exists
    std::list<Vertex>::iterator vIter =
        std::find(vertices.begin(), vertices.end(), v);
    if (vIter != vertices.end()) return &(*vIter);

    // add new vertex
    vertices.push_back(v);
    return &vertices.back();
}

HalfEdge* Mesh::addEdge(int x1, int y1, int x2, int y2)
{
    Vertex* v1 = addVertex(x1, y1);
    Vertex* v2 = addVertex(x2, y2);

    // don't allow single edge cycles
    if (*v1 == *v2)
    {
        return NULL;
    }

    HalfEdge e1;
    e1.origin = v1;

    HalfEdge e2;
    e2.origin = v2;

    e1.twin = &e2;
    e2.twin = &e1;

    // check if edge already exists
    std::list<HalfEdge>::iterator eIter =
        std::find(edges.begin(), edges.end(), e1);
    if (eIter != edges.end()) return &(*eIter);

    // add new edge
    edges.push_back(e1);
    HalfEdge* ep1 = &edges.back();
    edges.push_back(e2);
    HalfEdge* ep2 = &edges.back();

    ep1->twin = ep2;
    ep2->twin = ep1;

    // adjust edge flow at affected vertices
    mergeEdge(v1, ep1);
    mergeEdge(v2, ep2);

    return ep1;
}

void Mesh::createFaces()
{
    for (HalfEdge& s : edges)
    {
        if (s.face) continue;
        if (!interior(&s)) continue;

        faces.push_back(Face());
        faces.back().edge = &s;
        s.face = &faces.back();
        HalfEdge* e = s.next;
        while (*e != s)
        {
            e->face = &faces.back();
            e = e->next;
        }
    }
}

