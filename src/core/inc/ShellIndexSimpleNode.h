#pragma once

//PlainNode is a node for an undirected and unweighted graph
namespace graphpp
{
    class SimpleNode : public INode {

    public:

        SimpleNode(IVertex *v, ShellIndexType type){
            vertex = v;
            shellIndexType = type;
            currentDegree = (int)(v->getDegree(type));
        }

        void markAsRemove() {
            currentDegree = 0;
        }

        int getDegree() {
            return currentDegree;
        };

        int decreaseDegree() {
            currentDegree--;
            return currentDegree;
        };

    private:
        int currentDegree;
    };

}  // namespace graphpp
