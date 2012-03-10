// Project: Open eGovernment :: Compass

package de.gasi.oeg.compass;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class CompassView extends View {
	private Paint   m_paint    = new Paint();
    private Path    m_path     = new Path();
    private boolean m_animate  = false;
    private int     m_angle    = 0;
    private int     m_fg_color = Color.BLUE;
    private int     m_bg_color = Color.YELLOW;
    private Boolean m_debug    = false;

    public CompassView(Context context, AttributeSet attrs) {
      super(context, attrs);

      // TODO: Construct path only here.

    }

    public void setShowDebug(Boolean debug) {
    	m_debug = debug;
    }
    
    public void setForegroundColor(int color) {
    	m_fg_color = colorCodeToColorValue(color);
    }
    
    public void setBackgroundColor(int color) {
    	m_bg_color = colorCodeToColorValue(color);
    }

    public void setDirection(int angle) {
      if (m_angle != angle) {       // Call invalidate() only if value changed.
        m_angle = angle;
        invalidate();
      }
    }
    
    public int colorCodeToColorValue(int code) {
      switch (code) {
      case  0: return Color.BLACK;
      case  1: return Color.WHITE;
      case  2: return Color.LTGRAY;
      case  3: return Color.GRAY;
      case  4: return Color.DKGRAY;
      case  5: return Color.RED;
      case  6: return Color.BLUE;
      case  7: return Color.GREEN;
      case  8: return Color.CYAN;
      case  9: return Color.MAGENTA;
      case 10: return Color.YELLOW;
      }
      return Color.TRANSPARENT;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        canvas.drawColor(m_bg_color);

        if (m_debug)
            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
               "onDraw: m_animate=" + m_animate);

        m_paint.setAntiAlias(true);
        m_paint.setColor(m_fg_color);
        m_paint.setStyle(Paint.Style.FILL_AND_STROKE);

        int w = canvas.getWidth();
        int h = canvas.getHeight();
        int cx = w / 2;
        int cy = h / 2;
        int nl = (int) (Math.min(w, h) * 0.6);     // Needle length.
        int nw = (int) nl/5;                       // Needle width.

        m_path.reset();                            // 0,0 ist der Drehpunkt des Zeigers.
        m_path.moveTo(0,  -nl/2);                  // Spitze des Zeigers.
        m_path.lineTo(nw,  nl/2);                  // Unten und etwas nach rechts
        m_path.lineTo(0,   (int) (nl/2 * 0.8));    // Eine kleine Kerbe nach oben (hinten).
        m_path.lineTo(-nw, nl/2);                  // Unten und etwas nach links.
        m_path.close();

        canvas.translate(cx, cy);                  // Else it is in the left/bottom corner.
        canvas.rotate(m_angle);
        canvas.drawPath(m_path, m_paint);
    }

    @Override
    protected void onAttachedToWindow() {
        m_animate = true;
        if (m_debug)
            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
               "onAttachedToWindow: m_animate=" + m_animate);
        super.onAttachedToWindow();
    }

    @Override
    protected void onDetachedFromWindow() {
        m_animate = false;
        if (m_debug)
            Log.d(de.gasi.oeg.compass.Settings.oeg_app_name,
             "onDetachedFromWindow: m_animate=" + m_animate);
        super.onDetachedFromWindow();
    }

}

