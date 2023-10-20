#include <stdio.h>
#include "pico/stdlib.h"
#include "../modules/depg0213_epd/depg0213_epd.h"


depg0213_ret_t _epd_reset_cb(void *handle) {
    // Implement your hard reset function here,
    // RESET pin needs to be pulled low for at least 200us.
    return DEPG0213_OK;
}

depg0213_ret_t _epd_poll_busy(void *handle) {
    // Return DEPG0213_ERROR if timeout or error occurred.
    // Implement your GPIO read function here.
    return DEPG0213_OK;
}

depg0213_ret_t _epd_write_cmd_cb(void *handle, uint8_t *cmd, uint8_t len) {
    // handle is the user pointer
    // The first byte of the command need to set D/CX to low,
    // while the rest of the command parameters requires D/CX to be high.
    // Implement your SPI transmit function here.
    return DEPG0213_OK;
}

depg0213_ret_t _epd_write_data_cb(void *handle, uint8_t *data, uint16_t len) {
    // handle is the user pointer
    // Set D/CX to high while transmitting data.
    // Implement your SPI transmit function here.
    return DEPG0213_OK;
}

static unsigned char bitmap_bytes[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x7f, 0x80, 0x61, 0xe0, 0x7f, 0xc0,
        0x7f, 0xc0, 0x63, 0xc0, 0x7f, 0xc0,
        0x61, 0xe0, 0x67, 0x80, 0x60, 0x00,
        0x60, 0xe0, 0x6f, 0x00, 0x60, 0x00,
        0x60, 0x60, 0x7e, 0x00, 0x60, 0x00,
        0x60, 0x60, 0x7c, 0x00, 0x7f, 0x80,
        0x60, 0x60, 0x7e, 0x00, 0x7f, 0x80,
        0x60, 0xe0, 0x7f, 0x00, 0x60, 0x00,
        0x60, 0xe0, 0x67, 0x80, 0x60, 0x00,
        0x61, 0xe0, 0x63, 0xc0, 0x60, 0x00,
        0x7f, 0xc0, 0x61, 0xe0, 0x7f, 0xc0,
        0x7f, 0x80, 0x60, 0xf0, 0x7f, 0xc0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


int main() {
    setup_default_uart();
    printf("Hello, World!\n");

    depg0213_epd_t epd = {
            .user_data = &bitmap_bytes,
            .cb = {
                    .reset_cb = _epd_reset_cb,
                    .poll_busy_cb = _epd_poll_busy,
                    .write_cmd_cb = _epd_write_cmd_cb,
                    .write_data_cb = _epd_write_data_cb
            }
    };

    depg0213_epd_init(&epd);



    return 0;
}
