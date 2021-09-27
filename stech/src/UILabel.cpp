#include "UILabel.h"

void UILabel::draw() {
    if (this->lineWrap) {
        unsigned int height = text.length() / this->maxLineWidth + 1;
        for (unsigned int i = 0; i < height; i++) {
            std::string sub = text.substr(i * this->maxLineWidth, this->maxLineWidth);

            DrawTextEx(
                    font,
                    text.c_str(),
                    {position.x, position.y + (float) (i * size)},
                    (float) size,
                    0,
                    fontColor
            );

        }
    } else {

        DrawTextEx(
                font,
                text.c_str(),
                {position.x, position.y},
                (float) size,
                0,
                fontColor
        );
    }
}

UILabel::UILabel(const Font &font, const std::string &text) : font(font), text(text) {
    this->font = font;
    this->text = text;
}

void UILabel::update() {

}
