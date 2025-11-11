package ubi.pt.pdm_project.util;

public class LevelCoordinates {
    public float x;
    public float y;
    public int level;

    public LevelCoordinates(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public LevelCoordinates(float x, float y, int level) {
        this.x = x;
        this.y = y;
        this.level = level;
    }
}