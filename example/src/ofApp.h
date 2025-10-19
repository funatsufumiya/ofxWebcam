#pragma once

#include "ofMain.h"

#define USE_CV

#ifdef USE_CV
#include "ofxCv.h"
#endif // USE_CV

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		#ifdef USE_CV
		void updateCv();
		#endif // USE_CV
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit() override;

		int w = 1280;
		int h = 720;

		#ifdef USE_CV
		ofThread* th;
		cv::VideoCapture cap;
		std::queue<cv::Mat> mats;
		ofImage img;
		#else
		ofVideoGrabber grabber;
		#endif // USE_CV
		
};
