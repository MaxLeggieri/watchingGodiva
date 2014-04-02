#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    camWidth 		= 640;	// try to grab at this size.
	camHeight 		= 480;
    
    int screenW = ofGetWidth();
    int screenH = ofGetHeight();
    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
    
    grabOld.allocate(camWidth, camHeight);
    grabNew.allocate(camWidth, camHeight);
    camImage.allocate(camWidth, camHeight);
    
    
    grayDiff.allocate(camWidth,camHeight);
    
    godiva_base.loadImage("/Users/Max/Documents/of_v0.8.0_osx_release/apps/myApps/Godiva1/src/godiva_base.jpg");
    godiva_base.resize(screenW, screenH);
    
    godiva_left.loadImage("/Users/Max/Documents/of_v0.8.0_osx_release/apps/myApps/Godiva1/src/godiva0.jpg");
    godiva_left.resize(screenW, screenH);
    
    godiva_right.loadImage("/Users/Max/Documents/of_v0.8.0_osx_release/apps/myApps/Godiva1/src/godiva1.jpg");
    godiva_right.resize(screenW, screenH);
    
    godiva_up.loadImage("/Users/Max/Documents/of_v0.8.0_osx_release/apps/myApps/Godiva1/src/godiva2.jpg");
    godiva_up.resize(screenW, screenH);
    
    
    grabOld.setFromPixels(vidGrabber.getPixels(), camWidth,camHeight);
    
    
    
    alpha = 255;
    
    
    
    ofSetVerticalSync(true);
    ofBackground(0,0,0);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
	if (bNewFrame){
        
        camImage.setFromPixels(vidGrabber.getPixels(), camWidth,camHeight);
        
        grabNew = camImage;
        
        // take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grabOld, grabNew);
		grayDiff.threshold(80);
        
        contourFinder.findContours(grayDiff, 20, (camWidth*camHeight)/3, 10, true);
        
        
        grabOld.setFromPixels(grabNew.getPixels(), camWidth, camHeight);
        
        
        
        
        
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    //printf("go go ");
    //god.draw(0,0);
    ofBackground(0, 0, 0);
    
        ofEnableAlphaBlending();
        
        ofSetColor(255,255,255);
        godiva_base.draw(0,0);
        
    if (action) {
        ofSetColor(255,255,255,movement==1?alpha-=5:0);
        godiva_left.draw(0,0);
        
        ofSetColor(255,255,255,movement==2?alpha-=5:0);
        godiva_right.draw(0,0);
        
        ofSetColor(255,255,255,movement==3?alpha-=5:0);
        godiva_up.draw(0,0);
    }
    
        
        ofDisableAlphaBlending();
        
        
        
        if (alpha <= 0) {
            action = false;
            alpha = 255;
            movement = 0;
        }
    
    
    
    
    //videoTexture.draw(0, 0);
    
    //printf("blob %i: x %f\n",0,contourFinder.blobs[0].boundingRect.getCenter().x);
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        
        if(action) {
            break;
        }
        
        if (i == 0) {
            
            if (oldBlobX == 0) {
                oldBlobX = contourFinder.blobs[i].boundingRect.getCenter().x;
                break;
            }
            
            if (oldBlobY == 0) {
                oldBlobY = contourFinder.blobs[i].boundingRect.getCenter().y;
                break;
            }
            
            float newBlobX = contourFinder.blobs[i].boundingRect.getCenter().x;
            float newBlobY = contourFinder.blobs[i].boundingRect.getCenter().y;
            
            if (newBlobX != oldBlobX) {
                
                if (newBlobX > oldBlobX) {
                    
                    float xDiff = newBlobX-oldBlobX;
                    
                    
                    if (xDiff > 10) {
                        printf(" <<<<<<<<<<<<< ");
                        printf("diff: %f",xDiff);
                        action = true;
                        movement = 1;
                    }
                    
                } else {
                    
                    float xDiff = oldBlobX-newBlobX;
                    
                    if (xDiff > 10) {
                        printf(" >>>>>>>>>>>>> ");
                        printf("diff: %f",xDiff);
                        action = true;
                        movement = 2;
                    }
                    
                }
            }
            
            if (newBlobY != oldBlobY) {
                
                
                
                if (newBlobY < oldBlobY) {
                    float yDiff = oldBlobY-newBlobY;
                    if (yDiff > 5) {
                        printf(" ^^^^^^^^^^^^^ ");
                        printf("diff: %f",oldBlobY-newBlobY);
                        action = true;
                        movement = 3;
                    }
                    
                }
            }
            
            oldBlobX = newBlobX;
            oldBlobY = newBlobY;
        }
        
        //printf("blob %i: x %f\n",i,contourFinder.blobs[i].boundingRect.getCenter().x);
        //printf("blob %i: y %f\n",i,contourFinder.blobs[i].boundingRect.getCenter().x);
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
