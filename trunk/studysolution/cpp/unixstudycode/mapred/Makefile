# weizili@360.cn 
#
# The study test code project 
#
# Please use gmake but not make in FreeBSD OS
#

		
SUBDIRS=src/phase1_map src/phase1_reduce src/phase2_map src/phase2_reduce


    
TOPDIR=`pwd`

all:
	for t in $(SUBDIRS); do $(MAKE) -C $$t; done
	
clean:
	for t in $(SUBDIRS); do $(MAKE) clean -C $$t; done

