package ubi.pt.pdm_project;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.view.View;

public class TMXView extends View {

    private Bitmap mapBitmap;
    private float scale;
    private Player player;

    public TMXView(
            Context context, Bitmap bitmap, float scale, Player player) {
        super(context);
        this.mapBitmap = bitmap;
        this.scale = scale;
        this.player = player;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        if (mapBitmap != null) {
            int screenWidth = getWidth();
            int screenHeight = getHeight();

            int mapWidth = mapBitmap.getWidth();
            int mapHeight = mapBitmap.getHeight();

            // Compute scaled map size
            float scaledWidth = mapWidth * scale;
            float scaledHeight = mapHeight * scale;

            // Compute offset to center the map
            float offsetX = (screenWidth - scaledWidth) / 2f;
            float offsetY = (screenHeight - scaledHeight) / 2f;

            // Apply scale + translation
            Matrix m = new Matrix();
            m.postScale(scale, scale);
            m.postTranslate(offsetX, offsetY);

            // Draw the map centered
            canvas.drawBitmap(mapBitmap, m, null);

            if (player != null && player.sprite != null) {
                canvas.save();
                canvas.translate(offsetX, offsetY);
                canvas.scale(scale, scale);
                canvas.drawBitmap(player.sprite, player.x, player.y, null);
                canvas.restore();
            }

        }
    }

}
