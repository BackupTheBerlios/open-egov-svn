//$Id:$
//
//Project:  Open E-Government :: Salaat Times
//Author:   Gerrit M. Albrecht

package de.gasi.oeg.salaattimes;

import android.os.Bundle;
import android.preference.PreferenceActivity;
import de.gasi.oeg.salaattimes.R;

public class SettingsActivity extends PreferenceActivity {

	@Override
    public void onCreate(Bundle savedInstanceState) {       
        super.onCreate(savedInstanceState);       
        addPreferencesFromResource(R.xml.preferences);       
    }

}
