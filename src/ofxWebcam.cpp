#include "ofxWebcam.h"
#include "ofxAsync.h"
#include <codecvt>

std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

void ofxWebcam::open(cv::VideoCapture& capture, int device_id){
    #if defined(WIN32)
        capture.open(device_id, cv::CAP_MSMF);
    #elif __APPLE__ && TARGET_OS_MAC
        capture.open(device_id, cv::CAP_AVFOUNDATION);
    #else
        capture.open(device_id);
    #endif // WIN32
}

void ofxWebcam::listDevices(){

ofLogNotice("ofxWebcam") << "============";

#if defined(WIN32)
    listDevicesMSMF();
#elif __APPLE__ && TARGET_OS_MAC
    listDevicesAVFoundation();
#else
    listDevicesCv();
#endif

ofLogNotice("ofxWebcam") << "============";

}

void ofxWebcam::listDevicesMSMF(){
    using namespace enumerate_cameras_windows;
    vector<CameraInfo> camera_infos;
    if(MSMF_enumerate_cameras(camera_infos)){
        int i=0;
        for(auto&& info: camera_infos){
            ofLogNotice("ofxWebcam") << i << ": "
                << ws2s(info.name) << "(" << ws2s(info.path) << ")";
            ++i;
        }
    }
}

void ofxWebcam::listDevicesAVFoundation(){
}

void ofxWebcam::listDevicesCv(){
    const int max_id = 15;

    for(int i=0; i<=max_id; ++i){
        const int device_id = i;

        cv::VideoCapture _cap;

        open(_cap, device_id);

        if(_cap.isOpened()){
            int width = _cap.get(cv::CAP_PROP_FRAME_WIDTH);
            int height = _cap.get(cv::CAP_PROP_FRAME_HEIGHT);
            float fps = _cap.get(cv::CAP_PROP_FPS);
            auto fps_str = ofToString(fps, 2, 0, '\0');

            ofLogNotice("ofxWebcam") << device_id << ": "
                << width << " x " << height
                << ", fps: " << fps_str;
        }

    }
}

void ofxWebcam::setup(int width, int height, int device_id, float fps){

    open(cap, device_id);

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
