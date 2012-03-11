//$Id:$
//
//Project:  Open E-Government :: Salaat Times
//Author:   Gerrit M. Albrecht

package de.gasi.oeg.salaattimes;

import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;


// Schreibweisen der Zeitennamen:
// Fadjr, Shuruk, Zuhr, Assr, Maghrib, Isha'a
// Fajr, Sunrise, Dhuhr, Asr, Maghrib, Isha

// 17.02.2012, 25. Rabii
// 5:42 7:23 12:28 14:58 17:30 19:06

// https://en.wikipedia.org/wiki/Salah
// http://www.salat-time.com/
// http://praytimes.org/calculation/
// http://praytimes.org/wiki/A_note_on_Dhuhr
// http://www.islamicfinder.org/prayerCustomized.php?id=95089&city=magdeburg&state=&state_name=Sachsen-Anhalt&zipcode=&country=germany&latitude=52.1667&longitude=11.6667&timezone=1.00&daylight=1&pmethod=1&HanfiShafi=1&dhuhrInterval=1&maghribInterval=1&fajrTwilight1=&fajrTwilight2=&ishaTwilight=0&ishaInterval=0&start_month_daylight=3&start_day_daylight=25&end_month_daylight=10&end_day_daylight=28&start_daylight_year=2012&end_daylight_year=2012&day=17&month=02&year=2012&lang=
// http://www.islamicfinder.org/prayerDetail.php?country=germany&city=Magdeburg&state=&lang=&home=2011-9-19

// https://encrypted.google.com/url?sa=t&rct=j&q=shuruk%20sonnenuntergang&source=web&cd=4&ved=0CD8QFjAD&url=http%3A%2F%2Fde.answers.yahoo.com%2Fquestion%2Findex%3Fqid%3D20080225055925AABWCln&ei=giI-T7q6F8rxsgajy6CsBA&usg=AFQjCNFxOsr58o9IJjmfbCQlmDbnkdFQQw&cad=rja
// https://encrypted.google.com/url?sa=t&rct=j&q=shuruk%20sonnenuntergang&source=web&cd=1&ved=0CCAQFjAA&url=http%3A%2F%2Fwww.gutefrage.net%2Ffrage%2Fislamische-gebetszeiten-hilfe-bei-fadjr-u-shuruk-ramadan&ei=giI-T7q6F8rxsgajy6CsBA&usg=AFQjCNFIqXD1j2K_ueRFSFLSxvYOMsT81w&cad=rja
// https://encrypted.google.com/url?sa=t&rct=j&q=shuruk%20sonnenuntergang&source=web&cd=3&ved=0CDgQFjAC&url=http%3A%2F%2Fwww.izaachen.de%2Findex.php%3Fsite%3Dgebetszeiten%26folder%3DA&ei=giI-T7q6F8rxsgajy6CsBA&usg=AFQjCNFFgrD6jQF4yoY-wd7Uzn_NGmAHCw&cad=rja
// https://encrypted.google.com/url?sa=t&rct=j&q=shuruk%20sonnenuntergang&source=web&cd=6&ved=0CFUQFjAF&url=http%3A%2F%2Fwww.muslima-aktiv.de%2Fforum%2Fviewtopic.php%3Ff%3D3%26t%3D3171&ei=giI-T7q6F8rxsgajy6CsBA&usg=AFQjCNH5sC4pqd2aXcer86d8edQMXYwL1A&cad=rja
// http://praytimes.org/wiki/Calculation_Methods

//Convention 	Fajr Angle 	Isha Angle
//Muslim World League 	18 	17
//Islamic Society of North America (ISNA) 	15 	15
//Egyptian General Authority of Survey 	19.5 	17.5
//Umm al-Qura University, Makkah 	18.5 	90 min after Maghrib
//120 min during Ramadan
//University of Islamic Sciences, Karachi 	18 	18
//Institute of Geophysics, University of Tehran 	17.7 	14*
//Shia Ithna Ashari, Leva Research Institute, Qum 	16 	14 

