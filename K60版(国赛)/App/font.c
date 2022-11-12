//数组定义
unsigned char const SD_OK[6*2*16] = 
{
    //共6个字节，一个字占用(16+7)/8=2行，共16列。
    /* T */
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,
    0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,
    /* F */
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
    0x7E,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,
    /* 卡 */
    0x00,0x00,0x01,0x80,0x01,0x80,0x00,0xF0,0x01,0x80,0x01,0x8E,0x03,0xF8,0x3F,0x80,
    0x01,0x80,0x01,0xB0,0x01,0x98,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x00,0x00,
    /*   */
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    /* 正 */
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x07,0x80,0x00,0xC0,0x00,0xC0,0x0E,0xF8,
    0x06,0xE0,0x0C,0xC0,0x0C,0xC0,0x0C,0xC0,0x0F,0xFF,0x38,0x00,0x00,0x00,0x00,0x00,
    /* 常 */
    0x00,0x00,0x01,0x80,0x0D,0xB8,0x07,0xE0,0x01,0xFE,0x1F,0x0E,0x37,0xF8,0x36,0x60,
    0x03,0xC0,0x01,0xF8,0x0F,0x98,0x0D,0x98,0x0D,0xF8,0x01,0xB0,0x01,0x80,0x01,0x80,
};
unsigned char const SD_ERROR[6*2*16] = 
{
    //共6个字节，一个字占用(16+7)/8=2行，共16列。
    /* T */
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,
    0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,
    /* F */
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
    0x7E,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,
    /* 卡 */
    0x00,0x00,0x01,0x80,0x01,0x80,0x00,0xF0,0x01,0x80,0x01,0x8E,0x03,0xF8,0x3F,0x80,
    0x01,0x80,0x01,0xB0,0x01,0x98,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x00,0x00,
    /*   */
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    /* 异 */
    0x00,0x00,0x00,0x00,0x05,0xF0,0x07,0x60,0x07,0xE0,0x07,0x18,0x03,0x3C,0x03,0xE0,
    0x03,0x3F,0x3F,0xF8,0x03,0x30,0x03,0x30,0x06,0x30,0x0C,0x30,0x00,0x30,0x00,0x00,
    /* 常 */
    0x00,0x00,0x01,0x80,0x0D,0xB8,0x07,0xE0,0x01,0xFE,0x1F,0x0E,0x37,0xF8,0x36,0x60,
    0x03,0xC0,0x01,0xF8,0x0F,0x98,0x0D,0x98,0x0D,0xF8,0x01,0xB0,0x01,0x80,0x01,0x80,
};
unsigned char const SD_OFF[6*2*16] = 
{
    //共6个字节，一个字占用(16+7)/8=2行，共16列。
    /* T */
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,
    0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,
    /* F */
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
    0x7E,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x00,0x00,0x00,0x00,
    /* 卡 */
    0x00,0x00,0x01,0x80,0x01,0x80,0x00,0xF0,0x01,0x80,0x01,0x8E,0x03,0xF8,0x3F,0x80,
    0x01,0x80,0x01,0xB0,0x01,0x98,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x00,0x00,
    /* 未 */
    0x00,0x00,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xC0,0x03,0x80,0x01,0xF0,0x1F,0x80,
    0x03,0xC0,0x07,0xE0,0x07,0xF0,0x0D,0xBC,0x39,0x9F,0x01,0x80,0x01,0x80,0x01,0x80,
    /* 插 */
    0x00,0x00,0x00,0x00,0x0E,0x18,0x0C,0x70,0x0C,0x70,0x0C,0x37,0x1F,0xFC,0x0E,0x30,
    0x0C,0xFE,0x1D,0xE3,0x7F,0x7E,0x0D,0xE6,0x0D,0xE6,0x0D,0xBC,0x0C,0x00,0x00,0x00,
    /* 入 */
    0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x01,0x80,0x01,0x80,0x03,0xC0,0x03,0xC0,
    0x06,0x60,0x06,0x30,0x0C,0x38,0x18,0x1C,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,
};
unsigned char const Back[7*2*16] = 
{
    //共7个字节，一个字占用(16+7)/8=2行，共16列。
    /* 按 */
    0x00,0x00,0x00,0x40,0x18,0x60,0x18,0x60,0x1B,0xFE,0x1B,0xFE,0x7F,0x64,0x72,0x64,
    0x13,0xFE,0x17,0xFE,0x7C,0x98,0x71,0x90,0x11,0xF0,0x11,0x78,0x31,0xFC,0x33,0x8C,
    /* 键 */
    0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x7E,0x1B,0xFE,0x33,0xBF,0x3D,0x7F,0xE3,0x1E,
    0x7B,0x7C,0x3B,0xFE,0x35,0xFC,0x7D,0xD8,0x37,0x7E,0x3B,0xD0,0x3A,0x70,0x06,0x1E,
    /* 返 */
    0x00,0x00,0x00,0x00,0x00,0x18,0x03,0xFC,0x3B,0xC0,0x33,0x00,0x7F,0xFC,0x7B,0xF8,
    0x5B,0x98,0x33,0xF0,0x3A,0x70,0x1E,0xF8,0x1D,0x9C,0x3F,0x08,0x3F,0xF2,0x00,0xFE,
    /* 回 */
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x3F,0xFE,0x30,0x0E,0x37,0xEE,0x37,0xEC,
    0x36,0x6C,0x36,0x6C,0x37,0xEC,0x37,0xCC,0x30,0x0C,0x37,0xFC,0x3F,0xFC,0x10,0x08,
    /* 主 */
    0x00,0x00,0x00,0x00,0x01,0x80,0x01,0x80,0x01,0x80,0x3F,0xFC,0x3F,0xFC,0x01,0x80,
    0x01,0x80,0x1F,0xF8,0x1F,0xF8,0x01,0x80,0x01,0x80,0x01,0x80,0x7F,0xFE,0x3F,0xFE,
    /* 界 */
    0x00,0x00,0x00,0x00,0x0F,0xFC,0x1F,0xFC,0x19,0x8C,0x1F,0xF8,0x1D,0x88,0x1F,0xF8,
    0x0F,0xF8,0x06,0x30,0x1E,0x7C,0x7E,0x2E,0x76,0x66,0x06,0x60,0x0C,0x60,0x1C,0x60,
    /* 面 */
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0x7F,0xFF,0x01,0x80,0x1F,0xFC,0x1F,0xFC,
    0x1A,0x6C,0x13,0xEC,0x13,0xEC,0x13,0xEC,0x13,0xEC,0x12,0x6C,0x1F,0xF8,0x1F,0xF8,
};
