#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Dr DAQ用ヘッダファイルのインクルード
#include <libusbdrdaq/usbDrDaqApi.h>
#ifndef PICO_STATUS
#include <libusbdrdaq/PicoStatus.h>

#endif

// device handle
int16_t handle;

// APIの返り値を格納する変数

PICO_STATUS status;

int main(int arvc, char *argv[]) {
    //    デバイスオープン

    printf("Opening the device...\n");
    status = UsbDrDaqOpenUnit(&handle);
    if (status != PICO_OK) {
        printf("Unable to open Dr.DAQ device\n");
        return EXIT_FAILURE;

    }

    printf("OK\n");
    printf("Enabling LED...\n");
    status = UsbDrDaqEnableRGBLED(handle, (int16_t) 1);
    if (status != PICO_OK) {
        printf("Unable to enable LED \n");
        return EXIT_FAILURE;
    }
    //キー入力待ち
    getchar();

    //LED点灯
    UsbDrDaqSetRGBLED(handle, 255, 0, 0);
    sleep(2);
    UsbDrDaqSetRGBLED(handle, 0, 0, 0);
    sleep(1);

    UsbDrDaqSetRGBLED(handle, 0, 255, 0);
    sleep(2);
    UsbDrDaqSetRGBLED(handle, 0, 0, 0);
    sleep(1);

    UsbDrDaqSetRGBLED(handle, 0, 0, 255);
    sleep(2);
    UsbDrDaqSetRGBLED(handle, 0, 0, 0);
    sleep(1);

    printf("Done.\n");

    //    RGBLED disable
    UsbDrDaqSetRGBLED(handle, (int16_t) 0);

    //    Close device
    UsbDrDaqCloseUnit(handle);
    return EXIT_SUCCESS;

}

