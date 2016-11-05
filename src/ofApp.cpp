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
    
    
    /*********** Image *************/
    
    image.loadImage("blue.png");
    //image.loadImage("sea_blue.jpg");
    w = image.getWidth();
    h = image.getHeight();
    pixels = w * h;
    updatedImage.allocate(w, h, OF_IMAGE_COLOR);//allocate
    
    light.normalize();
    
    tempV.resize(pixels);
    odata.resize(pixels);
    ndata.resize(pixels);
    
    for (int i=0; i<pixels; i++) {
        tempV[i] = 0.0;
        odata[i] = 0.0;
        ndata[i] = 0.0;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
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
    
    // TODO: may not need to normalize
    /*
    // Now normalize the FFT magnitude values
    maxValue = 0;
    for(int i = 0; i < fft->getBinSize(); i++) {
        if(abs(fftData[i]) > maxValue) { maxValue = abs(fftData[i]); }
    }
    for(int i = 0; i < fft->getBinSize(); i++) { fftData[i] /= maxValue; }
    */
    
    for (int i = 0; i < fft->getBinSize(); i++) {
        if (fftData[i] > threshold) {
            ripple();
            sim();
            for (int i=0; i<pixels; i++) {//Make each first ripple
                int x = i % w;
                int y = i / w;
                
                ofVec3f n = ofVec3f(getVal(x - eps, y) - getVal(x + eps, y), getVal(x, y - eps) - getVal(x, y + eps), eps * 2.0);//Check pixels around
                n.normalize();
                float spec = (1 - (light.x + n.x)) + (1 - (light.y + n.y));
                spec /= 2;
                
                if (spec > z)
                    spec = (spec - z) / (1 - z);
                else
                    spec = 0;
                
                spec *= 255.0;
                
                ofColor c = image.getColor(x + n.x * 60, y + n.y * 60);//Get "edge" of ripple
                c += spec;//Make "edge" brighter
                updatedImage.setColor(x, y, c);
            }
            updatedImage.update();
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    updatedImage.draw(0, 0);
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

//--------------------------------------------------------------
float ofApp::getVal(int x, int y){
    if (x < 1 || y < 1 || x >= w - 1 || y >= h - 1){return 0;}
    float a = odata[x+y*w];
    return a;
}

//--------------------------------------------------------------
void ofApp::sim(){
    //Store current situation then update.
    for (int i=0; i<pixels; i++) {
        tempV[i] = odata[i];
    }
    for (int i=0; i<pixels; i++) {
        odata[i] = ndata[i];
    }
    for (int i=0; i<pixels; i++) {
        ndata[i] = tempV[i];
    }
    
    //Spread
    for (int i=0; i<pixels; i++) {
        int x = i % w;
        int y = i / w;
        if (x > 1 || y > 1 || x <= w - 1 || y <= h - 1){
            float val = (odata[(x-1)+y*w] + odata[(x+1)+y*w] + odata[x+(y-1)*w] + odata[x+(y+1)*w]) / 2;
            val = val - ndata[x+y*w];
            val *= 0.96875;
            ndata[x+y*w] = val;
        }
    }
}
//--------------------------------------------------------------
void ofApp::ripple(){
    //Randomly make ripple
    int rx = (int)ofRandom(w - 10) + 5;
    int ry = (int)ofRandom(h - 10) + 5;
    for (int x = -5; x < 5; x++){
        for (int y = -5; y < 5; y++){
            int targetPix = (rx + x) + (w * (ry + y));
            odata[targetPix] = 100;
        }
    }
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
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //Make ripple
    for (int x = -10; x < 10; x++) {
        for (int y = -10; y < 10; y++) {
            int targetPix = (mouseX + x) + (w * (mouseY + y));
            odata[targetPix] = 0.1;
        }
    }
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
