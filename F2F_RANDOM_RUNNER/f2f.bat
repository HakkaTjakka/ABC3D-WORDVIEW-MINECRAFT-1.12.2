@echo off
f2f.exe > f2f.log
type f2f.log
timeout 2
copy mcfunctions \saves\ABC\data\functions\abc /Y
rem copy mcfunctions\*.* \saves\ABC3D\data\functions\abc /Y > NUL
timeout 5


