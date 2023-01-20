//
// Created by samuel on 12/25/22.
//

#include "SSD1306.h"

namespace PetrolEngine{
    void SSD1306::clear() {
        for (uint16 i=0; i < bufferSize; i++) BUFFER[i] = 0x00;
    }

    void SSD1306::swapBuffers() {
        // Set col, row, and page address for sending data buffer
        write_cmd(SET_COL_ADDR);
        write_cmd(0);
        write_cmd(WIDTH - 1);
        write_cmd(SET_PAGE_ADDR);
        write_cmd(0);
        write_cmd((HEIGHT / 8) - 1);

        for(uint16 i=0; i < bufferSize; i++) write_data(BUFFER[i]);
    }

    SSD1306::SSD1306() {
        bufferSize = WIDTH * HEIGHT / 8;

        // Display init
        write_cmd(SET_DISP | 0x00);

        // Set horizontal address mode
        write_cmd(SET_MEM_ADDR);
        write_cmd(0x00);

        // Start line from 0
        write_cmd(SET_DISP_START_LINE);
        write_cmd(0x00);
        // Set seg-map

        if (flipped) write_cmd(SET_SEG_REMAP);
        else         write_cmd(SET_SEG_REMAP | 0x01);

        // Set oled height
        write_cmd(SET_MUX_RATIO);
        write_cmd(HEIGHT - 1);

        // Set COM output scan directionscan from bottom up, COM[0] to COM[N-1]
        if (flipped) write_cmd(SET_COM_OUT_DIR_REVERSE);
        else         write_cmd(SET_COM_OUT_DIR);

        // Set display offset
        write_cmd(SET_DISP_OFFSET);
        write_cmd(0x00);

        // Set COM pins hardware configuration,0x12 for 12864,and 0x02 for 12832
        write_cmd(SET_COM_PIN_CFG);
        if      (HEIGHT == 64) write_cmd(0x12);
        else if (HEIGHT == 32) write_cmd(0x02);

        // Set display clock divide ratio
        write_cmd(SET_DISP_CLK_DIV);
        write_cmd(0x80);

        // Set per-charge period
        write_cmd(SET_PRECHARGE);
        write_cmd(0xF1);

        // Set VCOMH deselect level
        write_cmd(SET_VCOM_DESEL);
        write_cmd(0x30);

        // Contrast set 255
        write_cmd(SET_CONTRAST);
        write_cmd(0xFF);

        // Set oled on following from RAM
        write_cmd(SET_ENTIRE_ON);

        // NO inverse , which '0' for pixel off, '1' for pixel on
        write_cmd(SET_NORM_INV);

        // Set charge pump
        write_cmd(SET_CHARGE_PUMP);
        write_cmd(0x14);

        // Set scroll disable
        write_cmd(SET_SCROLL | 0x00);

        // Turn oled on
        write_cmd(SET_DISP | 0x01);
    }
}