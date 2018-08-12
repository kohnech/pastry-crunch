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

INCLUDE_DIRS +=	-I$(CURDIR) \
				-I$(PROJ_ROOT)/inc \
				-I$(GTEST_PATH)/include \
				-I$(GMOCK_PATH)/include


LIBS= -lgtest -lgmock -lpthread
LIBS_PATH= -L$(BUILDDIR) -L$(GTEST_PATH)/lib -L$(GMOCK_PATH)/lib

####################################################

## Tests
SRCS = 	main_Test.cpp



.PHONY: all clean

all: unit-tests

## Note this command must be run inside a docker container with gtest/gmock unless you have it installed natively
unit-tests:
	$(CXX) $(CXXFLAGS) $(SRCS) $(INCLUDE_DIRS) $(LIBS_PATH) $(LIBS) -L$(PROJ_ROOT)/build -o $(BUILDDIR)/$(COMPONENT_NAME)

run-unit-tests:
	$(BUILDDIR)/$(COMPONENT_NAME)

clean:
	rm -f $(BUILDDIR)/$(COMPONENT_NAME)
