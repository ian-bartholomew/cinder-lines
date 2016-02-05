//
//  ParticleController.h
//  ParticleLines
//
//  Created by Ian Bartholomew on 2/2/16.
//
//

#pragma once

#include "cinder/app/App.h"
#include "Particle.h"
#include <list>

using namespace std;
using namespace cinder;

class ParticleController {
  public:    
    void update(uint numParticles);
    void draw();
    void addParticles( int amt );
    void removeParticles( int amt );
    void drawLines(float zoneRadiusSquared, float lineAlpha, float fillAlpha);
    
private:
    std::vector<Particle> mParticles;
};
