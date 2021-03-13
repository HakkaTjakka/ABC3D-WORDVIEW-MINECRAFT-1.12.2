@echo off
robocopy abc\region.new abc\region /MIR
copy abc\level.new abc\level.dat /Y
timeout 2
