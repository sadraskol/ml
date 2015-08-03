gtest_dir = deps/gtest-1.7.0
cppflags = -isystem $(gtest_dir)/include
cxxflags = -g -Wall -Wextra -pthread -std=c++11
gtest_headers = $(gtest_dir)/include/gtest/*.h \
				$(gtest_dir)/include/gtest/internal/*.h
build_dir=build
bin_dir=bin
src_dir=src
test_dir=test
data_dir=data
tests=$(bin_dir)/Matrix_test $(bin_dir)/MnistParser_test

all : $(bin_dir)/run

$(bin_dir)/run : main.cc $(build_dir)/Matrix.o $(build_dir)/Network.o
	$(CXX) $(cppflags) $(cxxflags) -lpthread $^ -o $@

test : $(tests)

clean :
	rm -f *.o *.a $(tests)
	rm -f $(build_dir)/*
	rm -f $(bin_dir)/*

$(build_dir)/Matrix.o : $(src_dir)/Matrix.h $(src_dir)/Matrix.cc $(gtest_headers)
	$(CXX) $(cppflags) $(cxxflags) -c $(src_dir)/Matrix.cc -o $@

$(build_dir)/Network.o : $(src_dir)/Network.h $(src_dir)/Network.cc $(gtest_headers)
	$(CXX) $(cppflags) $(cxxflags) -c $(src_dir)/Network.cc -o $@

$(build_dir)/MnistParser.o : $(src_dir)/MnistParser.h $(src_dir)/MnistParser.cc $(gtest_headers)
	$(CXX) $(cppflags) $(cxxflags) -c $(src_dir)/MnistParser.cc -o $@

## Tests ##
## Tests files ## 
$(bin_dir)/Matrix_test : $(build_dir)/Matrix.o $(build_dir)/Matrix_test.o $(build_dir)/gtest_main.a
	$(CXX) $(cppflags) $(cxxflags) -lpthread $^ -o $@

$(bin_dir)/MnistParser_test : $(build_dir)/MnistParser.o $(build_dir)/MnistParser_test.o $(build_dir)/gtest_main.a
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

$(build_dir)/Matrix_test.o : $(test_dir)/Matrix_test.cc $(src_dir)/Matrix.h $(gtest_headers)
	$(CXX) $(cppflags) $(cxxflags) -c $(test_dir)/Matrix_test.cc -o $@

$(build_dir)/MnistParser_test.o : $(test_dir)/MnistParser_test.cc $(src_dir)/MnistParser.h $(gtest_headers)
	$(CXX) $(cppflags) $(cxxflags) -c $(test_dir)/MnistParser_test.cc -o $@

