#include "Algorithm.h"
#include "DataPoint.h"
#include "DistanceFunction.h"
#include <sstream>
#include <fstream>
#include <iostream>

void studentMain()
{
    Algorithm *a1 = new Algorithm("textfile_55555.txt");
    float **centroids = new float *[2];
    centroids[0] = new float[3];
    centroids[0][0] = 0.5f;
    centroids[0][1] = 4.5f;
    centroids[0][2] = 0;
    centroids[1] = new float[3];
    centroids[1][0] = 5;
    centroids[1][1] = 0.4f;
    centroids[1][2] = 1.5f;
    a1->setCentroids(centroids, 2, 3);
    DataPoint ***results = a1->fullRun(1, 20);
    if (results == NULL)
    {
        std::cout << "results == NULL" << std::endl;
    }
    else
    {
        for (int i = 0; i < 20; i++)
        {
            std::cout << "Generation: " << i << std::endl;
            if (results[i] == NULL)
            {
                std::cout << "results[" << i << "] == NULL" << std::endl;
            }
            else
            {
                for(int j=0; j < 2; j++){
                    std::cout << "Centroid: " << j << std::endl;
                    if(results[i][j] == NULL){
                        std::cout << "results[" << i << "][" << j << "] == NULL" << std::endl;
                    } else {
                        results[i][j]->printOut();
                        delete results[i][j];
                        results[i][j] = NULL;
                    }
                }
                delete[] results[i];
                results[i] = NULL;
            }
        }
        delete[] results;
        results = NULL;
    }
    for(int i=0; i < 2; i++){
        delete[] centroids[i];
        centroids[i] = NULL;
    }
    delete[] centroids;
    centroids = NULL;
    delete a1;
    a1 = NULL;

}

int main(int argc, char const* argv[]) {
    studentMain();

    DataPoint *Empty1 = new DataPoint("");
    DataPoint *Empty2 = new DataPoint("()");
    DataPoint *Testdp1 = new DataPoint("(5,1,9)");
    DataPoint *Testdp2 = new DataPoint("(7,8,8)");

    Algorithm* testAlgo = new Algorithm("textfile_55555.txt");
    Algorithm* testAlgo3 = new Algorithm(testAlgo);
    testAlgo->getNumDataPoints();
    testAlgo->getCentroids();
    testAlgo->getDataPoints();

    DataPoint** dpTestList = new DataPoint*[2];
    dpTestList[0] = Testdp1;
    dpTestList[1] = Testdp2;

    Algorithm *testAlgo2 = new Algorithm(dpTestList, 2);
    delete testAlgo2;
    delete testAlgo3;

    float** centTest = new float*[1];
    centTest[0] = new float[2];
    centTest[0][0] = 0.5f;
    centTest[0][1] = 4.5f;
    testAlgo->setCentroids(centTest, 1, 2);

    DataPoint*** TestAlgoEvolution = testAlgo->fullRun(1, 2);

    delete TestAlgoEvolution[0][0];
    delete [] TestAlgoEvolution[0];

    delete TestAlgoEvolution[1][0];
    delete [] TestAlgoEvolution[1];

    delete [] TestAlgoEvolution;

    delete testAlgo;

    delete[] centTest[0];
    delete[] centTest;
    centTest = NULL;
    
    
    DistanceFunction::ManhattanDistance(Testdp1, Testdp2);
    DistanceFunction::ManhattanDistance(Empty1, Empty2);
    DistanceFunction::ManhattanDistance(NULL, NULL);
    DistanceFunction::ChebyshevDistance(Testdp1, Testdp2);
    DistanceFunction::ChebyshevDistance(Empty1, Empty2);
    DistanceFunction::ChebyshevDistance(NULL, NULL);
    DistanceFunction::EuclideanDistance(Testdp1, Testdp2);
    DistanceFunction::EuclideanDistance(Empty1, Empty2);
    DistanceFunction::EuclideanDistance(NULL, NULL);

    delete Testdp1;
    delete Testdp2;
    delete Empty1;
    delete Empty2;

    delete [] dpTestList;

    
    return 0;
}
/*
Expected output can be found in studentExampleOutput.txt
*/