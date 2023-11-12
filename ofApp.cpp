#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofColor color;
	for (int i = 0; i < 3; i++) {

		auto noise_seed = ofRandom(1000);
		color.setHsb(ofMap(i, 0, 3, 0, 255), 150, 255);

		for (int x = -210; x <= 210; x += 3) {

			for (int y = -210; y <= 210; y += 3) {

				vector<glm::vec2> vertices;
				vertices.push_back(glm::vec2(x, y));
				for (int i = 0; i < 65; i++) {

					auto deg = ofMap(ofNoise(noise_seed, vertices.back().x * 0.004, vertices.back().y * 0.004, ofGetFrameNum() * 0.015), 0, 1, -360, 360);
					auto vertex = vertices.back() + glm::vec2(2 * cos(deg * DEG_TO_RAD), 2 * sin(deg * DEG_TO_RAD));
					vertices.push_back(vertex);
				}

				ofSetColor(color, 8);
				ofNoFill();

				ofBeginShape();
				ofVertices(vertices);
				ofEndShape();
			}
		}
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}