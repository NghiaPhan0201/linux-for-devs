

# LED Character Device Driver

This project implements a simple Linux character device driver (`led_driver`) and a userspace application (`led_app`) that interacts with it. The driver creates a device file (`/dev/led_device`) which, when written with the strings "on" or "off", prints corresponding kernel messages: `LED: turn led on` or `LED: turn led off`.

## Project Structure
- `led_driver.c`: Source code for the kernel module that implements the character device driver.
- `led_app.c`: Source code for the userspace application that writes "on" or "off" to the device file.
- `Makefile`: Script to build the kernel module and the userspace application.

## Prerequisites
- A Linux system with kernel headers installed for the running kernel version (e.g., `linux-headers-5.15.0-139-generic`).
- `gcc` and `make` for compiling the userspace application and kernel module.
- Root privileges (`sudo`) for installing the kernel module and modifying device file permissions.

Install required tools:
```bash
sudo apt-get install build-essential linux-headers-$(uname -r)
```

## Building the Project
1. Clone or download the project to your local machine.
2. Navigate to the project directory:
   ```bash
   cd /path/to/L12_13_Basic_Kernel_Module
   ```
3. Clean any previous build artifacts:
   ```bash
   make clean
   ```
4. Build the kernel module (`led_driver.ko`) and the userspace application (`led_app`):
   ```bash
   make
   ```

This will generate:
- `led_driver.ko`: The kernel module.
- `led_app`: The userspace executable.

## Installing the Kernel Module
1. Load the kernel module into the kernel:
   ```bash
   sudo insmod led_driver.ko
   ```
2. Verify that the device file `/dev/led_device` is created:
   ```bash
   ls /dev/led_device
   ```
3. If the device file is not accessible, grant read/write permissions:
   ```bash
   sudo chmod 666 /dev/led_device
   ```
4. Check kernel logs to confirm the module loaded successfully:
   ```bash
   dmesg | grep LED
   ```
   You should see a message like:
   ```
   LED: Driver initialized, Major=...
   ```

## Running the Userspace Application
1. Run the application to send the "on" command:
   ```bash
   ./led_app on
   ```
   Expected output:
   ```
   Command 'on' sent to device
   ```
2. Check kernel logs to verify the driver response:
   ```bash
   dmesg | grep LED
   ```
   You should see:
   ```
   LED: turn led on
   ```
3. Repeat for the "off" command:
   ```bash
   ./led_app off
   ```
   Expected kernel log:
   ```
   LED: turn led off
   ```

## Cleaning Up
1. Unload the kernel module:
   ```bash
   sudo rmmod led_driver
   ```
2. Verify the module is removed by checking kernel logs:
   ```bash
   dmesg | grep LED
   ```
   You should see:
   ```
   LED: Driver unloaded
   ```
3. Clean build artifacts:
   ```bash
   make clean
   ```

## Troubleshooting
- **Error: `./led_app: No such file or directory`**:
  - Ensure `led_app.c` exists and `make` includes the `gcc -o led_app led_app.c` command in the `Makefile`.
  - Run `gcc -o led_app led_app.c` manually to check for compilation errors.
  - Verify `gcc` is installed: `sudo apt-get install build-essential`.
- **Error: `/dev/led_device not found`**:
  - Check kernel logs with `dmesg | grep LED` to diagnose module loading issues.
  - Ensure the module is loaded: `sudo insmod led_driver.ko`.
- **Permission denied when running `./led_app`**:
  - Grant permissions to the device file: `sudo chmod 666 /dev/led_device`.
- **Compilation errors**:
  - Ensure kernel headers match the running kernel: `uname -r` and `sudo apt-get install linux-headers-$(uname -r)`.


