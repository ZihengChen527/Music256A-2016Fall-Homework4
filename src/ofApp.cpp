#include <cstdlib>
#include <cmath>
#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    
    /*********** Audio *************/
    
    // Setup the sound stream
    soundStream.setup(this, 0, MY_CHANNELS, MY_SRATE, MY_BUFFERSIZE, MY_NBUFFERS);
    
    // Resize and initialize left and right buffers...
    left.resize( MY_BUFFERSIZE, 0 );
    right.resize( MY_BUFFERSIZE, 0 );
    
    // Resize and initialize left and right history buffers...
    leftHistory.resize(  MY_BUFFERHISTORY, left  );
    rightHistory.resize( MY_BUFFERHISTORY, right );
    
    // Setup the fft
    fft = ofxFft::create(MY_BUFFERSIZE, OF_FFT_WINDOW_HAMMING);
    
    /************ Ripple ***********/
	ofSetLogLevel(OF_LOG_VERBOSE);
	agua.setup(1024, 768);
}

//--------------------------------------------------------------
void ofApp::update(){
	agua.update();
	//ofSetWindowTitle( ofToString(ofGetFrameRate()) + " FPS" );
    
    // Normalize the left channel waveform
    float maxValue = 0;
    for(int i = 0; i < left.size(); i++) {
        if(abs(left[i]) > maxValue) { maxValue = abs(left[i]); }
    }
    for(int i = 0; i < left.size(); i++) { left[i] /= maxValue; }
    
    // Take the FFT of the left channel
    fft->setSignal(&left[0]);
    
    // Get the magnitudes and copy them to audioBins
    float* fftData = fft->getAmplitude();
     
    for (int i = 0; i < fft->getBinSize(); i++) {
        if (fftData[i] > threshold1 && fftData[i] < threshold2) {
            //std::cout << fftData[i] << std::endl;
            agua.disturb(rand() % 1024, rand() % 768, fftData[i] * 30, 50);
        }
        if (fftData[i] > threshold2) {
            agua.disturb(rand() % 1024, rand() % 768, 50, 400);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	agua.draw(true);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	agua.disturb(x,y,10,128);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == OF_MOUSE_BUTTON_1)
		agua.disturb(x,y,10,128);
	else
		agua.disturb(x,y,50,500);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

//--------------------------------------------------------------
// audioIn() -- deal with incoming audio buffer
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    // Write incoming audio to buffer. Note: samples are interleaved.
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2];
        right[i]	= input[i*2+1];
    }
}
