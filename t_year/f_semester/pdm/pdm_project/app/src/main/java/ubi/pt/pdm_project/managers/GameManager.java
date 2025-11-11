package ubi.pt.pdm_project.managers;

import android.util.Log;

import ubi.pt.pdm_project.tmxconverter.TMXSurfaceView;

public class GameManager extends Thread {
    private boolean running = false;
    private static final int FPS = 60;
    private final TMXSurfaceView view;

    public GameManager(TMXSurfaceView view) {
        this.view = view;
    }

    public void setRunning(boolean running) {
        this.running = running;
    }

    @Override
    public void run() {
        Log.d("GameDebug", "Game Loop running: " + running);

        long frameTime = 1000 / FPS;
        while (running) {
            long start = System.currentTimeMillis();
            view.update();
            view.drawFrame();

            long elapsed = System.currentTimeMillis() - start;
            long sleep = frameTime - elapsed;
            if (sleep > 0) {
                try { Thread.sleep(sleep); } catch (InterruptedException ignored) {}
            }
        }
    }
}