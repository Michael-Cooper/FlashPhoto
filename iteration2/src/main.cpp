//
//  main.cpp
//  Originally created by the CSci-3081W TAs.
//


#include "FlashPhotoApp.h"
#include "ColorData.h"
// #include <stddef.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>
// #include <png.h>
// #include <zlib.h>

int main(int argc, char* argv[]) {
	FlashPhotoApp *app = new FlashPhotoApp(argc, argv, 800, 600, ColorData(1,1,0.95));
	// runMainLoop returns when the user closes the graphics window.
	app->runMainLoop();
	delete app;
	exit(0);
}
