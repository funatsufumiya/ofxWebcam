#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofLogToConsole();

	webcam.setup(w, h, device_id, webcam_fps);
}

//--------------------------------------------------------------
void ofApp::update(){
	webcam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	webcam.draw(0, 0);

	ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate(), 2, 0, '\0'), 20, 20);
	ofDrawBitmapStringHighlight("Webcam FPS: " + ofToString(webcam.getFps(), 2, 0, '\0'), 20, 40);
	ofDrawBitmapStringHighlight("Webcam size: " +
		ofToString(webcam.getWidth(), 0, 0, '\0')
		+ " x " +
		ofToString(webcam.getHeight(), 0, 0, '\0')
	, 20, 60);
}

//--------------------------------------------------------------
void ofApp::exit(){
	#ifdef USE_CV
	ofLog() << "Gracefully exitting...";
	if(th != nullptr){
		th->stopThread();
		th->waitForThread();
	}
	#endif // USE_CV
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_ESC){
		ofExit();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
