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
    uint                    mNumParticles;
    ParticleController      mParticleController;
    params::InterfaceGlRef	mParams;
    float                   mZoneRadiusSqrd, mLineAlpha, mFillAlpha;
    bool                    bPause, bDrawParticles, bEnableMultiSample, bEnableLineSmooth, bEnablePolySmooth;
};

void ParticleLinesApp::setup()
{
    mNumParticles = 50;
    mZoneRadiusSqrd = 25000.0f;
    mLineAlpha = 1.0f;
    mFillAlpha = 0.5f;
    bDrawParticles = TRUE;
    bEnableLineSmooth = TRUE;
    bEnableMultiSample = TRUE;
    bEnablePolySmooth = FALSE;
    bPause = FALSE;
    
    //set up params
    mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( ivec2( 200, 300 ) ) );
    mParams->addParam( "Zone Radius", &mZoneRadiusSqrd ).min( 100.0f ).step( 500.0f );
    mParams->addParam( "Draw Particles", &bDrawParticles );
    mParams->addParam( "Number  Particles", &mNumParticles );
    mParams->addSeparator();
    mParams->addParam( "Enable Multisample", &bEnableMultiSample );
    mParams->addParam( "Enable Line Smooth", &bEnableLineSmooth );
    mParams->addParam( "Enable Poly Smooth", &bEnablePolySmooth );
    mParams->addSeparator();
    mParams->addParam("Pause", &bPause).key("space");
    mParams->addSeparator();
    mParams->addParam( "Line Alpha", &mLineAlpha ).min( 0.0f ).max(1.0f).step( 0.01f );
    mParams->addParam( "Fill Alpha", &mFillAlpha ).min( 0.0f ).max(1.0f).step( 0.01f );
    
    mParticleController.addParticles(mNumParticles);
    
    gl::enableAdditiveBlending();
//    gl::enableAlphaBlending();
    
}

void ParticleLinesApp::update()
{
    if (!bPause) mParticleController.update(mNumParticles);
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
    
    mParticleController.drawLines(mZoneRadiusSqrd, mLineAlpha, mFillAlpha);
    if (bDrawParticles) mParticleController.draw();
    
    // Draw the interface
    mParams->draw();
}

CINDER_APP( ParticleLinesApp, RendererGl, [&]( App::Settings *settings ) {
    settings->setWindowSize( 1280, 720 );
})