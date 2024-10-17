@echo off

pushd ..\
call Vendor\Bin\preamake\premake5.exe vs2022
popd

PAUSE