@echo off

SET MyProgram="%~1"
set OUT="%TEMP%\output.txt"

if  %MyProgram%=="" (
	echo please specify path to program
	exit /B 1
)

%MyProgram% file1.txt > %OUT% || goto err
fc %OUT% "%~dp0file1-out.txt" > nul || goto err
echo test 1 has passed

%MyProgram% file2.txt > %OUT% || goto err
fc %OUT% "%~dp0file2-out.txt" > nul || goto err
echo test 2 has passed

%MyProgram% file3.txt > %OUT% || goto err
fc %OUT% "%~dp0file3-out.txt" > nul || goto err
echo test 3 has passed

%MyProgram% file4.txt > %OUT% || goto err
fc %OUT% "%~dp0file4-out.txt" > nul || goto err
echo test 4 has passed

%MyProgram% file5.txt > %OUT% || goto err
fc %OUT% "%~dp0file5-out.txt" > nul || goto err
echo test 5 has passed

%MyProgram% file6.txt > %OUT% || goto err
fc %OUT% "%~dp0file6-out.txt" > nul || goto err
echo test 6 has passed

%MyProgram% file7.txt > %OUT% || goto err
fc %OUT% "%~dp0file7-out.txt" > nul || goto err
echo test 7 has passed

echo All the tests have passed successfully
exit /B 0

:err
echo test failed
exit /B 1