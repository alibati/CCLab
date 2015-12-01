#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Clone.h"
#include "ofxFaceTracker.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxVideoRecorder.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void exit();
    void audioIn(float * input, int bufferSize, int nChannels);

	void dragEvent(ofDragInfo dragInfo);
	void loadFace(string face);
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);

	void keyPressed(int key);

	ofxFaceTrackerThreaded camTracker;
	ofVideoGrabber cam;
	
	ofxFaceTracker srcTracker;
	ofImage src;
	vector<ofVec2f> srcPoints;
	
	bool cloneReady;
	Clone clone;
	ofFbo srcFbo, maskFbo;

	ofDirectory faces;
	int currentFace;
    
    
    ofVideoPlayer myPlayer;
    ofVideoGrabber      vidGrabber;
    ofxVideoRecorder    vidRecorder;
    

    
    ofSoundStream       soundStream;
    bool bRecording, videostop;

    int sampleRate;
    int channels;
    string fileName;
    string fileExt;
    ofImage    screenImg;

};
