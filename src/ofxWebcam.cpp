#include "ofxWebcam.h"
#include "ofxAsync.h"

void ofxWebcam::setup(int width, int height, int device_id, float fps){

#if defined(WIN32)
    cap.open(device_id, cv::CAP_MSMF);
#else
    cap.open(device_id);
#endif // WIN32

    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FPS, fps);

    startThread();
}

void ofxWebcam::update(){
	if(mats.size() > 0){
		auto&& mat = mats.front();
		ofxCv::copy(mat, img);
		mats.pop();
		img.update();
	}
    if(!is_updating_by_thread){
        is_frame_new = false;
    }
}

float ofxWebcam::getWidth(){
    return cap.get(cv::CAP_PROP_FRAME_WIDTH);
}

float ofxWebcam::getHeight(){
    return cap.get(cv::CAP_PROP_FRAME_HEIGHT);
}

float ofxWebcam::getFps(){
    return cap.get(cv::CAP_PROP_FPS);
}

bool ofxWebcam::isAllocated(){
    return img.isAllocated();
}

std::optional<ofTexture> ofxWebcam::getTexture(){
    if(img.isAllocated()){
        return img.getTexture();
    }else{
        return std::nullopt;
    }
}

void ofxWebcam::draw(float x, float y){
    if(img.isAllocated()){
        img.draw(x, y);
    }
}

void ofxWebcam::draw(float x, float y, float w, float h){
    if(img.isAllocated()){
        img.draw(x, y, w, h);
    }
}

bool ofxWebcam::isFrameNew(){
    return is_frame_new;
}

void ofxWebcam::startThread(){
    ofAddListener(ofEvents().exit, this, &ofxWebcam::exit);

	ofxAsync::run([&](ofThread* thread){
		ofLogNotice("ofxWebcam") << "thread started";

		this->th = thread;

		thread->sleep(1);

		while(thread->isThreadRunning()){
			updateCv();
			thread->sleep(1);
		}
	});
}

void ofxWebcam::updateCv(){
    is_updating_by_thread = true;
	cv::Mat mat;
	cap.read(mat);
	ofxCv::convertColor(mat, mat, cv::COLOR_BGR2RGB);
    if(mats.size() < 2){ // WORKAROUND: not create too many queues
	    mats.push(mat);
    }
    is_frame_new = true;
    is_updating_by_thread = false;
}

void ofxWebcam::exit(ofEventArgs& e){
    // ofLogNotice("ofxWebcam") << "exitting";
    if(th != nullptr){
        th->stopThread();
        th->waitForThread();
    }
}
