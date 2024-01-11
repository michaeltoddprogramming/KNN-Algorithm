#include "Algorithm.h"
#include "DataPoint.h"
#include "DistanceFunction.h"
#include <fstream>

Algorithm::Algorithm(std::string textfile) {
    this->k = -1;
    this->centroids = NULL; 

    std::string text;
    std::fstream File(textfile.c_str());

    numberOfDataPoints = 0;
    while (getline(File, text)) {
        if (text == "") continue;

        while (text.find(')') != std::string::npos) {
            text.erase(0, text.find(')') + 1);
            numberOfDataPoints++;
        }
    }
    dataPoints = new DataPoint*[numberOfDataPoints];

    File.clear();
    File.seekg(0);

    int i = 0;
    while (getline(File, text)) {
        if (text == "") continue;

        while (text.find(')') != std::string::npos) {
            std::string dataPointString = text.substr(0, text.find(')') + 1);
            dataPoints[i] = new DataPoint(dataPointString);
            text.erase(0, text.find(')') + 1);

            i++;
        }
    }
    File.close();
}

Algorithm::Algorithm(DataPoint** dps, int numberOfDataPoints) {
    k = -1;
    centroids = NULL;
    if (dps != NULL && numberOfDataPoints >= 0) {
        this->numberOfDataPoints = numberOfDataPoints;
        dataPoints = new DataPoint*[numberOfDataPoints];
        for (int i = 0; i < numberOfDataPoints; i++) {
            dataPoints[i] = new DataPoint(dps[i]);
        }
    } else {
        dataPoints = new DataPoint*[0];
        this->numberOfDataPoints = 0;    
    }
}

Algorithm::Algorithm(Algorithm* other) {
    k = -1;
    centroids = NULL;
    if (other != NULL) {
        numberOfDataPoints = other->numberOfDataPoints;  
            dataPoints = new DataPoint*[numberOfDataPoints];
            
            for (int i = 0; i < numberOfDataPoints; i++) {
                if(other->dataPoints[i] != NULL)
                dataPoints[i] = new DataPoint(other->dataPoints[i]);
                else {
                    dataPoints[i] = NULL;
                }
            }
    } else {
        dataPoints = new DataPoint*[0];
        numberOfDataPoints = 0;
    }
}

Algorithm::~Algorithm() {
    if (centroids != NULL) {
        for (int i = 0; i < k; i++) {
            if (centroids[i] != NULL) {
                delete centroids[i];
            }
        }
        delete[] centroids;
        centroids = NULL;
    }

        for (int i = 0; i < numberOfDataPoints; i++) {
            delete dataPoints[i];
        }
        delete[] dataPoints;
        dataPoints = NULL;
}

DataPoint** Algorithm::getDataPoints() const {
    return dataPoints;
}

GroupInfo* Algorithm::formGroup(int distanceMetric) {
    GroupInfo* newGroup = new GroupInfo;
    float dist;
    float minDist;
    int* dpsindex = new int[numberOfDataPoints];

    newGroup->sizes = new int[k];
    newGroup->groups = new DataPoint**[k];

    for (int i = 0; i < k; i++) {
        newGroup->sizes[i] = 0;
    }

    for (int i = 0; i < numberOfDataPoints; i++) {
        minDist = INFINITY;
        int minIndex = 0;
        for (int j = 0; j < k; j++) {
            switch (distanceMetric) {
                case 0: dist = DistanceFunction::ManhattanDistance(this->centroids[j], this->dataPoints[i]); break;
                case 1: dist = DistanceFunction::EuclideanDistance(this->centroids[j], this->dataPoints[i]); break;
                case 2: dist = DistanceFunction::ChebyshevDistance(this->centroids[j], this->dataPoints[i]); break;
                default: dist = INFINITY;
            }      
            if (dist < minDist) {
                minDist = dist;
                minIndex = j;
            }
        }   
        newGroup->sizes[minIndex]++;
        dpsindex[i] = minIndex;
    }
    for (int i = 0; i < k; i++) {
        newGroup->groups[i] = new DataPoint*[newGroup->sizes[i]];

        for (int j = 0; j < newGroup->sizes[i]; j++) {
            newGroup->groups[i][j] = NULL;
        }
    }
    for (int i = 0; i < numberOfDataPoints; i++) {
        int centroidIndex = dpsindex[i];
        
        for (int y = 0; y < newGroup->sizes[centroidIndex]; y++) {
            if (newGroup->groups[centroidIndex][y] == NULL) {
                newGroup->groups[centroidIndex][y] = dataPoints[i];
                break;
            }
        }
    }
    delete [] dpsindex;
    dpsindex = NULL;
    return newGroup;
}

