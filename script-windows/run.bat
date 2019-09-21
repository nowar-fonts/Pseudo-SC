%~d0
cd "%~dp0"

.\otfccdump.exe --ignore-hints -o base.otd "%~1"

.\pseudo-sc.exe base.otd

if exist Fonts rmdir /s /q Fonts
mkdir Fonts

.\otfccbuild.exe -q -O3 -o Fonts\ARIALN.ttf base.otd
copy Fonts\ARIALN.ttf Fonts\bHEI00M.ttf
copy Fonts\ARIALN.ttf Fonts\bKAI00M.ttf
copy Fonts\ARIALN.ttf Fonts\blei00d.ttf
copy Fonts\ARIALN.ttf Fonts\FRIZQT__.ttf

rem leave chat font as-is
copy "%~1" Fonts\arheiuhk_bd.ttf
copy "%~1" Fonts\bHEI01B.ttf

del base.otd
pause
