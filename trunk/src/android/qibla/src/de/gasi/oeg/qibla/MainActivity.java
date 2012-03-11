// $Id:$
//
// Project:  Open E-Government :: Qibla
// Author:   Gerrit M. Albrecht

package de.gasi.oeg.qibla;

import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.location.Criteria;
import android.location.LocationManager;
import android.location.LocationProvider;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {

	private LocationManager m_loc_man;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        m_loc_man = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
        boolean enabledOnly = true;
        List<String> providers = m_loc_man.getProviders(enabledOnly);
        for (String provider : providers) {
          Log.d("qibla", "Available provider: " + provider);
        }

        Criteria criteria = new Criteria();
        criteria.setAccuracy(Criteria.ACCURACY_COARSE);
        criteria.setPowerRequirement(Criteria.POWER_LOW);
        criteria.setAltitudeRequired(false);
        criteria.setBearingRequired(false);
        criteria.setSpeedRequired(false);
        criteria.setCostAllowed(true);
        String bestProvider = m_loc_man.getBestProvider(criteria, true);
        LocationProvider locationProvider = m_loc_man.getProvider(bestProvider);
    }






}

