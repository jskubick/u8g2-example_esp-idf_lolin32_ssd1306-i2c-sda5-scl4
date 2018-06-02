/**	The purpose of this is to illustrate a fully-working example project
 *  that uses u8g2 with the built-in 128x64 OLED (connected via I2C using IO 4 & 5) in an
 *  esp-idf project that builds successfully in Eclipse.
 *  The commented-out code was part of the esp-idf template
 *  (from https://github.com/espressif/esp-idf-template) was left in place so you can
 *  compare it to the original template.
 *
 *  Most of the actual code was taken from examples shared by Neil Kolban on Github
 *  ( see https://github.com/nkolban/esp32-snippets/tree/master/hardware/displays/U8G2 ).
 */

// begin code NOT in the esp-idf template, but required for the display to work:
#define SDA_PIN 5
#define SCL_PIN 4
#define I2C_ADDRESS 0x78
#include "u8g2_esp32_hal.c"
#include <u8g2.h>

u8g2_t u8g2;

// The commented-out #include directives are part of the default esp-idf template, but
// aren't necessary for THIS specific example app. The #include for "esp_event.h" IS required.
//#include "freertos/FreeRTOS.h"
//#include "esp_wifi.h"
//#include "esp_system.h"
#include "esp_event.h"
//#include "esp_event_loop.h"
//#include "nvs_flash.h"
//#include "driver/gpio.h"



esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

/**
 * Initialize Neil Kolban's U8G2 HAL & configure it with the proper values for our board.
 */
void initDisplay() {
	u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	u8g2_esp32_hal.sda = SDA_PIN;
	u8g2_esp32_hal.scl = SCL_PIN;
	u8g2_esp32_hal_init(u8g2_esp32_hal);

	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8g2_esp32_i2c_byte_cb, u8g2_esp32_gpio_and_delay_cb);
	u8x8_SetI2CAddress(&u8g2.u8x8, I2C_ADDRESS);

	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
}

void printHello() {
	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
	u8g2_DrawStr(&u8g2, 0,15,"Hello!");
	u8g2_SendBuffer(&u8g2);

	// disclaimer: I have no idea what vTaskDelete does, or why/whether it's actually necessary.
	// I'm still a relative Noob with esp-idf myself.
	// I copied it blindly because that's what other example code I've seen has done.
	vTaskDelete(NULL);
}

void app_main(void)
{
	initDisplay();
	printHello();

	/****************************************************************
	 * The code from the official esp-idf template project follows,
	 * and is commented-out for two reasons:
	 *
	 * 1) Nothing in it is directly relevant to the task of this specific example
	 *    (showing how to use u8g2 on a Wemos LOLIN32 with onboard SSD1306 128x64 OLED
	 *    connected via I2C using the pins ordinarily called "GPIO4" and "GPIO5".
	 *
	 * 2) The template blinks a LED connected to GPIO4... which is an obvious problem,
	 *    since that pin is already being used by the OLED.
	 *
	 *
		nvs_flash_init();
		tcpip_adapter_init();
		ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
		wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
		ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
		ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
		ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
		wifi_config_t sta_config = {
			.sta = {
				.ssid = "access_point_name",
				.password = "password",
				.bssid_set = false
			}
		};
		ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
		ESP_ERROR_CHECK( esp_wifi_start() );
		ESP_ERROR_CHECK( esp_wifi_connect() );

		gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
		int level = 0;

		while (true) {
			 gpio_set_level(GPIO_NUM_4, level);
			 level = !level;
			 vTaskDelay(300 / portTICK_PERIOD_MS);
		}
	****************************************************************/
}



