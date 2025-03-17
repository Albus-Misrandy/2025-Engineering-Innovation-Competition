#include "OledScreen.h"
#include <string.h>
#include <stdio.h>

// 显存缓冲区（128x64像素，8页）
static uint8_t oled_buffer[OLED_HEIGHT/8][OLED_WIDTH];

// I2C底层通信
static void OLED_WriteCmd(uint8_t cmd) {
    uint8_t buf[2] = {0x00, cmd};
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, buf, 2, 100);
}

static void OLED_WriteData(uint8_t data) {
    uint8_t buf[2] = {0x40, data};
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, buf, 2, 100);
}

// OLED初始化
void OLED_Init(void) {
    HAL_Delay(100);
    OLED_WriteCmd(0xAE); // 关闭显示
    OLED_WriteCmd(0xD5); // 设置时钟分频
    OLED_WriteCmd(0x80);
    OLED_WriteCmd(0xA8); // 设置多路复用率
    OLED_WriteCmd(0x3F);
    OLED_WriteCmd(0xD3); // 设置显示偏移
    OLED_WriteCmd(0x00);
    OLED_WriteCmd(0x40); // 设置显示起始行
    OLED_WriteCmd(0x8D); // 电荷泵设置
    OLED_WriteCmd(0x14);
    OLED_WriteCmd(0x20); // 内存模式
    OLED_WriteCmd(0x00);
    OLED_WriteCmd(0xA1); // 段重映射
    OLED_WriteCmd(0xC8); // 扫描方向
    OLED_WriteCmd(0xDA); // COM引脚配置
    OLED_WriteCmd(0x12);
    OLED_WriteCmd(0x81); // 对比度
    OLED_WriteCmd(0xCF);
    OLED_WriteCmd(0xD9); // 预充电周期
    OLED_WriteCmd(0xF1);
    OLED_WriteCmd(0xDB); // VCOMH电压
    OLED_WriteCmd(0x40);
    OLED_WriteCmd(0xA4); // 正常显示
    OLED_WriteCmd(0xA6); // 正常极性
    OLED_WriteCmd(0xAF); // 开启显示
    OLED_Clear();
}

// 清屏函数
void OLED_Clear(void) {
    memset(oled_buffer, 0, sizeof(oled_buffer));
    OLED_Display();
}

// 显示单个字符
void OLED_ShowChar(uint8_t x, uint8_t y, char ch) {
    uint8_t index = 10; // 默认显示+
    if(ch >= '0' && ch <= '9') index = ch - '0';
    
    for(uint8_t page = 0; page < 3; page++) { // 24高度=3页（每页8行）
        for(uint8_t col = 0; col < FONT_WIDTH; col++) {
            uint8_t data = LargeFont[index][page*FONT_WIDTH + col];
            oled_buffer[page + y][x + col] = data;
        }
    }
}

// 显示表达式
void OLED_ShowExpression(char* expr) {
    uint8_t start_x = (128 - (7*(FONT_WIDTH+CHAR_SPACE)-CHAR_SPACE))/2; // 居中计算
    uint8_t y_pos = 2; // 垂直居中（64-24)/2/8=2.5≈2
    
    for(uint8_t i=0; i<strlen(expr); i++) {
        OLED_ShowChar(start_x + i*(FONT_WIDTH+CHAR_SPACE), y_pos, expr[i]);
    }
    OLED_Display();
}

// 刷新显示
void OLED_Display(void) {
    for(uint8_t page=0; page<8; page++) {
        OLED_WriteCmd(0xB0 + page); // 设置页地址
        OLED_WriteCmd(0x00);        // 列低地址
        OLED_WriteCmd(0x10);        // 列高地址
        for(uint8_t col=0; col<128; col++) {
            OLED_WriteData(oled_buffer[page][col]);
        }
    }
}

// 对串口数据进行处理
void print_to_screen(int* data)
{
    char expr[7];
    expr[3] = '+';
    for (int i = 0; i < 3; i++)
    {
        expr[i] = '0' + data[i];
    }
    for (int i = 4; i < 7; i++)
    {
        expr[i] = '0' + data[i];
    }
    OLED_ShowExpression(expr);
}
