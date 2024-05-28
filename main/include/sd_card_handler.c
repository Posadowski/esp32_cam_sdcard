#include "sd_card_handler.h"

static const char *TAG = "sd_card: ";

esp_err_t init_sd_card(void)
{
    // Initialize the SDMMC host structure
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    // SD slot configuration
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_config.width = 4; // Use 4 data lines

    // Optionally, set the clock speed
    // slot_config.freq_high = SDMMC_FREQ_HIGHSPEED;
    
    // Optionally, set the card to be pulled out and inserted (pull-up/pull-down)
    gpio_set_pull_mode(GPIO_NUM_15, GPIO_PULLUP_ONLY); // CMD
    gpio_set_pull_mode(GPIO_NUM_2, GPIO_PULLUP_ONLY);  // D0
    gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_ONLY);  // D1
    gpio_set_pull_mode(GPIO_NUM_12, GPIO_PULLUP_ONLY); // D2
    gpio_set_pull_mode(GPIO_NUM_13, GPIO_PULLUP_ONLY); // D3

    //Mounting the FAT file system
    const char mount_point[] = "/sdcard";
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    // Initialize card
    sdmmc_card_t* card;
    esp_err_t ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG,"Failed to mount file system. If the card is not formatted, format it.\n");
        } else {
            ESP_LOGE(TAG,"The SD card failed to initialize:  (%s).\n", esp_err_to_name(ret));
        }
        return ret;
    }

    // Karta pomyślnie zainicjalizowana i zamontowana
    ESP_LOGI(TAG,"SD card mounted on %s\n", mount_point);
    sdmmc_card_print_info(stdout, card);
    return ESP_OK;
}