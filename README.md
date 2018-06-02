This is an example project to illustrate how to use the onboard 128x64 OLED display
(connected via I2C, hardwired to the pins used by GPIO 4 and 5) in an ESP-IDF project.

The project was created using Eclipse (Oxygen) on Windows.

If you figure out how to turn it into a CLion or PlatformIO project, PLEASE fork it and share it on Github.

# How to build

If you haven't already done it, go to https://esp-idf/readthedocs.io & follow the directions in the "Get Started" section to download and set up the ESP-IDF
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



Now, open the MinGW32 shell, and...

`cd /c/path/to/some-directory/u8g2-example_esp-idf_lolin32_ssd1306-i2c-sda5-scl4` (note the forward slashes and notation for the c: drive)

## Critical next steps:

Ensure your LOLIN32 board is connected to the USB port, and that you DON'T already have a serial monitor window opened to it

`make menuconfig`

 cursor-down to "Serial flasher config".
 
 * Make sure "Default serial port" is set to the correct port. If you're running Windows, this will be something like `COM7` 
 
 * If desired, set the default baud rate to 230400 or 921600.
 
 * After flashing (Reset after flashing) and change if necessary.
 
 * set 'make monitor' baud rate to 115200bps
 
 * Exit, Exit.
 
 The moment of truth: `make monitor flash`
 
 If you get lucky, it will successfully compile, and in a few moments you'll be greeted by "Hello!" on the OLED.
 
 ## Now, get it to work in Eclipse...
 
 Follow the directions at https://esp-idf.readthedocs.io/en/latest/get-started/eclipse-setup.html (note & follow the alternate setup instructions for Windows,
 if applicable).
