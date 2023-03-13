//
// Created by Jean on 2/25/2023.
//

#pragma once


#include <vector>
#include <cstdint>
#include <jevarg.h>

class FrameBuffer {
public:
    explicit FrameBuffer(const jevarg::size<int> &size);

    void fill(const jevarg::color &pixel);

    const std::uint8_t *getData() const;

    void drawPixel(int x, int y, const jevarg::color &color);

    void drawPixel(const jevarg::vec2<int> &pos, const jevarg::color &color);

    void drawLine(const jevarg::vec2<int> &src, const jevarg::vec2<int> &dst, const jevarg::color &color);

    void drawRectangle(const jevarg::vec2<int> &pos, const jevarg::size<int> &size, const jevarg::color &color);

    void
    drawRectangle(const jevarg::vec2<int> &pos, const jevarg::size<int> &size, float angle, const jevarg::color &color);

    void filter();

private:
    std::vector<std::uint8_t> mData;
    jevarg::size<int> mSize;
};
