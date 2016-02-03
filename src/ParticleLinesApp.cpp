#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ParticleLinesApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
  
  private:
    ParticleController mParticleController;
};

void ParticleLinesApp::setup()
{
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    
    mParticleController.addParticles(50);
}

void ParticleLinesApp::update()
{
    mParticleController.update();
}

void ParticleLinesApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::color( ColorAf( 1, 1, 1, 0.75 ) );
    
    mParticleController.draw();
}

CINDER_APP( ParticleLinesApp, RendererGl(), [&]( App::Settings *settings ) {
    settings->setWindowSize( 1280, 720 );
})