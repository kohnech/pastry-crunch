## Project
COMPONENT_NAME ?= bakery-street
export PROJ_ROOT := $(CURDIR)
SUBDIRS = tests
SRCDIR = $(PROJ_ROOT)/src
BUILDDIR = $(PROJ_ROOT)/build
TOOLSDIR = $(PROJ_ROOT)/tools
3RDPARTYDIR = $(PROJ_ROOT)/3rd-party

## 3rd-party settings
SDL_VERSION=2.0.8
SDL_PATH = $(3RDPARTYDIR)/SDL2-$(SDL_VERSION)
SDL_IMAGE_VERSION=2.0.1
SDL_IMAGE_PATH =$(3RDPARTYDIR)/SDL2_image-$(SDL_IMAGE_VERSION)

INCLUDE_DIRS += -I$(PROJ_ROOT)/inc \
				-I$(SDL_PATH)/include \
				-I$(SDL_PATH)/include/SDL2 \
				-I$(SDL_IMAGE_PATH)/include

## Libs
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lsndio
LIBS_PATH = -L$(BUILDDIR) -L$(SDL_PATH)/lib -L$(SDL_IMAGE_PATH)/lib -L$(3RDPARTYDIR)/sndio
export LD_LIBRARY_PATH=$(SDL_PATH)/lib:$(3RDPARTYDIR)/sndio:$(SDL_IMAGE_PATH)/lib:$LD_LIBRARY_PATH

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

## Machine
CORES ?= $(shell nproc)
MAKEFLAGS+="-j $(CORES)"

## Sources
SRCS = 	CApp.cpp \
		CSurface.cpp \
		CEvent.cpp \
		CAnimation.cpp \
		CEntity.cpp \
		CTile.cpp \
		CMap.cpp \
		CArea.cpp \
		CCamera.cpp \
		CGrid.cpp

HDRS = 	inc/CApp.h \
		inc/CSurface.h \
		inc/CEvent.h \
		inc/CAnimation.h \
		inc/CEntity.h \
		inc/CTile.h \
		inc/CMap.h \
		inc/CArea.h \
		inc/CCamera.h \
		inc/CGrid.h

OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))

## Make targets
.PHONY: all clean run

help:
	@echo
	@echo '  all                   - build and create main executable.'
	@echo '  lint                  - run clang formating for c++'
	@echo '  clang-format          - run clang-format on c++ files following rules specified in .clang-format.'
	@echo '  run                   - run main executable.'
	@echo '  clean                 - clean project.'
	@echo

all: $(BUILDDIR) $(BUILDDIR)/$(COMPONENT_NAME)

run: $(BUILDDIR)/$(COMPONENT_NAME)
	$(BUILDDIR)/$(COMPONENT_NAME)

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

lint: clang-format

clang-format:
	find ./inc ./src -regex '.*\.\(cpp\|hpp\|cc\|cxx\|h\)' -exec clang-format-5.0 -style=file -i {} \;

clean:
	rm -f $(OBJS)
	rm -f $(BUILDDIR)/$(COMPONENT_NAME)
	rm -f $(BUILDDIR)/main.o
	rm -f $(BUILDDIR)/$(STATIC)
