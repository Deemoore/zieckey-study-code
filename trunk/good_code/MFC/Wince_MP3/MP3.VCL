<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: MP3 - Win32 (WCE MIPSII) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"MIPSIIRel/MP3.res" /d UNDER_CE=500 /d _WIN32_WCE=500 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WCE_PLATFORM_argon" /d "MIPS" /d "_MIPS_" /d "R4000" /d "MIPSII" /d "_AFXDLL" /r "E:\app\MP3\MP3.rc"" 
Creating temporary file "C:\DOCUME~1\winnie\LOCALS~1\Temp\RSP1B.tmp" with contents
[
/nologo /W3 /D "MIPS" /D "_MIPS_" /D "R4000" /D "MIPSII" /D UNDER_CE=500 /D _WIN32_WCE=500 /D "WCE_PLATFORM_argon" /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /D "_AFXDLL" /Fp"MIPSIIRel/MP3.pch" /Yu"stdafx.h" /Fo"MIPSIIRel/" /QMmips2 /QMFPE /O2 /MC /c 
"E:\app\MP3\MP3.cpp"
"E:\app\MP3\MP3Dlg.cpp"
]
Creating command line "clmips.exe @C:\DOCUME~1\winnie\LOCALS~1\Temp\RSP1B.tmp" 
Creating temporary file "C:\DOCUME~1\winnie\LOCALS~1\Temp\RSP1C.tmp" with contents
[
/nologo /W3 /D "MIPS" /D "_MIPS_" /D "R4000" /D "MIPSII" /D UNDER_CE=500 /D _WIN32_WCE=500 /D "WCE_PLATFORM_argon" /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /D "_AFXDLL" /Fp"MIPSIIRel/MP3.pch" /Yc"stdafx.h" /Fo"MIPSIIRel/" /QMmips2 /QMFPE /O2 /MC /c 
"E:\app\MP3\StdAfx.cpp"
]
Creating command line "clmips.exe @C:\DOCUME~1\winnie\LOCALS~1\Temp\RSP1C.tmp" 
Creating temporary file "C:\DOCUME~1\winnie\LOCALS~1\Temp\RSP1D.tmp" with contents
[
/nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"wWinMainCRTStartup" /incremental:no /pdb:"MIPSIIRel/MP3.pdb" /out:"MIPSIIRel/MP3.exe" /subsystem:windowsce,5.00 /MACHINE:MIPS 
.\MIPSIIRel\MP3.obj
.\MIPSIIRel\MP3Dlg.obj
.\MIPSIIRel\StdAfx.obj
.\MIPSIIRel\MP3.res
]
Creating command line "link.exe @C:\DOCUME~1\winnie\LOCALS~1\Temp\RSP1D.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
StdAfx.cpp
Compiling...
MP3.cpp
MP3Dlg.cpp
Generating Code...
Linking...




<h3>Results</h3>
MP3.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
