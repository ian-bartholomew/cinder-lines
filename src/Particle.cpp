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

Particle::Particle(vec2 loc, uint id){
    mID = id;
    reset(loc);
}

void Particle::reset(vec2 loc){
    mLoc = loc;
    mDir = Rand::randVec2();
    mVel = Rand::randFloat( 2.0f );
    mRadius = Rand::randFloat( 0.5f, 2.0f );
}

bool Particle::isConnectedToParticle(uint id){
    if(std::find(mConnectedParticles.begin(), mConnectedParticles.end(), id) != mConnectedParticles.end()) {
        return TRUE;
    } else {
        return FALSE;
    }
}

bool Particle::isOutsideBounds(vec2 bounds){
    return mLoc.x > bounds.x || mLoc.y > bounds.y || mLoc.x < 0 || mLoc.y < 0;
}

void Particle::draw(){
    gl::drawSolidEllipse(mLoc, mRadius, mRadius);
}

void Particle::update(){
    mLoc += mDir * mVel;
    mConnectedParticles.clear(); // clear each run
}