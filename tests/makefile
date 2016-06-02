## A Makefile for tests
# Created by CSCI3081W Guru
# Copyright (c) CSCI3081W Guru. All rights reserved.

# Modified by chen4162

all: build test_initialize test_FlashPhoto_tool test_libphoto_filter test_valid_input_command test_invalid_input_command

UNAME = $(shell uname)
CC 		= g++
CFLAGS 	= -g -c -Wall
LDFLAGS = -g


ifeq ($(UNAME), Darwin) # Mac OSX
	LINK_LIBS += -framework glut -framework opengl
	EXECUTABLE = testFlashPhoto
else # LINUX
	LINK_LIBS +=  -lglut -lGL -lGLU
	EXECUTABLE = testFlashPhoto
endif


PHOTO = photo
GLUI = glui
PNG = png
JPEG = jpeg
FLASH = FlashPhoto
MIA = Mia
TESTFLASH = testFlashPhoto


PHOTO_PATH = ../libphoto
GLUI_PATH = ../glui
JPEG_PATH = ../jpeg-9a
PNG_PATH = ../libpng-1.6.16
FLASH_PATH = ../FlashPhoto
MIA_PATH = ../Mia
TESTFLASH_PATH = ../tests


REL_PATH = ../tests
IMG_PATH = ./images
REL_IMG = $(REL_PATH)/$(IMG_PATH)


FLASH_EXEC = $(FLASH_PATH)/$(FLASH)
MIA_EXEC = $(MIA_PATH)/$(MIA)
TESTFLASH_EXEC = $(TESTFLASH_PATH)/$(TESTFLASH)

PHOTO_LIB = $(PHOTO_PATH)/lib$(PHOTO).a
GLUI_LIB = $(GLUI_PATH)/lib/lib$(GLUI).a
PNG_LIB = $(PNG_PATH)/lib/lib$(PNG).a
JPEG_LIB = $(JPEG_PATH)/lib/lib$(JPEG).a


INCLUDE += -I$(PHOTO_PATH)/src
INCLUDE += -I$(GLUI_PATH)/include
INCLUDE += -I$(PNG_PATH)/include
INCLUDE += -I$(JPEG_PATH)/include
INCLUDE += -I$(FLASH_PATH)/src
INCLUDE += -I$(MIA_PATH)/src


OBJECT_DIR = object_files
SOURCE_DIR = src


LINK_LIBS +=  -L$(PHOTO_PATH)/ -l$(PHOTO)
LINK_LIBS +=  -L$(GLUI_PATH)/lib/ -l$(GLUI) -lglui -lpthread
LINK_LIBS +=  -L$(PNG_PATH)/lib/ -l$(PNG)
LINK_LIBS +=  -L$(JPEG_PATH)/lib/ -l$(JPEG)
LINK_LIBS +=  -lz


# Include nvidia drivers if necessary:
NVIDIA_LIB =  /usr/lib/nvidia-304 #or whichever nvidia number shows up in that dir
ifneq ($(NVIDIA_LIB), )
	LINK_LIBS += -L$(NVIDIA_LIB)
endif


