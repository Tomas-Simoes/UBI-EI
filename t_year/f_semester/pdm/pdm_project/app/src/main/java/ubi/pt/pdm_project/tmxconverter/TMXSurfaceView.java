package ubi.pt.pdm_project.tmxconverter;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.util.ArrayList;
import java.util.List;

import ubi.pt.pdm_project.R;
import ubi.pt.pdm_project.activities.GameActivity;
import ubi.pt.pdm_project.managers.GameManager;
import ubi.pt.pdm_project.managers.LayerManager;
import ubi.pt.pdm_project.entities.Player;
import ubi.pt.pdm_project.entities.Necromancer;
import ubi.pt.pdm_project.util.AnimatedCoin;
import ubi.pt.pdm_project.util.AnimatedEnemy;
import ubi.pt.pdm_project.util.LevelCoordinates;


public class TMXSurfaceView extends SurfaceView implements SurfaceHolder.Callback {
    private Bitmap mapBitmap;
    private TileMapData mapData;

    private float scale;
    private Player player;
    private int coinScore = 0;
    private int blueScore = 0;

    public GameManager gameManager;
    private LayerManager layerManager;

    private float tiltX, tiltY;
    private float offsetX, offsetY;
    private float scaledMapWidth, scaledMapHeight;

    private Bitmap[] blueCoinFrames;
    private List<AnimatedCoin> blueCoins = new ArrayList<>();

    private Bitmap[] coinFrames;
    private List<AnimatedCoin> coins = new ArrayList<>();

    private List<AnimatedEnemy> animatedEnemies = new ArrayList<>();
    private int currentLevel;

    private final LevelCoordinates[] enemiesCoordinates = new LevelCoordinates[] {
            new LevelCoordinates(200, 360, 4),
            new LevelCoordinates(50, 200, 4),
            new LevelCoordinates(38, 560, 4),

    };

    public TMXSurfaceView(Context context, Bitmap bitmap, TileMapData mapData, float scale, Player player, int level) {
        super(context);
        getHolder().addCallback(this);

        this.mapBitmap = bitmap;
        this.mapData = mapData;
        this.scale = scale;
        this.player = player;
        this.currentLevel = level;

        this.gameManager = new GameManager(this);
        this.layerManager = new LayerManager(mapData);

        removeStaticCoins();
        initAnimations();
        initEnemies(context);
    }

    private void removeStaticCoins() {
        Integer blueCLayerIndex = mapData.getLayerIndex("BlueCoinds");
        if (blueCLayerIndex != null) {
            TileMapData.Layer layer = mapData.layers.get(blueCLayerIndex);
            for (int y = 0; y < layer.height; y++) {
                for (int x = 0; x < layer.width; x++) {
                    layer.tiles[y][x] = 0;
                }
            }
        }

        Integer coinsLayerIndex = mapData.getLayerIndex("Coins");
        if (coinsLayerIndex != null) {
            TileMapData.Layer layer = mapData.layers.get(coinsLayerIndex);
            for (int y = 0; y < layer.height; y++) {
                for (int x = 0; x < layer.width; x++) {
                    layer.tiles[y][x] = 0;
                }
            }
        }

        mapBitmap = TMXLoader.createBitmap(mapData, getContext());
    }

    private void initAnimations() {
        Bitmap blueSheet = BitmapFactory.decodeResource(getResources(), R.drawable.bluecoin_idle);
        int frameCount = 8;
        int frameWidth = blueSheet.getWidth() / frameCount;
        int frameHeight = blueSheet.getHeight();

        blueCoinFrames = new Bitmap[frameCount];
        for (int i = 0; i < frameCount; i++) {
            blueCoinFrames[i] = Bitmap.createBitmap(blueSheet, i * frameWidth, 0, frameWidth, frameHeight);
        }

        for (LayerManager.TilePosition pos : layerManager.getBlueCoins()) {
            float pixelX = pos.x * mapData.tilewidth + mapData.tilewidth / 2f;
            float pixelY = pos.y * mapData.tileheight + mapData.tileheight / 2f;

            blueCoins.add(new AnimatedCoin(pixelX, pixelY, blueCoinFrames));

            pos.gid = 1;
        }

        Bitmap coinSheet = BitmapFactory.decodeResource(getResources(), R.drawable.coin_idle);
        frameCount = 8;
        frameWidth = coinSheet.getWidth() / frameCount;
        frameHeight = coinSheet.getHeight();

        coinFrames = new Bitmap[frameCount];
        for (int i = 0; i < frameCount; i++) {
            coinFrames[i] = Bitmap.createBitmap(coinSheet, i * frameWidth, 0, frameWidth, frameHeight);
        }

        for (LayerManager.TilePosition pos : layerManager.getCoins()) {
            float pixelX = pos.x * mapData.tilewidth + mapData.tilewidth / 2f;
            float pixelY = pos.y * mapData.tileheight + mapData.tileheight / 2f;

            coins.add(new AnimatedCoin(pixelX, pixelY, coinFrames));

            pos.gid = 1;
        }
    }

