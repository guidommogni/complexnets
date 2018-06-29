#pragma once

#include "IVertex.h"

namespace graphpp
{
    class INode {
    public:
        IVertex *vertex;
        ShellIndexType shellIndexType;

        // getDegree returns the current "bin" for the node to be inserted in, the current shell index
        virtual void markAsRemove()  = 0;
        virtual int getDegree()  = 0;
        virtual int decreaseDegree()  = 0;

        virtual ~INode() {}
    };
}; // namespace graphpp
