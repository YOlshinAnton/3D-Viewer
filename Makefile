PROJECT=3DViewer
MAJOR=2
MINOR=0
PACKAGE=$(PROJECT)-$(MAJOR).$(MINOR)
APP=$(PROJECT).app
SOURCEDIR=$(shell pwd)
BUILINSTALL=.
BUILDIR=build
BUILD=$(BUILINSTALL)/$(BUILDIR)
INSTALL_DFT=..
INSTALL=$(shell cat appsettings.ini | grep -e '^INSTALL_LOCATION' | awk '{split($$0,a,"=")} {print a[2]}')
OPEN=open

all: clean install open dvi

dvi: clean_dvi html

html: clean_dvi
	doxygen
	$(OPEN) Documentation/html/index.html

open: 
	$(OPEN) $(INSTALL)/$(BUILDIR)/$(APP)

install: build
	mkdir -p $(INSTALL)/$(BUILDIR)
	cp -r $(BUILD)/$(APP) $(INSTALL)/$(BUILDIR)

uninstall: clean_build clean_install

build: clean_build 
	mkdir -p $(BUILD)
	cd $(BUILD); \
	cmake $(SOURCEDIR);\
	cmake --build .;

dist: clean
	mkdir -p $(PACKAGE)
	cp Controllers/* $(PACKAGE)
	cp Models/* $(PACKAGE)
	find View -type f -exec cp {} $(PACKAGE) \;
	cp main.cc $(PACKAGE)
	tar czf $(PACKAGE).tar.gz '$(PACKAGE)'
	rm -rf $(PACKAGE)

test:
	make -C Testing.Geometry test

coverage:
	make -C Testing.Geometry

style:
	sh ./Testing.Geometry/format.sh . -n

format:
	sh ./Testing.Geometry/format.sh . -i

clean_git: clean clean_cmake clean_mac clean_qt 

clean: clean_dvi clean_install clean_build clean_dist clean_test

clean_dvi:
	rm -rf Documentation

clean_install:
	rm -rf $(INSTALL)/$(BUILDIR)

clean_build:
	rm -rf $(BUILD)

clean_dist:
	rm -rf $(PACKAGE).tar.gz

clean_test:
	make -C Testing.Geometry clean

clean_qt:
	rm -rf .qt
	find .. -name 'build-src*' -exec rm -rf '{}' \;

clean_cmake:
	find . -name 'CMakeLists.txt.user' -delete
	find . -name 'CMakeFiles' -exec rm -rf {} \;
	find . -name 'cmake_install.cmake' -delete

clean_mac:
	find .. -name '\.DS_Store' -delete


print_install_dir:
	echo '$(INSTALL)'
