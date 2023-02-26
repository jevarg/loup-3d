//
// Created by Jean on 2/25/2023.
//

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const jevarg::size<int> &size) : mData(size.width * size.height * 4), mSize(size) {
    std::fill(mData.begin(), mData.end(), 0);
}

void FrameBuffer::drawPixel(int x, int y, const jevarg::color &color) {
    int offset = (y * mSize.width + x) * 4;

    mData[offset] = color.r;
    mData[offset + 1] = color.g;
    mData[offset + 2] = color.b;
    mData[offset + 3] = color.a;
}

void FrameBuffer::drawPixel(const jevarg::vec2<int> &pos, const jevarg::color &color) {
    drawPixel(pos.x, pos.y, color);
}

void FrameBuffer::fill(const jevarg::color &pixel) {
    for (int i = 0; i < mData.size() / 4; ++i) {
        reinterpret_cast<jevarg::color *>(mData.data())[i] = pixel;
    }
//    std::fill(mData.begin(), mData.end(), 0);
}

const std::uint8_t *FrameBuffer::getData() const {
    return mData.data();
}

void FrameBuffer::drawLine(const jevarg::vec2<int> &src, const jevarg::vec2<int> &dst, const jevarg::color &color) {
    int dx = std::abs(dst.x - src.x);
    int dy = std::abs(dst.y - src.y);
    int sx = (src.x < dst.x) ? 1 : -1;
    int sy = (src.y < dst.y) ? 1 : -1;
    int err = dx - dy;
    int x = src.x;
    int y = src.y;

    while (x != dst.x || y != dst.y) {
        drawPixel(x, y, color);

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }

        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}
