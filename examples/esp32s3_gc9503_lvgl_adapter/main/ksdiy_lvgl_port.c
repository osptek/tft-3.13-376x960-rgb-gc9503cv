#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_timer.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_gc9503.h"
#include "esp_ldo_regulator.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lv_demos.h"
#include "driver/i2c_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_io_additions.h"
#include "esp_lv_adapter.h"

static const char *TAG = "example";


#define JPG_IMAGE_MAX_SIZE (450 * 1024)


#define EXAMPLE_LCD_NUM_FB 2
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ (16 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL 1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_BK_LIGHT 4
#define EXAMPLE_PIN_NUM_HSYNC 6
#define EXAMPLE_PIN_NUM_VSYNC 5
#define EXAMPLE_PIN_NUM_DE 15
#define EXAMPLE_PIN_NUM_PCLK 7

#define EXAMPLE_PIN_NUM_DATA0 47 // B0
#define EXAMPLE_PIN_NUM_DATA1 21 // B1
#define EXAMPLE_PIN_NUM_DATA2 14 // B2
#define EXAMPLE_PIN_NUM_DATA3 13 // B3
#define EXAMPLE_PIN_NUM_DATA4 12 // B4

#define EXAMPLE_PIN_NUM_DATA5 11  // G0
#define EXAMPLE_PIN_NUM_DATA6 10  // G1
#define EXAMPLE_PIN_NUM_DATA7 9   // G2
#define EXAMPLE_PIN_NUM_DATA8 46  // G3
#define EXAMPLE_PIN_NUM_DATA9 3   // G4
#define EXAMPLE_PIN_NUM_DATA10 20 // G5

#define EXAMPLE_PIN_NUM_DATA11 19 // R0
#define EXAMPLE_PIN_NUM_DATA12 8  // R1
#define EXAMPLE_PIN_NUM_DATA13 18 // R2
#define EXAMPLE_PIN_NUM_DATA14 17 // R3
#define EXAMPLE_PIN_NUM_DATA15 16 // R4

#define EXAMPLE_PIN_NUM_DISP_EN -1

#define TEST_LCD_IO_SPI_CS_1 (GPIO_NUM_48)
#define TEST_LCD_IO_SPI_SCL_1 (GPIO_NUM_17)
#define TEST_LCD_IO_SPI_SDO_1 (GPIO_NUM_16)

#define EXAMPLE_LCD_H_RES 376
#define EXAMPLE_LCD_V_RES 960
static lv_disp_t *lvgl_disp = NULL;
bool ksdiy_lvgl_lock(int timeout_ms)
{
    return esp_lv_adapter_lock(timeout_ms) == ESP_OK;
}
void ksdiy_lvgl_unlock(void)
{
    esp_lv_adapter_unlock();
}
void ksdiy_lvgl_port_init(void)
{
  

#if EXAMPLE_PIN_NUM_BK_LIGHT >= 0
    ESP_LOGI(TAG, "Turn off LCD backlight");
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << EXAMPLE_PIN_NUM_BK_LIGHT};
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));
#endif
#if EXAMPLE_PIN_NUM_BK_LIGHT >= 0
    ESP_LOGI(TAG, "Turn on LCD backlight");
    gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);
