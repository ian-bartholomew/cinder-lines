#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Particle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ParticleLinesApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void ParticleLinesApp::setup()
{
}

void ParticleLinesApp::mouseDown( MouseEvent event )
{
}

void ParticleLinesApp::update()
{
}

void ParticleLinesApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::color( Color::white() );
}

CINDER_APP( ParticleLinesApp, RendererGl(), [&]( App::Settings *settings ) {
    settings->setWindowSize( 1280, 720 );
})