/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "ksdiy_lvgl_port.h"
#include "lv_demos.h"

static const char *TAG = "app_main";

void app_main(void)
{

    // 初始化LVGL port
    ksdiy_lvgl_port_init();
    ESP_LOGI(TAG, "LVGL port initialized");
    if (ksdiy_lvgl_lock(100))  // 尝试获取锁，超时 100ms
    {
        lv_demo_music();             // 初始化 UI 界面（由 SquareLine Studio 生成）
        ksdiy_lvgl_unlock();   // 释放锁
    }
}