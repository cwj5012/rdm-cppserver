echo off

if not exist "out_cpp" mkdir out_cpp

cd proto

for %%i in (./*.proto) do "../../bin/protoc.exe" ./%%i --cpp_out=../out_cpp

pause