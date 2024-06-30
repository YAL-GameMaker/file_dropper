@echo off
set /p ver="Version?: "
echo Uploading %ver%...
set user=yellowafterlife
set ext=gamemaker-file-dropper
::cmd /C itchio-butler push file_dropper-for-GMS1.gmez %user%/%ext%:gms1 --userversion=%ver%
::cmd /C itchio-butler push file_dropper-for-GMS2.yymp %user%/%ext%:gms2 --userversion=%ver%
::cmd /C itchio-butler push file_dropper-for-GMS2.3+.yymps %user%/%ext%:gms2.3 --userversion=%ver%
::cmd /C itchio-butler push file_dropper-demo-for-GMS1.zip %user%/%ext%:demo1 --userversion=%ver%
cmd /C itchio-butler push file_dropper-demo-for-GMS2.3+.zip %user%/%ext%:demo2.3 --userversion=%ver%

pause