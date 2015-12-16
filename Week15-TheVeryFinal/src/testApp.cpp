#include "testApp.h"

using namespace ofxCv;

void testApp::setup() {
#ifdef TARGET_OSX
	//ofSetDataPathRoot("../data/");
#endif
//	ofSetVerticalSync(true);
	cloneReady = false;


    scanline.loadImage(ofFilePath::getAbsolutePath("scanline1.png"));
    /*
    source1.setFile(ofFilePath::getAbsolutePath("testMovie2015-12-15-19-42-23-209.mov"));
    source2.setFile(ofFilePath::getAbsolutePath("testMovie2015-12-15-19-42-23-209.mov"));
    source3.setFile(ofFilePath::getAbsolutePath("testMovie2015-12-15-19-42-23-209.mov"));

    

    
    distortion.setup(kAudioUnitType_Effect, kAudioUnitSubType_Distortion);
    delay.setup(kAudioUnitType_Effect, kAudioUnitSubType_Delay);
    filter.setup(kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
    
    //	We'll send each of our sources through its own effect, and also
    //	through its own tap so that we can see the individual waveforms
    //	later
    
    source1.connectTo(distortion).connectTo(tap1);
    source2.connectTo(delay).connectTo(tap2);
    source3.connectTo(filter).connectTo(tap3);
    
    
    
    mixer.setInputBusCount(3);
    tap1.connectTo(mixer, 0);
    tap2.connectTo(mixer, 1);
    tap3.connectTo(mixer, 2);
    
    //	Now, we'll send the mixer's single output bus through a shared
    //	compressor effect, then to the output
    
    compressor.setup(kAudioUnitType_Effect, kAudioUnitSubType_DynamicsProcessor);
    
    mixer.connectTo(compressor).connectTo(output);
    
    //	You can set the individual volume of each input bus on the mixer
    //	Volume is in the range of 0 (muted) to 1 (unchanged)
    //	You can set the volume higher than 1, but it may result in clipping
    
    //	We'll set the volume of bus 2 (the hi hat loop) to 0.5, since
    //	they're kind of loud
    
    mixer.setInputVolume(0.5, 2);
    
    //	Now, start the output. The output will cause the mixer to pull
    //	from each of the sources connected to it
    
    output.start();
    
    //	Start each of the loops at the same time so that they're in sync
    
    source1.loop();
    source2.loop();
    source3.loop();
    

    */
    

    ofSetFrameRate(60);

	cam.initGrabber(1280, 720);
	clone.setup(cam.getWidth(), cam.getHeight());
	ofFbo::Settings settings;
	settings.width = cam.getWidth();
	settings.height = cam.getHeight();
	maskFbo.allocate(settings);
	srcFbo.allocate(settings);
	camTracker.setup();
	srcTracker.setup();
	srcTracker.setIterations(25);
	srcTracker.setAttempts(4);

	faces.allowExt("jpg");
	faces.allowExt("png");
	faces.listDir("faces");
	currentFace = 0;
	if(faces.size()!=0){
		loadFace(faces.getPath(currentFace));
	}
    
    

    /*
     VIDEO RECORDER
    */
    
    
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(1280, 720);
    vidRecorder.setFfmpegLocation(ofFilePath::getAbsolutePath("ffmpeg"));
    screenImg.allocate(1280, 720, OF_IMAGE_COLOR);
    
    fileName = "testMovie";
    fileExt = ".mov"; // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats
    
    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("3000k");
    vidRecorder.setAudioCodec("mp3");
    vidRecorder.setAudioBitrate("192k");
    
    
    soundStream.listDevices();
    soundStream.setDeviceID(3);

    
    sampleRate = 16000;
    channels = 2;
    
    soundStream.setup(this, 0, channels, sampleRate, 256, 4);
    bRecording = false;
    
    
    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &testApp::recordingComplete);

    
}


