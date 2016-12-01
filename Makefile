# MOOC C++ for C Programmers
# Copyright 2016 O Hung Lun. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# * Neither the name of Google Inc. nor the names of its contributors may be
#   used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Author: hunglun.o@gmail.com (O Hung Lun)
#

# This should point to place where you unpacked or cloned Ceres.
CPPFC_SRC_DIR := /Usr/local

# This should point to the place where you built Ceres. If you got Ceres by
# installing it, then this will likely be /usr/local/lib.
CPPFC_BIN_DIR := /Usr/local

# The place you unpacked or cloned Eigen. If Eigen was installed from packages,
# this will likely be /usr/local/include. 
GTEST_SRC_DIR := /Users/hl/Github/googletest/googletest
GTEST_BUILD_DIR := /Users/hl/build/gtest

INCLUDES := -I$(CPPFC_SRC_DIR)/include \
	    -I$(GTEST_SRC_DIR)/include

CPPFC_LIBRARY := -lceres
CPPFC_LIBRARY_PATH := -L$(CPPFC_BIN_DIR)/lib -L$(GTEST_BUILD_DIR)
CPPFC_LIBRARY_DEPENDENCIES = -lgflags -lglog -lgtest


# If Ceres was built with CXSparse:
#CPPFC_LIBRARY_DEPENDENCIES += -lcxsparse

# The set of object files for your application.
APPLICATION_OBJS := dikjstra.o

BUILD_DIR := build

# Disabling debug asserts via -DNDEBUG helps make Eigen faster, at the cost of
# not getting handy assert failures when there are issues in your code.
#CFLAGS := -O2 -DNDEBUG
#CFLAGS := -DDEBUG -std=c++11 -g
CFLAGS := -std=c++11 -g

all: dikjstra

dikjstra: $(APPLICATION_OBJS)
	clang++ \
		$(APPLICATION_OBJS) \
		$(CPPFC_LIBRARY_PATH) \
		$(CPPFC_LIBRARY) \
		$(CPPFC_LIBRARY_DEPENDENCIES) \
		$(CFLAGS) \
		-o $(BUILD_DIR)/dikjstra

# If you have files ending in .cpp instead of .cc, fix the next line
# appropriately.
%.o: %.cc $(DEPS)
	clang++ -c -o $@ $< $(CFLAGS) $(INCLUDES)
