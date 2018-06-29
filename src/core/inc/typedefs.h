// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#pragma once

#include "AdjacencyListGraph.h"
#include "DirectedGraphAspect.h"
#include "DirectedVertexAspect.h"
#include "WeightedGraphAspect.h"
#include "WeightedVertexAspect.h"
#include "AdjacencyListVertex.h"
#include "SimpleVertexAspect.h"

typedef graphpp::AdjacencyListVertex Vertex;
typedef graphpp::AdjacencyListGraph<Vertex> Graph;
typedef graphpp::SimpleVertexAspect<Vertex> SimpleVertex;
typedef graphpp::AdjacencyListGraph<SimpleVertex> SimpleGraph;
typedef graphpp::WeightedVertexAspect<Vertex> WeightedVertex;
typedef graphpp::WeightedGraphAspect<WeightedVertex, graphpp::AdjacencyListGraph<WeightedVertex>>
    WeightedGraph;
typedef graphpp::DirectedVertexAspect<Vertex> DirectedVertex;
typedef graphpp::DirectedGraphAspect<DirectedVertex, graphpp::AdjacencyListGraph<DirectedVertex>>
    DirectedGraph;

