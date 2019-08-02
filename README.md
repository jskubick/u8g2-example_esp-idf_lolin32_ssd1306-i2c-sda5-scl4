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
 
  **DO NOT** attempt to load this project into Eclipse until you've done `make menuconfig` and gotten it to successfully compile and flash at least once using the MinGW32 shell via `make flash`. Trust me... if you can't get it to build and flash from the shell, **it's not going to magically work in Eclipse, either**. Everything that causes it to be dysfunctional and break in the shell is going to make it even *more* dysfunctional, and cause it to break in Eclipse as well. Fix the shell-build errors *first*.
  
  **WARNING** This entire example project assumes that you're using ESP-IDF v3.x. As of August 2019, 3.x is still the 'stable' release, but the LATEST release is 4.x. ESP-IDF 4.x makes a major change to the way projects are built (using CMake instead of Make), which ultimately changes the steps for getting it to work in Eclipse (and might affect whether you'd necessarily *want* to use Eclipse in the first place, as opposed to CLion, PlatformIO, or something else). 
 
 If you want this example project to work without major headaches, you **must** have ESP-IDF v3.x installed. If you didn't ***explicitly*** go out of your way to check out a 3.x/stable release of ESP-IDF, you probably got the 'latest' release... which is going to be 4.x or later... and almost certainly won't work with Eclipse using the directions that follow.
 
 I apologize for the confusion, but it's just a sad fact of life. Build tools and SDKs are, almost by definition, bleeding-edge and volatile. The useful half-life of any tutorial that tries to provide step-by-step instructions is approximately 3-9 months before something breaks it.
 
 So... assuming you explicitly have ESP-IDF v3.x and you're using Eclipse Oxygen through Eclipse Cpp 2019-06, this should work. The further you diverge, the more likely something is going to at least slightly break.
 
 1. Load Eclipse
 
 2. File -> Open projects from file system
 
 3. Click `Directory...` button (after "Import source"), and select the directory where you checked out this repository (ex: c:\path\to\some-directory\u8g2-example_esp-idf_lolin32_ssd1306-i2c-sda5-scl4)
 
 4. It should find the project to import as "Eclipse project" & select its checkbox. Click `Finish`
 
 5. Right-click the project in "Project Explorer" and select 'Properties'.

 6. Expand "C/C++ Build", then select 'Environment'.
 
 7. Update the values of IDF_PATH and PATH to reflect your system. 
     * For IDF_PATH, the '/root/' part is almost guaranteed to be wrong on your system. 
	 * If you're running Windows and unzipped Espressif's toolchail set into its default destination ("c:\msys32"), you MIGHT not have to make any changes to PATH. 
 
 8. To build and flash, you can right-click "Build Targets -> flash" under the Project in Project Explorer.
 
 ## Troubleshooting
 
 ### Access Denied error involving the serial port

Make sure you don't have an open MinGW32 window where you ran `make monitor` or `make monitor flash` when you launch the "flash" build target within Eclipse.

### `make flash` times out when you try to run it under Windows

Run `make menuconfig` and make sure your serial port's name looks something like `COM4`, and **not** like `/dev/tty` or `/dev/usbserial`. Just to be perfectly clear, if you're running Windows and your serial port's name begins with a forward-slash... it's **wrong**.

### You have the COM port set up correctly, but "make flash" *still* times out
	
Your board might have something dropping it out of bootloader mode. Try this:
1. Unplug the USB cable from your ESP32 board.
2. While pressing and holding the button marked 'Boot' or 'BT', reconnect the USB cable. Make sure you don't accidentally release the button... not even for an instant.
3. Relaunch `make flash`. Remember, the button has to remain continuously pressed from the moment you plug in the USB cable until the moment `make flash` either succeeds or fails.
4. If it fails... try again, being *extra careful* this time to avoid releasing the button.
	
### Eclipse gives you an error like, `Program 'xtensa-esp32-elf-gcc' not found in PATH`

Review steps 5-7 of the instructions for loading the project into Eclipse. Basically, PATH (and almost certainly, IDF_PATH) are pointing to somewhere that is valid on my computer, but not on yours.

 
 ## Credits
 
 Neil Kolban's esp32-snippets example code -- https://github.com/nkolban/esp32-snippets/tree/master/hardware/displays/U8G2
 
 Oli Kraus' u8g2 library -- https://github.com/olikraus/u8g2