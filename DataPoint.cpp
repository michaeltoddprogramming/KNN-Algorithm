#include <iostream>
#include <string>
#include <sstream>
#include "DataPoint.h" 

DataPoint::DataPoint(std::string line) {
    std::string cleanedLine;
    std::stringstream ss(line);

    line = "";
    while (!ss.eof()) {
        ss >> cleanedLine;
        line += cleanedLine;
    }

    if (line == "" || line == "()") {
        this->numberOfAttributes = 0;
        this->attributes = new float[0];
        return;
    }
    line.erase(0, 1);
    std::string temp = line;
    int nummies = 1;
    while (temp.find(',') != std::string::npos) {
        temp.erase(0, temp.find(',') + 1);
        nummies++;
    }
    this->numberOfAttributes = nummies;
    this->attributes = new float[nummies];
    std::string num;
    int count = 0;
    while (line.find(',') != std::string::npos) {
        num = line.substr(0, line.find(','));
        std::stringstream ss(num);
        ss >> this->attributes[count];
        line.erase(0, line.find(',') + 1);
        count++;
    }
    num = line.substr(0, line.find(')'));

    std::stringstream ssClean(num);
    ssClean >> this->attributes[count];
}

DataPoint::DataPoint(DataPoint *other) { 
    if(other == NULL) {
        this->attributes = new float[0];
        this->numberOfAttributes = 0;
    } else {
        this->numberOfAttributes = other->numberOfAttributes;
        this->attributes = new float[other->numberOfAttributes];
        for(int i = 0; i < other->numberOfAttributes; i++) {
            this->attributes[i] = other->attributes[i];
        }
    }
}

DataPoint::DataPoint(float *attributes, int numberOfAttributes) {
    if(attributes == NULL || numberOfAttributes <= 0) {
        this->attributes = new float[0];
        this->numberOfAttributes = 0;
    } else {
        this->numberOfAttributes = numberOfAttributes;
        this->attributes = new float[numberOfAttributes];
        for (int i = 0; i < numberOfAttributes; i++) 
            this->attributes[i] = attributes[i];
    }

}

 DataPoint::~DataPoint() {
    delete [] attributes;
    attributes = NULL;
 }

DataPoint *DataPoint::clone() {
    DataPoint *clone = new DataPoint(this);
    return clone;
}

float *DataPoint::getAttributes() {
    return attributes;
}
int DataPoint::getNumberOfAttributes() {
    return numberOfAttributes;
}
