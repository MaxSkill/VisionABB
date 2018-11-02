
#include "wtypes.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "lib/cvui.h"
#include "lib/EnhancedWindow.h"
#define wFILTER "FILTER"
#define wMain "VISION ONES"
#define WINDOW3_NAME "Windows 3"
#define WINDOW4_NAME "Windows 4"
using namespace cv;
bool selectObject = false;
Rect selection;
Point origin;
int trackObject = 0;
Mat image;
int valCCD1 = 0;
int valCCD2 = 0;
int valCCD3 = 0;
int valCCD4 = 0;
int valCCD5 = 0;
int valCCD6 = 0;
int tvalCCD1 = 0;
int tvalCCD2 = 0;
int tvalCCD3 = 0;
int tvalCCD4 = 0;
int tvalCCD5 = 0;
int tvalCCD6 = 0;
bool ckRGB = false;
bool tckRGB = false;
bool ck11 = false;
bool ck12 = false;
bool ck21 = false;
bool ck22 = false;
bool c31 = false;
bool ck32 = false;
bool ck41 = false;
bool ck42= false;
bool ck6 = false;
bool blFilter = false;
bool blRun = false;
double szRectX = 0;
double szRectY = 0;
double szKenelX = 0;
double szKenelY = 0;
double szBlurX = 0;
double szBlurY = 0;
double typeBinary = 1;
double minBinary =0;
cv::Point anchors[3]; // one anchor for each mouse button
cv::Rect rois[3]; // one ROI for each mouse button
unsigned int colors[] = { 0xff0000, 0x00ff00, 0x0000ff };
int xBlur =100;
int yBlur = 50;
int xBinary = 100;
int yBinary = 100;
int xCanny = 100;
int yCanny = 120;
EnhancedWindow grBlur(xBlur, yBlur + 20, 200, 300, "Clear Blob", true, true, true);
EnhancedWindow grbinary(xBlur, xBlur + 40, 200, 280, "Binary", true, false, true);
EnhancedWindow grcanny(xBlur, yBlur + 60, 200, 260, "Canny", true, false, true);
int xCropArea = 100;
int yCropArea = 80;
int xCropTrigger = 100;
int yCropTrigger = 100;
int xSampling = 100;
int ySampling = 120;
EnhancedWindow grCropArea(xCropArea, yCropArea + 20, 200, 300, "Crop Area", true, true, true);
EnhancedWindow grCropTrigger(xCropArea, yCropArea + 40, 200, 280, "Crop  Trigger", true, false, true);
EnhancedWindow grSampling(xCropArea, yCropArea + 60, 200, 260, "Sampling", true, false, true);
EnhancedWindow grContour(xCropArea, yCropArea + 80, 200, 240, "Contour", true, false, true);

bool blSetting = true;
bool blTool = false;
bool blCom= false;
bool blResut = false;
String textIntput="";
Mat frFilter = cv::Mat(350, 200, CV_8UC3);

VideoCapture cap(1);
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
void fFilter(const cv::String& name) {
	//Mat imghow;
	//image.copyTo(imghow);
	//cvui::context(name);
	
	//if (cvui::button(image, 110, 90, "Setting CCD")) {
	//	blSetting = !blSetting;
	//	cvui::printf(image, 200, 95, "Button clicked!");
	//	std::cout << "Button clicked on: " << name << std::endl;
	//}

	// Tell cvui to update its internal structures regarding a particular window.
	//
	// If cvui is being used in multiple windows, you need to enclose all component
	// calls between the pair cvui::context(NAME)/cvui::update(NAME), where NAME is
	// the name of the window being worked on.
	//if (blSetting == true)
	//{
		//cvui::checkbox()
	
	/*	settings.begin(frFilter);
	if (!settings.isMinimized()) {
		cvui::checkbox("RGB", &ckRGB);
		cvui::space(5);
		cvui::text("Brightness ");
		cvui::space(10); // add 10px of space between UI components
		cvui::trackbar(settings.width() - 20, &valCCD1, 0, 255);
		cvui::space(10);
		
		cvui::text("CONTRAST ");
		cvui::space(10); // add 10px of space between UI components
		cvui::trackbar(settings.width() - 20, &valCCD2, 0, 255);
		
		cvui::space(10);
		cvui::text("SATURATION ");
		cvui::space(10); // add 10px of space between UI components
		cvui::trackbar(settings.width() - 20, &valCCD3, 0, 255);
		
		cvui::space(10);
		cvui::text("HUE");
		cvui::space(10); // add 10px of space between UI components
		cvui::trackbar(settings.width() - 20, &valCCD4, 0, 255);
		
		cvui::space(10);
		cvui::text("GAIN");
		cvui::space(10); // add 10px of space between UI components
		cvui::trackbar(settings.width() - 20, &valCCD5, 0, 255);
		
		cvui::space(10);
		cvui::text("EXPOSURE");
		cvui::space(10); // add 10px of space between UI components
		cvui::trackbar(settings.width() - 20, &valCCD6, -5, 5);		

		cvui::space(10);
		cvui::text("EXPOSURE");
		cvui::space(10); // add 10px of space between UI components
		cvui::trackbar(settings.width() - 20, &valCCD6, -5, 5);
		settings.end();*/
		cvui::update(name);
		cvui::imshow(name, frFilter);
		//cap.set(CV_CAP_PROP_AUTO_EXPOSURE, false);
	
		//cap.set(CV_CAP_PROP_AUTOFOCUS, 0)
	//}
	

}

