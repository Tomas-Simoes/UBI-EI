package ubi.pt.pdm_project.entities;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

import ubi.pt.pdm_project.tmxconverter.TileMapData;

public class Player {
    public float x, y;
    public float vx = 0f, vy = 0f;
    public Bitmap sprite;

    private static final float ACCELERATION = 0.05f;
    private static final float MAX_SPEED = 5f;
    private static final float FRICTION = 0.95f;

    private float minX = 0, maxX = 1000;
    private float minY = 0, maxY = 1000;

    public Player(Context context, float startX, float startY) {
        Bitmap original_sprite = loadBitmapFromAssets(context, "Player.png");
        this.sprite = Bitmap.createScaledBitmap(original_sprite, 60, 60, true);

        this.x = startX;
        this.y = startY;
    }

    public void setBounds(float minX, float maxX, float minY, float maxY) {
        this.minX = minX;
        this.maxX = maxX;
        this.minY = minY;
        this.maxY = maxY;
    }

    public void update(float tiltX, float tiltY, TileMapData mapData) {
        // remove noise
        float threshold = 1.0f;
        if (Math.abs(tiltX) < threshold) tiltX = 0;
        if (Math.abs(tiltY) < threshold) tiltY = 0;

        // velocity based on tilt
        vx += -tiltX * ACCELERATION;
        vy += tiltY * ACCELERATION;

        // clamp velocity
        float speed = (float) Math.sqrt(vx * vx + vy * vy);
        if (speed > MAX_SPEED) {
            vx = (vx / speed) * MAX_SPEED;
            vy = (vy / speed) * MAX_SPEED;
        }

        float newX = x + vx;
        float newY = y + vy;

        // check collision with walls
        if (mapData != null && mapData.collisionMap != null) {
            boolean collisionX = checkCollision(newX, y, mapData);
            boolean collisionY = checkCollision(x, newY, mapData);
            boolean collisionBoth = checkCollision(newX, newY, mapData);

            // if collision -> stop movement
            if (collisionBoth) {
                if (collisionX) {
                    vx = 0; // stop horizontal movement
                    newX = x;
                }
                if (collisionY) {
                    vy = 0; // stop vertical movement
                    newY = y;
                }
            }
        }

        x = newX;
        y = newY;

        // apply friction
        vx *= FRICTION;
        vy *= FRICTION;

        // bounds checking
        float halfWidth = sprite.getWidth() / 2f;
        float halfHeight = sprite.getHeight() / 2f;

        if (x < minX + halfWidth) {
            x = minX + halfWidth;
            vx = 0;
        }
        if (x > maxX - halfWidth) {
            x = maxX - halfWidth;
            vx = 0;
        }
        if (y < minY + halfHeight) {
            y = minY + halfHeight;
            vy = 0;
        }
        if (y > maxY - halfHeight) {
            y = maxY - halfHeight;
            vy = 0;
        }
    }

    private boolean checkCollision(float pixelX, float pixelY, TileMapData mapData) {
        int tileX = (int) (pixelX / mapData.tilewidth);
        int tileY = (int) (pixelY / mapData.tileheight);

        // check if out of bounds
        if (tileX < 0 || tileX >= mapData.width || tileY < 0 || tileY >= mapData.height) {
            return true;
        }

        return mapData.collisionMap[tileY][tileX];
    }

    private Bitmap loadBitmapFromAssets(Context context, String filename) {
        Bitmap bitmap = null;
        try {
            bitmap = BitmapFactory.decodeStream(context.getAssets().open(filename));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return bitmap;
    }
}