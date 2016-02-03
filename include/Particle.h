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
    ~Particle();
    
    void draw();
    void update();
    
};
