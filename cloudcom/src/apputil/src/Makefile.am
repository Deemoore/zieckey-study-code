myincludedir=${abs_srcdir}/../include
test_srcdir=${abs_srcdir}/../test

#1.oslib project
lib_LTLIBRARIES = libqapputillib.la



OBJDIR=.obj

#2.source
libqapputillib_la_SOURCES =	QAppUtilPrerequisits.cpp\
							QCACenter.cpp


#libqapputillib_la_SOURCES = ${abs_srcdir}/*.cpp 


#3.preprocessor
#libqapputillib_la_CPPFLAGS =
AM_CPPFLAGS = -I${myincludedir}             \
			  -I${includedir}               \
			  -I${prefix}/include				\
			  -I${abs_srcdir}/../.. \
			  -I${abs_srcdir}/../../q3rdparty/include \
			  -I${abs_srcdir}/../../q3rdparty/unixinclude \
			  -I/usr/include/glib-2.0       \
			  -I/usr/lib/glib-2.0/include		\
			  -Wshadow -Wcast-qual -Wcast-align  -Wwrite-strings -Woverloaded-virtual	\
			  -Wsign-promo -Wsign-compare -Winvalid-pch 		\
			  -Wl,-rpath-link=${prefix}/lib -Wl,-rpath=${prefix}/lib -Wl,-rpath=.\
			  -fms-extensions -Wall -fno-gnu-keywords ${MyCPPFLAGS} -fPIC

#4.pre-compiler-header for this project
#gch=QOSLibPrerequisits.h.gch
#gch_h=../include/QOSLibPrerequisits.h
#${gch}:${gch_h}
#	$(CXXCOMPILE) $< $(AM_CPPFLAGS)  

#${libqapputillib_la_SOURCES}:${gch}



#5.link
libqapputillib_la_LDFLAGS = -version-info 0:1:0 -fPIC -Wl,-rpath-link=${prefix}/lib -Wl,-rpath=${prefix}/lib -Wl,-rpath=. ${MyLDFLAGS}
libqapputillib_la_LIBADD  = -L/usr/local/lib -L${libdir} -L${prefix}/lib -lrt -lpthread -lqoslib -lqnetworklib -lcurl

#6.install header
#liboslib_ladir = ${includedir}/hoslib
#liboslib_la_HEADERS = ${myincludedir}/*.h
