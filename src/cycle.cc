#include "Triangulate/cycle.h"

Cycle::Cycle() : parent(nullptr) {}

void Cycle::findParent(std::vector<Cycle>& cycles)
{
    Vertex* m = lowerLeftVertex();
    Vertex* v = nullptr;
    for (Cycle& c : cycles)
    {
        if (c == *this) continue;
        for (HalfEdge* e : c.edges)
        {
            if (e->origin->position.x < m->position.x)
            {
                if (!v || e->origin->position.x > v->position.x)
                {
                    m = e->origin;
                    this->parent = &c;
                }
            }
        }
    }
}

Cycle* Cycle::root()
{
    Cycle* r = parent;
    while (!r->isFace() && r->parent)
    {
        r = r->parent;
    }
    return r;
}

Vertex* Cycle::lowerLeftVertex() const
{
    return lowerLeftEdge()->origin;
}

HalfEdge* Cycle::lowerLeftEdge() const
{
   HalfEdge* e = edges[0];
   HalfEdge* m = e; 
   e = e->next;
   for (int i = 1; i < edges.size(); i++)
   {
       if (e->origin->position.x < m->origin->position.x)
       {
           m = e;
       }
       else if (equal(e->origin->position.x, m->origin->position.x))
       {
           if (e->origin->position.y < m->origin->position.y)
           {
               m = e;
           }
       }
       e = e->next;
   }
   return m;
}

bool Cycle::isFace() const
{
    HalfEdge* e = lowerLeftEdge();
    if (angleBetween(e->prev->origin->position - e->origin->position,
            e->next->origin->position - e->origin->position) > PI)
        return true;
    return false;
}

bool operator==(const Cycle& a, const Cycle& b)
{
    if (a.edges.size() != b.edges.size()) return false;
    
    HalfEdge* a_m = a.lowerLeftEdge();
    HalfEdge* b_m = b.lowerLeftEdge();

    if (*a_m != *b_m) return false;

    HalfEdge* a_e = a_m->next;
    HalfEdge* b_e = b_m->next;

    while (a_e != a_m && b_e != b_m)
    {
        if (*a_e != *b_e) return false;
        a_e = a_e->next;
        b_e = b_e->next;
    }
    return true;
}
