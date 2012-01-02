# weizili@360.cn 
#
# The study test code project 
#
# Please use gmake but not make in FreeBSD OS
#

		
SUBDIRS=src/phase1_map src/phase1_reduce src/phase2_map src/phase2_reduce

TOPDIR=$(shell echo `pwd`)
_datenow=$(shell echo `date +%Y%m%d`)
_timenow=$(shell echo `date +%H%M%S`)
PACKAGE_DIR=weizili_mapred_v$(_datenow)$(_timenow)
PACKAGE=$(PACKAGE_DIR).tar.gz

all:
	for t in $(SUBDIRS); do $(MAKE) -C $$t; done

deploy:	
	$(MAKE) clean
	$(MAKE) 
	mkdir -p $(PACKAGE_DIR)/logs
	rm -rf $(PACKAGE_DIR)/*
	cp ./bin/phase* ./bin/run.sh $(PACKAGE_DIR)
	tar zcvf $(PACKAGE) $(PACKAGE_DIR)
	rm -rf $(PACKAGE_DIR)

t:	
	echo $(PACKAGE_DIR)
	
clean:
	for t in $(SUBDIRS); do $(MAKE) clean -C $$t; done

