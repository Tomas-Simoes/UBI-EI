package ubi.pt.pdm_project;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

public class Player {
    public float x, y;
    public int size;
    public Bitmap sprite;
    public float rotationAngle = 0;

    public Player(Context context, float startX, float startY) {
        this.sprite = loadBitmapFromAssets(context, "Player.png"); // pass a valid context here
        this.x = startX;
        this.y = startY;
        this.size = sprite.getWidth(); // assume square bitmap
    }

    public void updateRotation(float dx, float dy) {
        float distance = (float) Math.sqrt(dx*dx + dy*dy);
        rotationAngle += distance * 5; // tweak rotation speed
        if (rotationAngle > 360) rotationAngle -= 360;
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
