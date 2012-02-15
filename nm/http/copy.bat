set TopDir=E:\New-UMS\trunk\nm

set SrcDir=.
copy  %SrcDir%\"Pocket PC 2003 (ARMV4)"\Release\http.lib %TopDir%\3rdparty\lib\release
copy  %SrcDir%\"Pocket PC 2003 (ARMV4)"\Debug\http.lib %TopDir%\3rdparty\lib\debug

copy  %SrcDir%\"Pocket PC 2003 (ARMV4)"\Release\http.pdb %TopDir%\3rdparty\lib\release
copy  %SrcDir%\"Pocket PC 2003 (ARMV4)"\Debug\http.pdb %TopDir%\3rdparty\lib\debug

copy  %SrcDir%\include\*.h %TopDir%\http\include
copy  %SrcDir%\..\net\include\*.h %TopDir%\net\include
pause