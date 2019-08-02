This is an example project to illustrate how to use the onboard 128x64 OLED display
(connected via I2C, hardwired to the pins used by GPIO 4 and 5) in an ESP-IDF project.

This is the exact board used and tested: https://amazon.com/gp/product/B072HBW53G

The project was created using Eclipse (Oxygen) on Windows.

If you figure out how to turn it into a CLion or PlatformIO project, PLEASE fork it and share it on Github.

# How to build

If you haven't already done it, go to https://esp-idf.readthedocs.io & follow the directions in the "Get Started" section to download and set up the ESP-IDF
toolchain. It's extremely well-written (in fact, it's just about the finest documentation I've ever SEEN for an embedded development
platform. Espressif has fantastic technical writers.)

 Make sure you can at least build and run the hello_world project from the esp-idf examples/get-started/ directory, then continue with the directions 
for setting up Eclipse.

Now, do the following ("c:\path\to\some-directory" is the path to wherever you want your projects to go).

`cd c:\path\to\some-directory`

`git clone https://github.com/jskubick/u8g2-example_esp-idf_lolin32_ssd1306-i2c-sda5-scl4.git`

`cd u8g2-example_esp-idf_lolin32_ssd1306-i2c-sda5-scl4`

`mkdir components`

`cd components`

`git clone https://github.com/olikraus/u8g2.git`


## Critical next steps:

open the MinGW32 shell, and...

`cd /c/path/to/some-directory/u8g2-example_esp-idf_lolin32_ssd1306-i2c-sda5-scl4` (note the forward slashes and notation for the c: drive)

Ensure your LOLIN32 board is connected to the USB port, and that you DON'T already have a serial monitor window opened to it

`make menuconfig`

 cursor-down to "Serial flasher config".
 
 * Make sure "Default serial port" is set to the correct port. If you're running Windows, this will be something like `COM7`
 
 Additional settings from "Serial flasher config" --
 
 * Default baud rate can be 230400 or 921600 (your choice)
 
 * After flashing (Reset after flashing)
 
 * 'make monitor' baud rate: 115200bps
 
 * Exit, Exit. When asked whether you want to save your new configuration, say yes.
 
 The moment of truth: `make monitor flash`
 
 If you get lucky, it will successfully compile, and in a few moments you'll be greeted by "Hello!" on the OLED.
 
 ## Now, get it to work in Eclipse...
 
 ###Warning!###
 
 This example project was created using ESP-IDF v3.x. As of 8/2/2019, Espressif is in the process of transitioning ESP-IDF to use CMake as its build system from v4.x onwards.
 
 If you're just getting started with ESP-IDF and are depending upon this example precisely because you aren't
 sure what you're doing and want a "known-good" example project to follow, I highly recommend using v3.x of ESP-IDF instead.
 
 More precisely, if the instructions at https://docs.espressif.com/projects/esp-idf/en/latest/get-started/eclipse-setup.html still say
 anything about it being 'experimental' or 'pre-release', I *strongly* advise you to look at the older version of the docs instead:
 
 * For Windows users: https://docs.espressif.com/projects/esp-idf/en/stable/get-started/eclipse-setup-windows.html#eclipse-windows-setup
 
 * For everyone else: https://docs.espressif.com/projects/esp-idf/en/stable/get-started/eclipse-setup.html
 
 
 Alternate, time-saving approach that might work if you get lucky (but is likely to be at least slightly broken if you're reading this in 2019 or later). I've learned the hard way that step-by-step directions involving Github projects and IDEs have a half-life of approximately 3-9 months before one or more updates break them. You've been warned. Hence, the previous paragraph.
 
 **DO NOT** attempt to load this project into Eclipse until you've done `make menuconfig` and gotten it to successfully compile and flash at least once using the MinGW32 shell. Trust me... if it won't build and flash from the shell, it's going to be at least as dysfunctional in Eclipse, *guaranteed.*
 
 1. Load Eclipse
 
 2. File -> Open projects from file system
 
 3. Click `Directory...` button (after "Import source"), and select the directory where you checked out this repository (ex: c:\path\to\some-directory\u8g2-example_esp-idf_lolin32_ssd1306-i2c-sda5-scl4)
 
 4. It should find the project to import as "Eclipse project" & select its checkbox. Click `Finish`
 
 5. To build and flash, you can right-click "Build Targets -> flash" under the Project in Project Explorer.
 
 ## Tips
 
 * Make sure you don't have an open MinGW32 window where you ran `make monitor` or `make monitor flash` when you launch the "flash" build target from within Eclipse. If you get what appears to be an "access denied" error in Eclipse involving the serial port, this is almost certainly the REAL problem.
 
 * If you're running Windows and `make flash` times out, go back into `make menuconfig` and make sure your serial port looks like `COM4` (port number will vary, depending upon how Windows decides to enumerate your USB COM ports). If your serial port name begins with a forward-slash (as in, `/dev/tty`), it's wrong... find out the COMxx name of the USB serial port assigned to your ESP32 by Windows using Device Manager, and change it to that. I remember that in my case, ESP-IDF incorrectly defaulted to something like /dev/usbserial or something to that effect.
 
 * If you have the COM port set up correctly & `make flash` STILL times out, try *this* to forcibly keep the board in bootloader mode and prevent anything you might have already flashed to the board from taking control:
  1. Unplug the USB cable from your ESP32 board.
  2. While pressing and holding the 'BOOT' (or 'BT') button on the board, reconnect the USB cable. Don't release the button.
  3. Relaunch `make flash` while still pressing the button, and don't release it until `make flash` either finishes successfully or dies with an error.
  4. If it dies with an error or fails to work, try again... being *extra* careful to not release the BT/Boot button while or after plugging in the USB cable.
 
 * If you've gotten spoiled by IntelliJ and Android Studio, remember... Eclipse does NOT (by default, at least) auto-save source files for you when you build. I went through several hours of frustration before discovering this. If changes you've made don't seem to be getting flashed, make sure you saved the changed source files first.
 
 * If it doesn't build from the commandline, it's NOT going to build in Eclipse. Anything that causes a commandline build to fail will almost certainly cause an Eclipse build to fail as well... except you'll have a much harder time figuring out what the actual problem *is.*
 
 ## Credits
 
 Neil Kolban's esp32-snippets example code -- https://github.com/nkolban/esp32-snippets/tree/master/hardware/displays/U8G2
 
 Oli Kraus' u8g2 library -- https://github.com/olikraus/u8g2