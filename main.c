#include <stdlib.h>
#include <stdio.h>
//#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>

#include </Applications/PicoScope 6.app/Contents/Resources/include/libusbdrdaq-1.0/usbDrDaqApi.h>

#ifndef PICO_STATUS

#include </Applications/PicoScope 6.app/Contents/Resources/include/libusbdrdaq-1.0/PicoStatus.h>

#endif

//デバイスハンドル
PICO_STATUS status;
int16_t handle;

static volatile sig_atomic_t eflag = 0;

static void handler(int signum) {
    eflag = 1;
}

int main(int argc, char *argv[]) {
    // データ取得時間問隔（3秒単位
    uint64_t interval = 3;
    uint64_t i;
    float value;
    uint16_t overflow;
    uint32_t c;
    // ctr + cで終了
    if (signal(SIGINT, handler) == SIG_ERR) {
        return EXIT_FAILURE;
    }
    // もし引き数があれば、最初の引き数を数値に変換した値をデータ取得問隔とする
    if (argc > 1) {
        interval = (uint64_t) strtoul(argv[1], NULL, 10);
        //　ただし0秒にならないようにする
        if (interval == 0) {
            interval = 1;
        }
    }

    status = UsbDrDaqOpenUnit(&handle);

    if (status != PICO_OK) {
        fprintf(stderr,
               "Unable to open DrDaq \n");
        return EXIT_FAILURE;
    }

    status = UsbDrDaqPhTemperatureCompensation(handle, 1);

    if (status != PICO_OK) {
        fprintf(stderr, "UsbDrDaqPhTemperatureCompensation action failed. return value: %d\n", (int32_t) status);

    }
    i = 0;
    while (eflag != 1) {
        printf("%llu\t", i);
        for (c = 1; c <= USB_DRDAQ_MAX_CHANNELS; c++) {
            value = 0;
            status = UsbDrDaqGetSingleF(handle, (USB_DRDAQ_INPUTS) c, &value, &overflow);
            printf("%4.2f\t", value);
        }
            printf("\n");
            fflush(stdout);
            i += interval;
            sleep(interval);
        }
    fprintf(stderr, "Aborted \n");
    UsbDrDaqCloseUnit(handle);

    return EXIT_SUCCESS;
}
