#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ParticleLinesApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
  
  private:
    ParticleController      mParticleController;
    params::InterfaceGlRef	mParams;
    float                   mZoneRadiusSqrd;
    bool                    bDrawParticles, bEnableMultiSample, bEnableLineSmooth, bEnablePolySmooth;
};

void ParticleLinesApp::setup()
{
    
    mZoneRadiusSqrd = 25000.0f;
    bDrawParticles = TRUE;
    bEnableLineSmooth = TRUE;
    bEnableMultiSample = TRUE;
    bEnablePolySmooth = FALSE;
    
    //set up params
    mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( ivec2( 200, 300 ) ) );
    mParams->addParam( "Zone Radius", &mZoneRadiusSqrd ).min( 100.0f ).step( 500.0f );
    mParams->addParam( "Draw Particles", &bDrawParticles );
    mParams->addParam( "Enable Multisample", &bEnableMultiSample );
    mParams->addParam( "Enable Line Smooth", &bEnableLineSmooth );
    mParams->addParam( "Enable Poly Smooth", &bEnablePolySmooth );
    
    mParticleController.addParticles(50);
    
}

void ParticleLinesApp::update()
{
    mParticleController.update();
}

void ParticleLinesApp::draw()
{
    
    if (bEnableMultiSample) glEnable( GL_MULTISAMPLE_ARB );
    
    if (bEnableLineSmooth) {
        glEnable( GL_LINE_SMOOTH );
        glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    }
    
    if (bEnablePolySmooth) {
        glEnable( GL_POLYGON_SMOOTH );
        glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
    }
    
	gl::clear( Color( 0, 0, 0 ) );
    
    mParticleController.drawLines(mZoneRadiusSqrd);
    if (bDrawParticles) mParticleController.draw();
    
    // Draw the interface
    mParams->draw();
}

CINDER_APP( ParticleLinesApp, RendererGl, [&]( App::Settings *settings ) {
    settings->setWindowSize( 1280, 720 );
})