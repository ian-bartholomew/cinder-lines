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
        mParticles.pop_back();
    }
}

void ParticleController::update(uint numParticles){
    // adjust the number of particle if needed 
    if (mParticles.size() != numParticles) {
        mParticles.clear();
        addParticles(numParticles);
    }
    
    for( auto & p : mParticles ){
        p.update();
    }
}

void ParticleController::draw(){
    gl::color( ColorAf( 1, 1, 1, 0.75 ) );
    for( auto & p : mParticles ){
        p.draw();
    }
}

void ParticleController::drawLines(float zoneRadiusSquared, float lineAlpha, float fillAlpha){
    {
        list<vec2> pts;
        
        for( vector<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ) {
            
            vector<Particle>::iterator p2 = p1;
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
                    
                    for ( auto &it : p1->mConnectedParticles){
                        if (p2->isConnectedToParticle(it)){
//                            float a = std::min(std::min((length2(p1->mLoc - p2->mLoc)/zoneRadiusSquared),(length2(p2->mLoc - it.mLoc)/zoneRadiusSquared)),(length2(it.mLoc - p1->mLoc)/zoneRadiusSquared));
                            pts.push_back(p1->mLoc);
                            pts.push_back(p2->mLoc);
                            pts.push_back(mParticles.at(it).mLoc);
                            
                            
                        }
                    }
                }
            }
        }
        
        gl::VertBatch vb( GL_TRIANGLES );
        for (auto &p : pts) {
            vb.color( 1, 1, 1, fillAlpha -  0.2f);
            vb.vertex( p.x, p.y );
        }
        vb.draw();

    }
}