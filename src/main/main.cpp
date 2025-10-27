#include <iostream>
#include <libusb.h>

int main() {
    libusb_device **devs;
    libusb_context *ctx = NULL;
    int r;
    ssize_t cnt;

    r = libusb_init(&ctx);
    if (r < 0) {
        std::cerr << "Init Error " << r << std::endl;
        return 1;
    }

    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, 3);
    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        std::cerr << "Get Device Error" << std::endl;
        libusb_exit(ctx);
        return 1;
    }

    std::cout << cnt << " Devices in list." << std::endl;

    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            std::cerr << "failed to get device descriptor" << std::endl;
            continue;
        }
        std::cout << "Vendor: " << desc.idVendor
                  << " Product: " << desc.idProduct << std::endl;
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);

    return 0;
}

awdaawdawdawdawdawdawdawdawdawdawdawdawdawdawdaawdawdadawdawdawdawdadad