@echo off

SET MyProgram="%~1"
set OUT="%TEMP%\output.txt"

if  %MyProgram%=="" (
	echo please specify path to program
	exit /B 1
)

%MyProgram% graph1.txt > %OUT% || goto err
fc %OUT% "%~dp01-out.txt" > nul || goto err
echo test 1 has passed

%MyProgram% graph2.txt > %OUT% || goto err
fc %OUT% "%~dp02-out.txt" > nul || goto err
echo test 2 has passed

%MyProgram% graph3.txt > %OUT% || goto err
fc %OUT% "%~dp03-out.txt" > nul || goto err
echo test 3 has passed

%MyProgram% graph4.txt > %OUT% || goto err
fc %OUT% "%~dp04-out.txt" > nul || goto err
echo test 4 has passed

%MyProgram% graph5.txt > %OUT% || goto err
fc %OUT% "%~dp05-out.txt" > nul || goto err
echo test 5 has passed

%MyProgram% graph-invalid1.txt > nul && goto err
echo test 6 has passed

%MyProgram% graph-invalid2.txt > nul && goto err
echo test 7 has passed

echo All the tests have passed successfully
exit /B 0

:err
echo test failed
exit /B 1