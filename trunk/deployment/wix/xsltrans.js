// $Id$

var oArgs = WScript.Arguments;

if (oArgs.length == 0) {
  WScript.Echo ("Usage: cscript xsltrans.js xml xsl");
  WScript.Quit();
}
xmlFile = oArgs(0) + ".xml";
xslFile = oArgs(1) + ".xsl";

var xsl = new ActiveXObject("MSXML2.DOMDOCUMENT.6.0");
var xml = new ActiveXObject("MSXML2.DOMDocument.6.0");
xml.validateOnParse = false;
xml.async = false;
xml.load(xmlFile);

if (xml.parseError.errorCode != 0)
  WScript.Echo ("XML Parse Error : " + xml.parseError.reason);

xsl.async = false;
xsl.load(xslFile);

if (xsl.parseError.errorCode != 0)
  WScript.Echo("XSL Parse Error : " + xsl.parseError.reason);

try {
  WScript.Echo(xml.transformNode(xsl.documentElement));
}
catch(error) {
  WScript.Echo("Transformation Error : " + error.number + "*" + error.description);
}

