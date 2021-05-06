; -- 64Bit.iss --
; Demonstrates installation of a program built for the x64 (a.k.a. AMD64)
; architecture.
; To successfully run this installation and the program it installs,
; you must have a "x64" edition of Windows.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

#define ApplicationVersion  "4.4.0"
#define ApplicationName     "qTsConverter"

[Setup]
AppName={#ApplicationName}
AppVersion={#ApplicationVersion}
WizardStyle=modern
DefaultDirName={autopf}\{#ApplicationName}
DefaultGroupName={#ApplicationName}
UninstallDisplayIcon={app}\{#ApplicationName}.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Inno Setup Examples Output
OutputBaseFilename={#ApplicationName}_win_x64_{#ApplicationVersion}.exe
; "ArchitecturesAllowed=x64" specifies that Setup cannot run on
; anything but x64.
ArchitecturesAllowed=x64
; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
ArchitecturesInstallIn64BitMode=x64

[Files]
Source: "{#ApplicationName}.exe"; DestDir: "{app}"; DestName: "{#ApplicationName}.exe"
Source: "libQtXlsxWriterd.dll"; DestDir: "{app}"

[Icons]
Name: "{group}\{#ApplicationName}"; Filename: "{app}\{#ApplicationName}.exe"
