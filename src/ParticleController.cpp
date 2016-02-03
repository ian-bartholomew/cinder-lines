//
//  ParticleController.cpp
//  ParticleLines
//
//  Created by Ian Bartholomew on 2/2/16.
//
//

#include "ParticleController.h"
#include "Particle.h"
#include "cinder/Rand.h"

using namespace std;
using namespace cinder;

void ParticleController::addParticles(int amt){
    for (uint i = 0; i < amt; i++) {
        float x = Rand::randFloat( app::getWindowWidth() );
        float y = Rand::randFloat( app::getWindowHeight() );
        mParticles.push_back( Particle( vec2( x, y ) ) );
    }
}

void ParticleController::removeParticles(int amt){
    for (uint i = 0; i < amt; i++) {
        mParticles.pop_front();
    }
}

void ParticleController::update(){
    vec2 windowBounds = vec2(app::getWindowWidth(), app::getWindowHeight());
    
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        if (p->isOutsideBounds(windowBounds)) {
            float x = Rand::randFloat( app::getWindowWidth() );
            float y = Rand::randFloat( app::getWindowHeight() );
            p->reset(vec2( x, y ));
        }
        p->update();
    }
}

void ParticleController::draw(){
    gl::color( ColorAf( 1, 1, 1, 0.75 ) );
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->draw();
    }
}

void ParticleController::drawLines(float zoneRadiusSquared){
    {
        for( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ) {
            
            list<Particle>::iterator p2 = p1;
            for( ++p2; p2 != mParticles.end(); ++p2 ) {
                vec2 dir = p1->mLoc - p2->mLoc;
                float distSqrd = length2(dir);
                
                if( distSqrd <= zoneRadiusSquared ) {
                    gl::color( ColorAf( 1, 1, 1, 1.0f - ( distSqrd/zoneRadiusSquared) ) );
                    gl::drawLine(p1->mLoc, p2->mLoc);
                }
            }
        }
    }
}