public class SalaatTimesCalculator {

	public static boolean m_show_fadjr           = true;
	public static boolean m_show_shuruk          = true;
	public static boolean m_show_zuhr            = true;
	public static boolean m_show_assr            = true;
	public static boolean m_show_ghurub          = true;
	public static boolean m_show_maghrib         = true;
	public static boolean m_show_ishaa           = true;
	public static String  m_name_fadjr           = "Fadjr";
	public static String  m_name_shuruk          = "Shuruk"; // Sonnenaufgang.
	public static String  m_name_zuhr            = "Zuhr";
	public static String  m_name_assr            = "Assr";
	public static String  m_name_ghurub          = "Ghurub"; // Sonnenuntergang.
	public static String  m_name_maghrib         = "Maghrib";
	public static String  m_name_ishaa           = "Isha'a";
	public static String  m_str_fadjr            = "";
	public static String  m_str_shuruk           = "";
	public static String  m_str_zuhr             = "";
	public static String  m_str_assr             = "";
	public static String  m_str_ghurub           = "";
	public static String  m_str_maghrib          = "";
	public static String  m_str_ishaa            = "";

    public static double  m_daylight_saving_time = 0.0;
    public static double  m_time_zone            = 1.0;

    public static double  m_latitude             = 51.5000;
    public static double  m_longitude            = 12.0000;
    public static Date    m_date                 = new Date(System.currentTimeMillis());
    public static double  m_julian_date          = 0.0;

    public enum CalculationMethods {
    	ISNA,                          // Islamic Society of North America (ISNA)
    	Jafari,                        // Ithna Ashari.
    	Karachi,                       // University of Islamic Sciences, Karachi.
    	MWL,                           // Muslim World League (MWL), https://de.wikipedia.org/wiki/Islamische_Weltliga
    	Makkah,                        // Umm al-Qura, Makkah.
    	Egypt,                         // Egyptian General Authority of Survey.
    	Tehran,                        // Institute of Geophysics, University of Tehran.
        // TODO: Turkey?
    	Custom                         // Customized settings.
    }

    public enum JuristicAsrMethods {   // Juristic methods.
    	Shafii,                        // Shafii (standard).
    	Hanafi                         // Hanafi.
    }

    public enum AdjustingMethods {     // Adjusting methods for higher latitudes.
      MidNight,                        // middle of night.
      OneSeventh,                      // 1/7th of night.
      AngleBased,                      // angle/60th of night.
      None                             // No adjustment.
    }

    public enum TimeFormats {          // Time formats.
      Hours24,                         // 24-hour format.
      Hours12,                         // 12-hour format.
      Hours12NoSuffix,                 // 12-hour format with no suffix.
      Floating                         // Floating point number.
    }

    private CalculationMethods  m_calculation_method  = CalculationMethods.MWL;
    private JuristicAsrMethods  m_juristic_asr_method = JuristicAsrMethods.Shafii;
    private AdjustingMethods    m_adjusting_method    = AdjustingMethods.AngleBased;
    private TimeFormats         m_time_format         = TimeFormats.Hours24;
    private int                 m_dhuhr_minutes       = 0;  // minutes after mid-day for Dhuhr.

    // this.methodParams[methodNum] = new Array(fa, ms, mv, is, iv);
    //
    // fa : fajr angle
    // ms : maghrib selector (0 = angle; 1 = minutes after sunset) 
    // mv : maghrib parameter value (in angle or minutes)
    // is : isha selector (0 = angle; 1 = minutes after maghrib)
    // iv : isha parameter value (in angle or minutes)

    private HashMap<CalculationMethods, double[]>  m_default_parameters;
    private double[]                               m_parameters;
    private double[]                               m_prayer_times_current;
    private int[]                                  m_offsets;

    public void setCoordinates(double latitude, double longitude) {
    	m_latitude  = latitude;
    	m_longitude = longitude;
    }

