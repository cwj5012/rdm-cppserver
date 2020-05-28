echo off

if not exist "out_cpp" mkdir out_cpp

for %%i in (./proto/*.proto) do "../bin/protoc.exe" ./proto/%%i --cpp_out=./out_cpp

pause