//
// Created by Guido Mogni on 6/29/18.
//

#ifndef COMPLEXNETS_SIMPLEGRAPHASPECT_H
#define COMPLEXNETS_SIMPLEGRAPHASPECT_H

#include "typedefs.h"

namespace graphpp
{
    template <class SimpleVertexAspect, class T>
    class SimpleGraphAspect : public T
    {
        SimpleGraphAspect(const bool isMultigraph = false, const bool isDigraph = false) : T(isDigraph, isMultigraph){};

    };
}


#endif //COMPLEXNETS_SIMPLEGRAPHASPECT_H
