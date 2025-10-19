#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include <optional>

class ofxWebcam {
public:
    void setup(int width, int height, int device_id=0, float fps=30.0);
    void update();
    void draw(float x, float y);
    void draw(float x, float y, float w, float h);
    float getWidth();
    float getHeight();
    float getFps();
    bool isFrameNew();
    std::optional<ofTexture> getTexture();
    bool isAllocated();

protected:
    ofThread* th;
    cv::VideoCapture cap;
    std::queue<cv::Mat> mats;
    ofImage img;

    bool is_updating_by_thread = false;
    bool is_frame_new = false;

    void startThread();
    void updateCv();
    void exit(ofEventArgs& e);
};