#include <iostream>
#include <libusb.h>


// 찾을 USB 장치의 제품 ID
const int PRODUCT_ID = 24577;

ssize_t print_dev_list(libusb_context *ctx){
    ssize_t cnt = 0;
    libusb_device **devs;

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

    return cnt;
}

// 지정된 제품 ID를 가진 USB 장치를 찾아 핸들을 반환하는 함수
libusb_device_handle* find_device(libusb_context *ctx, uint16_t product_id) {
    libusb_device **devs; // 장치 목록을 저장할 포인터
    // 시스템의 모든 USB 장치 목록을 가져옵니다.
    ssize_t cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        std::cerr << "Get Device Error" << std::endl;
        return NULL;
    }

    libusb_device_handle *handle = NULL; // 열린 장치 핸들
    // 장치 목록을 순회하며 일치하는 제품 ID를 찾습니다.
    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device_descriptor desc; // 장치 디스크립터
        // 현재 장치의 디스크립터를 가져옵니다.
        int r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            continue;
        }

        // 제품 ID가 일치하는지 확인합니다.
        if (desc.idProduct == product_id) {
            // 장치를 엽니다.
            r = libusb_open(devs[i], &handle);
            if (r < 0) {
                std::cerr << "Failed to open device" << std::endl;
                handle = NULL;
            }
            break; // 장치를 찾고 열었으므로 루프를 종료합니다.
        }
    }

    // 장치 목록을 해제합니다.
    libusb_free_device_list(devs, 1);
    return handle; // 열린 장치 핸들을 반환합니다.
}



int main() {
    libusb_context *ctx = NULL;
    int r = libusb_init(&ctx);
    if (r < 0) {
        std::cerr << "Init Error " << r << std::endl;
        return 1;
    }
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, 3); // for debuging


    ssize_t cnt = print_dev_list(ctx);
    



    // libusb_device_handle *handle = find_device(ctx, PRODUCT_ID);

    // if (!handle) {
    //     std::cerr << "Device not found or could not be opened." << std::endl;
    //     libusb_exit(ctx);
    //     return 1;
    // }

    // std::cout << "Device found and opened." << std::endl;


    // libusb_device **devs;
    // libusb_context *ctx = NULL;
    // int r;
    // ssize_t cnt;

    // r = libusb_init(&ctx);
    // if (r < 0) {
    //     std::cerr << "Init Error " << r << std::endl;
    //     return 1;
    // }

    // libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, 3);
    // cnt = libusb_get_device_list(ctx, &devs);
    // if (cnt < 0) {
    //     std::cerr << "Get Device Error" << std::endl;
    //     libusb_exit(ctx);
    //     return 1;
    // }

    // std::cout << cnt << " Devices in list." << std::endl;

    // for (ssize_t i = 0; i < cnt; i++) {
    //     libusb_device_descriptor desc;
    //     int r = libusb_get_device_descriptor(devs[i], &desc);
    //     if (r < 0) {
    //         std::cerr << "failed to get device descriptor" << std::endl;
    //         continue;
    //     }
    //     std::cout << "Vendor: " << desc.idVendor
    //               << " Product: " << desc.idProduct << std::endl;
    // }

    // libusb_free_device_list(devs, 1);
    // libusb_exit(ctx);

    return 0;
}

