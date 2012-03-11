// $Id:$

package de.gasi.oeg.houbi;

import android.util.Log;
import android.view.GestureDetector.SimpleOnGestureListener;
import android.view.MotionEvent;

public class MyGestureDetector extends SimpleOnGestureListener {

	@Override
	 public boolean onDoubleTapEvent(MotionEvent e)
	 {
	    Log.i("Houbi", "onDoubleTapEvent");
	    return true;
	}

}
