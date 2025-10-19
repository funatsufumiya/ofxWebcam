#include "ofApp.h"
#include "ofxAsync.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofLogToConsole();

	#ifdef USE_CV

	cap.open(0);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, w);

	ofxAsync::run([&](ofThread* thread){
		ofLog() << "thread started";

		this->th = thread;

		thread->sleep(1);

		while(thread->isThreadRunning()){
			updateCv();
			thread->sleep(1);
		}
	});

	#else
	grabber.setup(w, h);
	#endif // USE_CV
}

//--------------------------------------------------------------
void ofApp::update(){
	#ifdef USE_CV
	if(mats.size() > 0){
		auto&& mat = mats.front();
		ofxCv::copy(mat, img);
		mats.pop();
		img.update();
	}
	#else
	grabber.update();
	#endif // USE_CV
}

#ifdef USE_CV
//--------------------------------------------------------------
void ofApp::updateCv(){
	// ofLog() << "updateCv";
	cv::Mat mat;
	cap.read(mat);
	ofxCv::convertColor(mat, mat, cv::COLOR_BGR2RGB);
	mats.push(mat);
}
#endif // USE_CV

//--------------------------------------------------------------
void ofApp::draw(){
	#ifdef USE_CV
	if(img.isAllocated()){
		img.draw(0, 0);
	}
	#else
	grabber.draw(0, 0);
	#endif // USE_CV
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 2, 0, '\0'), 20, 20);
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
