## Project
COMPONENT_NAME ?= sdl2-first-test
export PROJ_ROOT := $(CURDIR)
SUBDIRS = tests
SRCDIR = $(PROJ_ROOT)/src
BUILDDIR = $(PROJ_ROOT)/build
TOOLSDIR = $(PROJ_ROOT)/tools
3RDPARTYDIR = $(PROJ_ROOT)/3rd-party

## 3rd-party settings
SDL_VERSION=2.0.8
SDL_PATH = $(3RDPARTYDIR)/SDL2-$(SDL_VERSION)

INCLUDE_DIRS += -I$(PROJ_ROOT)/inc \
				-I$(3RDPARTYDIR)/SDL2-$(SDL_VERSION)/include

## Libs
LIBS = -lSDL2 -lSDL2main
LIBS_PATH = -L$(BUILDDIR) -L$(SDL_PATH)/lib

## Compiler
BUILD_TYPE ?= DEBUG
CXX = g++
STATIC = libfirsttest.a
DYNAMIC = libfirsttest.so
CXXFLAGS = -Wall -Winline -Werror -pipe -std=c++11 -fPIC
ifeq ($(BUILD_TYPE),DEBUG)
	CXXFLAGS += -g -O0
else ifeq ($(BUILD_TYPE),RELEASE)
	CXXFLAGS += -O3
endif

## Sources
SRCS = 	CApp.cpp

HDRS = 	inc/CApp.h

OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))

## Make targets
.PHONY: all clean

all: $(BUILDDIR) $(BUILDDIR)/$(COMPONENT_NAME)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(COMPONENT_NAME): $(BUILDDIR)/main.o $(OBJS) $(HDRS)
	$(CXX) -o $@ $(BUILDDIR)/main.o $(OBJS) $(LIBS_PATH) $(LIBS)

$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp $(HDRS)
	$(CXX) -o $@ $(INCLUDE_DIRS) -c $(CXXFLAGS) $(SRCDIR)/main.cpp

$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@echo [Compile] $<
	@$(CXX) $(INCLUDE_DIRS) -c $(CXXFLAGS) $< -o $@

$(BUILDDIR)/$(STATIC): $(OBJS)
	@echo "[Link (Static)]"
	@ar rcs $@ $^

clean:
	rm -f $(OBJS)
	rm -f $(BUILDDIR)/$(COMPONENT_NAME)
	rm -f $(BUILDDIR)/main.o
	rm -f $(BUILDDIR)/$(STATIC)
