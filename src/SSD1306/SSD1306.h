#pragma once

#include <Core/Window/Window.h>


#define OLED_ADDRESS 0x3C

#define SET_CONTRAST 0x81
#define SET_ENTIRE_ON 0xA4
#define SET_NORM_INV 0xA6
#define SET_DISP 0xAE
#define SET_MEM_ADDR 0x20
#define SET_COL_ADDR 0x21
#define SET_PAGE_ADDR 0x22
#define SET_DISP_START_LINE 0x40
#define SET_SEG_REMAP 0xA0
#define SET_MUX_RATIO 0xA8
#define SET_COM_OUT_DIR 0xC8
#define SET_DISP_OFFSET 0xD3
#define SET_COM_PIN_CFG 0xDA
#define SET_DISP_CLK_DIV 0xD5
#define SET_PRECHARGE 0xD9
#define SET_VCOM_DESEL 0xDB
#define SET_CHARGE_PUMP 0x8D
#define SET_SCROLL 0x2E
#define SET_HOR_SCROLL 0x26
#define SET_COM_OUT_DIR_REVERSE 0xC0

namespace PetrolEngine{
    class SSD1306 : public WindowApi {
    public:
        const uint8 WIDTH = 128;
        const uint8 HEIGHT = 64;

        bool flipped = false;

        uint8 bufferSize;
        uint8 pages;

        uint8_t BUFFER[1024];

        void drawPixel(uint8_t x, uint8_t y) {
            BUFFER[x + WIDTH * (y / 8)] |= 0x01 << (y % 8);
        }


        void clear();
        void swapBuffers() override;

        // dummy functions
        void showCursor(bool show   ) override {};
        void setVSync  (bool enabled) override {};
        void setIcon   (Image* image) override {};
        void pollEvents(            ) override {};
        void close     (            ) override {};

        int init() override {};

        bool shouldClose() override { return false; };
        bool isPressed(Keys key) override { return false; };

        void (*write_cmd )(uint8);
        void (*write_data)(uint8);

        SSD1306();
        ~SSD1306() override = default;
    };
}