    private void initEnemies(Context context) {
        animatedEnemies.clear();
        for (LevelCoordinates coords : enemiesCoordinates) {
            if (coords.level == currentLevel) {
                animatedEnemies.add(new AnimatedEnemy(coords.x, coords.y, context));
            }
        }
    }

    public void update() {
        player.update(tiltX, tiltY, mapData);

        for (AnimatedEnemy e : animatedEnemies) {
            e.update(player, mapData, coinScore, blueScore);
        }

        LayerManager.TilePosition blueCoin = layerManager.checkBlueCoinCollision(player.x, player.y);
        if (blueCoin != null) {
            layerManager.removeBlueCoin(blueCoin);

            AnimatedCoin collected = null;
            for (AnimatedCoin c : blueCoins) {
                int tileX = (int) (c.x / mapData.tilewidth);
                int tileY = (int) (c.y / mapData.tileheight);
                if (tileX == blueCoin.x && tileY == blueCoin.y) {
                    collected = c;
                    break;
                }
            }
            if (collected != null) blueCoins.remove(collected);

            blueScore++;
            Log.d("Game", "Blue coin collected! Score: " + blueScore);
        }

        LayerManager.TilePosition coin = layerManager.checkCoinCollision(player.x, player.y);
        if (coin != null) {
            layerManager.removeCoin(coin);

            AnimatedCoin collected = null;
            for (AnimatedCoin c : coins) {
                int tileX = (int) (c.x / mapData.tilewidth);
                int tileY = (int) (c.y / mapData.tileheight);
                if (tileX == coin.x && tileY == coin.y) {
                    collected = c;
                    break;
                }
            }
            if (collected != null) coins.remove(collected);

            coinScore++;
            Log.d("Game", "Coin collected! Score: " + coinScore);
        }

        if (layerManager.isOnWater(player.x, player.y)) {
            if (getContext() instanceof GameActivity) {
                GameActivity activity = (GameActivity) getContext();
                activity.runOnUiThread(() -> activity.onDeath(coinScore, blueScore));
                gameManager.setRunning(false);
            }
        }

        if (coinScore >= 4) {
            if (getContext() instanceof GameActivity) {
                GameActivity activity = (GameActivity) getContext();
                activity.runOnUiThread(() -> activity.completeLevel(coinScore, blueScore));
                gameManager.setRunning(false);
            }
        }
    }

    public void drawFrame() {
        Canvas canvas = getHolder().lockCanvas();
        if (canvas != null) {
            synchronized (getHolder()) {
                drawScene(canvas);
            }
            getHolder().unlockCanvasAndPost(canvas);
        }
    }

    private void drawScene(Canvas canvas) {
        if (mapBitmap == null) return;

        int screenWidth = getWidth();
        int screenHeight = getHeight();

        int mapWidth = mapBitmap.getWidth();
        int mapHeight = mapBitmap.getHeight();

        scaledMapWidth = mapWidth * scale;
        scaledMapHeight = mapHeight * scale;

        offsetX = (screenWidth - scaledMapWidth) / 2f;
        offsetY = (screenHeight - scaledMapHeight) / 2f;

        Matrix m = new Matrix();
        m.postScale(scale, scale);
        m.postTranslate(offsetX, offsetY);

        canvas.drawBitmap(mapBitmap, m, null);

        float coinScale = 1.5f;
        for (AnimatedCoin c : blueCoins) {
            Bitmap frame = c.getCurrentFrame();
            float screenX = offsetX + (c.x * scale) - (frame.getWidth() * coinScale) / 2f;
            float screenY = offsetY + (c.y * scale) - (frame.getHeight() * coinScale) / 2f;

            Matrix matrix = new Matrix();
            matrix.postScale(coinScale, coinScale);
            matrix.postTranslate(screenX, screenY);

            canvas.drawBitmap(frame, matrix, null);
        }

        for (AnimatedCoin c : coins) {
            Bitmap frame = c.getCurrentFrame();
            float screenX = offsetX + (c.x * scale) - (frame.getWidth() * coinScale) / 2f;
            float screenY = offsetY + (c.y * scale) - (frame.getHeight() * coinScale) / 2f;

            Matrix matrix = new Matrix();
            matrix.postScale(coinScale, coinScale);
            matrix.postTranslate(screenX, screenY);

            canvas.drawBitmap(frame, matrix, null);
        }


        // Draw player
        if (player != null && player.sprite != null) {
            float screenX = offsetX + (player.x * scale) - player.sprite.getWidth() / 2f;
            float screenY = offsetY + (player.y * scale) - player.sprite.getHeight() / 2f;
            canvas.drawBitmap(player.sprite, screenX, screenY, null);
        }

        for (AnimatedEnemy e : animatedEnemies) {
            e.draw(canvas, offsetX, offsetY, scale);
        }

    }

    public void setTilt(float x, float y) {
        this.tiltX = x;
        this.tiltY = y;
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        if (mapBitmap != null && player != null) {
            player.setBounds(0, mapBitmap.getWidth(), 0, mapBitmap.getHeight());
        }
        gameManager.setRunning(true);
        gameManager.start();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        gameManager.setRunning(false);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int f, int w, int h) {}
}
