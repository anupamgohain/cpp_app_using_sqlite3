@ECHO off
setlocal enabledelayedexpansion
echo TODO LIST (Using SQLite)
echo Architecture (Batch -- Shell -- C++ -- SQLite)
echo.
echo Searching Linux-like environment for Windows ...
for /f %%a in ('dir \sh.exe /b /s 2^>NUL') do set p=%%a
echo.
if defined p (
echo Linux-like environment found.
) else (
echo No Linux-like environment found.
echo Exiting program
pause
exit
)
:while_loop
cls
echo.
echo ------------------------------------
echo               TODOS
echo ------------------------------------
%p% shell/showList.sh
echo ------------------------------------
echo.
echo 1. To add a new TODO item.
echo 2. To update a TODO item.
echo 3. To delete a TODO item.
echo 4. To toggle item complete.
echo 5. To clear completed item.
echo 6. To exit application.
set /p ch="Enter your choice: "
if %ch% equ 1 (
	GOTO addTodoItem
)
if %ch% equ 2 (
	GOTO updateTodoItem
)
if %ch% equ 3 (
	GOTO deleteTodoItem
)
if %ch% equ 4 (
	GOTO toggleTodoItem
)
if %ch% equ 5 (
	GOTO clearTodoItem
)
if %ch% equ 6 (
	GOTO:EOF
)

:addTodoItem
echo.
%p% shell/addList.sh
echo.
echo Refreshing...
timeout 3 > NUL
GOTO while_loop

:updateTodoItem
echo.
%p% shell/updateList.sh
echo.
echo Refreshing...
timeout 3 > NUL
GOTO while_loop

:deleteTodoItem
echo.
%p% shell/deleteList.sh
echo.
echo Refreshing...
timeout 3 > NUL
GOTO while_loop

:toggleTodoItem
echo.
%p% shell/toggleList.sh
echo.
echo Refreshing...
timeout 3 > NUL
GOTO while_loop

:clearTodoItem
echo.
%p% shell/clearList.sh
echo.
echo Refreshing...
timeout 3 > NUL
GOTO while_loop
GOTO:EOF
