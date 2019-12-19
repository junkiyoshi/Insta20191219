#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	ofxAssimpModelLoader model_loader;
	model_loader.loadModel("fuji3.stl");
	this->mesh = model_loader.getMesh(0);

	for (auto& vertex : this->mesh.getVertices()) {

		vertex -= glm::vec3(75, 0, 75);
		auto value = ofMap(vertex.y, 80, 0, 255, 0);
		this->mesh.addColor(ofColor(value));
	}

	ofSetSmoothLighting(true);
	pointLight.setDiffuseColor(ofFloatColor(.85, .85, .85));
	pointLight.setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));
	pointLight.setPosition(-200, 200, 200);
	pointLight.enable();
}

//--------------------------------------------------------------
void ofApp::update(){

	this->draw_mesh = this->mesh;
	for (auto& vertex : this->draw_mesh.getVertices()) {

		if (vertex.y > 0) {

			int param = 0;
			auto noise_value = ofNoise(vertex.x * 0.01, vertex.z * 0.01, ofGetFrameNum() * 0.035);
			if (noise_value > 0.5) {

				param = ofMap(noise_value, 0.5, 1, 0, 30);
				param = (param / 5) * 5;
			}
			vertex += glm::vec3(0, param, 0);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	this->cam.begin();

	this->draw_mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
