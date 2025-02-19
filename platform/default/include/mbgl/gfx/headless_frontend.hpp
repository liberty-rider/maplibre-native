#pragma once

#include <mbgl/gfx/headless_backend.hpp>
#include <mbgl/gfx/rendering_stats.hpp>
#include <mbgl/map/camera.hpp>
#include <mbgl/renderer/renderer_frontend.hpp>
#include <mbgl/util/async_task.hpp>

#include <atomic>
#include <memory>
#include <optional>

namespace mbgl {

class Renderer;
class Map;
class TransformState;

class HeadlessFrontend : public RendererFrontend {
public:
    struct RenderResult {
        PremultipliedImage image;
        gfx::RenderingStats stats;
    };

    HeadlessFrontend(float pixelRatio_,
                     gfx::HeadlessBackend::SwapBehaviour swapBehavior = gfx::HeadlessBackend::SwapBehaviour::NoFlush,
                     gfx::ContextMode mode = gfx::ContextMode::Unique,
                     const std::optional<std::string>& localFontFamily = std::nullopt);
    HeadlessFrontend(Size,
                     float pixelRatio_,
                     gfx::HeadlessBackend::SwapBehaviour swapBehavior = gfx::HeadlessBackend::SwapBehaviour::NoFlush,
                     gfx::ContextMode mode = gfx::ContextMode::Unique,
                     const std::optional<std::string>& localFontFamily = std::nullopt);
    ~HeadlessFrontend() override;

    void reset() override;
    void update(std::shared_ptr<UpdateParameters>) override;
    void setObserver(RendererObserver&) override;

    double getFrameTime() const;
    Size getSize() const;
    void setSize(Size);

    Renderer* getRenderer();
    gfx::RendererBackend* getBackend();
    CameraOptions getCameraOptions();

    bool hasImage(const std::string&);
    bool hasLayer(const std::string&);
    bool hasSource(const std::string&);

    ScreenCoordinate pixelForLatLng(const LatLng&);
    LatLng latLngForPixel(const ScreenCoordinate&);

    PremultipliedImage readStillImage();
    RenderResult render(Map&);
    void renderOnce(Map&);

    std::optional<TransformState> getTransformState() const;

private:
    Size size;
    float pixelRatio;

    std::atomic<double> frameTime;
    std::unique_ptr<gfx::HeadlessBackend> backend;
    util::AsyncTask asyncInvalidate;

    std::unique_ptr<Renderer> renderer;
    std::shared_ptr<UpdateParameters> updateParameters;
};

} // namespace mbgl
