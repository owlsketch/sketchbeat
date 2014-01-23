#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableDepthTest();

    verdana.loadFont("verdana.ttf",12,true,false);

    //setting up colors
    colorVec.reserve(5);
    colorVec[0] = 0x36A691;
    colorVec[1] = 0x40C486;
    colorVec[2] = 0x5FFF86;
    colorVec[3] = 0x47C741;
    colorVec[4] = 0x97FF53;

    ranCol = ofRandom(0,4);

    //song list positioning
    pos = 0;

    dir.listDir("Music/");
    songsize = dir.size();
    if(dir.size())
    {
        songlist.resize(songsize);
    }
    for (int i =0; i < songsize; i++)
    {
        songlist[i] = dir.getName(i);
        cout << songlist[i] << endl;
    }
    songData = (dir.getPath(pos));
    sound.loadSound(songData);
    sound.play();

    pause = true;
    change = false;

    time = int(ofGetElapsedTimef()); //get elapsed time

    time2 = 0;
    mainSphere.setRadius(ofGetWidth()/4.8); //radius of inner sphere is 1/4.2 size of screenwidth


    // the fft needs to be smoothed out, so we create an array of floats
	// for that purpose: Create an array of 8192 all valued at 0.
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}

	nBandsToGet = 128; //number of samples

	sampleBand = 2;
	counter = 0;
}

//--------------------------------------------------------------
void testApp::update(){

    if (change == true)
    {
        if(pos < 0)
        {
            pos = songsize - 1;
        }
        if (pos >= songsize)
        {
            pos = 0;
        }
        songData = (dir.getPath(pos));
        sound.stop();
        sound.unloadSound();
        sound.loadSound(songData);
        sound.play();
        change = false;
    }
    ofSoundUpdate();

    extSphere.setRadius(ofGetWidth()/4.6);

    time = ofGetElapsedTimef(); //update on time

    //  grab the fft, and put in into a "smoothed" array,
	//		by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values from SoundSpectrum for fft
	for (int i = 0;i < nBandsToGet; i++){

		// let the smoothed value sink to zero:
		fftSmoothed[i] *= 0.96f; //freq.?

		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

	}

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetWindowTitle("OrbitAL - Orbital Audio Listener");
    ofBackgroundGradient(230,100,OF_GRADIENT_CIRCULAR);


    // draw the fft resutls:
	ofSetColor(255,255,255,255);

	float width = (float)(ofGetWidth()) / nBandsToGet;
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		//ofRect(x_pos,y_pos,width,height)
		ofRect(i*width,ofGetHeight(),width,-(fftSmoothed[i] * 200));
	}
	freq = (fftSmoothed[0] + fftSmoothed[1] + fftSmoothed[2] + fftSmoothed [3] + fftSmoothed[4] + fftSmoothed[5])/12;


    if (time != time2) //change in color and radius of inner sphere every sec.
    {

        ranCol = ofRandom(0,4);
    }

    counter++;
    if(counter >=4)
    {
        if((freq * ofGetWidth()/4.8) > ofGetWidth()/4.8)
        {
            mainSphere.setRadius(ofGetWidth()/4.8);
        }
        else
        {
            mainSphere.setRadius(freq * ofGetWidth()/4.8);
        }
        counter = 0;
    }
    else{ mainSphere.setRadius(mainSphere.getRadius() - .10);}

    ofSetHexColor(colorVec[ranCol]);
    mainSphere.drawFaces();

    ofSetColor(250);
    mainSphere.drawWireframe();

    ofSetColor(160);

    extSphere.setPosition(ofGetWidth()/2,ofGetHeight()/2,0);
    extSphere.drawWireframe();
    extSphere.rotate(.1,-1.0,1.0,0.0);

    mainSphere.setPosition(ofGetWidth()/2,ofGetHeight()/2,0);
    mainSphere.rotate(.6, 1.0, -1.0, 0.0);

    time2 = time;

    if(pause == true) //music is playing
    {
        ofNoFill();
        ofTriangle(17,8,17,27,28,17);
        verdana.drawString(songData,32,23);
    }
    else
    {
        ofNoFill();
        ofRect(13,10,5,15);
        ofRect(23,10,5,15);
        verdana.drawString(songData,32,23);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key == 358)
    {
        pos++;
        change = true;
    }
    if (key == 356)
    {
        pos--;
        change = true;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    //pause/play
    if (key == 32)
    {
        sound.setPaused(pause);
        if (pause == true)
        { pause = false; }
        else{pause = true;}
    }
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
