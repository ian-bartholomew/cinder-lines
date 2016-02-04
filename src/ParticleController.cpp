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
        mParticles.push_back( Particle( vec2( x, y ), i) );
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

void ParticleController::drawLines(float zoneRadiusSquared, float lineAlpha, float fillAlpha){
    {
        for( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ) {
            
            list<Particle>::iterator p2 = p1;
            for( ++p2; p2 != mParticles.end(); ++p2 ) {
                // check that we have not already drawn a line, because we don't want to draw two
                if (!p1->isConnectedToParticle(p2->mID)) {
                    vec2 dir = p1->mLoc - p2->mLoc;
                    float distSqrd = length2(dir);
                    
                    if( distSqrd <= zoneRadiusSquared ) {
                        gl::color( ColorAf( 1, 1, 1, lineAlpha - ( distSqrd/zoneRadiusSquared) ) );
                        gl::drawLine(p1->mLoc, p2->mLoc);
                        p1->mConnectedParticles.push_back(p2->mID);
                        p2->mConnectedParticles.push_back(p1->mID);
                    }
                    
                    vector<uint> &pv = p1->mConnectedParticles;
                    for ( auto &it : pv){
                        if (p2->isConnectedToParticle(it)){
                            for (auto & p3 : mParticles) {
                                if (p3.mID == it) {
                                    float a = std::min(
                                                       std::min((length2(p1->mLoc - p2->mLoc)/zoneRadiusSquared),
                                                                (length2(p2->mLoc - p3.mLoc)/zoneRadiusSquared)),
                                                       (length2(p3.mLoc - p1->mLoc)/zoneRadiusSquared));
                                    gl::VertBatch vb( GL_TRIANGLES );
                                        vb.color( 1, 1, 1, fillAlpha -  a);
                                        vb.vertex( p1->mLoc.x, p1->mLoc.y );
                                        vb.color( 1, 1, 1, fillAlpha -  a);
                                        vb.vertex( p2->mLoc.x, p2->mLoc.y );
                                        vb.color( 1, 1, 1, fillAlpha -  a);
                                        vb.vertex( p3.mLoc.x, p3.mLoc.y );
                                    vb.draw();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}