#endif

    ESP_LOGI(TAG, "Install 3-wire SPI panel IO");
    spi_line_config_t line_config = {
        .cs_io_type = IO_TYPE_GPIO,
        .cs_gpio_num = TEST_LCD_IO_SPI_CS_1,
        .scl_io_type = IO_TYPE_GPIO,
        .scl_gpio_num = TEST_LCD_IO_SPI_SCL_1,
        .sda_io_type = IO_TYPE_GPIO,
        .sda_gpio_num = TEST_LCD_IO_SPI_SDO_1,
        .io_expander = NULL,
    };
    esp_lcd_panel_io_3wire_spi_config_t io_config = GC9503_PANEL_IO_3WIRE_SPI_CONFIG(line_config, 0);
    esp_lcd_panel_io_handle_t io_handle = NULL;
    (esp_lcd_new_panel_io_3wire_spi(&io_config, &io_handle));

    ESP_LOGI(TAG, "Install RGB LCD panel driver");
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_rgb_panel_config_t rgb_config = {
        .data_width = 16, // RGB565 in parallel mode, thus 16bit in width
        .bits_per_pixel = 16,
        .dma_burst_size = 64,
        .num_fbs = EXAMPLE_LCD_NUM_FB,
        .bounce_buffer_size_px = 30 * EXAMPLE_LCD_H_RES,
        .clk_src = LCD_CLK_SRC_PLL160M,
        .disp_gpio_num = EXAMPLE_PIN_NUM_DISP_EN,
        .pclk_gpio_num = EXAMPLE_PIN_NUM_PCLK,
        .vsync_gpio_num = EXAMPLE_PIN_NUM_VSYNC,
        .hsync_gpio_num = EXAMPLE_PIN_NUM_HSYNC,
        .de_gpio_num = EXAMPLE_PIN_NUM_DE,
        .data_gpio_nums = {
            EXAMPLE_PIN_NUM_DATA0,
            EXAMPLE_PIN_NUM_DATA1,
            EXAMPLE_PIN_NUM_DATA2,
            EXAMPLE_PIN_NUM_DATA3,
            EXAMPLE_PIN_NUM_DATA4,
            EXAMPLE_PIN_NUM_DATA5,
            EXAMPLE_PIN_NUM_DATA6,
            EXAMPLE_PIN_NUM_DATA7,
            EXAMPLE_PIN_NUM_DATA8,
            EXAMPLE_PIN_NUM_DATA9,
            EXAMPLE_PIN_NUM_DATA10,
            EXAMPLE_PIN_NUM_DATA11,
            EXAMPLE_PIN_NUM_DATA12,
            EXAMPLE_PIN_NUM_DATA13,
            EXAMPLE_PIN_NUM_DATA14,
            EXAMPLE_PIN_NUM_DATA15,
        },
        .timings = GC9503_376_960_PANEL_60HZ_RGB_TIMING(),
        .flags= {
            .fb_in_psram = true, // allocate frame buffer in PSRAM
        }
    };

    ESP_LOGI(TAG, "Initialize RGB LCD panel");

    gc9503_vendor_config_t vendor_config = {
        .rgb_config = &rgb_config,
        .flags = {
            .mirror_by_cmd = 0,
            .auto_del_panel_io = 1,
        },
    };
    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = -1,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
        .vendor_config = &vendor_config,
    };
    (esp_lcd_new_panel_gc9503(io_handle, &panel_config, &panel_handle));
    (esp_lcd_panel_reset(panel_handle));
    (esp_lcd_panel_init(panel_handle));


#if EXAMPLE_PIN_NUM_BK_LIGHT >= 0
    ESP_LOGI(TAG, "Turn on LCD backlight");
    gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);
#endif

  
    
    ESP_LOGI(TAG, "Initialize LVGL adapter");
    const esp_lv_adapter_config_t adapter_config = ESP_LV_ADAPTER_DEFAULT_CONFIG();
    ESP_ERROR_CHECK(esp_lv_adapter_init(&adapter_config));

    ESP_LOGI(TAG, "Register LCD display to LVGL");

       esp_lv_adapter_display_config_t disp_cfg = {
        .panel = panel_handle,
        .panel_io = io_handle,
        .profile = {
            .interface = ESP_LV_ADAPTER_PANEL_IF_RGB,
            .rotation = ESP_LV_ADAPTER_ROTATE_0,
            .hor_res = EXAMPLE_LCD_H_RES,
            .ver_res = EXAMPLE_LCD_V_RES,
            .buffer_height = EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES, 
            .use_psram = true,
            .enable_ppa_accel = false,
            .require_double_buffer = true,  
        },
        .tear_avoid_mode = ESP_LV_ADAPTER_TEAR_AVOID_MODE_DOUBLE_FULL,
    };
    lvgl_disp = esp_lv_adapter_register_display(&disp_cfg);
    if (lvgl_disp == NULL) {
        ESP_LOGE(TAG, "Failed to register display");
        return;
    }

    ESP_LOGI(TAG, "Start LVGL adapter task");
    ESP_ERROR_CHECK(esp_lv_adapter_start());

}
