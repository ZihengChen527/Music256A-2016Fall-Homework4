#pragma once
#include "ofMain.h"
#include "ofxFft.h"

//-----------------------------------------------------------------------------
// Preprocessor definitions
//-----------------------------------------------------------------------------
#define MY_SRATE         44100            // sample rate
#define MY_CHANNELS      2                // number of channels
#define MY_BUFFERHISTORY 50               // number of buffers to save
#define MY_BUFFERSIZE    512              // number of frames in a buffer
#define MY_NBUFFERS      2                // number of buffers latency
#define MY_PIE           3.14159265358979 // for convenience

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    float getVal(int x, int y);
    void sim();
    void ripple();
    
    // Get audio input samples
    void audioIn(float * input, int bufferSize, int nChannels);
    
    int w;//img width
    int h;//img height
    int pixels;//Number of pixel
    
    ofImage image;//Original image
    ofImage updatedImage;//Updated image
    
    vector<float> odata;//Old pixel
    vector<float> ndata;//New pixel
    vector<float> tempV;//For temp data
    
    float eps = 5.0;
    float z = 0.2;
    ofVec3f light = ofVec3f(1, 1, 0);
    
private:
    // Our sound stream object
    ofSoundStream soundStream;
    
    // Our FFT object
    ofxFft* fft;
    
    // Vectors for our left- and right-channel waveforms
    vector<float> left;
    vector<float> right;
    
    // Double vectors to save previous waveforms, for plotting in the ripple
    vector< vector<float> > leftHistory;
    vector< vector<float> > rightHistory;
    
    float threshold = 0.8;
    
};
