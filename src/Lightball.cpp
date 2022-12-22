//
//  lightbol.cpp
//  bachelor_thesis_JEF
//
//  Created by Kaat Clinckemaillie on 25/11/2022.
//

#include "Lightball.h"

void Lightball::setup(int r,int g,int b, int v_x, int v_y, int x, int y, int colorI){
    colorIndex = colorI;
    color.set(r, g , b);
    pos.x = x;
    pos.y = y;
    velo.x = v_x;
    velo.y = v_y;
    
}

void Lightball::update(){
    pos.x -= ofGetLastFrameTime() * velo.x;
    pos.y += ofGetLastFrameTime() * velo.y;
}

void Lightball::draw(){
    ofSetColor(color);
    ofDrawCircle(pos.x, pos.y, radius);
}
