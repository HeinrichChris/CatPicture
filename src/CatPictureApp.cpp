// Added some comments to your code but still need to be commented more
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
	/** added a variable to get rid of the multiplication in your for loop
	  * declaration. This removes having to use the (*surface_).getWidth() and 
	  * the (*surface_).getHeight() calls. */
	static const int surfaceLength = width*height;

	void drawRect(int x, int y, int width, int height, int red, int green, int blue, uint8_t* dataArray);
	void tint(int red, int green, int blue, uint8_t* dataArray);
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

	// initialize red, green, and blue to the current color of the dataArray
	int red = dataArray[0];
	int green = dataArray[1];
	int blue = dataArray[2];

	// change each color by the previous color updated by some factor
	for(int i = 0;i<surfaceLength;i++){ //removed the .getWidth() and .getHeight() and replaced it with surfaceLength
		red = red*3;
		green = green++;
		blue = blue*2;

		// check for each color to be below 255
		if(red>255)
			red = 1;
		if(green>255)
			green = 0;
		if(blue > 255)
			blue = 1;
	}

	drawRect(0,0,width/2, height/2, 255-red, 255-green, 255-blue, dataArray); //replaced (*surface_).getWidth() with width/2 and (*surface_).getHeight() with height/2
	tint(50, 10, 25, dataArray);
	(*texture_).update(*surface_,(*surface_).getBounds());
}

void CatPictureApp::draw()
{
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

void CatPictureApp::tint(int red, int green, int blue, uint8_t* dataArray){
	for(int i = 0; i<surfaceLength;i++){ //did the same thing in the update for loop
		dataArray[3*i] += red;
		dataArray[3*i+1] += green;
		dataArray[3*i+2] += blue;

		if(dataArray[3*i] > 255)
			dataArray[3*i] = 255;
		if(dataArray[3*i+1] > 255)
			dataArray[3*i+1] = 255;
		if(dataArray[3*i+2] > 255)
			dataArray[3*i+2] = 255;
	}
}
CINDER_APP_BASIC( CatPictureApp, RendererGl )
