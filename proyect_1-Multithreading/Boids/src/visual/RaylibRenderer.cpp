#include "visual/Renderer.hpp"

#include "raylib.h"

#include <cmath>

class RaylibRenderer : public Renderer {
public:
    bool init(int width, int height, const char* title) override {
        width_ = width;
        height_ = height;
        InitWindow(width, height, title);
        SetTargetFPS(60);
        return IsWindowReady();
    }

    void beginDrawing() override {
        BeginDrawing();
        ClearBackground({10, 12, 30});
    }

    void drawFlock(const Flock& flock) override {
        for (int i = 0; i < flock.getBoidCount(); ++i) {
            const Boid& boid = flock.getBoid(i);
            const float cx = static_cast<float>(boid.getPosition().getX());
            const float cy = static_cast<float>(boid.getPosition().getY());

            const float speed = static_cast<float>(boid.getVelocity().magnitude());
            const unsigned char brightness = static_cast<unsigned char>(
                120 + static_cast<int>(speed * 40.0f));
            const Color bodyColor{brightness, 220, 255, 255};
            DrawCircle(static_cast<int>(cx), static_cast<int>(cy), 3.0f, bodyColor);

            const Vector2D heading = boid.getVelocity().normalized();
            const float hx = cx + static_cast<float>(heading.getX()) * 6.0f;
            const float hy = cy + static_cast<float>(heading.getY()) * 6.0f;
            DrawLineEx({cx, cy}, {hx, hy}, 1.5f, WHITE);
        }
    }

    void endDrawing() override {
        EndDrawing();
    }

    bool shouldClose() override {
        return WindowShouldClose();
    }

    void shutdown() override {
        CloseWindow();
    }

private:
    int width_ = 0;
    int height_ = 0;
};

Renderer* createRaylibRenderer() {
    return new RaylibRenderer();
}
