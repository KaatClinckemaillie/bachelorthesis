//
//  lightbol.cpp
//  bachelor_thesis_JEF
//
//  Created by Kaat Clinckemaillie on 25/11/2022.
//

#include "Lightbol.h"

void Lightbol::setup(int r,int g,int b, int v_x, int v_y, int x, int y, int colorI){
    colorIndex = colorI;
    color.set(r, g , b);
    pos.x = x;
    pos.y = y;
    velo.x = v_x;
    velo.y = v_y;
    
}

void Lightbol::update(){
    pos.x -= velo.x;
    pos.y += velo.y;
}

void Lightbol::draw(){
    ofSetColor(color);
    ofDrawCircle(pos.x, pos.y, 10);
}
