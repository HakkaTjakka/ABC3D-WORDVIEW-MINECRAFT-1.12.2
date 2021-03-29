@echo off

rem f2f.exe -save rem save back region file from /saves/template/region/r.0.0.mca with calculated blocks used for .mcfunction files
rem f2f.exe -f2f rem make .mcfuntion files from font (from texture resources/abc_16x16.png). to directory mcfunctions
f2f.exe -f2f -save

rem copy mcfunctions\*.* \saves\ABC\data\functions\abc /Y
copy mcfunctions\*.* \saves\template\data\functions\abc /Y 

timeout 5


