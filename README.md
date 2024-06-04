| Supported Targets | ESP32 | 
| ----------------- | ----- | 

# _ESP32 CAM_

This is the simple example how to use ESP32_CAM. 

Code for handling avi files taken from https://github.com/rolinh/libgwavi/

## Prerequisites

1. Set target
```
idf.py set-target esp32
```

2. Add a dependency on espressif/esp32-camera component:

```
idf.py add-dependency "espressif/esp32-camera"
```

3. Enable PSRAM in menuconfig (also set Flash and PSRAM frequiencies to 80MHz)

