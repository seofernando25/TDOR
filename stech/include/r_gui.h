#pragma once

#include "raylib.h"
#include "string.h"

typedef enum Alignment {
    ALIGN_START = 0,
    ALIGN_END = 1,
    ALIGN_CENTER = 2,
} Alignment;


typedef struct TextStyle {
    Font font;
    float fontSize;
    float fontSpacing;
    Color fontColor;
    Color accentColor;
} TextStyle;

TextStyle currentStyle;

void LoadDefaultGUIStyle() {
    currentStyle = (TextStyle) {
            GetFontDefault(), // Font
            16.f, // Font Size
            0.f, // Font Spacing
            BLACK, // Font tint
            GREEN,
    };
}

void SDrawText(const char *text, float x, float y, Alignment hAlignment, Alignment vAlignment) {
    Vector2 dim = MeasureTextEx(currentStyle.font, text, currentStyle.fontSize, currentStyle.fontSpacing);
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

    DrawTextEx(
            currentStyle.font,
            text,
            (Vector2) {x + offset.x, y + offset.y},
            currentStyle.fontSize,
            currentStyle.fontSpacing,
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
    DrawRectangleRec((Rectangle) {rect.x + 5, rect.y + 5, rect.width, rect.height}, bg);
    DrawRectangleRec(rect, fg);
}

void STextBox(char *text, int x, int y, int charPerLine, Alignment hAlignment, Alignment vAlignment) {
    // Using the default values a screen should fit 40x15 characters
    int height = (int)strlen(text) / charPerLine + 1;
    Rectangle rect = (Rectangle) {x, y, (float)(charPerLine + 1) * currentStyle.fontSize / 2,
                                  currentStyle.fontSize * ((float)height + 0.5f)};
    Vector2 offset = GetAlignmentOffset(rect.width, rect.height, hAlignment, vAlignment);
    rect.x += offset.x;
    rect.y += offset.y;
    SDrawBox(rect, GetContrastingColor(currentStyle.fontColor), currentStyle.accentColor);
    float rectCenterX = rect.x + rect.width / 2;

    for (int i = 0; i < height; i++) {
        int memOffset = i * charPerLine;
        int end = memOffset + charPerLine;
        char temp = text[end];
        text[end] = '\0';
        SDrawText(&text[memOffset], rectCenterX, rect.y + (float) i * currentStyle.fontSize, ALIGN_CENTER, ALIGN_START);
        text[end] = temp;
    }
}

bool STextWriterHelper(char *text, int buffSize, bool enable) {
    if (!enable)
        return false;

    int key = GetCharPressed(); // Returns codepoint as Unicode
    int curCount = (int) strlen(text);
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
    SDrawText(">", x, y, ALIGN_START, ALIGN_START);
    SDrawText(text, x + currentStyle.fontSize / 2, y, ALIGN_START, ALIGN_START);
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
            SDrawText(">", x, y + i * (float) currentStyle.fontSize, ALIGN_START, ALIGN_START);
        SDrawText(items[i], x + currentStyle.fontSize / 2, y + i * (float) currentStyle.fontSize, ALIGN_START,
                  ALIGN_START);
    }
}

