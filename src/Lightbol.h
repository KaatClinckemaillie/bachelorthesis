//
//  lightbol.h
//  bachelor_thesis_JEF
//
//  Created by Kaat Clinckemaillie on 25/11/2022.
//

#pragma once
#include "ofMain.h"

class Lightbol {
public:
    int radius = 10;
    ofPoint pos;
    ofColor color;
    int speed;
    int colorIndex;
    void draw();
    void update();
    void setup(int r,int g,int b, int s, int x, int y,int colorI);
    
};