    public void setDate(Date date) {
    	m_date = date;
    }

    public double julianDate() {
        return m_julian_date;
    }

    public void setJulianDate(double d) {
    	m_julian_date = d;
    }

    // calculate julian date from a calendar date
    private double calcJulianDate(int year, int month, int day) {
        if (month <= 2) {
            year -= 1;
            month += 12;
        }
        double A = Math.floor(year / 100.0);

        double B = 2 - A + Math.floor(A / 4.0);

        double JD = Math.floor(365.25 * (year + 4716))
                + Math.floor(30.6001 * (month + 1)) + day + B - 1524.5;

        return JD;
    }

    // convert a calendar date to julian date (second method)
    private double calcJulianDateX(int year, int month, int day) {
        double J1970 = 2440588.0;
        Date date = new Date(year, month - 1, day);

        double ms = date.getTime(); // # of milliseconds since midnight Jan 1,
        // 1970
        double days = Math.floor(ms / (1000.0 * 60.0 * 60.0 * 24.0));
        return J1970 + days - 0.5;
    }

    public void calc() {
    	Calendar calendar = Calendar.getInstance();
    	//Date now = new Date();
    	calendar.setTime(m_date);

        int year  = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH) + 1;
        int day   = calendar.get(Calendar.DATE);

        setJulianDate(calcJulianDate(year, month, day));
        double diff = m_longitude / (15.0 * 24.0);
        setJulianDate(julianDate() - diff);

        // Tuning offsets {Fajr, Sunrise, Dhuhr, Asr, Sunset, Maghrib, Isha} in minutes.
        m_offsets = new int[7];
        m_offsets[0] = 0;
        m_offsets[1] = 0;
        m_offsets[2] = 0;
        m_offsets[3] = 0;
        m_offsets[4] = 0;
        m_offsets[5] = 0;
        m_offsets[6] = 0;

        // Result strings.
    	m_str_fadjr   = "";
    	m_str_shuruk  = "";
    	m_str_zuhr    = "";
    	m_str_assr    = "";
    	m_str_ghurub  = "";
    	m_str_maghrib = "";
    	m_str_ishaa   = "";

        // fa : fajr angle
        // ms : maghrib selector (0 = angle; 1 = minutes after sunset)
        // mv : maghrib parameter value (in angle or minutes)
        // is : isha selector (0 = angle; 1 = minutes after maghrib)
        // iv : isha parameter value (in angle or minutes)

        m_default_parameters = new HashMap<CalculationMethods, double[]>();


        double[] values = { 0, 0, 0, 0, 0 };

        // Jafari.
        values[0] = 16;
        values[1] = 0;
        values[2] = 4;
        values[3] = 0;
        values[4] = 14;
        m_default_parameters.put(CalculationMethods.Jafari, values);

        // Karachi.
        values[0] = 18;
        values[1] = 1;
        values[2] = 0;
        values[3] = 0;
        values[4] = 18;
        m_default_parameters.put(CalculationMethods.Karachi, values);

        // ISNA.
        values[0] = 15;
        values[1] = 1;
        values[2] = 0;
        values[3] = 0;
        values[4] = 15;
        m_default_parameters.put(CalculationMethods.ISNA, values);

        // MWL.
        values[0] = 18;
        values[1] = 1;
        values[2] = 0;
        values[3] = 0;
        values[4] = 17;
        m_default_parameters.put(CalculationMethods.MWL, values);

        // Makkah.
        values[0] = 18.5;
        values[1] = 1;
        values[2] = 0;
        values[3] = 1;
        values[4] = 90;
        m_default_parameters.put(CalculationMethods.Makkah, values);

        // Egypt.
        values[0] = 19.5;
        values[1] = 1;
        values[2] = 0;
        values[3] = 0;
        values[4] = 17.5;
        m_default_parameters.put(CalculationMethods.Egypt, values);

        // Tehran.
        values[0] = 17.7;
        values[1] = 0;
        values[2] = 4.5;
        values[3] = 0;
        values[4] = 14;
        m_default_parameters.put(CalculationMethods.Tehran, values);

