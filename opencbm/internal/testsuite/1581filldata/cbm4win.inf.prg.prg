;
; This is the install INF for cbm4wdm.
; Copyright (c) 2005 Spiro Trikaliotis
;

[Version]
Signature = "$Chicago$"
Class     = OpenCBM4Wdm
ClassGuid = {270C079C-E1CE-49cf-B8C9-80DC4C33221F}
Provider  = %Spiro%
DriverVer = 08/24/2005,0.1.0.28
Catalogfile = cbm4wdm.cat ; in case we decide to sign that driver some day...

;
; Standard INF sections
;
[Manufacturer]
%Spiro% = OpenCbmDeviceList

[DestinationDirs]
DefaultDestDir          = 11  ; copy everything unspecified into SYSTEM32
OpenCbmCopyFiles.driver.nt = 10, system32\drivers  ; copy the driver files into SYSTEM32\DRIVERS
OpenCbmCopyFiles.driver = 10, system32\drivers  ; copy the driver files into SYSTEM32\DRIVERS
OpenCbmCopyFiles.dll    = 11  ; the DLL should go into SYSTEM32
OpenCbmCopyFiles.vdd    = 11  ; the VDD should go into SYSTEM32

;
; Information on the installation media
;
[SourceDisksNames]
1 = %DiskName%,cbm4wdm.sys,0

[SourceDisksFiles]
cbm4wdm.sys    = 1
cbm4w98.sys    = 1
opencbm.dll    = 1
opencbmvdd.dll = 1

;
; CLASS sections
;

; install class (for Win 2000/XP)
[ClassInstall32]
AddReg=RegisterCbmClass

; install class (for Win 98/Me)
[ClassInstall]
AddReg=RegisterCbmClass

[RegisterCbmClass]
HKR,,,0,%ClassName%
; HKR,,EnumPropPages32,,"prop-provider.dll,provider-entry-point"
HKR,,Icon,,-5

;
; 2000/XP specific cbm4win Device Sections
;
[OpenCbmDeviceList]
%DriverName% = cbm4win,root\cbm4wdm

[cbm4win.NTx86]
CopyFiles = OpenCbmCopyFiles.driver.nt,OpenCbmCopyFiles.dll,OpenCbmCopyFiles.vdd

[cbm4win.NTx86.Services]
AddService = opencbm,2,cbm4win.service	; ,cbm4win.EventLog

[cbm4win.service]
DisplayName   = %ServiceName%
ServiceType   = 1
StartType     = 3
ErrorControl  = 1
ServiceBinary = %12%\cbm4wdm.sys

[cbm4win.EventLog]
HKR,,EventMessageFile,0x00020000,"%12%\cbm4wdm"
HKR,,TypesSupported,0x00010001,7 

;
; 98/Me specific cbm4win Device Sections
;
[cbm4win]
CopyFiles = OpenCbmCopyFiles.driver,OpenCbmCopyFiles.dll
AddReg    = AddReg98

[AddReg98]
HKR,,DevLoader,,*ntkern
HKR,,NTMPDriver,,cbm4w98.sys

;
; common cbm4win Device Sections
;
[OpencbmCopyFiles.driver.nt]
cbm4wdm.sys,,,2

[OpencbmCopyFiles.driver]
cbm4w98.sys,,,2

[OpencbmCopyFiles.dll]
opencbm.dll,,,2

[OpencbmCopyFiles.vdd]
opencbmvdd.dll,,,2

;
; Strings used throughout this file
;
[Strings]
Spiro        = "Spiro Trikaliotis"
DiskName     = "OpenCBM driver diskette"
ClassName    = "CBM drivers"
DriverName   = "CBM4WIN parallel port driver"
ServiceName  = "CBM4WIN Service"

[Strings.0407]
Spiro        = "Spiro Trikaliotis"
DiskName     = "OpenCBM Treiber Diskette"
ClassName    = "CBM Treiber"
DriverName   = "CBM4WIN Parallel-Port-Treiber"
ServiceName  = "CBM4WIN Service"
