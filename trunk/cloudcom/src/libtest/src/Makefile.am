myincludedir=${abs_srcdir}/../include

#1.oslib project
bin_PROGRAMS=qlibtest

#2.source
qlibtest_SOURCES =	QLibTest.cpp\
					QLibTestPrerequisits.cpp\
                    QLevelDBBenchAnalyse.cpp\
					QMain.cpp\
					QTestAppShell.cpp\
					QTestBase64.cpp\
					QTestCACenter.cpp\
					QTestCompileCheck.cpp\
					QTestCurl.cpp\
					QTestEditHistory.cpp\
					QTestFileUtil.cpp\
					QTestINIParser.cpp\
					QTestIsPod.cpp\
					QTestLog.cpp\
					QTestMemAlloc.cpp\
					QTestMemcached.cpp\
					QTestMemoryDataStream.cpp\
					QTestOS.cpp\
					QTestSample.cpp\
					QTestSTL.cpp\
					QTestString.cpp\
					QTestThreads.cpp\
					QTestTrivial.cpp
					
#3.preprocessor
AM_CPPFLAGS = -I${myincludedir}             \
			  -I${includedir}               \
			  -I${prefix}/include				\
			  -I${abs_srcdir}/../.. \
			  -I${abs_srcdir}/../../q3rdparty/include \
			  -I${abs_srcdir}/../../q3rdparty/unixinclude \
			  -I/usr/include       \
			  -I/usr/local/include       \
			  -I../include			\
			  -I/usr/include/glib-2.0       \
			  -I/usr/lib/glib-2.0/include		\
			  -Wshadow -Wcast-qual -Wcast-align  -Wwrite-strings -Woverloaded-virtual	\
			  -Wsign-promo -Wsign-compare -Winvalid-pch 		\
			  -fms-extensions -Wall -fno-gnu-keywords ${MyCPPFLAGS} -fPIC
			

#4.compiler
#qlibtest_CXXFLAGS =
#AM_CXXFLAGS          = -O2

#5.link
qlibtest_LDFLAGS = -version-info 0:1:0 -fPIC -Wl,-rpath-link=${prefix}/lib -Wl,-rpath=${prefix}/lib -Wl,-rpath=. ${MyLDFLAGS}
#qlibtest_LDADD  = -L$(libdir) -L${prefix}/lib -lqoslib -lqnetworklib -lqapputillib   #-lcurl
qlibtest_LDADD  = -L$(libdir) -L${prefix}/lib -lqoslib -lqnetworklib -lqapputillib -lcurl -lmemcached ${prefix}/lib/libidea.a 


#6.install