        // Custom.
        values[0] = 18;
        values[1] = 1;
        values[2] = 0;
        values[3] = 0;
        values[4] = 17;
        m_default_parameters.put(CalculationMethods.Custom, values);


        // compute prayer times at given julian date
        double[] times = {5, 6, 12, 13, 18, 18, 18}; // default times

        times = computeTimes(times);
        times = adjustTimes(times);
        times = tuneTimes(times);

        adjustTimesFormat(times);

        
    }

    // get time in milliseconds since 1970 Jan 1
    // long timestamp = System.currentTimeMillis();

    // http://www.ummah.net/astronomy/saltime
    // http://aa.usno.navy.mil/faq/docs/SunApprox.html

    private double m_equation_of_time  = 0.0; // equation of time
    private double m_declination_angle = 0.0; // declination angle of sun

    private void sunPosition(double jd) {
    	double d = jd - 2451545;
        double g = fixangle(357.529 + 0.98560028 * d);
        double q = fixangle(280.459 + 0.98564736 * d);
        double L = fixangle(q + (1.915 * dsin(g)) + (0.020 * dsin(2 * g)));

        // double r = 1.00014 - 0.01671 * [self dcos:g] - 0.00014 * [self dcos:(2*g)];
        double e = 23.439 - (0.00000036 * d);
        m_declination_angle = darcsin(dsin(e) * dsin(L));
        double ra = darctan2((dcos(e) * dsin(L)), (dcos(L))) / 15.0;
        m_equation_of_time = q/15.0 - fixhour(ra);
    }

    // Calculate sun's declination angle for a given time.
    private double declinationAngle(double jd) {
        sunPosition(jd);
        return m_declination_angle;
    }

    // Calculate the equation of time.
    private double equationOfTime(double jd) {
        sunPosition(jd);
        return m_equation_of_time;
    }

    // Calculate the time of Asr
    // Shafii: step=1, Hanafi: step=2
    private double calculateAsr(double step, double t) {
        double d = declinationAngle(m_julian_date + t);
        double g = -darccot(step + dtan(Math.abs(m_latitude - d)));
        return computeTime(g, t);
    }

    // Calculate noon (MidDay, Dhuhr, Zawal) time.
    private double calculateNoon(double t) {
        return fixhour(12 - equationOfTime(m_julian_date + t));
    }

    // Calculate the time for a given angle a.
    private double computeTime(double a, double t) {
        double d = declinationAngle(m_julian_date + t);
        double b = -dsin(a) - dsin(d) * dsin(m_latitude);  // Beg
        double m = dcos(d) * dcos(m_latitude);             // Mid
        double v = darccos(b/m) / 15.0;

        return calculateNoon(t) + (a > 90 ? -v : v);
    }
 
    // Math functions.

    // range reduce angle in degrees.
    private double fixangle(double a) {
        a = a - (360 * (Math.floor(a / 360.0)));

        a = a < 0 ? (a + 360) : a;
        
        return a;
    }

    // range reduce hours to 0..23
    private double fixhour(double a) {
        a = a - 24.0 * Math.floor(a / 24.0);
        a = a < 0 ? (a + 24) : a;
        return a;
    }

    // compute the difference between two times.
    private double timeDiff(double time1, double time2) {
        return fixhour(time2 - time1);
    }

    // Converts radians to degrees.
    private double radiansToDegrees(double x) {
        return ((x * 180.0) / Math.PI);
    }

    // Converts degrees to radians.
    private double DegreesToRadians(double x) {
        return ((x * Math.PI) / 180.0);
    }

    // degree sin
    private double dsin(double x) {
        return (Math.sin(DegreesToRadians(x)));
    }

    // degree cos
    private double dcos(double x) {
        return (Math.cos(DegreesToRadians(x)));
    }

    // degree tan
    private double dtan(double x) {
        return (Math.tan(DegreesToRadians(x)));
    }

    // degree arcsin
    private double darcsin(double x) {
        double val = Math.asin(x);
        return radiansToDegrees(val);
    }

    // degree arccos
    private double darccos(double x) {
        double val = Math.acos(x);
        return radiansToDegrees(val);
    }

    // degree arctan
    private double darctan(double x) {
        double val = Math.atan(x);
        return radiansToDegrees(val);
    }

    // degree arctan2
    private double darctan2(double y, double x) {
        double val = Math.atan2(y, x);
        return radiansToDegrees(val);
    }

    // degree arccot
    private double darccot(double x) {
        double val = Math.atan2(1.0, x);
        return radiansToDegrees(val);
    }

    // the night portion used for adjusting times in higher latitudes
    private double nightPortion(double angle) {
      double calc = 0.0;

      switch (adjustingMethod()) {
      case AngleBased:
    	  calc = angle / 60.0;
    	  break;
      case MidNight:
    	  calc = 0.5;
    	  break;
      case OneSeventh:
    	  calc = 0.14285714285714285714285714285714;   // 1/7.
    	  break;
   	  default:
   		  break;
      }

      return calc;
    }

    // compute prayer times at given julian date
    private double[] computeTimes(double[] times) {

        double[] t = dayPortion(times);

        double Fajr    = computeTime(180 - m_default_parameters.get(calculationMethod())[0], t[0]);
        double Sunrise = computeTime(180 - 0.833, t[1]);
        double Dhuhr   = calculateNoon(t[2]);
        double Asr;
        if (juristicAsrMethod() == JuristicAsrMethods.Hanafi)
          Asr = calculateAsr(1, t[3]);
        else
          Asr = calculateAsr(1+1, t[3]);
        	
        double Sunset  = computeTime(0.833, t[4]);
        double Maghrib = computeTime(m_default_parameters.get(calculationMethod())[2], t[5]);
        double Isha    = computeTime(m_default_parameters.get(calculationMethod())[4], t[6]);

        double[] CTimes = {Fajr, Sunrise, Dhuhr, Asr, Sunset, Maghrib, Isha};

        return CTimes;
    }

    // Adjust times in a prayer time array.
    private double[] adjustTimes(double[] times) {
        for (int i = 0; i < times.length; i++) {
            //times[i] += timeZone() - m_longitude / 15;
        }
/*
        times[2] += dhuhrMinutes() / 60; // Dhuhr
        if (m_default_parameters.get(calculationMethod())[1] == 1) // Maghrib
        {
            times[5] = times[4] + m_default_parameters.get(calculationMethod())[2]/ 60;
        }
        if (methodParams.get(calculationMethod())[3] == 1) // Isha
        {
            times[6] = times[5] + m_default_parameters.get(calculationMethod())[4]/ 60;
        }

        if (getAdjustHighLats() != getNone()) {
            times = adjustHighLatTimes(times);
        }
*/
        return times;
    }

    // Tune timings for adjustments, set time offsets
    public void tune(int[] offsetTimes) {
        for (int i = 0; i < offsetTimes.length; i++) {
            // should be 7 in order
            // of Fajr, Sunrise,
            // Dhuhr, Asr, Sunset,
            // Maghrib, Isha
            m_offsets[i] = offsetTimes[i];
        }
    }

    private double[] tuneTimes(double[] times) {
        for (int i = 0; i < times.length; i++) {
            times[i] = times[i] + m_offsets[i] / 60.0;
        }

        return times;
    }

    // convert hours to day portions
    private double[] dayPortion(double[] times) {
        for (int i = 0; i < 7; i++) {
            times[i] /= 24;
        }
        return times;
    }

    // Parameters.

    public void setTimeZone(double time_zone) {
    	m_time_zone = time_zone;
    }

    public void setCalculationMethod(CalculationMethods calculation_method) {
        m_calculation_method = calculation_method;
    }
    
    public CalculationMethods calculationMethod() {
        return m_calculation_method;
    }

    public void setJuristicAsrMethod(JuristicAsrMethods juristic_asr_method) {
        m_juristic_asr_method = juristic_asr_method;
    }

    public JuristicAsrMethods juristicAsrMethod() {
        return m_juristic_asr_method;
    }

    public void setAdjustingMethod(AdjustingMethods adjusting_method) {
    	m_adjusting_method = adjusting_method;
    }

    public AdjustingMethods adjustingMethod() {
        return m_adjusting_method;
    }


    public void setTimeFormat(TimeFormats time_format) {
    	m_time_format = time_format;
    }

    public TimeFormats timeFormat() {
        return m_time_format;
    }

    public void setDhuhrMinutes(int dhuhr_minutes) {
    	m_dhuhr_minutes = dhuhr_minutes;
    }

    public int dhuhrMinutes() {
        return m_dhuhr_minutes;
    }

    // Results.

    String getFadjrTime() {
    	return m_str_fadjr;
    }

    String getShurukTime() {
    	return m_str_shuruk;
    }

    String getZuhrTime() {
    	return m_str_zuhr;
    }

    String getAssrTime() {
    	return m_str_assr;
    }

    String getGhurubTime() {
    	return m_str_ghurub;
    }

    String getMaghribTime() {
    	return m_str_maghrib;
    }

    String getIshaaTime() {
    	return m_str_ishaa;
    }

    // convert double hours to 24h format
    public String floatToTime24(double time) {

        String result;

        if (Double.isNaN(time)) {
            return "---";
        }

        time = fixhour(time + 0.5 / 60.0); // add 0.5 minutes to round
        int hours = (int)Math.floor(time);
        double minutes = Math.floor((time - hours) * 60.0);

        if ((hours >= 0 && hours <= 9) && (minutes >= 0 && minutes <= 9)) {
            result = "0" + hours + ":0" + Math.round(minutes);
        } else if ((hours >= 0 && hours <= 9)) {
            result = "0" + hours + ":" + Math.round(minutes);
        } else if ((minutes >= 0 && minutes <= 9)) {
            result = hours + ":0" + Math.round(minutes);
        } else {
            result = hours + ":" + Math.round(minutes);
        }
        return result;
    }

    // convert double hours to 12h format
    public String floatToTime12(double time, boolean noSuffix) {

        if (Double.isNaN(time)) {
            return "---";
        }

        time = fixhour(time + 0.5 / 60); // add 0.5 minutes to round
        int hours = (int)Math.floor(time);
        double minutes = Math.floor((time - hours) * 60);
        String suffix, result;
        if (hours >= 12) {
            suffix = "pm";
        } else {
            suffix = "am";
        }
        hours = ((((hours+ 12) -1) % (12))+ 1);
        /*hours = (hours + 12) - 1;
        int hrs = (int) hours % 12;
        hrs += 1;*/
        if (noSuffix == false) {
            if ((hours >= 0 && hours <= 9) && (minutes >= 0 && minutes <= 9)) {
                result = "0" + hours + ":0" + Math.round(minutes) + " "
                        + suffix;
            } else if ((hours >= 0 && hours <= 9)) {
                result = "0" + hours + ":" + Math.round(minutes) + " " + suffix;
            } else if ((minutes >= 0 && minutes <= 9)) {
                result = hours + ":0" + Math.round(minutes) + " " + suffix;
            } else {
                result = hours + ":" + Math.round(minutes) + " " + suffix;
            }

        } else {
            if ((hours >= 0 && hours <= 9) && (minutes >= 0 && minutes <= 9)) {
                result = "0" + hours + ":0" + Math.round(minutes);
            } else if ((hours >= 0 && hours <= 9)) {
                result = "0" + hours + ":" + Math.round(minutes);
            } else if ((minutes >= 0 && minutes <= 9)) {
                result = hours + ":0" + Math.round(minutes);
            } else {
                result = hours + ":" + Math.round(minutes);
            }
        }
        return result;

    }

    // convert double hours to 12h format with no suffix
    public String floatToTime12NS(double time) {
        return floatToTime12(time, true);
    }


    // convert times array to given time format
    private void adjustTimesFormat(double[] times) {
    	m_str_fadjr   = "";
    	m_str_shuruk  = "";
    	m_str_zuhr    = "";
    	m_str_assr    = "";
    	m_str_ghurub  = "";
    	m_str_maghrib = "";
    	m_str_ishaa   = "";

        if (timeFormat() == TimeFormats.Floating) {
      	    m_str_fadjr   = String.valueOf(times[0]);
      	    m_str_shuruk  = String.valueOf(times[1]);
      	    m_str_zuhr    = String.valueOf(times[2]);
        	m_str_assr    = String.valueOf(times[3]);
        	m_str_ghurub  = String.valueOf(times[4]);
         	m_str_maghrib = String.valueOf(times[5]);
      	    m_str_ishaa   = String.valueOf(times[6]);
        }
        else if (timeFormat() == TimeFormats.Hours12) {
        	m_str_fadjr   = floatToTime12(times[0], false);
      	    m_str_shuruk  = floatToTime12(times[1], false);
      	    m_str_zuhr    = floatToTime12(times[2], false);
        	m_str_assr    = floatToTime12(times[3], false);
        	m_str_ghurub  = floatToTime12(times[4], false);
         	m_str_maghrib = floatToTime12(times[5], false);
      	    m_str_ishaa   = floatToTime12(times[6], false);
        }
        else if (timeFormat() == TimeFormats.Hours12NoSuffix) {
        	m_str_fadjr   = floatToTime12(times[0], true);
      	    m_str_shuruk  = floatToTime12(times[1], true);
      	    m_str_zuhr    = floatToTime12(times[2], true);
        	m_str_assr    = floatToTime12(times[3], true);
        	m_str_ghurub  = floatToTime12(times[4], true);
         	m_str_maghrib = floatToTime12(times[5], true);
      	    m_str_ishaa   = floatToTime12(times[6], true);
        } else {
        	m_str_fadjr   = floatToTime24(times[0]);
      	    m_str_shuruk  = floatToTime24(times[1]);
      	    m_str_zuhr    = floatToTime24(times[2]);
        	m_str_assr    = floatToTime24(times[3]);
        	m_str_ghurub  = floatToTime24(times[4]);
         	m_str_maghrib = floatToTime24(times[5]);
      	    m_str_ishaa   = floatToTime24(times[6]);
        }
    }

    // adjust Fajr, Isha and Maghrib for locations in higher latitudes
    private double[] adjustHighLatTimes(double[] times) {
        double nightTime = timeDiff(times[4], times[1]); // sunset to sunrise
/*
        // Adjust Fajr
        double FajrDiff = nightPortion(methodParams.get(this.getCalcMethod())[0]) * nightTime;

        if (Double.isNaN(times[0]) || timeDiff(times[0], times[1]) > FajrDiff) {
            times[0] = times[1] - FajrDiff;
        }

        // Adjust Isha
        double IshaAngle = (methodParams.get(this.getCalcMethod())[3] == 0) ? methodParams.get(this.getCalcMethod())[4] : 18;
        double IshaDiff = this.nightPortion(IshaAngle) * nightTime;
        if (Double.isNaN(times[6]) || this.timeDiff(times[4], times[6]) > IshaDiff) {
            times[6] = times[4] + IshaDiff;
        }

        // Adjust Maghrib
        double MaghribAngle = (methodParams.get(this.getCalcMethod())[1] == 0) ? methodParams.get(this.getCalcMethod())[2] : 4;
        double MaghribDiff = nightPortion(MaghribAngle) * nightTime;
        if (Double.isNaN(times[5]) || this.timeDiff(times[4], times[5]) > MaghribDiff) {
            times[5] = times[4] + MaghribDiff;
        }
*/
        return times;
    }

}

