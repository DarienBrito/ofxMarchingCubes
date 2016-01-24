#pragma once

#include "ofMain.h"

#include <functional>

/** This class generates meshes using the a sample function.
 */
class ofxMarchingCubes {
public:
    /** Ctor
     *
     * \param gridSize the edge length of the square grid.
     * \param targetValue the iso surfance target value.
     * \param sample the sample function used to determine the iso surface value of a point in space.
     */
    ofxMarchingCubes(int gridSize, float targetValue, std::function<float (float, float, float)> sample);

    /** Add vertices and normals to the grid.
     *
     * \param mesh a reference to an ofMesh instance used to store the generated mesh data.
     */
    void generateMesh(ofMesh &mesh) const;

private:
    /** Finds the approximate point of intersection of the surface between two points with the values a and b.
     *
     * \param a the first value.
     * \param b the second value.
     * \param desired the desired value.
     *
     * \return the offset value.
     */
    float getOffset(float a, float b, float desired) const;

    /** Calculates the gradient of the scalar field at a point.
     *
     * \param normal reference to a normal.
     * \param x the x coordinate of the point.
     * \param y the y coordinate of the point.
     * \param z the z coordinate of the point.
     */
    void getNormal(ofVec3f &normal, float x, float y, float z) const;

    /** Performs the Marching Cubes algorithm on a single cube.
     *
     * \param x the x coordinate of the cube.
     * \param y the y coordinate of the cube.
     * \param z the z coordinate of the cube.
     * \param scale a scale factor.
     * \param mesh a reference to the ofMesh instance used to store the generated mesh.
     */
    void marchCube(float x, float y, float z, float scale, ofMesh &mesh) const;

    /** The edge length of the square grid.
     */
    const int gridSize;

    /** The size of a single step through the grid.
     */
    const float stepSize;

    /** The target value of the iso surface.
     */
    const float targetValue;

    /** The sample function used to calculate the iso surface of a point in the grid.
     */
    const std::function<float (float, float, float)> sample;
};
