package ubi.pt.pdm_project.entities;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Color;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import ubi.pt.pdm_project.R;
import ubi.pt.pdm_project.activities.GameActivity;

public class Necromancer {

    private static class Projectile {
        float x, y;
        float vx, vy;
        float speed = 2f;
        float radius = 2f;

        Projectile(float startX, float startY, float targetX, float targetY) {
            this.x = startX;
            this.y = startY;

            float dx = targetX - startX;
            float dy = targetY - startY;
            float len = (float) Math.sqrt(dx * dx + dy * dy);
            this.vx = (dx / len) * speed;
            this.vy = (dy / len) * speed;
        }

        boolean update(int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
            x += vx;
            y += vy;
            return (x < 0 || y < 0 || x > mapWidth * tileWidth || y > mapHeight * tileHeight);
        }

        void draw(Canvas canvas, float offsetX, float offsetY, float scale, Paint paint) {
            float screenX = offsetX + (x * scale);
            float screenY = offsetY + (y * scale);
            canvas.drawCircle(screenX, screenY, radius * scale, paint);
        }

        boolean collidesWith(Player player) {
            float dx = player.x - x;
            float dy = player.y - y;
            float distSq = dx * dx + dy * dy;
            float radiusSum = player.sprite.getWidth() * 0.2f;;
            return distSq < radiusSum * radiusSum;
        }
    }

    private Context context;
    private float x, y;
    private Bitmap enemySprite;
    private List<Projectile> projectiles = new ArrayList<>();
    private long lastShotTime = 0;
    private long shootIntervalMs = 2000;
    private Paint projectilePaint;

    public Necromancer(Context context, float x, float y) {
        this.context = context;
        this.x = x;
        this.y = y;

        this.enemySprite = BitmapFactory.decodeResource(context.getResources(), R.drawable.necromancer);

        projectilePaint = new Paint();
        projectilePaint.setColor(Color.RED);
        projectilePaint.setStyle(Paint.Style.FILL);
        projectilePaint.setAntiAlias(true);
    }

    public void update(Player player, int mapWidth, int mapHeight, int tileWidth, int tileHeight, int coinScore, int blueScore) {
        long now = System.currentTimeMillis();

        if (now - lastShotTime >= shootIntervalMs) {
            projectiles.add(new Projectile(x, y, player.x, player.y));
            lastShotTime = now;
        }

        Iterator<Projectile> it = projectiles.iterator();
        while (it.hasNext()) {
            Projectile p = it.next();
            if (p.update(mapWidth, mapHeight, tileWidth, tileHeight)) {
                it.remove(); // off-screen
            } else if (p.collidesWith(player)) {
                if (context instanceof GameActivity) {
                    final GameActivity activity = (GameActivity) context;
                    activity.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            activity.mapView.gameManager.setRunning(false);
                            activity.onDeath(coinScore, blueScore);
                        }
                    });
                }
                it.remove();
            }
        }
    }

    public void draw(Canvas canvas, float offsetX, float offsetY, float scale) {
        for (Projectile p : projectiles) {
            p.draw(canvas, offsetX, offsetY, scale, projectilePaint);
        }
    }
}
