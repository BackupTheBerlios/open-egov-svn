<?xml version="1.0" encoding="iso-8859-1"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" indent="yes" encoding="iso-8859-1" omit-xml-declaration="yes" />
  <xsl:strip-space elements="*" />


  <xsl:template match="object">
    <xsl:variable name="filename"><xsl:value-of select="@name" />.php</xsl:variable>

    <xsl:document href="{$filename}" method="xml" indent="yes" encoding="iso-8859-1" omit-xml-declaration="yes">
      <xsl:text disable-output-escaping="yes">&lt;? include("../../functions.php"); printHeader(_("Objekt </xsl:text>
        <xsl:value-of select="@name" />
      <xsl:text disable-output-escaping="yes">")); ?></xsl:text>

        <xsl:if test="not(return/@type='')">
          <xsl:value-of select="return/@type" /><br />
        </xsl:if>

      <xsl:text disable-output-escaping="yes">&lt;? printFooter(); ?></xsl:text>
    </xsl:document>
  </xsl:template>


  <xsl:template match="/">
    <xsl:apply-templates select="/api/objects/object" />
  </xsl:template>

</xsl:stylesheet>

