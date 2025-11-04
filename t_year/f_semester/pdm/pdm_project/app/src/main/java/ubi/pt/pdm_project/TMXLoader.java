package ubi.pt.pdm_project;

import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.Log;

/**
 * Loader for .tmx XML map file
 */
public class TMXLoader {

    /**
     * Create a bitmap based on the data in the TileMapData structure.
     *
     * @param t           data structure describing the TileMap
     * @param c           application context
     * @param startLayer  index of the first layer to render
     * @param endLayer    index of the last layer to render
     * @return            bitmap of the map, or null if loading fails
     */
    public static Bitmap createBitmap(TileMapData t, Context c, int startLayer, int endLayer) {
        if (t == null) {
            Log.e("TMXLoader", "TileMapData is null");
            return null;
        }

        // Validate layer indices
        if (startLayer < 0 || endLayer > t.layers.size() || startLayer >= endLayer) {
            Log.e("TMXLoader", "Invalid layer indices: start=" + startLayer + ", end=" + endLayer + ", total layers=" + t.layers.size());
            return null;
        }

        try {
            AssetManager assetManager = c.getAssets();

            // Create a bitmap of the size of the map
            // NOTE: For production, consider tile-based rendering for large maps
            // to avoid memory issues
            Bitmap mapImage = Bitmap.createBitmap(
                    t.width * t.tilewidth,
                    t.height * t.tileheight,
                    Bitmap.Config.ARGB_8888
            );

            // Load all tilesets that are used into memory
            Bitmap[] tilesets = new Bitmap[t.tilesets.size()];

            for (int i = 0; i < tilesets.length; i++) {
                TileMapData.TileSet tileset = t.tilesets.get(i);

                if (tileset.ImageFilename == null) {
                    Log.e("TMXLoader", "Tileset #" + i + " has no image filename (external tileset?)");
                    Log.e("TMXLoader", "Please embed your tilesets in the TMX file instead of using external .tsx references");
                    return null;
                }

                try {
                    tilesets[i] = BitmapFactory.decodeStream(assetManager.open(tileset.ImageFilename));
                    if (tilesets[i] == null) {
                        Log.e("TMXLoader", "Failed to load tileset image: " + tileset.ImageFilename);
                        return null;
                    }
                    Log.d("TMXLoader", "Loaded tileset: " + tileset.ImageFilename +
                            " (" + tilesets[i].getWidth() + "x" + tilesets[i].getHeight() + ")");
                } catch (IOException e) {
                    Log.e("TMXLoader", "Cannot find tileset image: " + tileset.ImageFilename, e);
                    return null;
                }
            }

            // Create a Canvas reference to draw on the map bitmap
            Canvas mapCanvas = new Canvas(mapImage);
            Paint paint = new Paint();
            paint.setFilterBitmap(false); // Disable filtering for crisp pixel art

            // Reusable rectangles to avoid object allocation in loops
            Rect source = new Rect();
            Rect dest = new Rect();

            // Loop through specified layers and render all tiles
            for (int layerIdx = startLayer; layerIdx < endLayer; layerIdx++) {
                TileMapData.Layer layer = t.layers.get(layerIdx);

                // Apply layer opacity
                paint.setAlpha((int)(layer.opacity * 255));

                for (int y = 0; y < layer.height; y++) {
                    for (int x = 0; x < layer.width; x++) {
                        long currentGID = t.getGIDAt(x, y, layerIdx);

                        // Skip empty tiles (GID 0)
                        if (currentGID == 0) continue;

                        Long localGID = t.getLocalID(currentGID);
                        Integer currentTileSetIndex = t.getTileSetIndex(currentGID);

                        // Validate tile data
                        if (localGID == null || currentTileSetIndex == null) {
                            Log.w("TMXLoader", "Invalid GID " + currentGID + " at position (" + x + "," + y + ") in layer " + layerIdx);
                            continue;
                        }

                        if (currentTileSetIndex < 0 || currentTileSetIndex >= tilesets.length) {
                            Log.w("TMXLoader", "Tileset index out of bounds: " + currentTileSetIndex);
                            continue;
                        }

                        TileMapData.TileSet tileset = t.tilesets.get(currentTileSetIndex);
                        Bitmap tilesetBitmap = tilesets[currentTileSetIndex];

                        if (tilesetBitmap == null) continue;

                        // Calculate tile position in tileset
                        int tilesPerRow = tileset.imageWidth / t.tilewidth;
                        if (tilesPerRow == 0) {
                            Log.w("TMXLoader", "Invalid tileset dimensions");
                            continue;
                        }

                        int tileRow = localGID.intValue() / tilesPerRow;
                        int tileCol = localGID.intValue() % tilesPerRow;

                        // Set source rectangle (position in tileset)
                        source.left = tileCol * t.tilewidth;
                        source.top = tileRow * t.tileheight;
                        source.right = source.left + t.tilewidth;
                        source.bottom = source.top + t.tileheight;

                        // Set destination rectangle (position on map)
                        dest.left = x * t.tilewidth;
                        dest.top = y * t.tileheight;
                        dest.right = dest.left + t.tilewidth;
                        dest.bottom = dest.top + t.tileheight;

                        // Draw tile
                        mapCanvas.drawBitmap(tilesetBitmap, source, dest, paint);
                    }
                }
            }

            return mapImage;

        } catch (OutOfMemoryError e) {
            Log.e("TMXLoader", "Out of memory creating map bitmap. Map too large: " +
                    (t.width * t.tilewidth) + "x" + (t.height * t.tileheight), e);
            return null;
        } catch (Exception e) {
            Log.e("TMXLoader", "Unexpected error creating bitmap", e);
            return null;
        }
    }

