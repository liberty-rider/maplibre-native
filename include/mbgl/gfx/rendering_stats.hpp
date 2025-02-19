#pragma once

namespace mbgl {
namespace gfx {

struct RenderingStats {
    RenderingStats() = default;
    bool isZero() const;

    int numDrawCalls;
    int numActiveTextures;
    int numCreatedTextures;
    int numBuffers;
    int numFrameBuffers;

    int memTextures;
    int memIndexBuffers;
    int memVertexBuffers;

    int stencilClears = 0;
    int stencilUpdates = 0;

    RenderingStats& operator+=(const RenderingStats& right);
};

inline RenderingStats& RenderingStats::operator+=(const RenderingStats& r) {
    numDrawCalls += r.numDrawCalls;
    numActiveTextures += r.numActiveTextures;
    numCreatedTextures += r.numCreatedTextures;
    numBuffers += r.numBuffers;
    numFrameBuffers += r.numFrameBuffers;

    memTextures += r.memTextures;
    memIndexBuffers += r.memIndexBuffers;
    memVertexBuffers += r.memVertexBuffers;

    stencilClears += r.stencilClears;
    stencilUpdates += r.stencilUpdates;

    return *this;
}

} // namespace gfx
} // namespace mbgl
