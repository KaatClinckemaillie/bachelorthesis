//
//  lightbol.cpp
//  bachelor_thesis_JEF
//
//  Created by Kaat Clinckemaillie on 25/11/2022.
//

#include "Lightbol.h"

void Lightbol::setup(int r,int g,int b, int s, int x, int y, int colorI){
    colorIndex = colorI;
    color.set(r, g , b);
    pos.x = x;
    pos.y = y;
    speed = s + 3;
    
}

void Lightbol::update(){
    pos.x -= speed;
}

void Lightbol::draw(){
    ofSetColor(color);
    ofDrawCircle(pos.x, pos.y, 10);
}
