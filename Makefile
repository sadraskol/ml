gtest_dir = deps/gtest-1.7.0
cppflags = -isystem $(gtest_dir)/include
cxxflags = -O3 -Wall -Wextra -std=c++11
gtest_headers = $(gtest_dir)/include/gtest/*.h \
				$(gtest_dir)/include/gtest/internal/*.h

build_dir=build
bin_dir=bin
src_dir=src
test_dir=test

tests_src := $(notdir $(shell find $(test_dir) -type f -name *_test.cc))
tests_objects := $(patsubst %.cc,$(build_dir)/%.o,$(tests_src))
tests := $(patsubst %.cc,$(bin_dir)/%,$(tests_src))

sources := $(notdir $(shell find $(src_dir) -type f -name "*.h"))
objects := $(patsubst %.h,$(build_dir)/%.o,$(sources))

all : $(bin_dir)/run

$(bin_dir)/run : main.cc $(objects)
	$(CXX) $(cppflags) $(cxxflags) -lpthread $^ -o $@

test : $(tests)

clean :
	rm -f $(build_dir)/*
	rm -f $(bin_dir)/*

$(build_dir)/%.o : $(src_dir)/%.cc $(src_dir)/%.h
	$(CXX) $(cppflags) $(cxxflags) -c $< -o $@

## Tests ##
## Tests files ## 
$(bin_dir)/%_test : $(objects) $(build_dir)/%_test.o $(build_dir)/gtest_main.a
	$(CXX) $(cppflags) $(cxxflags) -lpthread $^ -o $@

## GTest tasks ##
gtest_srcs_ = $(gtest_dir)/src/*.cc $(gtest_dir)/src/*.h $(gtest_headers)
$(build_dir)/gtest-all.o : $(gtest_srcs_)
	$(CXX) $(cppflags) -I$(gtest_dir) $(cxxflags) -c \
           $(gtest_dir)/src/gtest-all.cc -o $@

$(build_dir)/gtest_main.o : $(gtest_srcs_)
	$(CXX) $(cppflags) -I$(gtest_dir) $(cxxflags) -c \
           $(gtest_dir)/src/gtest_main.cc -o $@

$(build_dir)/gtest.a : $(build_dir)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(build_dir)/gtest_main.a : $(build_dir)/gtest-all.o $(build_dir)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(build_dir)/%_test.o : $(test_dir)/%_test.cc $(objects) $(gtest_headers)
	$(CXX) $(cppflags) $(cxxflags) -c $< -o $@

