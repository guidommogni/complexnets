//
// Created by Guido Mogni on 6/29/18.
//

#ifndef COMPLEXNETS_SIMPLEVERTEX_H
#define COMPLEXNETS_SIMPLEVERTEX_H

#include "AdjacencyListVertex.h"


namespace graphpp
{
    template <class T>
    class SimpleVertexAspect : public T , public IVertex {

        using VertexContainer = std::vector<AdjacencyListVertex*>;
        using VerticesConstIterator = CAutonomousIterator<VertexContainer>;
        using VerticesIterator = AutonomousIterator<VertexContainer>;

        SimpleVertexAspect(VertexId id) : vertexId(id) {}

        void addEdge(T* v)
        {
            AdjacencyListVertex* other = static_cast<AdjacencyListVertex*>(v);
            insert_into(neighbors, other);
            ids.push_back(other->getVertexId());
        }

        IdsIterator getNeighborsIdsConstIterator(ShellIndexType type)
        {
            IdsIterator iter(ids);
            return iter;
        }

        VerticesIterator neighborsIterator()
        {
            return VerticesIterator(neighbors);
        }

        double getDegree(ShellIndexType type)
        {
            return (double) neighbors.size();
        }

        VertexId getVertexId() const
        {
            return vertexId;
        }

    private:
        VertexContainer neighbors;
        VertexId vertexId;
        NeighborsId ids;
    };

}
#endif //COMPLEXNETS_SIMPLEVERTEX_H
