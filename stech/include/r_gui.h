#ifndef TDOR_RGUI_H
#define TDOR_RGUI_H

#include "raylib.h"
#include <string>


typedef enum Alignment {
    ALIGN_START = 0,
    ALIGN_END = 1,
    ALIGN_CENTER = 2,
} Alignment;


typedef struct TextStyle {
    Font font;
    float fontSize;
    Color fontColor;
    Color accentColor;
} TextStyle;

TextStyle currentStyle{
        GetFontDefault(), // Font
        16.f, // Font Size
        BLACK, // Font tint
        GREEN,
};

void SDrawText(std::string text, float x, float y, Alignment hAlignment, Alignment vAlignment) {
    Vector2 dim = MeasureTextEx(currentStyle.font, text.c_str(), currentStyle.fontSize, 0.f);
    Vector2 offset = {0};
    switch (hAlignment) {
        case ALIGN_CENTER:
        case ALIGN_END:
            offset.x -= dim.x / (float) hAlignment;
            break;
        case ALIGN_START:
        default:
            break;
    }

    switch (vAlignment) {
        case ALIGN_CENTER:
        case ALIGN_END:
            offset.y -= dim.y / (float) vAlignment;
            break;
        case ALIGN_START:
        default:
            break;
    }

    DrawTextPro(
            currentStyle.font,
            text.c_str(),
            {x + offset.x, y + offset.y},
            {0, 0},
            0,
            currentStyle.fontSize,
            0,
            currentStyle.fontColor
    );
}

Color GetContrastingColor(Color c) {
    Color ret = {0, 0, 0, 255};
    if (c.r < 144)
        ret.r = 255;
    if (c.g < 144)
        ret.g = 255;
    if (c.b < 144)
        ret.b = 255;
    return ret;
}

Vector2 GetAlignmentOffset(float width, float height, Alignment hAlignment, Alignment vAlignment) {
    Vector2 offset = {0};
    switch (hAlignment) {
        case ALIGN_CENTER:
        case ALIGN_END:
            offset.x -= width / (float) hAlignment;
            break;
        case ALIGN_START:
        default:
            break;
    }

    switch (vAlignment) {
        case ALIGN_CENTER:
        case ALIGN_END:
            offset.y -= height / (float) vAlignment;
            break;
        case ALIGN_START:
        default:
            break;
    }
    return offset;
}

void SDrawBox(Rectangle rect, Color fg, Color bg) {
    DrawRectangleRec({rect.x + 5, rect.y + 5, rect.width, rect.height}, bg);
    DrawRectangleRec(rect, fg);
}

void STextBox(const std::string &text, int x, int y, int charPerLine, Alignment hAlignment, Alignment vAlignment) {
    // Using the default values a screen should fit 40x15 characters
    int height = text.length() / charPerLine + 1;
    Rectangle rect{(float) x, (float) y, (charPerLine + 1) * currentStyle.fontSize / 2,
                   currentStyle.fontSize * (height + 0.5f)};
    Vector2 offset = GetAlignmentOffset(rect.width, rect.height, hAlignment, vAlignment);
    rect.x += offset.x;
    rect.y += offset.y;
    SDrawBox(rect, GetContrastingColor(currentStyle.fontColor), currentStyle.accentColor);
    float rectCenterX = rect.x + rect.width / 2;

    for (int i = 0; i < height; i++) {
        std::string sub = text.substr(i * charPerLine, charPerLine);
        SDrawText(sub, rectCenterX, rect.y + (float) i * currentStyle.fontSize, ALIGN_CENTER, ALIGN_START);
    }
}

bool STextWriterHelper(char *text, int buffSize, bool enable) {
    if (!enable)
        return false;

    int key = GetCharPressed(); // Returns codepoint as Unicode
    int curCount = (int) (text);
    bool bufferNotFull = curCount < (buffSize - 1);
    // Only allow keys in range [32..125]
    if (bufferNotFull && key >= 32) {
        text[curCount] = (char) key;
        curCount++;
        text[curCount] = '\0';
    } else if (buffSize > 0 && IsKeyPressed(KEY_BACKSPACE)) {
        curCount--;
        text[curCount] = '\0';
    }

    return IsKeyPressed(KEY_ENTER);
}

bool SInputLine(int x, int y, char *text, int buffSize, bool enable) {
    STextWriterHelper(text, buffSize, enable);
    SDrawText(">", (float) x, (float) y, ALIGN_START, ALIGN_START);
    SDrawText(text, (float) x + currentStyle.fontSize / 2, (float) y, ALIGN_START, ALIGN_START);
//    DrawText(text, x, y, currentStyle.fontSize, BLACK);
    return IsKeyPressed(KEY_ENTER);
}

int SVList(int x, int y, char **items, int itemC, int *current) {
    if (IsKeyPressed(KEY_DOWN)) {
        *current = (*current + 1) % itemC;
    } else if (IsKeyPressed(KEY_UP)) {
        if (*current == 0) {
            *current = itemC;
        }
        *current = *current - 1;
    }


    for (int i = 0; i < itemC; ++i) {
        if (*current == i)
            SDrawText(">", (float) x, (float) y + (float) i * (float) currentStyle.fontSize, ALIGN_START, ALIGN_START);
        SDrawText(items[i], x + currentStyle.fontSize / 2, (float) y + (float) i * (float) currentStyle.fontSize,
                  ALIGN_START,
                  ALIGN_START);
    }
    return IsKeyPressed(KEY_ENTER);
}

#endif