PROJECT=geometry
PWD=$(shell pwd)
FILES=$(shell ls $(PWD)/../Models/geometry*.cc | grep -ve 'observer' -ve 'subject')
SOURCES = $(FILES:%.cc=%.cc)

INSTALL_INC=/usr/local/include
INSTALL_LIB=/usr/local/lib
INCLUDE=-I/usr/local/include/ -I/opt/local/include/ -I$(PWD)/../Models/
LIBPATH=-L/usr/local/lib/ -L/opt/local/lib/
LIBS_TEST=-lgtest -lpthread -coverage -lm

CC=g++ -std=c++17
CP=gcc -std=c11

all: gcov_report

build: $(PROJECT).a
	mkdir -p Build
	cp *.a Build

$(PROJECT).a:
	$(CC) $(INCLUDE) -c $(SOURCES);\
	ar rcs $@ *.o;\
	cp $@ lib$@
	rm -rf *.o

test: clean_test build
	cd Testing;\
	cp $(PWD)/Build/*.a .;\
	$(CC) $(INCLUDE) -c main.cc  --coverage;\
	$(CC) -o $@ main.o $(PROJECT).a $(LIBPATH) -lgtest --coverage;\
	./$@
	
test_gcov: clean_test  
	cd Testing;\
	cp $(SOURCES) .;\
	$(CC) --coverage $(INCLUDE) -c geometry.cc;\
	$(CC) --coverage $(INCLUDE) -c geometry_normalization_parameters.cc;\
	$(CC) --coverage $(INCLUDE) -c geometry_normalization_parameters_builder.cc;\
	$(CC) --coverage $(INCLUDE) -c geometry_defaults.cc;\
	$(CC) $(INCLUDE) -c main.cc;\
	$(CC) --coverage -o $@ *.o  $(LIBPATH) -lgtest;\
	./$@
	
clean: clean_test clean_gcov clean_check clean_mac
clean_test: clean_build
	rm -rf Testing/*.o Testing/*.a Testing/test*
clean_build:
	rm -rf Build
	rm -rf *.a
clean_gcov:
	rm -rf Testing/geometry*
	rm -rf Testing/*.gcda Testing/*.gcno
	rm -rf gcov_report*
	rm -rf report*
clean_mac:
	find . -name .DS_Store -exec rm {} \;
clean_check:
	rm -rf .clang-format
	
leaks: clean test
	cd Testing;\
	leaks -atExit -- ./test
	
style:
	cp ../materials/linters/.clang-format .clang-format
	sh ./format.sh .
	

# generate coverage report
gcov_report: clean test_gcov
	mkdir report
	lcov --no-external --directory ./ --capture --output-file report.info
	genhtml report.info --output-directory report
	rm -rf *.gcno *.info *.gcda
	open report/index.html
