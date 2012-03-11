//$Id:$
//
//Project:  Open E-Government :: Quran
//Author:   Gerrit M. Albrecht

package de.gasi.oeg.quran;

import java.io.InputStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import android.app.Activity;
import android.content.res.Resources;
import android.graphics.Typeface;
import android.os.Bundle;
import android.widget.TextView;

import com.kerul.arabicfont.ArabicUtilities;

public class MainActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main);

        TextView view;
        view = (TextView)this.findViewById(R.id.TextView);

		try {
		  String s = "";

		  // in raw and not in xml because it will get compiled as binary into the resources.
          // http://www.google.com/url?sa=D&q=http://developer.android.com/intl/de/guide/topics/resources/providing-resources.html&usg=AFQjCNEYXfTFRLRk4_u5DdQqnq2hDDsoBw
          // http://www.google.com/url?sa=D&q=http://developer.android.com/intl/de/reference/android/content/res/Resources.html%23getXml(int&usg=AFQjCNFipcxrLL6pAud4n6P7Bxb2aCfwMQ

          Resources res = getResources();
		  InputStream is = res.openRawResource(R.raw.quran);
		  DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		  try {
  		    DocumentBuilder builder = factory.newDocumentBuilder();
 		    Document dom = builder.parse(is);
 		    Element root = dom.getDocumentElement();
 		    NodeList citems = root.getElementsByTagName("chapters");

            s = root.getAttribute("title") + "\n\n";

		    for (int ci=0; ci<citems.getLength(); ci++) {
 			  Node citem = citems.item(ci);             // chapter-Tag

  	    	  if ((citem.getNodeType() == Node.ELEMENT_NODE) &&
     		      (citem.getNodeName() == "chapters")) {
  	    		s=s+"f";
  	    	  }

 			  if (citem.hasChildNodes()) {              // sura-Tags
	   			    NodeList sitems = citem.getChildNodes();
	   			 s=s+"3";

 	    			for (int si=0; si<sitems.getLength(); si++) {
 	 	    	 		  Node sitem = sitems.item(si);  // sura-Tag
 	 	    	 		s=s+"4";
   	 	 	   			  if (sitem.hasAttributes()) {
   	 	 	   			s=s+"5\n";
 	 	    	 		    NamedNodeMap a = sitem.getAttributes();
 	 	    	 		    int v = Integer.valueOf(a.getNamedItem("number").getNodeValue());
 	 	    	 		 s = s + "Sura: " + v + "\n";
 	 	    	 		 if (v != 1)
 	 	    	 			 continue;

 	 	    	 		 // Show sura.
 	 	    	 		 NodeList titems = sitem.getChildNodes();
 	 	    			 for (int ti=0; ti<titems.getLength(); ti++) {
 	 	    				Node titem = titems.item(ti);
 	 	    				if (titem == null)
 	 	    					continue;

//	 	 	    			s += "Latin: " + titem.getAttributes().getNamedItem("latin").getNodeValue() + "\n";
// 	 	 	    			s += "Title: " + titem.getAttributes().getNamedItem("title").getNodeValue() + "\n";
 	 	 	    			s += "Language: " + titem.getAttributes().getNamedItem("lang").getNodeValue() + "\n";
// 	 	 	    			s += "Transliteration: " + titem.getAttributes().getNamedItem("transliteration").getNodeValue() + "\n";
 	 	    			}
 	 	    			    	
   	   			  }
 	    		}
 			  }
 		    }
    	   }
 		   catch (Exception e) {
 			 s = s + e.getLocalizedMessage() + " " + e.getStackTrace().toString();  
 		   }

//		  doc.getDocumentElement().normalize();
			  //node.getNodeName();  node.getNodeValue(); node.getTextContent();

          view.setTypeface(Typeface.createFromAsset(getAssets(), "dejavusans.ttf"));
          view.setText(ArabicUtilities.reshape("\u0641\u0631\u0633"));
		  view.setText(s);
		}

		catch(Exception ex){
			view.setText("font cannot load: "+ ex.toString() );
		}
    }
}