DataPoint** Algorithm::getCentroids() const {
    return centroids;
}

DataPoint** Algorithm::singleRun(int distanceMetric) {
    if ((centroids == NULL) || (k <= 0)) {
        return NULL;
    }
    GroupInfo* singleGroup = formGroup(distanceMetric);
    
    if (singleGroup == NULL) {
        return NULL;
    }

    for (int i = 0; i < k; i++) {
        if (singleGroup->sizes != NULL)
        if (singleGroup->sizes[i] > 0) {
            if (singleGroup->groups[i] != NULL) {
                DataPoint* newCent = averagePositionOfGroup(singleGroup->groups[i], singleGroup->sizes[i]);
                if (newCent != NULL) {
                    if (centroids[i] != NULL)
                    delete centroids[i];
                    centroids[i] = newCent;
                } 

            }
        }
        if (singleGroup->groups[i] != NULL)
            delete [] singleGroup->groups[i]; // ---------------------inside if
    }
    if (singleGroup->sizes != NULL)
        delete [] singleGroup->sizes;
    if (singleGroup->groups != NULL)
        delete [] singleGroup->groups;

    delete singleGroup;
    singleGroup = NULL;
    return centroids;
}

DataPoint*** Algorithm::fullRun(int distanceMetric, int numberOfIterations) {
    if ((centroids == NULL) || (numberOfIterations <= 0)) {
        return NULL;
    }
    DataPoint*** centEvolution = new DataPoint**[numberOfIterations];
    for (int i = 0; i < numberOfIterations; i++) {
        centEvolution[i] = new DataPoint*[k];

        DataPoint** tempCent = singleRun(distanceMetric);

        if (tempCent != NULL) {
        for (int j = 0; j < k; j++) {
        if (tempCent[i] != NULL)
            centEvolution[i][j] = new DataPoint(tempCent[j]);
        else 
            centEvolution[i][j] = NULL;
        }

        } else return NULL;

    }
    return centEvolution;
}

int Algorithm::getNumDataPoints() const {
    return numberOfDataPoints;
}

DataPoint** Algorithm::setCentroids(float** rawCentroidPositions, int k, int numAttributes) {
    if(k <= 0 || rawCentroidPositions == NULL) {
    return NULL;
    }
    DataPoint** oldCents = centroids;
    this->k = k;
    centroids = new DataPoint*[k];
    
    for (int i = 0; i < k; i++) {
        centroids[i] = new DataPoint(rawCentroidPositions[i], numAttributes);
    }
    return oldCents;
}

DataPoint* Algorithm::averagePositionOfGroup(DataPoint** group, int size) const {
    if ((group == NULL) || (size <= 0) || (centroids == NULL)) 
        return NULL;

  
    int dim = group[0]->getNumberOfAttributes();

    float* avg = new float[dim];
    for (int i = 0; i < dim; i++) {
        avg[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < dim; j++) {
            if (group[i] != NULL)
                avg[j] += group[i]->getAttributes()[j];
        }
    }
    for (int i = 0; i < dim; i++) {
        avg[i] = avg[i] / size;
    }

    DataPoint* newCent = new DataPoint(avg, dim);

    delete[] avg;

    return newCent;
    
}