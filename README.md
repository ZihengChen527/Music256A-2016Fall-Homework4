#Music 256A Homework4 -- Sound Ripple

Sound ripple is a software that can generate ripples in real-time
according to the amplitude and rhythm of mic input audio. Two add-ons
(ofxFft, ofxWaterRipple) are required to run the program. While running,
the input audio buffers are normalized and then doing FFT to calculate 
the amplitude of each sample points, which determines the radius and 
radiation distance of each ripple. The value of the threshold to generate
ripple should be modified when running the program in different environments. 
The position of the ripple is randomized around the canvas.
