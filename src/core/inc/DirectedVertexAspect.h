#pragma once

#include "AdjacencyListVertex.h"


namespace graphpp
{
template <class T>
class DirectedVertexAspect : public T, public IVertex
{
public:
    typedef AdjacencyListVertex::Degree Degree;
    typedef AdjacencyListVertex::VertexId VertexId;
    typedef AdjacencyListVertex::VertexContainer VertexContainer;
    typedef AdjacencyListVertex::VerticesConstIterator VerticesConstIterator;
    typedef AdjacencyListVertex::VerticesIterator VerticesIterator;
    typedef std::list<VertexId> NeighborsId;
    typedef CAutonomousIterator<NeighborsId> IdsIterator;

    DirectedVertexAspect(VertexId id) : T(id), vertexId(id) {}

    void addEdge(DirectedVertexAspect<T>* other)
    {
        T::template addEdge<DirectedVertexAspect<T>>(other);
        insert_into(outNeighbors, other);
        outIds.push_back(other->getVertexId());
        other->addIncomingEdge(this);
    }

    void addIncomingEdge(DirectedVertexAspect<T>* other)
    {
        insert_into(inNeighbors, other);
        inIds.push_back(other->getVertexId());

    }

    void removeEdge(DirectedVertexAspect<T>* v)
    {
        T::template removeEdge<DirectedVertexAspect<T>>(v);
        AdjacencyListVertex* other = static_cast<AdjacencyListVertex*>(v);
        remove_first_from(outNeighbors, v);
        v->removeIncomingEdge(this);
    }

    void removeIncomingEdge(DirectedVertexAspect<T>* v)
    {
        remove_first_from(inNeighbors, v);
    }

    Degree inDegree() const
    {
        return inNeighbors.size();
    }

    Degree outDegree() const
    {
        return outNeighbors.size();
    }

    Degree inOutDegree() const
    {
        return inDegree() + outDegree();
    }

    VerticesConstIterator inNeighborsConstIterator() const
    {
        return VerticesConstIterator(inNeighbors);
    }

    VerticesConstIterator outNeighborsConstIterator() const
    {
        return VerticesConstIterator(outNeighbors);
    }

    VerticesIterator inNeighborsIterator()
    {
        return VerticesIterator(inNeighbors);
    }

    VerticesIterator outNeighborsIterator()
    {
        return VerticesIterator(outNeighbors);
    }

    IdsIterator getInNeighborsIds() const
    {
        IdsIterator iter(inIds);
        return iter;
    }

    IdsIterator getOutNeighborsIds() const
    {
        IdsIterator iter(outIds);
        return iter;
    }

    IdsIterator getNeighborsIdsConstIterator(ShellIndexType type)
    {
        if (type == ShellIndexTypeInDegree) {
            return getInNeighborsIds();
        } else {
            return getOutNeighborsIds();
        }
    }

    double getDegree(ShellIndexType type)
    {
        if (type == ShellIndexTypeInDegree) {
            return inNeighbors.size();
        } else {
            return outNeighbors.size();
        }
    }

    VertexId getVertexId() const
    {
        return vertexId;
    }

private:
    VertexContainer inNeighbors;
    VertexContainer outNeighbors;
    NeighborsId inIds;
    NeighborsId outIds;
    VertexId vertexId;

};
}  // namespace graphpp
