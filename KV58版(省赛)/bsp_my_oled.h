#ifndef __MY_OLED_H
#define __MY_OLED_H

#include "stdint.h"

void oled_fill(char uc_data);
void oled_display_6x8char(uint8_t uc_posx, uint8_t uc_posy, char uc_data);
void oled_display_6x8str(uint8_t uc_posx, uint8_t uc_posy, char uc_dataStr[]);
void oled_print_char(uint8_t uc_posx, uint8_t uc_posy, char c_data);
void oled_print_short(uint8_t uc_posx, uint8_t uc_posy, int16_t s_data);
void oled_display_16x8char(uint8_t uc_posx, uint8_t uc_posy, char uc_data);
void oled_display_16x8char_hl(uint8_t uc_posx, uint8_t uc_posy, char uc_data);
void oled_display_16x8str(uint8_t uc_posx, uint8_t uc_posy, char uc_dataStr[]);
void oled_display_16x8str_hl(uint8_t uc_posx, uint8_t uc_posy, char uc_dataStr[]);
void oled_print_16x8char(uint8_t uc_posx, uint8_t uc_posy, int8_t c_data);
void oled_print_16x8short(uint8_t uc_posx, uint8_t uc_posy, int16_t s_data);
void oled_print_16x8short_hl(uint8_t uc_posx, uint8_t uc_posy, int16_t s_data, int8_t bits_num);
void oled_display_6x8char_hl(uint8_t uc_posx, uint8_t uc_posy, char uc_data);
void oled_display_6x8str_hl(uint8_t uc_posx, uint8_t uc_posy, char uc_dataStr[]);
void oled_print_char_hl(uint8_t uc_posx, uint8_t uc_posy, int8_t c_data);
void oled_print_short_hl(uint8_t uc_posx, uint8_t uc_posy, int16_t s_data, int8_t bits_num);

#endif

