package ubi.pt.pdm_project.util;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;

import ubi.pt.pdm_project.entities.Necromancer;
import ubi.pt.pdm_project.entities.Player;
import ubi.pt.pdm_project.tmxconverter.TileMapData;
import ubi.pt.pdm_project.R;

public class AnimatedEnemy {

    private Necromancer enemy;
    private float x, y;

    // Animation fields
    private Bitmap[] frames;
    private int currentFrame = 0;
    private long lastFrameTime = 0;
    private int frameDurationMs = 150; // milliseconds per frame

    public AnimatedEnemy(float x, float y, Context context) {
        this.x = x;
        this.y = y;
        this.enemy = new Necromancer(context, x, y);

        // Load sprite sheet and split into frames
        Bitmap sheet = BitmapFactory.decodeResource(context.getResources(), R.drawable.necromancer_attack);
        int frameCount = 13; // for example
        int frameWidth = sheet.getWidth() / frameCount;
        int frameHeight = sheet.getHeight();
        frames = new Bitmap[frameCount];
        for (int i = 0; i < frameCount; i++) {
            frames[i] = Bitmap.createBitmap(sheet, i * frameWidth, 0, frameWidth, frameHeight);
        }
    }

    private Bitmap getCurrentFrame() {
        long now = System.currentTimeMillis();
        if (now - lastFrameTime >= frameDurationMs) {
            currentFrame = (currentFrame + 1) % frames.length;
            lastFrameTime = now;
        }
        return frames[currentFrame];
    }

    public void update(Player player, TileMapData mapData, int coinScore, int blueScore) {
        enemy.update(player, mapData.width, mapData.height, mapData.tilewidth, mapData.tileheight, coinScore, blueScore);
    }

    public void draw(Canvas canvas, float offsetX, float offsetY, float scale) {
        Bitmap frame = getCurrentFrame();
        float anchorX = 32;
        float anchorY = frame.getHeight();
        float screenX = offsetX + (x * scale) - anchorX;
        float screenY = offsetY + (y * scale) - anchorY;
        canvas.drawBitmap(frame, screenX, screenY, null);



        // Draw projectiles
        enemy.draw(canvas, offsetX, offsetY, scale);
    }
}
