// $Id:$

package de.gasi.oeg.houbi;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;

public class MainActivity extends Activity {

	private GestureDetector m_gesture_detector;
	private ImageView       m_imageview;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        m_gesture_detector = new GestureDetector(this, new MyGestureDetector());

        m_imageview = (ImageView)findViewById(R.id.ui_imageview);

        //onTouch gives you a chance for something to respond before the view does.
        //onClick is fired after the view responds
        m_imageview.setOnTouchListener(new OnTouchListener() {
          public boolean onTouch(View v, MotionEvent event)
          {
        	  m_gesture_detector.onTouchEvent(event);
              return true;
          }
        });
        
        m_imageview.setClickable(true);
        m_imageview.setOnClickListener(new View.OnClickListener() {
        	public void onClick(View v)
        	{
        	}
        });

        m_imageview.setLongClickable(true);
        m_imageview.setOnLongClickListener(new View.OnLongClickListener() {
            public boolean onLongClick(View v) {
            	
            	return true;
            }
        });
    }

    //Bitmap bm = BitmapFactory.decodeResource(getResources(), R.drawable.test);
    public void showImageFromFile(String path) { // e.g. "/sdcard/test.png"
        try {
            FileInputStream in;
            BufferedInputStream buf;

       	    in  = new FileInputStream(path);
            buf = new BufferedInputStream(in);
            byte[] bMapArray= new byte[buf.available()];
            buf.read(bMapArray);
            Bitmap bMap = BitmapFactory.decodeByteArray(bMapArray, 0, bMapArray.length);
            m_imageview.setImageBitmap(bMap);
            if (in != null) {
           	  in.close();
            }
            if (buf != null) {
         	  buf.close();
            }
        } catch (Exception e) {
            Log.e("Houbi: Error reading file", e.toString());
            Log.e("Houbi", "Local Image Exception", e);
        }
    }

    public void showImageFromURL(String imageURL) {
        try {
            // Open a new URL and get the InputStream to load data from it.
            URL url = new URL(imageURL);
            URLConnection conn = url.openConnection();
            conn.connect();
            InputStream is = conn.getInputStream();
            // Buffered is always good for a performance plus.
            BufferedInputStream bis = new BufferedInputStream(is);
            // Decode url-data to a bitmap.
            Bitmap bm = BitmapFactory.decodeStream(bis);
            bis.close();
            is.close();
            // Apply the Bitmap to the ImageView that will be returned.
            m_imageview.setImageBitmap(bm);
      } catch (IOException e) {
    	    //m_imageview.setImageResource(R.drawable.error);
            Log.e("Houbi", "Remote Image Exception", e);
      }
    }
}
