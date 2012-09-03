#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);

private:
	Surface* surface_;
	gl::Texture* texture_;

	static const int width=800;
	static const int height=600;
};

void CatPictureApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(width,height);
	(*settings).setResizable(false);
}

void CatPictureApp::setup()
{
	surface_ = new Surface(width, height, false);
	texture_ = new gl::Texture(*surface_);
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	uint8_t* dataArray = (*surface_).getData();

	for(int i = 0;i<(*surface_).getWidth()*(*surface_).getHeight();i++){
		dataArray[3*i]= dataArray[3*i]*3;
		dataArray[3*i+1]=dataArray[3*i+1]++;
		dataArray[3*i+2]=2*dataArray[3*i+2];

		if(dataArray[3*i]>255)
			dataArray[3*i] = 1;
		if(dataArray[3*i+1]>255)
			dataArray[3*i+1] = 0;
		if(dataArray[3*i+2] > 255)
			dataArray[3*i+2] = 1;
	}

	(*texture_).update(*surface_,(*surface_).getBounds());
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::draw(*texture_); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