// Update and show a window in a single call using cvui::imshow().
void compact(const cv::String& name) {
	// Create a frame for this window and fill it with a nice color
	cv::Mat frame = cv::Mat(200, 500, CV_8UC3);
	frame = cv::Scalar(255, 255, 255);

	// Inform cvui that the components to be rendered from now one belong to
	// a window in particular.
	//
	// If you don't inform that, cvui will assume the components belong to
	// the default window (informed in cvui::init()). In that case, the
	// interactions with all other windows being used will not work.
	cvui::context(name);

	cvui::printf(frame, 110, 50, "%s - click the button", name.c_str());
	if (cvui::button(frame, 110, 90, "Button")) {
		cvui::printf(frame, 200, 95, "Button clicked!");
		std::cout << "Button clicked on: " << name << std::endl;
	}

	// Tell cvui to update its internal structures regarding a particular window
	// then show it. Below we are using cvui::imshow(), which is cvui's version of
	// the existing cv::imshow(). They behave exactly the same, the only difference
	// is that cvui::imshow() will automatically call cvui::update(name) for you.
	
	cvui::imshow(name, frame);
}
Mat frame;

void Filter( Mat frame)
{
	if (blFilter == true)
	{
		
		grcanny.begin(frame);
		if (!grcanny.isMinimized()) {
			cvui::beginRow(-1, -1, 50);
			cvui::checkbox("view", &ck21, 0x1cbaf6);
			cvui::checkbox("using", &ck22);//, 0xff0000);
			cvui::endRow();
			cvui::space(10);
			cvui::text("Size Close", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szRectX, 1, "%.0f");
			cvui::counter(&szRectY, 1, "%.0f");
			cvui::endRow();
			//
		}
		grcanny.end();
		grbinary.begin(frame);
		if (!grbinary.isMinimized()) {
			cvui::beginRow(-1, -1, 50);
			//cvui::text("");
			//cvui::space(1);
			cvui::checkbox("view", &ck21, 0x1cbaf6);
			cvui::checkbox("using", &ck22);//, 0xff0000);
			cvui::endRow();
			cvui::space(10);
			cvui::beginColumn(-1, -1, 6);
			cvui::text("Type", 0.5, 0x148ae3);
			cvui::trackbar(180, &typeBinary, 1., 4., 2, "%.0Lf", cvui::TRACKBAR_DISCRETE | cvui::TRACKBAR_HIDE_SEGMENT_LABELS, 1.0);
			cvui::text("Value Min", 0.5, 0x148ae3);
			cvui::trackbar(180, &minBinary, 0., 255., 1, "%.0Lf", cvui::TRACKBAR_DISCRETE | cvui::TRACKBAR_HIDE_SEGMENT_LABELS, 1.0);
			cvui::endColumn();
		}
		grbinary.end();
		grBlur.begin(frame);
		if (!grBlur.isMinimized()) {
			cvui::beginRow(-1, -1, 50);
			//cvui::space(1);
			cvui::checkbox("view", &ck11, 0x1cbaf6);
			cvui::checkbox("using", &ck12);//, 0xff0000);
			cvui::endRow();

			cvui::space(10);
			cvui::text("Size Rec", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szRectX, 1, "%.0f");
			cvui::counter(&szRectY, 1, "%.0f");
			cvui::endRow();
			//
			cvui::space(10);
			cvui::text("Size Kenel", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szKenelX, 1, "%.0f");
			cvui::counter(&szKenelY, 1, "%.0f");
			cvui::endRow();
			//
			cvui::space(10);
			cvui::text("Size Blur", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szBlurX, 1, "%.0f");
			cvui::counter(&szBlurY, 1, "%.0f");
			cvui::endRow();
		}
		grBlur.end();
		
	}
}
void Tool(Mat frame)
{
	if (blTool == true)
	{
		
		grContour.begin(frame);
		if (!grContour.isMinimized()) {
			cvui::beginRow(-1, -1, 50);
			cvui::checkbox("view", &ck21, 0x1cbaf6);
			cvui::checkbox("using", &ck22);//, 0xff0000);
			cvui::endRow();
			cvui::space(10);
			cvui::text("Size Close", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szRectX, 1, "%.0f");
			cvui::counter(&szRectY, 1, "%.0f");
			cvui::endRow();
			//
		}
		grContour.end();
		grSampling.begin(frame);
		if (!grSampling.isMinimized()) {
			cvui::beginRow(-1, -1, 50);
			//cvui::text("");
			//cvui::space(1);
			cvui::checkbox("view", &ck21, 0x1cbaf6);
			cvui::checkbox("using", &ck22);//, 0xff0000);
			cvui::endRow();
			cvui::space(10);
			cvui::beginColumn(-1, -1, 6);
			cvui::text("Type", 0.5, 0x148ae3);
			cvui::trackbar(180, &typeBinary, 1., 4., 2, "%.0Lf", cvui::TRACKBAR_DISCRETE | cvui::TRACKBAR_HIDE_SEGMENT_LABELS, 1.0);
			cvui::text("Value Min", 0.5, 0x148ae3);
			cvui::trackbar(180, &minBinary, 0., 255., 1, "%.0Lf", cvui::TRACKBAR_DISCRETE | cvui::TRACKBAR_HIDE_SEGMENT_LABELS, 1.0);
			cvui::endColumn();
		}
		grSampling.end();
		grCropTrigger.begin(frame);
		if (!grCropTrigger.isMinimized()) {
			cvui::beginRow(-1, -1, 50);
			//cvui::space(1);
			cvui::checkbox("view", &ck11, 0x1cbaf6);
			cvui::checkbox("using", &ck12);//, 0xff0000);
			cvui::endRow();

			cvui::space(10);
			cvui::text("Size Rec", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szRectX, 1, "%.0f");
			cvui::counter(&szRectY, 1, "%.0f");
			cvui::endRow();
			//
			cvui::space(10);
			cvui::text("Size Kenel", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szKenelX, 1, "%.0f");
			cvui::counter(&szKenelY, 1, "%.0f");
			cvui::endRow();
			//
			cvui::space(10);
			cvui::text("Size Blur", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szBlurX, 1, "%.0f");
			cvui::counter(&szBlurY, 1, "%.0f");
			cvui::endRow();
		}
		grCropTrigger.end();
		grCropArea.begin(frame);
		if (!grCropArea.isMinimized()) {
			cvui::beginRow(-1, -1, 50);
			cvui::checkbox("view", &ck21, 0x1cbaf6);
			cvui::checkbox("using", &ck22);//, 0xff0000);
			cvui::endRow();
			cvui::space(10);
			cvui::text("Size Close", 0.4, 0x8ccbfb);
			cvui::space(10);
			cvui::beginRow(-1, -1, 90);
			cvui::text("with", 0.3, 0xb2a6a6);
			cvui::text("height", 0.3, 0xb2a6a6);
			cvui::endRow();
			cvui::space(5);
			cvui::beginRow(-1, -1, 5);
			cvui::counter(&szRectX, 1, "%.0f");
			cvui::counter(&szRectY, 1, "%.0f");
			cvui::endRow();
			//
		}
		grCropArea.end();
	}
}
void SetLocation()
{
	
	xBlur = grBlur.X();
	yBlur = grBlur.Y();
	grbinary.setX(xBlur);
	grbinary.setY(yBlur + 20);
	grcanny.setX(xBlur);
	grcanny.setY(yBlur + 40);
}
void Comunication(Mat frame,int x,int y,int w, int h)
{
	
	cvui::window(frame, x, y, w, h, "Comunication");
	cvui::text(frame, x+10, y + 30, "IP Address", 0.36, 0xb2a6a6);
	cvui::text(frame, x + 80, y + 30, "192.168.1.99:1025", 0.4, 0x0b9bf2);
	cvui::button(frame, x + 220, y + 25,60, 20, "SCAN");
}
std::string s("empty");
void on_mouse_click(int event, int x, int y, int, void*)
{
	if (event == EVENT_LBUTTONDOWN)    //are you missing this?
	{
		std::cout << "enter string: ";
		std::cin >> s;
	}
}
int main(int argc, const char *argv[])
{
	int height = 0;
	int with = 0;
	GetDesktopResolution(with, height);
	const cv::String windows[] = { wMain, wFILTER , WINDOW3_NAME, WINDOW4_NAME };
	cvui::init(wMain);
	moveWindow(wMain, 0, 0);
	//cvNamedWindow(WINDOW1_NAME, CV_WINDOW_NORMAL);
	//cvSetWindowProperty(WINDOW1_NAME, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	int h = 0;
	int w = 0;
	while (true) {
		frFilter = cv::Scalar(255, 255, 255);
		if (blSetting == true)
		{
			cap >> frame;
			if (frame.empty())
				break;
			//blSetting = false;
			frame.copyTo(image);
		}
		cv::resize(image, image, cv::Size(with, height), 0, 0, CV_INTER_LINEAR);
		cvui::context(wMain);
		
		if (cvui::button(image, 110, 0, 100, 30, "OFFLINE")) {
		
		}
		if (blRun==true)
		if (cvui::button(image, 0, 0,100,30, "RUN")) {
			blRun = false;
			goto X;
		}
		if (blRun == false)
		if (cvui::button(image, 0, 0,100, 30, "EDITOR")) {
		
			blRun = true;
		}
	X:
		if (blRun == false)
		{

			if (cvui::button(image, 0, 40, 100, 30, "CCD SETTING")) {
				cap.set(CV_CAP_PROP_SETTINGS, 1);
			}
			if (cvui::button(image, 0, 70, 100, 30, "FILTER")) {
				blFilter = !blFilter;
				blTool = false;
			}
			if (cvui::button(image, 0, 100, 100, 30, "TOOL")) {
				blTool = !blTool;
				blFilter = false;
			}
			if (cvui::button(image, 0, 130, 100, 30, "COMMUNICATION")) 
			{
				blCom = !blCom;
			}
			if (cvui::button(image, 0, 160, 100, 30, "RESULT")) {
			
			}
			Tool(image);
			if (blCom == true)Comunication(image, 100, 130, 300, 500);
			if (blFilter == true)
			{
				//
				Filter(image);
				SetLocation();
			}
		}
		//cvui::image(image, 50, 50, frFilter);
		
			cvui::update(wMain);
		
		cv::imshow(wMain, image);		
			//cvui::update(wFILTER);
			//cv::imshow(wFILTER, frFilter);
		
		/*grBlur.begin(frFilter);
		if (!grBlur.isMinimized()) {
			cvui::text("Clear Blob", 0.5, 0x148ae3);
			cvui::checkbox("view", &ck1);//, 0xff0000);
		/*cvui::text(frFilter, 10, 10, "Clear Blob", 0.5, 0x148ae3);
		cvui::checkbox(frFilter, 140, 10, "view", &ck1);//, 0xff0000);
		cvui::text(frFilter, 20, 40, "Size Rec", 0.4, 0x8ccbfb);
		cvui::counter(frFilter, 90, 40, &szRectX,1, "%.1f");
		cvui::counter(frFilter, 90, 65, &szRectY, 1, "%.1f");
		///+60
		cvui::text(frFilter, 20, 100, "Size Kenel", 0.4, 0x8ccbfb);
		cvui::counter(frFilter, 90, 100, &szRectX, 1, "%.1f");
		cvui::counter(frFilter, 90, 125, &szRectY, 1, "%.1f");
		///+60
		cvui::text(frFilter, 20, 160, "Size Blur", 0.4, 0x8ccbfb);
		cvui::counter(frFilter, 90, 160, &szRectX, 1, "%.1f");
		cvui::counter(frFilter, 90, 185, &szRectY, 1, "%.1f");
		grBlur.end();
		//cvui::update(wFILTER);
		
		}*/
		
	/*	cvui::beginColumn(frFilter, 20, 240, -1, -1, 6);
		cvui::text(frFilter, 10, 220, "Binary", 0.5, 0x148ae3);
		//cvui::trackbar(width, &doubleValue3, 0., 4., 2, "%.2Lf", cvui::TRACKBAR_DISCRETE, 0.25);
		cvui::trackbar(180, &typeBinary, 1., 4., 2, "%.0Lf", cvui::TRACKBAR_DISCRETE | cvui::TRACKBAR_HIDE_SEGMENT_LABELS, 1.0);
		cvui::endColumn();
		//cvui::trackbar(frFilter, 20, 230, 180, &szRectY, 1., 4., 2, "%.0f", cvui::TRACKBAR_DISCRETE, 1);
		cvui::update(wFILTER);*/
		//cv::imshow(wFILTER, frFilter);
		
		//fFilter(wFILTER);
		//int w = 1200; int h = 800;
		//cv::resize(image, image, cv::Size(w, h), 0, 0, CV_INTER_LINEAR);
	/*	for (int button = cvui::LEFT_BUTTON; button <= cvui::RIGHT_BUTTON; button++) {
			// Get the anchor, ROI and color associated with the mouse button
			cv::Point& anchor = anchors[button];
			cv::Rect& roi = rois[button];
			unsigned int color = colors[button];

			// The function "bool cvui::mouse(int button, int query)" allows you to query a particular mouse button for events.
			// E.g. cvui::mouse(cvui::RIGHT_BUTTON, cvui::DOWN)
			//
			// Available queries:
			//	- cvui::DOWN: mouse button was pressed. cvui::mouse() returns true for single frame only.
			//	- cvui::UP: mouse button was released. cvui::mouse() returns true for single frame only.
			//	- cvui::CLICK: mouse button was clicked (went down then up, no matter the amount of frames in between). cvui::mouse() returns true for single frame only.
			//	- cvui::IS_DOWN: mouse button is currently pressed. cvui::mouse() returns true for as long as the button is down/pressed.

			// Did the mouse button go down?
			if (cvui::mouse(button, cvui::DOWN)) {
				// Position the anchor at the mouse pointer.
				anchor.x = cvui::mouse().x;
				anchor.y = cvui::mouse().y;
			}

			// Is any mouse button down (pressed)?
			if (cvui::mouse(button, cvui::IS_DOWN)) {
				// Adjust roi dimensions according to mouse pointer
				int width = cvui::mouse().x - anchor.x;
				int height = cvui::mouse().y - anchor.y;

				roi.x = width < 0 ? anchor.x + width : anchor.x;
				roi.y = height < 0 ? anchor.y + height : anchor.y;
				roi.width = std::abs(width);
				roi.height = std::abs(height);

				// Show the roi coordinates and size
				cvui::printf(image, roi.x + 5, roi.y + 5, 0.3, color, "(%d,%d)", roi.x, roi.y);
				cvui::printf(image, cvui::mouse().x + 5, cvui::mouse().y + 5, 0.3, color, "w:%d, h:%d", roi.width, roi.height);
			}

			// Ensure ROI is within bounds
			roi.x = roi.x < 0 ? 0 : roi.x;
			roi.y = roi.y < 0 ? 0 : roi.y;
			roi.width = roi.x + roi.width > image.cols ? roi.width + image.cols - (roi.x + roi.width) : roi.width;
			roi.height = roi.y + roi.height > image.rows ? roi.height + image.rows - (roi.y + roi.height) : roi.height;

			// If the ROI is valid, render it in the frame and show in a window.
			if (roi.area() > 0) {
				cvui::rect(image, roi.x, roi.y, roi.width, roi.height, color);
				cvui::printf(image, roi.x + 5, roi.y - 10, 0.3, color, "Area %d", button);

				cv::imshow("ROI button" + std::to_string(button), frame(roi));
			}
		}
		cvui::update();
		cv::imshow(WINDOW1_NAME, image);
		if (selectObject && selection.width > 0 && selection.height > 0)
		{
			Mat roi(image, selection);
			bitwise_not(roi, roi);


			printf("%d %d %d %d\n", selection.x, selection.y, selection.width, selection.height);
		}
		*/
		if (selection.width > 0 && selection.height > 0)
			rectangle(image, selection, cv::Scalar(255, 0, 0));
		// The functions below will update a window and show them using cv::imshow().
		// In that case, you must call the pair cvui::context(NAME)/cvui::update(NAME)
		// to render components and update the window.
	//	window(WINDOW1_NAME);
		//window(WINDOW2_NAME);
		//window(WINDOW3_NAME);

		// The function below will do the same as the funcitons above, however it will
		// use cvui::imshow() (cvui's version of cv::imshow()), which will automatically
		// call cvui::update() for us.
		//compact(WINDOW4_NAME);

		// Check if ESC key was pressed
		char c;
		c = waitKey(30);
		if (c !=-1)
		{
						textIntput += c;
			std::cout << textIntput;
		}
		if (cv::waitKey(30) == 27) {

			break;
		}
		//std::cout << s;
	}

	return 0;
}