//--------------------------------------------------------------
void testApp::audioIn(float *input, int bufferSize, int nChannels){
    if(bRecording)
        vidRecorder.addAudioSamples(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void testApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    cout << "The recoded video file is now complete." << endl;
}


void testApp::update() {
    
    
    
    
    myPlayer.update();

	cam.update();
	if(cam.isFrameNew()) {
		camTracker.update(toCv(cam));
		
		cloneReady = camTracker.getFound();
		if(cloneReady) {
			ofMesh camMesh = camTracker.getImageMesh();
			camMesh.clearTexCoords();
			camMesh.addTexCoords(srcPoints);
			
			maskFbo.begin();
			ofClear(0, 255);
			camMesh.draw();
			maskFbo.end();
			
			srcFbo.begin();
			ofClear(0, 255);
			src.bind();
			camMesh.draw();
			src.unbind();
			srcFbo.end();
			
			clone.setStrength(16);
			clone.update(srcFbo.getTextureReference(), cam.getTextureReference(), maskFbo.getTextureReference());
		}
        
        ofEnableAlphaBlending();
        ofSetColor(255,255,255,(int)ofRandom(0,50));
        if ((int)ofRandom(0,50)>30){
        scanline.draw((int)ofRandom(0,100), (int)ofRandom(0,50));
        }else{
            scanline.draw((int)ofRandom(0,1500), (int)ofRandom(0,700));

        
        }
        ofDisableAlphaBlending();

        
	}

    
   
    
    
    
    videostop=myPlayer.getIsMovieDone();
    
    if (videostop){
        
        
        myPlayer.closeMovie();
    }
    
    
    vidRecorder.addFrame(screenImg);
    
    if (vidRecorder.hasAudioError()) {
        ofLogWarning("The video recorder failed to write some audio samples!");
    }
    
}

void testApp::exit() {
    vidRecorder.close();
//    ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
 //   vidRecorder.close();
}

void testApp::draw() {
	ofSetColor(255);
	
	if(src.getWidth() > 0 && cloneReady) {
		clone.draw(0, 0);
	} else {
		cam.draw(0, 0);
	}
	
	if(!camTracker.getFound()) {
		drawHighlightString("camera face not found", 10, 10);
	}
	if(src.getWidth() == 0) {
		drawHighlightString("drag an image here", 10, 30);
	} else if(!srcTracker.getFound()) {
		drawHighlightString("image face not found", 10, 30);
	}
    myPlayer.draw(0,0);
    
    
    

    
    ofEnableAlphaBlending();
    ofSetColor(255,255,255,(int)ofRandom(0,50));
    
    scanline.draw((int)ofRandom(0,10), (int)ofRandom(0,10));
    ofDisableAlphaBlending();

    
    
}

void testApp::loadFace(string face){
	src.loadImage(face);
	if(src.getWidth() > 0) {
		srcTracker.update(toCv(src));
		srcPoints = srcTracker.getImagePoints();
	}
}

void testApp::dragEvent(ofDragInfo dragInfo) {
	loadFace(dragInfo.files[0]);
}

void testApp::keyPressed(int key){
    /*
    if(key == 'e') delay.showUI();
    if(key == 'd') distortion.showUI();
    if(key == 'f') filter.showUI();
    */
    
    if(key=='r'){
        
        myPlayer.loadMovie("video/anonymous_start.mov");
        
        myPlayer.setLoopState(OF_LOOP_NONE);
        myPlayer.play();
        /*
        
        myPlayer2.loadMovie("video/scanlines.mp4");
        myPlayer2.setPixelFormat(OF_PIXELS_RGBA);
        myPlayer2.setLoopState(OF_LOOP_NORMAL);
        myPlayer2.play();
*/
        
        
        
        bRecording = !bRecording;
        if(bRecording && !vidRecorder.isInitialized()) {
            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 1280, 720, 30, sampleRate, channels);
            //          vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, vidGrabber.getWidth(), vidGrabber.getHeight(), 30); // no audio
            //            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 0,0,0, sampleRate, channels); // no video
            //          vidRecorder.setupCustomOutput(vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels, "-vcodec mpeg4 -b 1600k -acodec mp2 -ab 128k -f mpegts udp://localhost:1234"); // for custom ffmpeg output string (streaming, etc)
            
            // Start recording
            vidRecorder.start();
        }
        else if(!bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(true);
        }
        else if(bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(false);
        }
    }
    if(key=='c'){
        bRecording = false;
        vidRecorder.close();
    }

    
    
    
	switch(key){
	case OF_KEY_UP:
		currentFace++;
		break;
	case OF_KEY_DOWN:
		currentFace--;
		break;
	}
	currentFace = ofClamp(currentFace,0,faces.size());
	if(faces.size()!=0){
		loadFace(faces.getPath(currentFace));
	}
}
