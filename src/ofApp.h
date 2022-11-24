#pragma once

#include "ofMain.h"

class lightbol {
    public:
    int radius = 10;
    int x = 550;
    int y;
    void draw();
    lightbol(); //constructor
    ~lightbol(); //destructor
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		
        ofSerial    serial;
        string sensorValue;
        int byteData;
        int position = 50;
        lightbol newLightbol;
        
};
