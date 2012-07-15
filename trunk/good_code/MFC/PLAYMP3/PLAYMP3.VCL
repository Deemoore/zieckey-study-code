<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: PLAYMP3 - Win32 (WCE ARMV4I) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating temporary file "C:\DOCUME~1\huhao\LOCALS~1\Temp\RSP3EB.tmp" with contents
[
/nologo /W3 /D "ARM" /D "_ARM_" /D "ARMV4I" /D UNDER_CE=500 /D _WIN32_WCE=500 /D "WCE_PLATFORM_2440_CN" /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /D "_AFXDLL" /Fp"ARMV4IRel/PLAYMP3.pch" /Yu"stdafx.h" /Fo"ARMV4IRel/" /QRarch4T /QRinterwork-return /O2 /MC /c 
"C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\FullPathFile.cpp"
"C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\OpenFileDlg.cpp"
]
Creating command line "clarm.exe @C:\DOCUME~1\huhao\LOCALS~1\Temp\RSP3EB.tmp" 
Creating temporary file "C:\DOCUME~1\huhao\LOCALS~1\Temp\RSP3EC.tmp" with contents
[
/nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"wWinMainCRTStartup" /incremental:no /pdb:"ARMV4IRel/PLAYMP3.pdb" /out:"ARMV4IRel/PLAYMP3.exe" /subsystem:windowsce,5.00 /MACHINE:THUMB 
".\ARMV4IRel\CDXGraph.obj"
".\ARMV4IRel\FullPathFile.obj"
".\ARMV4IRel\Lrc.obj"
".\ARMV4IRel\OpenFileDlg.obj"
".\ARMV4IRel\PLAYMP3.obj"
".\ARMV4IRel\PLAYMP3Dlg.obj"
".\ARMV4IRel\StdAfx.obj"
".\ARMV4IRel\PLAYMP3.res"
]
Creating command line "link.exe @C:\DOCUME~1\huhao\LOCALS~1\Temp\RSP3EC.tmp"
<h3>Output Window</h3>
Compiling...
FullPathFile.cpp
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\FullPathFile.cpp(4) : warning C4005: 'UNDER_CE' : macro redefinition
        c:\program files\windows ce tools\wce420\vsm80\mfc\include\wce.h(279) : see previous definition of 'UNDER_CE'
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\FullPathFile.cpp(4) : warning C4005: '_WIN32_WCE' : macro redefinition
        unknown(0) : see previous definition of '_WIN32_WCE'
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\FullPathFile.cpp(4) : warning C4651: '/DUNDER_CE=420' specified for precompiled header but not for current compile
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\FullPathFile.cpp(4) : warning C4651: '/D_WIN32_WCE=420' specified for precompiled header but not for current compile
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\FullPathFile.cpp(4) : warning C4651: '/DWCE_PLATFORM_VCORE' specified for precompiled header but not for current compile
OpenFileDlg.cpp
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\OpenFileDlg.cpp(4) : warning C4005: 'UNDER_CE' : macro redefinition
        c:\program files\windows ce tools\wce420\vsm80\mfc\include\wce.h(279) : see previous definition of 'UNDER_CE'
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\OpenFileDlg.cpp(4) : warning C4005: '_WIN32_WCE' : macro redefinition
        unknown(0) : see previous definition of '_WIN32_WCE'
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\OpenFileDlg.cpp(4) : warning C4651: '/DUNDER_CE=420' specified for precompiled header but not for current compile
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\OpenFileDlg.cpp(4) : warning C4651: '/D_WIN32_WCE=420' specified for precompiled header but not for current compile
C:\Documents and Settings\huhao\桌面\7.17\BLACK_4.3\BLACKMP3_test_listctrl\PLAYMP3_OK_slider\OpenFileDlg.cpp(4) : warning C4651: '/DWCE_PLATFORM_VCORE' specified for precompiled header but not for current compile
Generating Code...
Linking...




<h3>Results</h3>
PLAYMP3.exe - 0 error(s), 10 warning(s)
</pre>
</body>
</html>
