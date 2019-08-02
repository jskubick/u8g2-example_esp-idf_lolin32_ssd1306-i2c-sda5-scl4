This is a complete example Eclipse project to illustrate how to use the onboard 128x64 OLED display
(connected via I2C, hardwired to the pins used by GPIO 4 and 5) using the u8g2 library in an ESP-IDF **3.x** project.

This is the exact board used and tested: https://amazon.com/gp/product/B072HBW53G

The project was created using Eclipse (originally "Oxygen", most recently 2019.6) on Windows.

# Warning

This project uses Git submodules, and *specifically* has dependencies upon ESP-IDF **v3.x**. If you don't know what this means, or why it matters, read every single sentence of the "Prerequisites" and "Download" sections carefully, or it's probably not going to work.

# Prerequisites

Follow the directions at https://docs.espressif.com/projects/esp-idf/en/stable/get-started/ to set up your toolchain.

When you get to the section on "Get ESP-IDF", it should look something like this:

    cd ~/esp
	git clone -b v3.2.2 --recursive https://github.com/espressif/esp-idf.git
	
**Make sure** that it includes the "-b v3.2.2", with a version that's "v3.2" (though a later release of 3.2, like "v3.2.3", should be fine). Newer releases of ESP-IDF (specifically, v4 and beyond) are likely to break this example project, because Espressif changed the default build system from 'make' to 'CMake'. It doesn't matter (much) if you're building from the MinGW shell, but will probably cause the project to fail to build in Eclipse.

Be sure you can at least build and run the hello_world project from the esp-idf examples/get-started/ directory, then continue with the directions for setting up Eclipse.

# Download

Assuming that "c:\path\to\some-directory" is the path to wherever you want the project to go:

`cd c:\path\to\some-directory`

`git clone --recursive https://github.com/jskubick/u8g2-example_esp-idf_lolin32_ssd1306-i2c-sda5-scl4.git`

Don't forget the "--recursive" flag. It's important. If you omit it, Git won't fetch the files for u8g2, and compilation will fail.


# Get it to work with MinGW32:

open the MinGW32 shell, and...

`cd /c/path/to/some-directory/u8g2-example_esp-idf_lolin32_ssd1306-i2c-sda5-scl4` (note the forward slashes and notation for the c: drive)

Ensure your LOLIN32 board is connected to the USB port, and that you DON'T already have a serial monitor window opened to it

`make menuconfig`

 cursor-down to "Serial flasher config".
 
 * Make sure "Default serial port" is set to the correct port. If you're running Windows, this will be something like `COM4`
 
 Additional settings from "Serial flasher config" --
 
 * Default baud rate can be 230400 or 921600 (your choice)
 
 * After flashing (Reset after flashing)
 
 * 'make monitor' baud rate: 115200bps
 
 * Exit, Exit. When asked whether you want to save your new configuration, say yes.
 
 The moment of truth: `make monitor flash`
 
 If you get lucky, it will successfully compile, and in a few moments you'll be greeted by "Hello!" on the OLED.
 
 # Get it to work in Eclipse...
 
  **DO NOT** attempt to load this project into Eclipse until you've done `make menuconfig` and gotten it to successfully compile and flash at least once using the MinGW32 shell via `make flash`. Trust me... if you can't get it to build and flash from the shell, **it's not going to magically work in Eclipse, either**. 
  
  **WARNING** This entire example project assumes that you're using ESP-IDF v3.x. As of August 2019, 3.x is still the 'stable' release, but the LATEST release is 4.x. ESP-IDF 4.x makes a major change to the way projects are built (using CMake instead of Make), which ultimately changes the steps for getting it to work in Eclipse (and might affect whether you'd necessarily *want* to use Eclipse in the first place, as opposed to CLion, PlatformIO, or something else). 
 
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

Run `make menuconfig` and make sure your serial port's name looks something like `COM4`, and **not** like `/dev/tty`, `/dev/ttyUSB0`, or `/dev/COM4`.

### You have the COM port set up correctly, but "make flash" *still* times out
	
Your board might have something dropping it out of bootloader mode. Try this:
1. Unplug the USB cable from your ESP32 board.
2. While pressing and holding the button marked 'Boot' or 'BT', reconnect the USB cable. Make sure you don't accidentally release the button... not even for an instant.
3. Relaunch `make flash`. Remember, the button has to remain continuously pressed from the moment you plug in the USB cable until the moment `make flash` either succeeds or fails.
4. If it fails... try again, being *extra careful* this time to avoid releasing the button.
	
### Eclipse gives you an error like, `Program 'xtensa-esp32-elf-gcc' not found in PATH`

Review steps 5-7 of the instructions for loading the project into Eclipse. Basically, PATH (and almost certainly, IDF_PATH) are pointing to somewhere that is valid on my computer, but not on yours.

### An error message implies that "u8g2" is missing

You probably forgot the "--recursive" flag when checking out the project from Github. To fix it, cd to the project's root directory and execute `git submodule update --init --recursive`

 
 ## Credits
 
 Neil Kolban's esp32-snippets example code -- https://github.com/nkolban/esp32-snippets/tree/master/hardware/displays/U8G2
 
 Oli Kraus' u8g2 library -- https://github.com/olikraus/u8g2