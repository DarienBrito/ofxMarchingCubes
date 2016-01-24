#pragma once

#include "ofMain.h"

#include <functional>

class ofxMarchingCubes {
public:
    ofxMarchingCubes(int dataSetSize, float targetValue, std::function<float (float, float, float)> sample);

    void  generateMesh(ofMesh &mesh);

private:
    float getOffset(float a, float b, float desired);
    void getNormal(ofVec3f &normal, float x, float y, float z);
    void marchCube(float x, float y, float z, float scale, ofMesh &mesh);

    const int dataSetSize;
    const float stepSize;
    const float targetValue;

    std::function<float (float, float, float)> sample;
};
