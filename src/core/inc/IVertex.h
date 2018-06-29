//
// Created by Guido Mogni on 6/24/18.
//

#ifndef COMPLEXNETS_IVERTEX_H
#define COMPLEXNETS_IVERTEX_H

#pragma once

enum ShellIndexType {
    // For an graph not directed or weighted
            Simple,
    // For a directed graph, calculates the (k,0)-core for non empty shells
            InDegre,
    // For a directed graph, calculates the (0,l)-core for non empty shells
            OutDegre,
    // For a weighted graph, calculates the shell index binning by equal population (x axe)
            WeightedEqualPopulation,
    // For a weighted graph, calculates the shell index binning by equal population (y axe)
            WeightedEqualStrength
};

namespace graphpp {
    class IVertex {
    public:
        using VertexId = unsigned int;
        typedef std::list<VertexId> NeighborsId;
        typedef CAutonomousIterator<NeighborsId> IdsIterator;
    public:
        // Empty virtual destructor for proper cleanup
        virtual ~IVertex() {}
        virtual VertexId getVertexId() const = 0;
        virtual double getDegree(ShellIndexType type) = 0;
        virtual IdsIterator getNeighborsIdsConstIterator(ShellIndexType type) = 0;
    };
}

#endif //COMPLEXNETS_IVERTEX_H
