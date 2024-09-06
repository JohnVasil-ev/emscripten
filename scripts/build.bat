@echo off

if exist build\web\ (
	rmdir /s/q .\build\web\
)

if not exist build\web\ (
	mkdir build\web\
)

xcopy /s .\public .\build\web

em++ .\src\main.cpp -o .\build\web\emsc-test.js
