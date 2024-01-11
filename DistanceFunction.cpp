#include "DistanceFunction.h"
#include "DataPoint.h"
#include <cmath>


float DistanceFunction::ManhattanDistance(DataPoint* dpA, DataPoint* dpB) {
    if ((dpA == NULL) || (dpB == NULL)) return INFINITY;
    if ( dpA->getNumberOfAttributes() != dpB->getNumberOfAttributes()) 
    return INFINITY;

    float dist = 0;
    for (int i = 0; i < dpA->getNumberOfAttributes(); i++) 
        dist = dist + fabs(dpA->getAttributes()[i] - dpB->getAttributes()[i]);
    return dist;
}
float DistanceFunction::ChebyshevDistance(DataPoint* dpA, DataPoint* dpB) {
    if (dpA == NULL || dpB == NULL || dpA->getNumberOfAttributes() != dpB->getNumberOfAttributes()) 
    return INFINITY;

    float diff = 0; 
    for (int i = 0; i < dpA->getNumberOfAttributes(); i++) {
        float absDiff = fabs(dpA->getAttributes()[i] - dpB->getAttributes()[i]);
        if (absDiff > diff) {
            diff = absDiff;
        } 
    }
    return diff;
}
float DistanceFunction::EuclideanDistance(DataPoint* dpA, DataPoint* dpB) {
    if (dpA == NULL || dpB == NULL || dpA->getNumberOfAttributes() != dpB->getNumberOfAttributes()) 
    return INFINITY;

    float dist = 0;
    for (int i = 0; i < dpA->getNumberOfAttributes(); i++) 
        dist = dist + (float) pow(dpA->getAttributes()[i] - dpB->getAttributes()[i], 2.0f);
    dist = (float)sqrt(dist);
    return dist;
}

