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

	void drawRect(int x, int y, int width, int height, int red, int green, int blue, uint8_t* dataArray);
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

	drawRect(0,0, 100,100, 255, 0, 0, dataArray);

	(*texture_).update(*surface_,(*surface_).getBounds());
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::draw(*texture_); 
}

void CatPictureApp::drawRect(int x, int y, int width, int height, int red, int green, int blue, uint8_t* dataArray){
	for(int i = y; i<height; i++){
		for(int j = x; j<width; j++){
			dataArray[3*(j+i*(*surface_).getWidth())] = red;
			dataArray[3*(j+i*(*surface_).getWidth())+1] = green;
			dataArray[3*(j+i*(*surface_).getWidth())+2] = blue;
		}
	}
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
