package ubi.pt.pdm_project.managers;

import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import ubi.pt.pdm_project.tmxconverter.TileMapData;

public class LayerManager {

    public static class TilePosition {
        public int x, y;
        public long gid;

        public TilePosition(int x, int y, long gid) {
            this.x = x;
            this.y = y;
            this.gid = gid;
        }
    }

    public TileMapData mapData;
    private List<TilePosition> coins;
    private List<TilePosition> blueCoins;
    private List<TilePosition> waterTiles;
    private TilePosition doorPosition;

    public LayerManager(TileMapData mapData) {
        this.mapData = mapData;
        this.coins = new ArrayList<>();
        this.blueCoins = new ArrayList<>();
        this.waterTiles = new ArrayList<>();

        initializeLayers();
    }

    private void initializeLayers() {
        Integer coinLayerIndex = mapData.getLayerIndex("Coins");
        Integer blueCoinLayerIndex = mapData.getLayerIndex("BlueCoinds");
        Integer waterLayerIndex = mapData.getLayerIndex("Water");
        Integer doorLayerIndex = mapData.getLayerIndex("Door");

        if (coinLayerIndex != null) {
            TileMapData.Layer coinLayer = mapData.layers.get(coinLayerIndex);
            for (int y = 0; y < coinLayer.height; y++) {
                for (int x = 0; x < coinLayer.width; x++) {
                    long gid = coinLayer.tiles[y][x];
                    if (gid != 0) {
                        coins.add(new TilePosition(x, y, gid));
                    }
                }
            }
            Log.d("LayerManager", "Found " + coins.size() + " coins");
        }

        if (blueCoinLayerIndex != null) {
            TileMapData.Layer blueCoinLayer = mapData.layers.get(blueCoinLayerIndex);
            for (int y = 0; y < blueCoinLayer.height; y++) {
                for (int x = 0; x < blueCoinLayer.width; x++) {
                    long gid = blueCoinLayer.tiles[y][x];
                    if (gid != 0) {
                        blueCoins.add(new TilePosition(x, y, gid));
                    }
                }
            }
            Log.d("LayerManager", "Found " + blueCoins.size() + " blue coins");
        }

        if (waterLayerIndex != null) {
            TileMapData.Layer waterLayer = mapData.layers.get(waterLayerIndex);
            for (int y = 0; y < waterLayer.height; y++) {
                for (int x = 0; x < waterLayer.width; x++) {
                    long gid = waterLayer.tiles[y][x];
                    if (gid != 0) {
                        waterTiles.add(new TilePosition(x, y, gid));
                    }
                }
            }
            Log.d("LayerManager", "Found " + waterTiles.size() + " water tiles");
        }

        if (doorLayerIndex != null) {
            TileMapData.Layer doorLayer = mapData.layers.get(doorLayerIndex);
            for (int y = 0; y < doorLayer.height; y++) {
                for (int x = 0; x < doorLayer.width; x++) {
                    long gid = doorLayer.tiles[y][x];
                    if (gid != 0) {
                        doorPosition = new TilePosition(x, y, gid);
                        Log.d("LayerManager", "Door found at tile (" + x + ", " + y + ")");
                        break;
                    }
                }
            }
        }
    }

    public TilePosition checkCoinCollision(float pixelX, float pixelY) {
        int tileX = (int) (pixelX / mapData.tilewidth);
        int tileY = (int) (pixelY / mapData.tileheight);

        for (TilePosition coin : coins) {
            if (coin.x == tileX && coin.y == tileY) {
                return coin;
            }
        }
        return null;
    }

    public TilePosition checkBlueCoinCollision(float pixelX, float pixelY) {
        int tileX = (int) (pixelX / mapData.tilewidth);
        int tileY = (int) (pixelY / mapData.tileheight);

        for (TilePosition coin : blueCoins) {
            if (coin.x == tileX && coin.y == tileY) {
                return coin;
            }
        }
        return null;
    }

    public boolean isOnWater(float pixelX, float pixelY) {
        int tileX = (int) (pixelX / mapData.tilewidth);
        int tileY = (int) (pixelY / mapData.tileheight);

        for (TilePosition water : waterTiles) {
            if (water.x == tileX && water.y == tileY) {
                return true;
            }
        }
        return false;
    }

    public boolean isAtDoor(float pixelX, float pixelY) {
        if (doorPosition == null) return false;

        int tileX = (int) (pixelX / mapData.tilewidth);
        int tileY = (int) (pixelY / mapData.tileheight);

        return doorPosition.x == tileX && doorPosition.y == tileY;
    }

    public void removeCoin(TilePosition coin) {
        coins.remove(coin);

        Integer coinLayerIndex = mapData.getLayerIndex("Coins");
        if (coinLayerIndex != null) {
            Log.d("Layer", "removing coin");
            mapData.layers.get(coinLayerIndex).tiles[coin.y][coin.x] = 0;
        }
    }

    public void removeBlueCoin(TilePosition coin) {
        blueCoins.remove(coin);
        // Also remove from the layer data
        Integer blueCoinLayerIndex = mapData.getLayerIndex("BlueCoinds");
        if (blueCoinLayerIndex != null) {
            mapData.layers.get(blueCoinLayerIndex).tiles[coin.y][coin.x] = 0;
        }
    }

    // Getters
    public List<TilePosition> getCoins() { return coins; }
    public List<TilePosition> getBlueCoins() { return blueCoins; }
    public List<TilePosition> getWaterTiles() { return waterTiles; }
    public TilePosition getDoorPosition() { return doorPosition; }
    public int getTotalCoins() { return coins.size() + blueCoins.size(); }
}