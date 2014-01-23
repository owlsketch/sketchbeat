#pragma once

#include "ofMain.h"

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

		//utils
		ofDirectory dir;
		vector<string> songlist;
		int pos;
		int songsize;

		int time,time2; //time intervals for calculations
		int counter;
		ofIcoSpherePrimitive mainSphere, extSphere; //inner sphere
        ofSoundPlayer sound;
        ofTrueTypeFont verdana;
        string songData;

        bool pause,change;

        float * fftSmoothed; //pointer?
        int nBandsToGet; //number of samples
        int sampleBand;
        float freq;

        //vector of a vector of set of colors for Sphere
        vector<int> colorVec;
        int ranCol;
};
