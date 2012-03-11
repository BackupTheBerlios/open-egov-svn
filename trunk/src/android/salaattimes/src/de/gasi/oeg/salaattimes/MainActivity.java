//$Id:$
//
//Project:  Open E-Government :: Salaat Times
//Author:   Gerrit M. Albrecht

package de.gasi.oeg.salaattimes;

import java.util.Date;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;
import de.gasi.oeg.salaattimes.SalaatTimesCalculator.AdjustingMethods;
import de.gasi.oeg.salaattimes.SalaatTimesCalculator.CalculationMethods;
import de.gasi.oeg.salaattimes.SalaatTimesCalculator.JuristicAsrMethods;

public class MainActivity extends Activity implements OnSharedPreferenceChangeListener {
    private SharedPreferences           m_prefs;
	public static SalaatTimesCalculator m_calc = new SalaatTimesCalculator();
	private String                      m_text = new String("");

	public void updateDisplay() {
        m_calc.calc();
		
        TextView view;

        view = (TextView)findViewById(R.id.ui_text_fadjr);
        if (view != null)
        	view.setText(SalaatTimesCalculator.m_name_fadjr);
        view = (TextView)findViewById(R.id.ui_text_shuruk);
        if (view != null)
        	view.setText(SalaatTimesCalculator.m_name_shuruk);
        view = (TextView)findViewById(R.id.ui_text_zuhr);
        if (view != null)
        	view.setText(SalaatTimesCalculator.m_name_zuhr);
        view = (TextView)findViewById(R.id.ui_text_assr);
        if (view != null)
        	view.setText(SalaatTimesCalculator.m_name_assr);
        view = (TextView)findViewById(R.id.ui_text_ghurub);
        if (view != null)
        	view.setText(SalaatTimesCalculator.m_name_ghurub);
        view = (TextView)findViewById(R.id.ui_text_maghrib);
        if (view != null)
        	view.setText(SalaatTimesCalculator.m_name_maghrib);
        view = (TextView)findViewById(R.id.ui_text_ishaa);
        if (view != null)
        	view.setText(SalaatTimesCalculator.m_name_ishaa);

        view = (TextView)findViewById(R.id.ui_value_fadjr);
        if (view != null)
        	view.setText(m_calc.getFadjrTime());
        view = (TextView)findViewById(R.id.ui_value_shuruk);
        if (view != null)
        	view.setText(m_calc.getShurukTime());
        view = (TextView)findViewById(R.id.ui_value_zuhr);
        if (view != null)
        	view.setText(m_calc.getZuhrTime());
        view = (TextView)findViewById(R.id.ui_value_assr);
        if (view != null)
        	view.setText(m_calc.getAssrTime());
        view = (TextView)findViewById(R.id.ui_value_ghurub);
        if (view != null)
        	view.setText(m_calc.getGhurubTime());
        view = (TextView)findViewById(R.id.ui_value_maghrib);
        if (view != null)
        	view.setText(m_calc.getMaghribTime());
        view = (TextView)findViewById(R.id.ui_value_ishaa);
        if (view != null)
        	view.setText(m_calc.getIshaaTime());

        Date d = new Date();

		view = (TextView)findViewById(R.id.ui_date_time);
		if (view != null)
			view.setText(d.toString());
	}

	private Handler  m_handler     = new Handler();
	private long     m_start_time  = 0L;
	private Runnable m_update_task = new Runnable() {
		   public void run() {
//		       final long start = System.currentTimeMillis();
//		       long millis = SystemClock.uptimeMillis() - start;
//		       int seconds = (int) (millis / 1000);
//		       int minutes = seconds / 60;
//		       seconds     = seconds % 60;
//
               String s;
//		       if (seconds < 10) {
//		           s = "-->" + minutes + ":0" + seconds;
//		       } else {
//		           s = "-->" + minutes + ":" + seconds;            
//		       }

               //Log.w("MILLIS", String.valueOf(System.currentTimeMillis()) + "\n" +
               // 	             String.valueOf(SystemClock.uptimeMillis())); 
               updateDisplay();

             // public final boolean postAtTime (Runnable r, long uptimeMillis)
             // uptimeMillis The absolute time at which the callback should run, using the uptimeMillis() time-base.
             // public final boolean postDelayed (Runnable r, long delayMillis)
             // delayMillis The delay (in milliseconds) until the Runnable will be executed.

   		       // Call this handler again if clock changes to a new value.
			   //m_handler.postAtTime(this, start + (((minutes * 60) + seconds + 1) * 1000));
			   m_handler.postDelayed(this, 500);
		   }
	};

	public void startTimer() {
    	  m_handler.removeCallbacks(m_update_task);      // Remove any unwanted other callbacks.
	      m_handler.postDelayed(m_update_task, 100);     // One shot after 100 ms.
	}

	public void stopTimer() {
		m_handler.removeCallbacks(m_update_task);
	}

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        m_prefs = PreferenceManager.getDefaultSharedPreferences(getBaseContext()); //this
        PreferenceManager.setDefaultValues(this, R.xml.preferences, false);

        // Register preference change listener.
        m_prefs.registerOnSharedPreferenceChangeListener(this);

        setContentView(R.layout.main);

        TextView clock;
        clock = (TextView)findViewById(R.id.ui_date_time);
        if (clock != null) {
        	clock.setTextColor(Color.GREEN);
        	clock.setBackgroundColor(Color.TRANSPARENT);
        }

        m_calc.setCoordinates(52.1393, 11.5865);
        m_calc.setTimeZone(1.0);
        m_calc.setCalculationMethod(CalculationMethods.MWL);
        m_calc.setJuristicAsrMethod(JuristicAsrMethods.Shafii);
        m_calc.setAdjustingMethod(AdjustingMethods.AngleBased);

        updateDisplay();
        startTimer();
    }

    @Override
    protected void onDestroy() {
        this.getPreferences(MODE_PRIVATE).unregisterOnSharedPreferenceChangeListener(this);
        super.onDestroy();
    }

    @Override
    protected void onResume()
    {
        startTimer();
//        if (de.gasi.oeg.compass.Settings.oeg_debug_logs)
//            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
//              "onResume()");
        super.onResume();
    }

    @Override
    protected void onStop()
    {
//        if (de.gasi.oeg.compass.Settings.oeg_debug_logs)
//            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
//              "onStop()");
    	stopTimer();
        super.onStop();
    }

    // Needed?
    @Override
    protected void onPause()
    {
//        if (de.gasi.oeg.compass.Settings.oeg_debug_logs)
//            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
//              "onPause()");
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

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
            case 0:
                actionSettings();
                return true;
            case 1:
                //actionAboutApp();
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

    // Handle updates to preferences.
    public void onSharedPreferenceChanged(SharedPreferences prefs, String key) {

    }
}

