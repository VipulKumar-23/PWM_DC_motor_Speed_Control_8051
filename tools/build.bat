@echo off
REM ==============================================================================
REM Automated Build Script for 8051 PWM Motor Controller
REM Supports Keil uVision UV4 CLI build and verification
REM ==============================================================================

set PROJECT_NAME=PWM_Motor_Control
set OUTPUT_DIR=Objects
set UV4_EXE=C:\Keil_v5\UV4\UV4.exe

echo [INFO] Checking build prerequisites...

if not exist %OUTPUT_DIR% (
    mkdir %OUTPUT_DIR%
)

if exist "%UV4_EXE%" (
    echo [INFO] Launching Keil uVision CLI compilation...
    "%UV4_EXE%" -b %PROJECT_NAME%.uvproj -o build.log
    if %ERRORLEVEL% equ 0 (
        echo [SUCCESS] Firmware HEX file compiled successfully!
    ) else (
        echo [WARNING] Build exited with code %ERRORLEVEL%. Check build.log for details.
    )
) else (
    echo [NOTICE] Keil uVision executable not detected at default path (%UV4_EXE%).
    echo [NOTICE] You can compile directly inside Keil uVision GUI (Press F7) or adjust UV4_EXE.
)

echo [INFO] Build process complete.
