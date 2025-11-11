package ubi.pt.pdm_project.managers;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;

import ubi.pt.pdm_project.tmxconverter.TMXSurfaceView;

public class InputManager implements SensorEventListener {

    private final SensorManager sensorManager;
    private final Sensor accelerometer;
    private final TMXSurfaceView gameView;
    private static final float TILT_Y_OFFSET = 6.5f;

    public InputManager(Context context, TMXSurfaceView gameView) {
        this.sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
        this.accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        this.gameView = gameView;

        if (accelerometer == null) {
            Log.e("InputManager", "No accelerometer found");
        } else {
            Log.d("InputManager", "Accelerometer ready: " + accelerometer.getName());
        }
    }

    public void register() {
        Log.d("InputManager", "Registered accelerometer listener");
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_GAME);
    }

    public void unregister() {
        Log.d("InputManager", "Unregistered accelerometer listener");
        sensorManager.unregisterListener(this);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        float tiltX = event.values[0]; // Left/right tilt (stays the same)
        float tiltY = event.values[1]; // Forward/backward tilt

        float adjustedTiltY = tiltY - TILT_Y_OFFSET;

        Log.d("SensorDebug", "Raw Y: " + tiltY + " | Adjusted Y: " + adjustedTiltY);

        gameView.setTilt(tiltX, adjustedTiltY);
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {}
}