#ifndef SD_CARD_HANDLER_H_
#define SD_CARD_HANDLER_H_

#include <stdio.h>

#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include <string.h>

#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"



esp_err_t init_sd_card(void);

#endif //SD_CARD_HANDLER_H_