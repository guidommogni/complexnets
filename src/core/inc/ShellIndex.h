#pragma once

#include "IShellIndex.h"
#include "IShellIndexNode.h"
#include "ShellIndexSimpleNode.h"
#include "IVertex.h"
#include "typedefs.h"
#include "ShellIndexDirectedNode.h"
#include "ShellIndexWeightedNode.h"

namespace graphpp {

    template<class Graph>
    class ShellIndex : public IShellIndex<Graph> {
    public:
        typedef typename IShellIndex<Graph>::ShellIndexContainer ShellIndexContainer;
        typedef typename IShellIndex<Graph>::ShellIndexIterator ShellIndexIterator;

        ShellIndex(Graph &g, ShellIndexType type) {
            currentType = type;
            totalVertexes = initMap(g);
            initMultimapSet(g);
            calculateShellIndex();
            currentType = type;
        }

        virtual ShellIndexIterator iterator() {
            return ShellIndexIterator(shellIndex);
        }

    private:
        INode *getNextNode() {
            for (int i = 0; i < totalVertexes; i++) {
                if (!nodesByCurrentDegree[i].empty()) {
                    return nodesByCurrentDegree[i].front();
                }
            }
            return nullptr;
        }

        void calculateShellIndex() {
            int k = 0;
            // While there are remaining vertices in the graph
            // Select the vertex with the lowest current degree
            while (getNextNode() != nullptr) {
                INode *nextVertex = getNextNode();
                IVertex *v = nextVertex->vertex;
                int degree = nextVertex->getDegree();

                // If the degree is higher than k, then we have a new higher k-core
                // If lower, then it belongs to the actual k-core
                if (degree > k) {
                    k = degree;
                }
                // Setting the coreness as the current k.
                shellIndex[v->getVertexId()] = k;
                // Will mark it as removed from the structure, since the coreness is already calculated
                nodesByVertexId[v->getVertexId()]->markAsRemove();
                nodesByCurrentDegree[degree].remove(nextVertex);

                IVertex::IdsIterator neighborsIt = v->getNeighborsIdsConstIterator(currentType);
                // Iterate through each of it's neighbors to reduce their degree by 1, since v was
                // removed.
                while (!neighborsIt.end()) {
                    // Get the vertex node to be able to lower it one level in the structure
                    INode *neighNode = nodesByVertexId[*neighborsIt];

                    if (neighNode->getDegree() > 0) {
                        // Remove it from the current level
                        nodesByCurrentDegree[neighNode->getDegree()].remove(neighNode);
                        neighNode->decreaseDegree();

                        if (neighNode->getDegree() > 0) {
                            // Re add it to a lower level if it still has a valid degree
                            nodesByCurrentDegree[neighNode->getDegree()].push_back(neighNode);
                        } else {
                            // Remove it and set coreness if the degree dropped to 0
                            shellIndex[neighNode->vertex->getVertexId()] = k;
                        }
                    }
                    ++neighborsIt;
                }
            }
        }

        int initMap(Graph &g) {
            VerticesConstIterator it = g.verticesConstIterator();
            int total = 0;

            // initialize all elements in zero
            while (!it.end()) {
                Vertex *v = *it;
                shellIndex.insert(
                        std::pair<typename IVertex::VertexId, unsigned int>(v->getVertexId(), 0));
                ++it;
                total++;
            }
            return total;
        }

        void initMultimapSet(Graph &g) {
            VerticesConstIterator it = g.verticesConstIterator();
            nodesByVertexId = new INode *[totalVertexes + 1];  // will not use index 0
            nodesByCurrentDegree =
                    new std::list<INode *>[totalVertexes];  // 0 won't exist, still max degree possible is n-1

            // initialize all elements using the vertex id and the vertex degree
            while (!it.end()) {
                Vertex *v = *it;
                INode *newNode = getNodeFromType(v, currentType);
                nodesByVertexId[v->getVertexId()] = newNode;
                nodesByCurrentDegree[newNode->getDegree()].push_back(newNode);
                ++it;
            }
        }

        INode* getNodeFromType(Vertex *v, ShellIndexType type){
            switch (type){
                case ShellIndexTypeSimple:
                    return new SimpleNode(v, type);
                case ShellIndexTypeInDegree:
                case ShellIndexTypeOutDegree:
                    return new DirectedNode(v, type);
                case ShellIndexTypeWeightedEqualPopulation:
                case ShellIndexTypeWeightedEqualStrength:
                    return new WeightedNode(v, type);
            }
        }

        typedef typename Graph::VerticesConstIterator VerticesConstIterator;
        typedef typename Vertex::VerticesConstIterator NeighbourConstIterator;

        // This container will be set with the coreness of each vertex when found.
        ShellIndexContainer shellIndex;

        // This structure represents an array of node pointers.
        // This nodes are the different node-vertexes in the main structure
        // The index of the array represents the id of the node.
        // Used to get the node structure in O(1), to allow it to be moved to another list.
        INode **nodesByVertexId;
        // This is the main structure, contains an array of linked lists.
        // The index of the array represents the current degree of the vertexes stored on that list.
        // The lists are doubly-linked lists to allow a node representation to be easily removed.
        std::list<INode *> *nodesByCurrentDegree;
        int totalVertexes;
        ShellIndexType currentType;
    };
}  // namespace graphpp