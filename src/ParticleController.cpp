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
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->draw();
    }
}