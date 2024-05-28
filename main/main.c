#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include <string.h>

#include "include/camera_handler.h"
#include "include/sd_card_handler.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// support IDF 5.x
#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif

#define MOUNT_POINT "/sdcard" 

static const char *TAG = "main: ";

void app_main(void)
{
#if ESP_CAMERA_SUPPORTED
    if(ESP_OK != init_camera()) {
        return;
    }
#endif

    if(ESP_OK != init_sd_card()) {
        return;
    }


    while(1){
        camera_fb_t *pic;
         ESP_LOGI(TAG, "Taking picture...");
         pic = esp_camera_fb_get();

        // use pic->buf to access the image
         ESP_LOGI(TAG, "Picture taken! Its size was: %zu bytes", pic->len);
         
                char file_path[64];
        snprintf(file_path, sizeof(file_path), MOUNT_POINT"/picture.jpg");
        FILE *file = fopen(file_path, "w");
        if (file != NULL) {
            fwrite(pic->buf, 1, pic->len, file);
            fclose(file);
            ESP_LOGI(TAG, "File saved: %s", file_path);
        } else {
            ESP_LOGE(TAG, "Failed to open file for writing");
        }
        
         esp_camera_fb_return(pic);

        vTaskDelay(5000 / portTICK_RATE_MS);
    }
}
