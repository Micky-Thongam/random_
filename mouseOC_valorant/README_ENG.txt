1. Short description. 
  $Two github repo combined to make it work with Valorant.
  *(https://github.com/LordOfMice/hidusbf)
  *(https://github.com/hfiref0x/KDU)

  This driver/program is intended to "overclock" USB mice (or 
  other devices) under Windows 98, 98SE, ME, 2000, XP, 2003, Vista, 
  7, 8, 8.1, 10, 11 including x64 versions.
  Also may be used for downclocking (and downclocking shall work always).

  !!! Warning - overclocking may not work for Low Speed USB devices which 
  controlled by non Microsoft USB stack, like OEM USB 3.x drivers
  at Windows 7 or with the newest Microsoft drivers.


  Program changes rate on selected devices only, not touching other devices
  on USB.

  You can learn more about theory and the program here:
  http://www.overclockers.ru/lab/15925/Razgon_USB_myshi_ili_Software_nanosit_otvetnyj_udar.html
  (in Russian language(*))

  I have personally tested it under Windows 98SE, 2000 SP2/SP4, 
  XP RTM/SP1/SP2/SP3, XP x64 SP2, 2003 x86 SP2, Vista 32 bit RTM/SP2, 
  Vista 64 bit RTM, 7 x86 SP1, 7 x64 SP1, 8 x64, 8.1 x64,
  10 x64 1803, 1809, 1909, 20H2, 21H1, 21H2.
  The first testing on x64 platform was performed by Dark_Cloud under
  Windows XP x64 SP1.

2. Running (for windows 8+):

$Prerequisites for 2kHz-8kHz:
Must be used on usb 3.x
Must be using the microsoft usb 3.x driver (this is the driver that comes with windows 8 / 8.1 / 10)
Must be running windows 8 / 8.1 / 10

$WARNING BSOD ALERT! -- If you get BSOD when running xmouse.bat, try editing the xmouse.bat and change the command to this:
*kdu -dse 0 -prv 1
echo "NOW OVERCLOCK AND PRESS .ENTER. ONCE YOU RESTARTED THE MOUSE"
pause
kdu -dse 6
"PRESS .ENTER."
pause*
STILL doesn't work? try incrementing the prv value (max = 30)

$Running Procedure:    
* Right click and install the SweetLow.CER(for first time user)
* Run xmouse.bat(as administrator) don't close it yet!
* Run the 1kHz, 2kHz-4kHz, 4kHz-8kHz batch file in the driver directory.
* Run setup, install service, check box "filter on device", choose refreshrate (31 and 62 represent different things on each driver)
{
1kHz driver		31 = 31Hz	62 = 62Hz
2kHz-4kHz driver	31 = 2000Hz	62 = 4000Hz
4kHz-8kHz driver	31 = 4000Hz	62 = 8000Hz
}
Click restart, press "ENTER" and close the xmouse.bat, minimize setup.exe and enjoy your game...


Once you are done with your game uncheck "filter on device", and press restart. 



!!!!!!!!!!{ If mouse stops working and disappears from the list:
Use tab and shift tab to highlight "mice only", press spacebar.
You will see your mouse again.
Use tab and shift tab to highlight your mouse.
Use tab and shift tab to highlight "filter on device", press spacebar.
Use tab and shift tab to highlight "restart", press spacebar. }
  
{If for some reason the above method don't work then use tab and arrow key to navigate to device manager 
and unistall the USB driver(check for the yellow color USB driver) }