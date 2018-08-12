CXX = g++
INC := -I$(CURDIR) $(INCLUDE_DIRS)
COMPONENT_NAME := mytests
CXXFLAGS = -Wall -Winline -Werror -pipe -std=c++11
BUILDDIR = $(PROJ_ROOT)/build
3RDPARTYDIR = $(PROJ_ROOT)/3rd-party

## 3rd-party settings
GTEST_VERSION=1.8.0
GTEST_PATH=$(3RDPARTYDIR)/googletest-release-$(GTEST_VERSION)/googletest
GMOCK_PATH=$(3RDPARTYDIR)/googletest-release-$(GTEST_VERSION)/googlemock
JSON_PATH=$(3RDPARTYDIR)/nlohmann

SDL_VERSION=2.0.8
SDL_PATH = $(3RDPARTYDIR)/SDL2-$(SDL_VERSION)
SDL_IMAGE_VERSION=2.0.1
SDL_IMAGE_PATH =$(3RDPARTYDIR)/SDL2_image-$(SDL_IMAGE_VERSION)
SDL_TTF_PATH =$(3RDPARTYDIR)/SDL2_ttf-2.0.14
SDL_FREETYPE_PATH =$(3RDPARTYDIR)/freetype-2.4.10

INCLUDE_DIRS +=	-I$(CURDIR) \
				-I$(PROJ_ROOT)/inc \
				-I$(GTEST_PATH)/include \
				-I$(GMOCK_PATH)/include \
				-I$(JSON_PATH)/include \
				-I$(SDL_PATH)/include \
                -I$(SDL_PATH)/include/SDL2 \
                -I$(SDL_IMAGE_PATH)/include \
                -I$(SDL_JSON_PATH)/include \
                -I$(SDL_TTF_PATH)/include \
                -I$(SDL_FREETYPE_PATH)/include


LIBS= -lgtest -lgmock -lpthread -lbakery-street -lSDL2_image -lSDL2_ttf -lfreetype -lsndio
#LIBS_PATH= -L$(BUILDDIR) -L$(GTEST_PATH)/lib -L$(GMOCK_PATH)/lib -L$(SDL_IMAGE_PATH)/lib -L$(SDL_TTF_PATH)/lib
LIBS_PATH = -L$(BUILDDIR) -L$(SDL_PATH)/lib -L$(SDL_IMAGE_PATH)/lib -L$(3RDPARTYDIR)/sndio -L$(SDL_TTF_PATH)/lib -L$(SDL_FREETYPE_PATH)/lib
####################################################

## Tests
SRCS = 	main_Test.cpp \
		GridTest.cpp


.PHONY: all clean

all: unit-tests

unit-tests: $(BUILDDIR)/$(COMPONENT_NAME)

$(BUILDDIR)/$(COMPONENT_NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(INCLUDE_DIRS) $(LIBS_PATH) $(LIBS) -o $(BUILDDIR)/$(COMPONENT_NAME)

run-unit-tests:
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH_) $(BUILDDIR)/$(COMPONENT_NAME)

clean:
	rm -f $(BUILDDIR)/$(COMPONENT_NAME)
