@echo off

if not exist "file_dropper-for-GMS1" mkdir "file_dropper-for-GMS1"
if not exist "file_dropper-for-GMS1\file_dropper\Assets\datafiles" mkdir "file_dropper-for-GMS1\file_dropper\Assets\datafiles"
cmd /C copyre ..\file_dropper.gmx\extensions\file_dropper.extension.gmx file_dropper-for-GMS1\file_dropper.extension.gmx
cmd /C copyre ..\file_dropper.gmx\extensions\file_dropper file_dropper-for-GMS1\file_dropper
cmd /C copyre ..\file_dropper.gmx\datafiles\file_dropper.html file_dropper-for-GMS1\file_dropper\Assets\datafiles\file_dropper.html
cd file_dropper-for-GMS1
cmd /C 7z a file_dropper-for-GMS1.7z *
move /Y file_dropper-for-GMS1.7z ../file_dropper-for-GMS1.gmez
cd ..

if not exist "file_dropper-for-GMS2\extensions" mkdir "file_dropper-for-GMS2\extensions"
if not exist "file_dropper-for-GMS2\datafiles" mkdir "file_dropper-for-GMS2\datafiles"
if not exist "file_dropper-for-GMS2\datafiles_yy" mkdir "file_dropper-for-GMS2\datafiles_yy"
cmd /C copyre ..\file_dropper_yy\extensions\file_dropper file_dropper-for-GMS2\extensions\file_dropper
cmd /C copyre ..\file_dropper_yy\datafiles\file_dropper.html file_dropper-for-GMS2\datafiles\file_dropper.html
cmd /C copyre ..\file_dropper_yy\datafiles_yy\file_dropper.html.yy file_dropper-for-GMS2\datafiles_yy\file_dropper.html.yy
cd file_dropper-for-GMS2
cmd /C 7z a file_dropper-for-GMS2.zip *
move /Y file_dropper-for-GMS2.zip ../file_dropper-for-GMS2.yymp
cd ..

if not exist "file_dropper-for-GMS2.3+\extensions" mkdir "file_dropper-for-GMS2.3+\extensions"
if not exist "file_dropper-for-GMS2.3+\datafiles" mkdir "file_dropper-for-GMS2.3+\datafiles"
cmd /C copyre ..\file_dropper_23\extensions\file_dropper file_dropper-for-GMS2.3+\extensions\file_dropper
cmd /C copyre ..\file_dropper_23\datafiles\file_dropper.html file_dropper-for-GMS2.3+\datafiles\file_dropper.html
cd file_dropper-for-GMS2.3+
cmd /C 7z a file_dropper-for-GMS2.3+.zip *
move /Y file_dropper-for-GMS2.3+.zip ../file_dropper-for-GMS2.3+.yymps
cd ..

pause