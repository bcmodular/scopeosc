; -- 64BitTwoArch.iss --
; Demonstrates how to install a program built for two different
; architectures (x86 and x64) using a single installer.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!
#define AppName "ScopeOSC"
#define RegSubKey "Software\BCModular\ScopeOSC"

[Setup]
AppName={#AppName}
AppVersion=0.1.0
DefaultDirName={pf}\{#AppName}
DefaultGroupName={#AppName}
UninstallDisplayIcon={app}\{#AppName}.ico
AppPublisher=BC Modular
AppPublisherURL=http://www.bcmodular.co.uk/
AppCopyright=Copyright (C) 2018 BC Modular
AppContact=support@bcmodular.co.uk
AppSupportURL=http://bcmodular.co.uk/forum/
AppUpdatesURL=http://www.scopesync.co.uk/
Compression=lzma2
SolidCompression=yes
LicenseFile=license.txt
; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
; On all other architectures it will install in "32-bit mode".
ArchitecturesInstallIn64BitMode=x64
; Note: We don't set ProcessorsAllowed because we want this
; installation to run on all architectures (including Itanium,
; since it's capable of running 32-bit code too).

[Types]
Name: "typical"; Description: "Typical installation"
Name: "full"; Description: "Full installation"
Name: "compact"; Description: "Compact installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Files]
; Install MyProg-x64.exe if running in 64-bit mode (x64; see above),
; MyProg.exe otherwise.
; Place all x64 files here
; Place all x86 files here, first one should be marked 'solidbreak'
; Place all common files here, first one should be marked 'solidbreak'
Source: "..\Scope DLL\*"; DestDir: "{code:GetScopeDir}\App\Dll"; Flags: ignoreversion solidbreak; Components: ScopeDLL
Source: "..\Scope DLL\*"; DestDir: "{code:GetScopeSDKDir}\App\Dll"; Flags: ignoreversion solidbreak; Components: ScopeSDKDLL
Source: "..\MS\vcredist_x86.exe"; DestDir: {tmp}; Flags: deleteafterinstall

[Icons]
Name: "{group}\Uninstall {#AppName}"; Filename: "{uninstallexe}"

[Components]
Name: "ScopeDLL"; Description: "Scope Module"; Types: full typical compact
Name: "ScopeSDKDLL"; Description: "Scope SDK Module"; Types: full

[Run]
Filename: "{tmp}\vcredist_x86.exe"; Parameters: "/passive /Q:a /c:""msiexec /qb /i vcredist.msi"" "; StatusMsg: Installing 2010 RunTime...

[Registry]
Root: HKCU; Subkey: "Software\ScopeOSC"; ValueType: string; ValueName: "InstallLocation"; ValueData: "{app}"

[Code]
// global vars
var
  ScopeDirPage1: TInputDirWizardPage;
  ScopeDirPage1ID: Integer;
  ScopeDirPage2: TInputDirWizardPage;
  ScopeDirPage2ID: Integer;

function GetScopeDir(Param: String): String;
var
  ScopeDir: String;
begin
  ScopeDir := ScopeDirPage1.Values[0];
  RegWriteStringValue(HKEY_CURRENT_USER, '{#RegSubKey}', 'ScopeDir', ScopeDir);
  { Return the selected ScopeDir }
  Result := ScopeDir;
end;

function GetScopeSDKDir(Param: String): String;
var
  ScopeSDKDir: String;
begin
  ScopeSDKDir := ScopeDirPage2.Values[0];
  RegWriteStringValue(HKEY_CURRENT_USER, '{#RegSubKey}', 'ScopeSDKDir', ScopeSDKDir);
  { Return the selected ScopeSDKDir }
  Result := ScopeSDKDir;
end;

procedure InitializeWizard;
var
  ScopeDir: String;
  ScopeSDKDir: String;
begin
  if not(RegQueryStringValue(HKEY_CURRENT_USER, '{#RegSubKey}', 'ScopeDir', ScopeDir)) then
  begin
    ScopeDir := ExpandConstant('{pf}\Scope PCI');
  end; 

  if not(RegQueryStringValue(HKEY_CURRENT_USER, '{#RegSubKey}', 'ScopeSDKDir', ScopeSDKDir)) then
  begin
    ScopeSDKDir := ExpandConstant('{pf}\Scope SDK PCI');
  end; 

  ScopeDirPage1 := CreateInputDirPage(
    wpSelectComponents,
    'Select Scope Directory',
    'Where should Scope files be installed?',
    '',
    False,
    '{#AppName}'
  );
  ScopeDirPage1.Add('Scope Installation Directory');
  ScopeDirPage1ID := ScopeDirPage1.ID;
  ScopeDirPage1.Values[0] := ScopeDir;
  
  ScopeDirPage2 := CreateInputDirPage(
    ScopeDirPage1ID,
    'Select Scope SDK Directory',
    'Where should Scope SDK files be installed?',
    '',
    False,
    '{#AppName}'
  );
  ScopeDirPage2.Add('Scope SDK Installation Directory');
  ScopeDirPage2ID := ScopeDirPage2.ID;
  ScopeDirPage2.Values[0] := ScopeSDKDir;
  
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  // initialize result to not skip any page (not necessary, but safer)
  Result := False;
  // if the page that is asked to be skipped is your custom page, then...
  if PageID = ScopeDirPage1ID then
    Result := not IsComponentSelected('ScopeDLL')
  else if PageID = ScopeDirPage2ID then
    Result := not IsComponentSelected('ScopeSDKDLL')
end;

procedure DecodeVersion (verstr: String; var verint: array of Integer);
var
  i,p: Integer; s: string;
begin
  // initialize array
  verint := [0,0,0,0];
  i := 0;
  while ((Length(verstr) > 0) and (i < 4)) do
  begin
    p := pos ('.', verstr);
    if p > 0 then
    begin
      if p = 1 then s:= '0' else s:= Copy (verstr, 1, p - 1);
      verint[i] := StrToInt(s);
      i := i + 1;
      verstr := Copy (verstr, p+1, Length(verstr));
    end
    else
    begin
      verint[i] := StrToInt (verstr);
      verstr := '';
    end;
  end;

end;

function CompareVersion (ver1, ver2: String) : Integer;
var
  verint1, verint2: array of Integer;
  i: integer;
begin

  SetArrayLength (verint1, 4);
  DecodeVersion (ver1, verint1);

  SetArrayLength (verint2, 4);
  DecodeVersion (ver2, verint2);

  Result := 0; i := 0;
  while ((Result = 0) and ( i < 4 )) do
  begin
    if verint1[i] > verint2[i] then
      Result := 1
    else
      if verint1[i] < verint2[i] then
        Result := -1
      else
        Result := 0;
    i := i + 1;
  end;

end;
