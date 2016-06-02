# Created by CSCI3081W Guru
# Copyright (c) CSCI3081W Guru. All rights reserved.

UNAME = $(shell uname)
CC 		= g++
CFLAGS 	= -g -c -Wall
LDFLAGS = -g



ifeq ($(UNAME), Darwin) # Mac OSX
	LINK_LIBS += -framework glut -framework opengl
	EXECUTABLE = FlashPhoto
else # LINUX
	LINK_LIBS +=  -lglut -lGL -lGLU
	EXECUTABLE = FlashPhoto
endif

PHOTO = photo
GLUI = glui
PNG = png
JPEG = jpeg


PHOTO_PATH = ./libphoto
GLUI_PATH = ./glui
JPEG_PATH = ./jpeg-9a
PNG_PATH = ./libpng-1.6.16
FLASHPHOTO_PATH = ./FlashPhoto
MIA_PATH = ./Mia
TEST_PATH = ./tests

FLASHPHOTO = $(FLASHPHOTO_PATH)/FlashPhoto
MIA = $(MIA_PATH)/Mia
TEST = $(TEST_PATH)/tests

PHOTO_LIB = $(PHOTO_PATH)/lib$(PHOTO).a
GLUI_LIB = $(GLUI_PATH)/lib/lib$(GLUI).acd
PNG_LIB = $(PNG_PATH)/lib/lib$(PNG).a
JPEG_LIB = $(JPEG_PATH)/lib/lib$(JPEG).a

INCLUDE += -I$(PHOTO_PATH)/src
INCLUDE += -I$(GLUI_PATH)/include
INCLUDE += -I$(PNG_PATH)/include
INCLUDE += -I$(JPEG_PATH)/include


OBJECT_DIR = object_files
SOURCE_DIR = src

LINK_LIBS +=  -L$(PHOTO_PATH)/ -l$(PHOTO)
LINK_LIBS +=  -L$(GLUI_PATH)/lib/ -l$(GLUI) -lglui -lpthread
LINK_LIBS +=  -L$(PNG_PATH)/lib/ -l$(PNG)
LINK_LIBS +=  -L$(JPEG_PATH)/lib/ -l$(JPEG)
LINK_LIBS +=  -lz


# Include nvidia drivers if necessary:
#NVIDIA_LIB =  /usr/lib/nvidia-304 #or whichever nvidia number shows up in that dir
ifneq ($(NVIDIA_LIB), )
	LINK_LIBS += -L$(NVIDIA_LIB)
endif

all: setup $(FLASHPHOTO) $(MIA) $(TEST) $(Doc)

rebuild: clean build

# Create the object_files directory only if it does not exist.
setup: | $(OBJECT_DIR)

$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)

$(FLASHPHOTO): $(GLUI_LIB) $(PNG_LIB) $(JPEG_LIB) $(LIBPHOTO_LIB)
	$(MAKE) -C $(FLASHPHOTO_PATH)

$(MIA): $(GLUI_LIB) $(PNG_LIB) $(JPEG_LIB) $(LIBPHOTO_LIB)
	$(MAKE) -C $(MIA_PATH)

$(TEST): 
	$(MAKE) -C $(TEST_PATH)

$(Doc): 
	doxygen Doxyfile	
	

# Pattern build targets
$(OBJECT_DIR)/FlashPhoto.o: $(SOURCE_DIR)/FlashPhoto.cpp $(SOURCE_DIR)/FlashPhoto.h
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.h
	#'Compiling arbitrary .cpp file with .h'
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	#'Compiling arbitrary .cpp file without .h'
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

clean:
	$(MAKE)  -C ./FlashPhoto clean
	$(MAKE)  -C ./Mia clean
	$(MAKE)  -C ./tests clean

cleanall: clean cleanglui cleanjpeg cleanpng cleanphoto cleanflashphoto cleanmia 

cleanglui:
	$(MAKE)  -C ./$(GLUI_PATH)/ clean

cleanphoto:
	$(MAKE)  -C ./$(PHOTO_PATH)/ clean

cleanjpeg:
	$(MAKE) -C ./$(JPEG_PATH) distclean
	cd $(JPEG_PATH); \
	rm -rf lib bin include share

cleanpng:
	$(MAKE) -C ./$(PNG_PATH) distclean
	cd $(PNG_PATH); \
	rm -rf lib bin include share

cleanflashphoto:
	$(MAKE)  -C ./$(FlASHPHOTO_PATH)/ clean

cleanmia:
	$(MAKE)  -C ./$(MIA_PATH)/ clean

$(PHOTO_LIB):
	$(MAKE) -C $(PHOTO_PATH)

$(GLUI_LIB):
	$(MAKE) -C $(GLUI_PATH) all

$(PNG_LIB):
	cd $(PNG_PATH); \
	./configure --enable-shared=no  --prefix=$(abspath $(PNG_PATH))
	$(MAKE) -C $(PNG_PATH)
	$(MAKE) -C $(PNG_PATH) check
	$(MAKE) -C $(PNG_PATH) install

$(JPEG_LIB):
	cd $(JPEG_PATH); \
	./configure --enable-shared=no --prefix=$(abspath $(JPEG_PATH))
	$(MAKE) -C $(JPEG_PATH)
	$(MAKE) -C $(JPEG_PATH) check
	$(MAKE) -C $(JPEG_PATH) install

doc:
	doxygen
