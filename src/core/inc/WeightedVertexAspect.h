#pragma once

#include "AdjacencyListVertex.h"


namespace graphpp
{
template <class T>
class WeightedVertexAspect : public T, public IVertex
{
public:
    // TODO: make these typedefs private
    typedef AdjacencyListVertex::VertexId VertexId;
    typedef double Weight;
    typedef std::map<VertexId, Weight> NeighborsWeights;
    typedef std::list<VertexId> NeighborsId;
    typedef CAutonomousIterator<NeighborsId> IdsIterator;
    typedef AutonomousIterator<NeighborsWeights> WeightsIterator;
    double distance;

    WeightedVertexAspect(VertexId id) : T(id), vertexId(id) {}

    void addEdge(WeightedVertexAspect<T>* other, Weight weight)
    {
        T::template addEdge<WeightedVertexAspect<T>>(other);
        weights.insert(std::pair<VertexId, Weight>(other->getVertexId(), weight));
        ids.push_back(other->getVertexId());
    }

    // TODO method should be const
    Weight edgeWeight(WeightedVertexAspect<T>* neighbour)
    {
        return weights[neighbour->getVertexId()];
    }

    WeightsIterator weightsIterator()
    {
        WeightsIterator iter(weights);
        return iter;
    }

    // TODO method should be const
    Weight strength()
    {
        WeightsIterator iter(weights);
        Weight str = 0.0;

        while (!iter.end())
        {
            str += iter->second;
            ++iter;
        }

        return str;
    }

    IdsIterator getNeighborsIdsConstIterator(ShellIndexType type)
    {
        IdsIterator iter(ids);
        return iter;
    }

    VertexId getVertexId() const
    {
        return vertexId;
    }

    double getDegree(ShellIndexType type)
    {
        return strength();
    }

private:
    NeighborsWeights weights;
    NeighborsId ids;
    VertexId vertexId;
};
}  // namespace graphpp
