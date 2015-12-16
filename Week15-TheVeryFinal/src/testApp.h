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
    
    /*
    ofxAudioUnitFilePlayer source1, source2, source3;
    ofxAudioUnitMixer mixer;

    
    ofxAudioUnit compressor;
    ofxAudioUnit delay;
    ofxAudioUnit distortion;
    ofxAudioUnit filter;
    ofxAudioUnitTap tap1, tap2, tap3;
    ofxAudioUnitOutput output;

    */
    
	ofxFaceTracker srcTracker;
	ofImage src;
	vector<ofVec2f> srcPoints;
	
    
    ofImage scanline;
    
	bool cloneReady;
	Clone clone;
	ofFbo srcFbo, maskFbo;

	ofDirectory faces;
	int currentFace;
    
    
    ofVideoPlayer myPlayer,myPlayer2;
    ofVideoGrabber      vidGrabber;
    ofxVideoRecorder    vidRecorder;
    

    
    ofSoundStream       soundStream;
    bool bRecording, videostop;

    int sampleRate;
    int channels;
    string fileName;
    string fileExt;
    ofImage    screenImg;
    
    
    //// SLIT SCANNING
    
    deque<ofPixels> frames;		//Frames buffer
    int N;						//Frames buffer size
    
    //Pixels array for constructing output image
    ofPixels imagePixels;
    ofImage image;				//Output image
    
    //Main processing function which
    //computes the pixel color (x, y) using frames buffer
    ofColor getSlitPixelColor( int x, int y );
    

};