    /**
     * Convenience method to render all layers
     */
    public static Bitmap createBitmap(TileMapData t, Context c) {
        if (t == null || t.layers.isEmpty()) return null;
        return createBitmap(t, c, 0, t.layers.size());
    }

    /**
     * Reads XML file from assets and returns a TileMapData structure describing its contents
     *
     * @param filename  path to the file in assets
     * @param c         context of the application to resolve assets folder
     * @return          data structure containing map data, or null if parsing fails
     */
    public static TileMapData readTMX(String filename, Context c) {
        TileMapData t = null;

        try {
            SAXParserFactory spf = SAXParserFactory.newInstance();
            SAXParser parser = spf.newSAXParser();
            XMLReader reader = parser.getXMLReader();

            // Create an instance of the TMX XML handler
            TMXHandler handler = new TMXHandler();
            reader.setContentHandler(handler);

            AssetManager assetManager = c.getAssets();
            reader.parse(new InputSource(assetManager.open(filename)));

            // Extract the created object
            t = handler.getData();

            if (t != null) {
                Log.d("TMXLoader", "Successfully parsed TMX: " + filename);
                Log.d("TMXLoader", "Map size: " + t.width + "x" + t.height);
                Log.d("TMXLoader", "Tilesets: " + t.tilesets.size());
                Log.d("TMXLoader", "Layers: " + t.layers.size());
                Log.d("TMXLoader", "Objects: " + t.objects.size());

                t.collisionMap = new boolean[t.height][t.width];

                for(TileMapData.Layer layer : t.layers) {
                    if("Walls".equalsIgnoreCase(layer.name)){
                        for (int y = 0; y < layer.height; y++) {
                            for (int x = 0; x < layer.width; x++) {
                                long gid = layer.tiles[y][x];
                                t.collisionMap[y][x] = gid != 0; // non-zero tile = solid
                            }
                        }
                        Log.d("TMXLoader", "Collision layer processed");
                    }
                }
            }

        } catch (ParserConfigurationException pce) {
            Log.e("TMXLoader", "SAX parser configuration error", pce);
        } catch (SAXException se) {
            Log.e("TMXLoader", "SAX parsing error", se);
        } catch (IOException ioe) {
            Log.e("TMXLoader", "IO error reading TMX file: " + filename, ioe);
        } catch (Exception e) {
            Log.e("TMXLoader", "Unexpected error parsing TMX", e);
        }

        return t;
    }
}