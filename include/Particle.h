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
    Particle(vec2 loc);
    
    void draw();
    void update();
    void reset(vec2 loc);
    bool isOutsideBounds(vec2 bounds);
    
private:
    vec2 mLoc, mDir;
    float mVel, mRadius;
};
