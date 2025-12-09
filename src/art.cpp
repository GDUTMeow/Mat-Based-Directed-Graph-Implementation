#include <iostream>
#include <string>
#include <cmath>

#define _USE_MATH_DEFINES
#include <cmath>

#include "../include/art.h"

// 获取一个 UTF-8 字符的字节长度
int get_utf8_char_len(unsigned char byte) {
    if (byte < 0x80) return 1;        // 0xxxxxxx -> 1 byte
    if ((byte & 0xE0) == 0xC0) return 2; // 110xxxxx -> 2 bytes
    if ((byte & 0xF0) == 0xE0) return 3; // 1110xxxx -> 3 bytes
    if ((byte & 0xF8) == 0xF0) return 4; // 11110xxx -> 4 bytes
    return 1; // 默认或错误情况，当作单字节处理
}

void RainbowPrint(const std::string& text, double frequency, double phase) {
    int char_index = 0;

    for (int i = 0; i < text.length();) {
        // 获取当前字符的字节长度
        int char_len = get_utf8_char_len((unsigned char)text[i]);

        // 检查是否有足够的字节来构成一个完整的字符
        if (i + char_len > text.length()) {
            std::cout << text.substr(i);
            break;
        }

        // 为字符计算颜色
        int r = static_cast<int>(std::sin(frequency * char_index + phase + 0) * 127 + 128);
        int g = static_cast<int>(std::sin(frequency * char_index + phase + 2 * M_PI / 3) * 127 + 128);
        int b = static_cast<int>(std::sin(frequency * char_index + phase + 4 * M_PI / 3) * 127 + 128);

        std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";

        for (int j = 0; j < char_len; ++j) {
            std::cout << text[i + j];
        }

        // 更新循环变量和颜色计数器
        i += char_len;
        char_index++;
    }

    // 重置颜色
    std::cout << "\033[0m";
}