#include "ofApp.h"

ofApp::ofApp()
: move(true)
, marchingCubes(72, 48.0, [this] (float x, float y, float z) { return sample(x, y, z); }) {
}

// sample1 finds the distance of (x, y, z) from three moving points
float ofApp::sample(float x, float y, float z) {
    auto result = 0.0, dx = 0.0, dy = 0.0, dz = 0.0;

    dx = x - sourcePoint[0].x;
    dy = y - sourcePoint[0].y;
    dz = z - sourcePoint[0].z;
    result += 0.5/(dx*dx + dy*dy + dz*dz);

    dx = x - sourcePoint[1].x;
    dy = y - sourcePoint[1].y;
    dz = z - sourcePoint[1].z;
    result += 1.0/(dx*dx + dy*dy + dz*dz);

    dx = x - sourcePoint[2].x;
    dy = y - sourcePoint[2].y;
    dz = z - sourcePoint[2].z;
    result += 1.5/(dx*dx + dy*dy + dz*dz);

    return result;
}

// Generate a sample data set.  sample1(), sample2() and sample3() define three scalar fields whose
// values vary by the X,Y and Z coordinates and by the time value set by setTime()
void ofApp::setTime(float newTime) {
    for (int source = 0; source < 3; source++) {
        sourcePoint[source].x = 0.5;
        sourcePoint[source].y = 0.5;
        sourcePoint[source].z = 0.5;
    }

    const auto offset = 1.0 + (sinf(newTime)/1.6);
    sourcePoint[0].x *= offset;
    sourcePoint[1].y *= offset;
    sourcePoint[2].z *= offset;
}

void ofApp::setup() {
    ofSetVerticalSync(true);

    ofSetSmoothLighting(true);

    pointLight.setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 500.0);
    pointLight.setDiffuseColor(ofFloatColor(0.85, 0.85, 0.85));
    pointLight.setSpecularColor(ofFloatColor(1.0f, 1.0f, 1.0f));

    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255, 255));
}

void ofApp::update() {
    static auto time = 0.0f;
    static auto lastTime = ofGetElapsedTimef();
    const auto now = ofGetElapsedTimef();
    const auto timeDelta = now - lastTime;
    lastTime = now;
    time += timeDelta;
    setTime(time);
}

void ofApp::draw() {
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    marchingCubes.generateMesh(mesh);

    ofEnableDepthTest();

    ofEnableLighting();

    pointLight.enable();

    material.begin();

    cam.begin();

    ofScale(500, 500, 500);
    ofSetColor(0);
    ofTranslate(-.5, -.5, -.5);
    mesh.draw();
    ofTranslate(.5, .5, .5);

    cam.end();

    material.end();

    pointLight.disable();

    ofDisableLighting();

    ofDisableDepthTest();
}

void ofApp::keyPressed(int key) {
}

void ofApp::keyReleased(int key) {
}

void ofApp::mouseMoved(int x, int y) {
}

void ofApp::mouseDragged(int x, int y, int button) {
}

void ofApp::mousePressed(int x, int y, int button) {
}

void ofApp::mouseReleased(int x, int y, int button) {
}

void ofApp::mouseEntered(int x, int y) {
}

void ofApp::mouseExited(int x, int y) {
}

void ofApp::windowResized(int w, int h) {
}

void ofApp::gotMessage(ofMessage msg) {
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
}
