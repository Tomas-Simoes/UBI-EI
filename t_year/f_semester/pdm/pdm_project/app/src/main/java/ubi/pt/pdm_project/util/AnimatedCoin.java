package ubi.pt.pdm_project.util;

import android.graphics.Bitmap;

 public class AnimatedCoin {
    public float x;
     public float y;
    Bitmap[] frames;
    int currentFrame = 0;
    long lastFrameTime = 0;
    int frameDurationMs = 100;

    public AnimatedCoin(float x, float y, Bitmap[] frames) {
        this.x = x;
        this.y = y;
        this.frames = frames;
    }

    public Bitmap getCurrentFrame() {
        long now = System.currentTimeMillis();
        if (now - lastFrameTime >= frameDurationMs) {
            currentFrame = (currentFrame + 1) % frames.length;
            lastFrameTime = now;
        }
        return frames[currentFrame];
    }
}
