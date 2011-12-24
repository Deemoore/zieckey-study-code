# weizili@360.cn 
#
# The study test code project 
#
# Please use gmake but not make in FreeBSD OS
#

		
SUBDIRS=src/map src/reduce

    
TOPDIR=`pwd`

all:
	for t in $(SUBDIRS); do $(MAKE) -C $$t; done
	cp src/map/map bin/
	cp src/reduce/reduce bin/
	
clean:
	for t in $(SUBDIRS); do $(MAKE) clean -C $$t; done

