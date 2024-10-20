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

4. Use custom partitions table

```bash
idf.py menuconfig
```

Partitions Table --->
    Partition Table --->
        Custom partition table CSV

## Connect USB devices to WSL

If you are using WSL for embedded programming, you will need to connect a USB to it

### Attach a USB device

1. List all of the USB devices connected to Windows by opening PowerShell

```PowerShell
usbipd list
```

2. Find the device you want to connect to wsl

```PowerShell
usbipd bind --busid <busid>
```
3. To attach the USB device, run the following command. (You no longer need to use an elevated administrator prompt.) 
Ensure that a WSL command prompt is open in order to keep the WSL 2 lightweight VM active. 
Note that as long as the USB device is attached to WSL, it cannot be used by Windows. Once attached to WSL, the USB device can be used by any distribution running as WSL 2. 
Verify that the device is attached using usbipd list. From the WSL prompt, run lsusb to verify that the USB device is listed and can be interacted with using Linux tools.

```PowerShell
usbipd attach --wsl --busid <busid>
```

4. Open Debian (or your preferred WSL command line)
list the attached USB devices using the command:

```bash
lsusb
```

5. Once you are done using the device in WSL, you can either physically disconnect the USB device or run this command from PowerShell:

```PowerShell
usbipd detach --busid <busid>
```


## The device appears via lsusb but is not visible in /dev/

1. Check if the driver is loaded

The driver for CP210x should be loaded on your system. You can check if it is present using the command below:

```bash
lsmod | grep cp210x
```
If you don't see any results, you may need to load the driver:

```bash
sudo modprobe cp210x
```

2. dmesg check

Try to check if the system detects the device but does not create the appropriate file in /dev/:

```bash
dmesg | grep cp210x
```

If the system detects the device but the file in /dev/ still does not appear, it is worth paying attention to possible error messages in the dmesg output

3. Reinstalling drivers

If the above steps do not work, try installing or updating the driver for CP210x, e.g. on Debian/Ubuntu systems:

```bash
sudo apt-get install cp210x-dkms
```