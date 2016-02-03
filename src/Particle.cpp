//
//  Particle.cpp
//  ParticleLines
//
//  Created by Ian Bartholomew on 2/2/16.
//
//

#include "Particle.h"
#include "cinder/Rand.h"

using namespace std;
using namespace cinder;

Particle::Particle(vec2 loc){
    reset(loc);
}

void Particle::reset(vec2 loc){
    mLoc = loc;
    mDir = Rand::randVec2();
    mVel = Rand::randFloat( 5.0f );
    mRadius = 4.0f - Rand::randFloat( 1.5f, 3.0f );
}

bool Particle::isOutsideBounds(vec2 bounds){
    return mLoc.x > bounds.x || mLoc.y > bounds.y || mLoc.x < 0 || mLoc.y < 0;
}

void Particle::draw(){
    gl::drawSolidCircle(mLoc, mRadius);
}

void Particle::update(){
    mLoc += mDir * mVel;
}