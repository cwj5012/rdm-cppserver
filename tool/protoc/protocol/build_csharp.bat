echo off

if not exist "out_csharp" mkdir out_csharp

for %%i in (./proto/*.proto) do "./protoc.exe" ./proto/%%i --csharp_out=./out_csharp

pause