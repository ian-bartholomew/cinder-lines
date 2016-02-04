//
//  Particle.h
//  ParticleLines
//
//  Created by Ian Bartholomew on 2/2/16.
//
//

#pragma once

#include "cinder/app/App.h"

using namespace std;
using namespace cinder;

class Particle {
  public:
    Particle(vec2 loc, uint id);

    vec2 mLoc;
    std::vector<uint> mConnectedParticles;
    uint mID;
    
    void draw();
    void update();
    void reset(vec2 loc);
    bool isOutsideBounds(vec2 bounds);
    bool isConnectedToParticle(uint id);
    
private:
    vec2 mDir;
    float mVel, mRadius;
};
