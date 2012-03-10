// $Id$
//
// Project:  Open E-Government :: Compass
// Author:   Gerrit M. Albrecht

package de.gasi.oeg.compass;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.content.res.Configuration;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

public class MainActivity extends Activity implements OnSharedPreferenceChangeListener {
    private SensorManager     m_sensor_manager;
    private Sensor            m_sensor;
    private CompassView       m_compass_view;
    private TextView          m_text_view;
    private SharedPreferences m_prefs;

    public static final String PREFS_NAME = "preferences";

    private final SensorEventListener m_listener = new SensorEventListener() {
        public void onSensorChanged(SensorEvent event) {
            if (de.gasi.oeg.compass.Settings.oeg_debug_logs)
                Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
                    "sensorChanged (" + event.values[0] + ", " + event.values[1] + ", " + event.values[2] + ")");

            if (m_compass_view != null) {
            	m_compass_view.setDirection((int) -event.values[0]);  // -1, da Kompass im Uhrzeigersinn und Canvas nicht.
            }

            if (m_text_view != null) {
                m_text_view.setText(getString(R.string.measured_angle) + ": " + (int) event.values[0] + "°");
            }
        }

        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        m_prefs = PreferenceManager.getDefaultSharedPreferences(getBaseContext()); //this
        PreferenceManager.setDefaultValues(this, R.xml.preferences, false);

        // register preference change listener.
        m_prefs.registerOnSharedPreferenceChangeListener(this);

        if (m_prefs.getBoolean("full_screen", true)) {
        	// Before setContentView!
            getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                                 WindowManager.LayoutParams.FLAG_FULLSCREEN);
            requestWindowFeature(Window.FEATURE_NO_TITLE);
        }

        if (de.gasi.oeg.compass.Settings.oeg_no_standby) {
        	
        }

        m_sensor_manager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        m_sensor = m_sensor_manager.getDefaultSensor(Sensor.TYPE_ORIENTATION);

        setContentView(R.layout.main);

        m_compass_view = (CompassView)findViewById(R.id.CompassView);
        m_text_view = (TextView)findViewById(R.id.TextView);
    }

    @Override
    protected void onDestroy() {
        this.getPreferences(MODE_PRIVATE).unregisterOnSharedPreferenceChangeListener(this);
        super.onDestroy();
    }

    @Override
	public void onConfigurationChanged(Configuration newConfig) {
    	Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
                "onConfigurationChanged()");
      super.onConfigurationChanged(newConfig);
    }

    @Override
    protected void onResume()
    {
        if (de.gasi.oeg.compass.Settings.oeg_debug_logs)
            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
              "onResume()");
        super.onResume();

        m_sensor_manager.registerListener(m_listener, m_sensor, // this
        		SensorManager.SENSOR_DELAY_GAME); // _NORMAL
    }

    @Override
    protected void onStop()
    {
        if (de.gasi.oeg.compass.Settings.oeg_debug_logs)
            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
              "onStop()");
        m_sensor_manager.unregisterListener(m_listener);
        super.onStop();
    }

    // Needed?
    @Override
    protected void onPause()
    {
        if (de.gasi.oeg.compass.Settings.oeg_debug_logs)
            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
              "onPause()");
        m_sensor_manager.unregisterListener(m_listener);
        super.onPause();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        menu.add(Menu.NONE, 0, 0, R.string.menu_settings);
        menu.add(Menu.NONE, 1, 0, R.string.menu_about_app);
        // TODO if()
        menu.add(Menu.NONE, 2, 0, R.string.menu_exit);

        return super.onCreateOptionsMenu(menu);
    }

    public void actionSettings() {
    	startActivity(new Intent(this, SettingsActivity.class));
    }

    public void actionAboutApp() {
    	AlertDialog.Builder alertbox = new AlertDialog.Builder(this);

    	alertbox.setTitle(R.string.app_name);
        alertbox.setMessage(R.string.about_app_text);

        // Add a neutral button to the alert box and assign a click listener
        alertbox.setNeutralButton(getString(R.string.button_okay),
        		new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
            	dialog.dismiss();
            }
        });
        alertbox.show();
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
            case 0:
                actionSettings();
                return true;
            case 1:
                actionAboutApp();
                return true;
            case 2:
                finish();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
      return super.onPrepareOptionsMenu(menu);
    }

    // handle updates to preferences
    public void onSharedPreferenceChanged(SharedPreferences prefs, String key) {
        Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
      		"onSharedPreferenceChanged(key=" + key + ") ALL: " + m_prefs.getAll().toString());

        if (key.equals("full_screen")) {
        	// it's not possible to remove/show the title after setContentView().
            if (m_prefs.getBoolean("full_screen", true)) {
                getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                                     WindowManager.LayoutParams.FLAG_FULLSCREEN);
            }
            else {
            	getWindow().clearFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
            }
        }
        else if (key.equals("debug_logs")) {
          m_compass_view.setShowDebug(m_prefs.getBoolean("debug_logs", false));
        }
        else if (key.equals("fav_fg_color")) {
            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
          		"FGC: " + m_prefs.getString("fav_fg_color", ""));
          m_compass_view.setForegroundColor(Integer.parseInt(m_prefs.getString("fav_fg_color", "0")));
        }
        else if (key.equals("fav_bg_color")) {
            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
          		"BGC: " + m_prefs.getString("fav_bg_color", ""));
          m_compass_view.setBackgroundColor(Integer.parseInt(m_prefs.getString("fav_bg_color", "0")));
        }
    }

}

