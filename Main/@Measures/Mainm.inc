;========================================
;Top Part
;========================================

[MeasureComputerName]
Measure=Plugin
Plugin=SysInfo
SysInfoType=COMPUTER_NAME
UpdateDivider=-1

[MeasureTime]
Measure=Time
Format=%H:%M:%S
[MeasureDate]
Measure=Time
Format=%a, %#b %#d
[MeasureOSBits]
Measure=Plugin
Plugin=SysInfo
SysInfoType=OS_BITS
UpdateDivider=-1
[MeasureMonitors]
Measure=Plugin
Plugin=SysInfo
SysInfoType=NUM_MONITORS
UpdateDivider=-1
[MeasureUsername]
Measure=Plugin
Plugin=SysInfo
SysInfoType=USER_NAME
UpdateDivider=-1

[MeasureProductName]
Measure=Registry
RegHKey=HKEY_LOCAL_MACHINE
RegKey=SOFTWARE\Microsoft\Windows NT\CurrentVersion
RegValue=ProductName
UpdateDivider=-1
[MeasureVersion]
Measure=Registry
RegHKey=HKEY_LOCAL_MACHINE
RegKey=SOFTWARE\Microsoft\Windows NT\CurrentVersion
RegValue=DisplayVersion
UpdateDivider=-1
[MeasureCurrentBuild]
Measure=Registry
RegHKey=HKEY_LOCAL_MACHINE
RegKey=SOFTWARE\Microsoft\Windows NT\CurrentVersion
RegValue=CurrentBuild
UpdateDivider=-1
[MeasureUBR]
Measure=Registry
RegHKey=HKEY_LOCAL_MACHINE
RegKey=SOFTWARE\Microsoft\Windows NT\CurrentVersion
RegValue=UBR
UpdateDivider=-1

;========================================
;RAM
;========================================

[MeasurePhysMemTotal]
Measure=PhysicalMemory
Total=1
UpdateDivider=-1
[MeasurePhysMemUsed]
Measure=PhysicalMemory
UpdateDivider=5
[MeasureRAM]
Measure=Calc
Formula=(MeasurePhysMemUsed / MeasurePhysMemTotal) * 100
UpdateDivider=5
[RAMTextActual]
Measure=Calc
Formula=MeasureRAM/5

;========================================
;CPU
;========================================

[MeasureCPU]
Measure=Plugin
Plugin=UsageMonitor
Alias=CPU
Index=0
RegExpSubstitute=1
Substitute="^0$":"0.01"
[CPUTextActual]
Measure=Calc
Formula=MeasureCPU/5

[CPUPhyC]
Measure=Plugin
Plugin=RunCommand
Parameter=wmic CPU Get NumberOfCores
State=Hide
OutputType=ANSI
RegExpSubstitute=1
Substitute="#CRLF#":"", "NumberOfCores":"", " ":""
UpdateDivider=-1

[CPUVirC]
Measure=Plugin
Plugin=RunCommand
Parameter=wmic CPU Get NumberOfLogicalProcessors
State=Hide
OutputType=ANSI
RegExpSubstitute=1
Substitute="#CRLF#":"", "NumberOfLogicalProcessors":"", " ":""
UpdateDivider=-1

;========================================
;GPU
;========================================

[MeasureGPU]
Measure=Plugin
Plugin=UsageMonitor
Alias=GPU
Index=0
Blacklist=dwm
DynamicVariables=1
[GPUTextActual]
Measure=Calc
Formula=MeasureGPU/5

;========================================
;Bin
;========================================

[RecycleBinFiles]
Measure=RecycleManager
RecycleType=COUNT
Drives=ALL
UpdateDivider=60
Group=Bin
Substitute=".0":""
[RecycleBinSize]
Measure=RecycleManager
RecycleType=SIZE
Drives=ALL
UpdateDivider=60
Group=Bin

;========================================
;Uptime
;========================================

[MeasureUptime]
Measure=Uptime
Format="%4!i! days, %3!i! hours, %2!i! minutes %1!i! seconds"

;========================================
;Internet
;========================================

[InternetType]
Measure=Plugin
Plugin=SysInfo
SysInfoType=ADAPTER_TYPE
SysInfoData=Best
UpdateDivider=-1
IfCondition=InternetType=6
IfTrueAction=[!SetVariable NetType Ethernet][!UpdateMeasure InternetStatus]
IfCondition2=InternetType=71
IfTrueAction2=[!SetVariable NetType Wifi][!UpdateMeasure InternetStatus]
[InternetName]
Measure=PLUGIN
Plugin=WifiStatus
WiFiInfoType=SSID
Substitute="-1":""
[InternetStatus]
Measure=PLUGIN
Plugin=SysInfo
SysInfoType=INTERNET_CONNECTIVITY
Substitute="-1.0":"Offline","1.0":"Connected"
DynamicVariables=1
IfCondition=InternetStatus = -1
IfTrueAction=[!SetOption Internet Text "%6#CRLF#%1#CRLF#Click here to connect to the internet"][!UpdateMeter Internet][!Redraw]
IfFalseAction=[!SetOption Internet Text "%6#CRLF#%1 %2-%3 Dl %4b | Ul %5b"][!UpdateMeter Internet][!Redraw]
[mAUTH]
Measure=PLUGIN
Plugin=WifiStatus
WiFiInfoType=AUTH
Substitute="-1":""
[InternetDownloadSpeed]
Measure=NetIn
Interface=Best
MinValue=0
AverageSize=5
[InternetUploadSpeed]
Measure=NetOut
Interface=Best
MinValue=0
AverageSize=5
[MeasurePing]
Measure=Plugin
Plugin=PingPlugin
DestAddress=www.google.fr

;========================================
;Names
;========================================

[MeasureGPUName]
Measure=Plugin
Plugin=RunCommand
Parameter=wmic path win32_VideoController get name
State=Hide
OutputType=ANSI
RegExpSubstitute=1
Substitute="Name.*#CRLF#":"","Intel.*#CRLF#":"","#CRLF#.*":"","  ":"","Radeon":"AMD Radeon","NVIDIA GeForce":"NVIDIA GeForce"
UpdateDivider=-1
[MeasureCPUName]
Measure=Registry
RegHKey=HKEY_LOCAL_MACHINE
RegKey=HARDWARE\DESCRIPTION\System\CentralProcessor\0
RegValue=ProcessorNameString
UpdateDivider=12000
RegExpSubstitute=1
Substitute="CPU":"","\(TM\)|\(tm\)|\(Tm\)":"","Processor":"","(\w{1,4}[\s\S]Core[s]?)":"","(Intel Core|Intel\(R\) Core)":"Intel(R) Core","@":"","AMD Ryzen ":"AMD Ryzen R"
UpdateDivider=-1
[MeasureMotherboardname]
Measure=Plugin
Plugin=RunCommand
Parameter=wmic baseboard get product
State=Hide
OutputType=ANSI
RegExpSubstitute=1
Substitute="Product.*#CRLF#":"","#CRLF#.*":"","  ":""
UpdateDivider=-1

; ================================================
; Drives
; ================================================


; ================================================
; Power
; ================================================
[MeasureBatteryStatus]
Measure=Plugin
Plugin=PowerPlugin
PowerState=ACLine
Substitute="0":"Unplugged","1":"Plugged"
[MeasureBatteryPercent]
Measure=Plugin
Plugin=PowerPlugin
PowerState=Percent
[MeasureBatteryLifetime]
Measure=Plugin
Plugin=PowerPlugin
PowerState=Lifetime