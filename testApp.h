#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"

class testApp : public ofBaseApp{

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
		
    
        ofImage             godiva_base;
        ofImage             godiva_left;
        ofImage             godiva_right;
        ofImage             godiva_up;
    
        int 				camWidth;
        int 				camHeight;
        ofVideoGrabber 		vidGrabber;
    
        ofxCvColorImage             camImage;
        ofxCvGrayscaleImage             grabOld;
        ofxCvGrayscaleImage             grabNew;
        ofxCvGrayscaleImage 	grayDiff;
    
        ofxCvContourFinder 	contourFinder;
    
    float oldBlobX;
    float oldBlobY;
    
    
    
    bool action;
    int movement;
    
    float alpha;
};