OBJECTS = $(addprefix $(OBJECT_DIR)/,  $(FILENAMES:.cpp=.o))
CPPFILES = $(wildcard $(SOURCE_DIR)/*.cpp)
FILENAMES =  $(notdir $(CPPFILES))

build: setup $(EXECUTABLE)

rebuild: clean build

# Create the object_files directory only if it does not exist.
setup: | $(OBJECT_DIR)

$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)

$(EXECUTABLE): $(GLUI_LIB) $(PNG_LIB) $(JPEG_LIB) $(PHOTO_LIB) $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LINK_LIBS) -o $@

# Explicitly defined build targets because of dependancy on other header files
$(OBJECT_DIR)/testFlashPhoto.o: $(SOURCE_DIR)/testFlashPhoto.cpp $(SOURCE_DIR)/testFlashPhoto.h
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

# Pattern build targets
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.h
	#'Compiling arbitrary .cpp file with .h'
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	#'Compiling arbitrary .cpp file without .h'
	$(CC) $(CFLAGS) $(INCLUDE)  -o $@ $<

##############################################################
# Initialize the mia and testing executable files.
test_initialize: test_mia test_flashphoto

test_mia:
	@cd $(MIA_PATH); \
	make

test_flashphoto: $(EXECUTABLE) $(TESTFLASH_EXEC)
	./testFlashPhoto

#############################################################
# Test the FlashPhoto's interative tools.
test_FlashPhoto_tool: test_pentool test_spraytool test_erasertool test_calligraphytool test_highlightertool test_stampspecialtool test_blurtool

test_pentool: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/out20.png -compare $(REL_IMG)/std20.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_pen_tool"; echo; \
	else echo "PASS: test_pen_tool"; echo; \
	fi; \

test_spraytool: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/out21.png -compare $(REL_IMG)/std21.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_spraycan_tool"; echo; \
	else echo "PASS: test_spraycan_tool"; echo; \
	fi; \

test_erasertool: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/out22.png -compare $(REL_IMG)/std22.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_esaser_tool"; echo; \
	else echo "PASS: test_esaser_tool"; echo; \
	fi; \

test_calligraphytool: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/out23.png -compare $(REL_IMG)/std23.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_calligraphypen_tool"; echo; \
	else echo "PASS: test_calligraphypen_tool"; echo; \
	fi; \

test_highlightertool: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/out24.png -compare $(REL_IMG)/std24.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_highlighter_tool"; echo; \
	else echo "PASS: test_highlighter_tool"; echo; \
	fi; \

test_stampspecialtool: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/out26.png -compare $(REL_IMG)/std26.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_stamp_tool"; echo; \
	else echo "PASS: test_stamp_tool"; echo; \
	fi; \

test_blurtool: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/out27.png -compare $(REL_IMG)/std27.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_blur_tool"; echo; \
	else echo "PASS: test_blur_tool"; echo; \
	fi; \

####################################################
# Test the libphoto filters.
test_libphoto_filter: test_blurfilter test_sharpenfilter test_edgedetectionfilter test_thresholdfilter test_saturationfilter test_channelfilter test_quantizefilter test_grayscalefilter

test_blurfilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -blur 6.5 $(REL_IMG)/out0.png; \
	./Mia $(REL_IMG)/out0.png -compare $(REL_IMG)/std0.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_blur_filter"; echo; \
	else echo "PASS: test_blur_filter"; echo; \
	fi; \

test_sharpenfilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -sharpen 5 $(REL_IMG)/out1.png; \
	./Mia $(REL_IMG)/out1.png -compare $(REL_IMG)/std1.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_sharpen_filter"; echo; \
	else echo "PASS: test_sharpen_filter"; echo; \
	fi; \

test_edgedetectionfilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -edgedetect $(REL_IMG)/out2.png; \
	./Mia $(REL_IMG)/out2.png -compare $(REL_IMG)/std2.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_edgedetection_filter"; echo; \
	else echo "PASS: test_edgedetection_filter"; echo; \
	fi; \

test_thresholdfilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -thresh 0.5 $(REL_IMG)/out3.png; \
	./Mia $(REL_IMG)/out3.png -compare $(REL_IMG)/std3.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_threshold_filter"; echo; \
	else echo "PASS: test_threshold_filter"; echo; \
	fi; \

test_saturationfilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -saturate 3.5 $(REL_IMG)/out4.png; \
	./Mia $(REL_IMG)/out4.png -compare $(REL_IMG)/std4.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_saturation_filter"; echo; \
	else echo "PASS: test_saturation_filter"; echo; \
	fi; \

test_channelfilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -multrgb 2.0 5.0 8.0 $(REL_IMG)/out5.png; \
	./Mia $(REL_IMG)/out5.png -compare $(REL_IMG)/std5.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_channel_filter"; echo; \
	else echo "PASS: test_channel_filter"; echo; \
	fi; \

test_quantizefilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -quantize 5 $(REL_IMG)/out6.png; \
	./Mia $(REL_IMG)/out6.png -compare $(REL_IMG)/std6.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_quantize_filter"; echo; \
	else echo "PASS: test_quantize_filter"; echo; \
	fi; \

test_grayscalefilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -saturate 0 $(REL_IMG)/out7.png; \
	./Mia $(REL_IMG)/out7.png -compare $(REL_IMG)/std7.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_grayscale_filter"; echo; \
	else echo "PASS: test_grayscale_filter"; echo; \
	fi; \

###########################################################
# Test the command line parsing aspect of the mia.
# valid input
test_valid_input_command: test_helpcmd0 test_helpcmd1 test_jpgtopng test_singlefilter test_multiplefilters test_applyimgdir test_compare

test_helpcmd0: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia -h

test_helpcmd1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia -h error

test_jpgtopng: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.jpg $(REL_IMG)/out10.png; \
	./Mia $(REL_IMG)/out10.png -compare $(REL_IMG)/std10.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_valid_jpg_to_png_command"; echo; \
	else echo "PASS: test_valid_jpg_to_png_command"; echo; \
	fi; \

test_singlefilter: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -sharpen 8 $(REL_IMG)/out11.png; \
	./Mia $(REL_IMG)/out11.png -compare $(REL_IMG)/std11.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_valid_single_filter_command"; echo; \
	else echo "PASS: test_valid_single_filter_command"; echo; \
	fi; \

test_multiplefilters: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/in0.png -sharpen 8 -edgedetect $(REL_IMG)/out12.png; \
	./Mia $(REL_IMG)/out12.png -compare $(REL_IMG)/std12.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_valid_multiple_filters_command"; echo; \
	else echo "PASS: test_valid_multiple_filters_command"; echo; \
	fi; \

test_applyimgdir: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/dirin#.png -sharpen 8 $(REL_IMG)/dirout#.png; \
	./Mia $(REL_IMG)/dirout1.png -compare $(REL_IMG)/dirstd1.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_valid_apply_each_img_in_dir_command (#1)"; echo; \
	else echo "PASS: test_valid_apply_each_img_in_dir_command (#1)"; echo; \
	fi; \
	./Mia $(REL_IMG)/dirout2.png -compare $(REL_IMG)/dirstd2.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_valid_apply_each_img_in_dir_command (#2)"; echo; \
	else echo "PASS: test_valid_apply_each_img_in_dir_command (#2)"; echo; \
	fi; \
	./Mia $(REL_IMG)/dirout3.png -compare $(REL_IMG)/dirstd3.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_valid_apply_each_img_in_dir_command (#3)"; echo; \
	else echo "PASS: test_valid_apply_each_img_in_dir_command (#3)"; echo; \
	fi; \

# Test the compare command in mia.
test_compare: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; \
	./Mia $(REL_IMG)/std30.png -compare $(REL_IMG)/std31.png; \
	if [ $$? -eq 2 ]; \
	then echo "FAIL: test_valid_compare_command (#1)"; echo; \
	else echo "PASS: test_valid_compare_command (#1)"; echo; \
	fi; \
	./Mia $(REL_IMG)/std31.png -compare $(REL_IMG)/std32.png; \
	if [ $$? -eq 2 ]; \
	then echo "PASS: test_valid_compare_command (#2)"; echo; \
	else echo "FAIL: test_valid_compare_command (#2)"; echo; \
	fi; \

#######################################
# invalid input. All errors should be handled, exit(1) and output help message.
test_invalid_input_command: test_wrong1 test_jpgtopng1 test_blurfilter1 test_sharpenfilter1 test_edgedetectionfilter1 test_thresholdfilter1 test_saturationfilter1 test_channelfilter1 test_quantizefilter1 test_grayscalefilter1 test_multiplefilters1 test_imgdir1 test_compare1

test_wrong1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_general_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_general_command command (invalid input file)"; echo; echo; \
	fi; \

test_jpgtopng1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out40.jpg $(REL_IMG)/in40.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_jpg_to_png_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_jpg_to_png_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png error $(REL_IMG)/out41.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_jpg_to_png_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_jpg_to_png_command (invalid output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png $(REL_IMG)/out42.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_jpg_to_png_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_jpg_to_png_command (extra arguments)"; echo; echo; \
	fi; \

test_blurfilter1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out50.png -blur 6.5 $(REL_IMG)/in50.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_blur_filter_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_blur_filter_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -blur 6 $(REL_IMG)/out51.png; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_blur_filter_command (parameter is an integer)"; echo; echo; \
	else echo "PASS: test_invalid_blur_filter_command (parameter is an integer)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -blur 6.5; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_blur_filter_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_blur_filter_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -blur; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_blur_filter_command (no parameters or output file)"; echo; echo; \
	else echo "FAIL: test_invalid_blur_filter_command (no parameters or output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -blur 6.5 $(REL_IMG)/out52.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_blur_filter_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_blur_filter_command (extra arguments)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -blur 6.5 error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_blur_filter_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_blur_filter_command (invalid output file)"; echo; echo; \
	fi; \

test_sharpenfilter1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out60.png -sharpen 8 $(REL_IMG)/in60.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_sharpen_filter_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_sharpen_filter_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -sharpen 8.5 $(REL_IMG)/out61.png; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_sharpen_filter_command (parameter is a float)"; echo; echo; \
	else echo "PASS: test_invalid_sharpen_filter_command (parameter is a float)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -sharpen 8; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_sharpen_filter_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_sharpen_filter_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -sharpen; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_sharpen_filter_command (no parameters or output file)"; echo; echo; \
	else echo "FAIL: test_invalid_sharpen_filter_command (no parameters or output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -sharpen 8 $(REL_IMG)/out62.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_sharpen_filter_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_sharpen_filter_command (extra arguments)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -sharpen 8 error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_sharpen_filter_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_sharpen_filter_command (invalid output file)"; echo; echo; \
	fi; \

test_edgedetectionfilter1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out70.png -edgedetect $(REL_IMG)/in70.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_edgedetection_filter_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_edgedetection_filter_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -edgedetect error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_edgedetection_filter_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_edgedetection_filter_command (invalid output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -edgedetect; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_edgedetection_filter_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_edgedetection_filter_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -edgedetect $(REL_IMG)/out71.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_edgedetection_filter_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_edgedetection_filter_command (extra arguments)"; echo; echo; \
	fi; \

test_thresholdfilter1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out80.png -thresh 6.5 $(REL_IMG)/in80.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_threshold_filter_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_threshold_filter_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -thresh 6 $(REL_IMG)/out81.png; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_threshold_filter_command (parameter is an integer)"; echo; echo; \
	else echo "PASS: test_invalid_threshold_filter_command (parameter is an integer)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -thresh 6.5; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_threshold_filter_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_threshold_filter_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -thresh; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_threshold_filter_command (no parameters or output file)"; echo; echo; \
	else echo "FAIL: test_invalid_threshold_filter_command (no parameters or output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -thresh 6.5 $(REL_IMG)/out82.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_threshold_filter_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_threshold_filter_command (extra arguments)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -thresh 6.5 error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_threshold_filter_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_threshold_filter_command (invalid output file)"; echo; echo; \
	fi; \

test_saturationfilter1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out90.png -saturate 6.5 $(REL_IMG)/in90.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_saturation_filter_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_saturation_filter_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate 6 $(REL_IMG)/out91.png; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_saturation_filter_command (parameter is an integer)"; echo; echo; \
	else echo "PASS: test_invalid_saturation_filter_command (parameter is an integer)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate 6.5; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_saturation_filter_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_saturation_filter_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_saturation_filter_command (no parameters or output file)"; echo; echo; \
	else echo "FAIL: test_invalid_saturation_filter_command (no parameters or output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate 6.5 $(REL_IMG)/out92.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_saturation_filter_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_saturation_filter_command (extra arguments)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate 6.5 error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_saturation_filter_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_saturation_filter_command (invalid output file)"; echo; echo; \
	fi; \

test_channelfilter1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/in1.png -multrgb 2.0 $(REL_IMG)/out100.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_channel_filter_command (miss two parameters)"; echo; echo; \
	else echo "FAIL: test_invalid_channel_filter_command (miss two parameters)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -multrgb 2.0 5.0 $(REL_IMG)/out101.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_channel_filter_command (miss one parameter)"; echo; echo; \
	else echo "FAIL: test_invalid_channel_filter_command (miss one parameter)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/out102.png -multrgb 2.0 5.0 8.0 $(REL_IMG)/in102.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_channel_filter_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_channel_filter_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -multrgb 2 5 8 $(REL_IMG)/out103.png; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_channel_filter_command (parameters are integers)"; echo; echo; \
	else echo "PASS: test_invalid_channel_filter_command (parameters are integers)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -multrgb 2.0 5.0 8.0; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_channel_filter_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_channel_filter_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -multrgb; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_channel_filter_command (no parameters or output file)"; echo; echo; \
	else echo "FAIL: test_invalid_channel_filter_command (no parameters or output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -multrgb 2.0 5.0 8.0 $(REL_IMG)/out104.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_channel_filter_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_channel_filter_command (extra arguments)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -multrgb 2.0 5.0 8.0 error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_channel_filter_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_channel_filter_command (invalid output file)"; echo; echo; \
	fi; \

test_quantizefilter1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out110.png -quantize 5 $(REL_IMG)/in110.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_quantize_filter_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_quantize_filter_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -quantize 5.5 $(REL_IMG)/out111.png; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_quantize_filter_command (parameter is a float)"; echo; echo; \
	else echo "PASS: test_invalid_quantize_filter_command (parameter is a float)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -quantize 5; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_quantize_filter_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_quantize_filter_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -quantize; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_quantize_filter_command (no parameters or output file)"; echo; echo; \
	else echo "FAIL: test_invalid_quantize_filter_command (no parameters or output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -quantize 5 $(REL_IMG)/out112.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_quantize_filter_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_quantize_filter_command (extra arguments)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -quantize 5 error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_quantize_filter_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_quantize_filter_command (invalid output file)"; echo; echo; \
	fi; \

test_grayscalefilter1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out120.png -saturate 0.0 $(REL_IMG)/in120.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_grayscale_filter_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_grayscale_filter_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate 0 $(REL_IMG)/out121.png; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_grayscale_filter_command (parameter is an integer)"; echo; echo; \
	else echo "PASS: test_invalid_grayscale_filter_command (parameter is an integer)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate 0.0; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_grayscale_filter_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_grayscale_filter_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_grayscale_filter_command (no parameters or output file)"; echo; echo; \
	else echo "FAIL: test_invalid_grayscale_filter_command (no parameters or output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate 0.0 $(REL_IMG)/out122.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_grayscale_filter_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_grayscale_filter_command (extra arguments)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -saturate 0.0 error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_grayscale_filter_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_grayscale_filter_command (invalid output file)"; echo; echo; \
	fi; \

test_multiplefilters1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/out130.png -sharpen 8 -edgedetect $(REL_IMG)/in130.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_multiple_filters_command (invalid input file)"; echo; echo; \
	else echo "FAIL: test_invalid_multiple_filters_command (invalid input file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png 8 -edgedetect $(REL_IMG)/out132.png; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_multiple_filters_command (miss the first filter)"; echo; echo; \
	else echo "FAIL: test_invalid_multiple_filters_command (miss the first filter)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -sharpen 8 -edgedetect; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_multiple_filters_command (no output file)"; echo; echo; \
	else echo "FAIL: test_invalid_multiple_filters_command (no output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in1.png -sharpen 8 -edgedetect error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_multiple_filters_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_multiple_filters_command (invalid output file)"; echo; echo; \
	fi; \


test_imgdir1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/in#.png -sharpen error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_apply_each_img_in_dir_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_apply_each_img_in_dir_command (invalid output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in#.png -sharpen; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_apply_each_img_in_dir_command (no parameters or output file)"; echo; echo; \
	else echo "FAIL: test_invalid_apply_each_img_in_dir_command (no parameters or output file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in#.png -sharpen 8 $(REL_IMG)/out#.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_apply_each_img_in_dir_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_apply_each_img_in_dir_command (extra arguments)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/in#.png -sharpen 8 error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_apply_each_img_in_dir_command (invalid output file)"; echo; echo; \
	else echo "FAIL: test_invalid_apply_each_img_in_dir_command (invalid output file)"; echo; echo; \
	fi; \

test_compare1: $(MIA_EXEC) test_mia
	@cd $(MIA_PATH); echo; echo; \
	./Mia $(REL_IMG)/std30.png -compare error; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_compare_command (invalid second file)"; echo; echo; \
	else echo "FAIL: test_invalid_compare_command (invalid second file)"; echo; echo;\
	fi; \
	./Mia $(REL_IMG)/std30.png -compare; \
	if [ $$? -eq 1 ]; \
	then echo "PASS: test_invalid_compare_command (no second file)"; echo; echo; \
	else echo "FAIL: test_invalid_compare_command (no second file)"; echo; echo; \
	fi; \
	./Mia $(REL_IMG)/std30.png -compare $(REL_IMG)/std31.png error; \
	if [ $$? -eq 1 ]; \
	then echo "FAIL: test_invalid_compare_command (extra arguments)"; echo; echo; \
	else echo "PASS: test_invalid_compare_command (extra arguments)"; echo; echo; \
	fi; \

#############################################################
clean:
	\rm -rf $(OBJECT_DIR) $(EXECUTABLE)

cleanall: clean cleanglui cleanjpeg cleanpng

cleanglui:
	$(MAKE)  -C ./$(GLUI_PATH)/ clean

cleanjpeg:
	$(MAKE) -C ./$(JPEG_PATH) distclean
	cd $(JPEG_PATH); \
	rm -rf lib bin include share

cleanpng:
	$(MAKE) -C ./$(PNG_PATH) distclean
	cd $(PNG_PATH); \
	rm -rf lib bin include share

$(PHOTO_LIB):
	$(MAKE) -C $(PHOTO_PATH) all

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
