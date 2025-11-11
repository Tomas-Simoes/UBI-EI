package ubi.pt.pdm_project.tmxconverter;

import java.util.HashMap;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Log;

public class TMXHandler extends DefaultHandler {

    private boolean inTileSet, inTile, inLayer, inData, inObjectGroup, inProperties;
    private String currentTileID;
    private String currentObjectGroupName;
    TileMapData.TMXObject currentObject;
    TileMapData.TileSet currentTileSet;
    TileMapData.Layer currentLayer;
    HashMap<String, HashMap<String, String>> currentTileSetProperties;
    HashMap<String, String> currentLayerProperties;
    private TileMapData data;

    private StringBuilder numberBuffer;
    private int currentX;
    private int currentY;

    public TMXHandler() {
        super();
        numberBuffer = new StringBuilder();
        currentX = 0;
        currentY = 0;
    }

    public TileMapData getData() { return data; }

    @Override
    public void startDocument() throws SAXException {
        data = new TileMapData();
    }

    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes atts) throws SAXException {
        switch (localName) {
            case "map":
                String orientation = atts.getValue("orientation");
                if (!"orthogonal".equals(orientation)) {
                    throw new SAXException("Unsupported orientation. Parse Terminated.");
                }
                data.orientation = orientation;

                try {
                    data.height = Integer.parseInt(atts.getValue("height"));
                    data.width = Integer.parseInt(atts.getValue("width"));
                    data.tilewidth = Integer.parseInt(atts.getValue("tilewidth"));
                    data.tileheight = Integer.parseInt(atts.getValue("tileheight"));
                } catch (NumberFormatException e) {
                    throw new SAXException("Invalid numeric attribute in <map>: " + e.getMessage());
                }

                Log.d("TMXHandler", "Map: " + data.width + "x" + data.height + " tiles " + data.tilewidth + "x" + data.tileheight);
                break;

            case "tileset":
                inTileSet = true;
                currentTileSet = new TileMapData.TileSet();

                String firstGidStr = atts.getValue("firstgid");
                if (firstGidStr == null) throw new SAXException("<tileset> missing required attribute 'firstgid'");
                currentTileSet.firstGID = Integer.parseInt(firstGidStr);

                // Check if this is an external tileset reference
                String source = atts.getValue("source");
                if (source != null) {
                    // External tileset - we'll handle this with a warning
                    Log.w("TMXHandler", "External tileset reference detected: " + source);
                    Log.w("TMXHandler", "External tilesets are not fully supported. Please embed tilesets in your TMX file.");
                    currentTileSet.name = source; // Store source as name for reference
                    currentTileSet.ImageFilename = null; // Mark as external
                } else {
                    // Inline tileset
                    String tileWidth = atts.getValue("tilewidth");
                    String tileHeight = atts.getValue("tileheight");
                    if (tileWidth != null) currentTileSet.tileWidth = Integer.parseInt(tileWidth);
                    if (tileHeight != null) currentTileSet.tileHeight = Integer.parseInt(tileHeight);
                    currentTileSet.name = atts.getValue("name");
                }
                currentTileSetProperties = new HashMap<>();
                break;

            case "image":
                if (inTileSet) {
                    currentTileSet.ImageFilename = atts.getValue("source");
                    String w = atts.getValue("width");
                    String h = atts.getValue("height");
                    if (w != null) currentTileSet.imageWidth = Integer.parseInt(w);
                    if (h != null) currentTileSet.imageHeight = Integer.parseInt(h);
                }
                break;

            case "tile":
                if (inTileSet) {
                    inTile = true;
                    currentTileID = atts.getValue("id");
                }
                break;

            case "properties":
                inProperties = true;
                if (inTile) currentTileSetProperties.put(currentTileID, new HashMap<String, String>());
                if (inLayer) currentLayerProperties = new HashMap<>();
                break;

            case "property":
                if (inProperties) {
                    String name = atts.getValue("name");
                    String value = atts.getValue("value");
                    if (inTile && currentTileID != null) {
                        currentTileSetProperties.get(currentTileID).put(name, value);
                    }
                    if (inLayer && currentLayerProperties != null) {
                        currentLayerProperties.put(name, value);
                    }
                }
                break;

            case "layer":
                inLayer = true;
                currentLayer = new TileMapData.Layer();
                currentLayer.name = atts.getValue("name");
                currentLayer.width = Integer.parseInt(atts.getValue("width"));
                currentLayer.height = Integer.parseInt(atts.getValue("height"));
                String opacityStr = atts.getValue("opacity");
                if (opacityStr != null) {
                    currentLayer.opacity = Double.parseDouble(opacityStr);
                } else {
                    currentLayer.opacity = 1.0;
                }
                currentLayer.tiles = new long[currentLayer.height][currentLayer.width];
                currentLayerProperties = new HashMap<>();
                currentX = 0;
                currentY = 0;
                numberBuffer.setLength(0);
                break;

            case "data":
                inData = true;
                String encoding = atts.getValue("encoding");
                if (!"csv".equals(encoding))
                    throw new SAXException("Unsupported encoding '" + encoding + "'. Only CSV encoding is supported.");
                break;

            case "objectgroup":
                inObjectGroup = true;
                currentObjectGroupName = atts.getValue("name");
                break;

            case "object":
                currentObject = new TileMapData.TMXObject();
                currentObject.name = atts.getValue("name");
                currentObject.type = atts.getValue("type");
                String xStr = atts.getValue("x");
                String yStr = atts.getValue("y");
                String widthStr = atts.getValue("width");
                String heightStr = atts.getValue("height");

                currentObject.x = xStr != null ? Integer.parseInt(xStr) : 0;
                currentObject.y = yStr != null ? Integer.parseInt(yStr) : 0;
                currentObject.width = widthStr != null ? Integer.parseInt(widthStr) : 0;
                currentObject.height = heightStr != null ? Integer.parseInt(heightStr) : 0;
                currentObject.objectGroup = inObjectGroup ? currentObjectGroupName : null;
                break;
        }
    }

    @Override
    public void endElement(String namespaceURI, String localName, String qName) throws SAXException {
        switch (localName) {
            case "tileset":
                inTileSet = false;
                currentTileSet.properties = currentTileSetProperties;

                // Only add tileset if it has valid image data or warn about external tilesets
                if (currentTileSet.ImageFilename != null || currentTileSet.name != null) {
                    data.tilesets.add(currentTileSet);
                    if (currentTileSet.ImageFilename == null) {
                        Log.w("TMXHandler", "Tileset added but has no image data (external tileset): " + currentTileSet.name);
                    }
                }
                currentTileSet = null;
                currentTileSetProperties = null;
                break;

            case "tile":
                inTile = false;
                currentTileID = null;
                break;

            case "properties":
                inProperties = false;
                break;

            case "layer":
                inLayer = false;
                if (currentLayerProperties != null) {
                    currentLayer.properties = currentLayerProperties;
                }
                data.layers.add(currentLayer);
                currentLayer = null;
                break;

            case "data":
                inData = false;
                // Flush last number if buffer has content
                if (numberBuffer.length() > 0) {
                    try {
                        long value = Long.parseLong(numberBuffer.toString());
                        if (currentY < currentLayer.height && currentX < currentLayer.width) {
                            currentLayer.tiles[currentY][currentX] = value;
                        }
                    } catch (NumberFormatException e) {
                        Log.w("TMXHandler", "Invalid number in CSV data: " + numberBuffer.toString());
                    }
                    numberBuffer.setLength(0);
                }
                currentX = 0;
                currentY = 0;
                break;

            case "objectgroup":
                inObjectGroup = false;
                break;

            case "object":
                if (currentObject != null) {
                    data.objects.add(currentObject);
                }
                break;
        }
    }

    @Override
    public void characters(char ch[], int start, int length) {
        if (!inData) return;

        for (int i = 0; i < length; i++) {
            char c = ch[start + i];

            if (c >= '0' && c <= '9') {
                // Append digit to buffer (StringBuilder handles growth automatically)
                numberBuffer.append(c);
            } else if (c == ',' || Character.isWhitespace(c)) {
                // Process accumulated number
                if (numberBuffer.length() > 0) {
                    try {
                        long value = Long.parseLong(numberBuffer.toString());

                        // Safety check to prevent array out of bounds
                        if (currentY < currentLayer.height && currentX < currentLayer.width) {
                            currentLayer.tiles[currentY][currentX] = value;
                        } else {
                            Log.w("TMXHandler", "Tile position out of bounds: x=" + currentX + ", y=" + currentY);
                        }

                        numberBuffer.setLength(0); // Clear buffer
                        currentX++;

                        if (currentX >= currentLayer.width) {
                            currentX = 0;
                            currentY++;
                        }
                    } catch (NumberFormatException e) {
                        Log.w("TMXHandler", "Invalid number in CSV: " + numberBuffer.toString());
                        numberBuffer.setLength(0);
                    }
                }
            }
        }
    }
}