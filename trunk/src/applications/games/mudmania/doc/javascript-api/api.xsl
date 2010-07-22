<?xml version="1.0" encoding="iso-8859-1"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" indent="yes" encoding="iso-8859-1" omit-xml-declaration="yes" />
  <xsl:strip-space elements="*" />


  <xsl:template match="object">
    <xsl:element name="a">
      <xsl:attribute name="href">objects/<xsl:value-of select="./@name" />.php</xsl:attribute>
      <xsl:value-of select="@name" /><br />
    </xsl:element>
  </xsl:template>


  <xsl:template match="function">
    <xsl:element name="a">
      <xsl:attribute name="href">functions/<xsl:value-of select="./@name" />.php</xsl:attribute>
      <xsl:value-of select="@name" /><br />
    </xsl:element>
  </xsl:template>


  <xsl:template match="/">
    <xsl:text disable-output-escaping="yes">&lt;? include("../functions.php"); printHeader(_("JavaScript-API")); ?></xsl:text>

    <h1>Objekte</h1>

    <p class="justify">
      <xsl:for-each select="/api/objects/object">
        <xsl:sort data-type="text" order="ascending" case-order="upper-first" select="@name" />
        <xsl:apply-templates select="." />
      </xsl:for-each>
    </p>

    <h1>Funktionen</h1>

    <p class="justify">
      <xsl:for-each select="/api/functions/function">
        <xsl:sort data-type="text" order="ascending" case-order="upper-first" select="@name" />
        <xsl:apply-templates select="." />
      </xsl:for-each>
    </p>

    <xsl:text disable-output-escaping="yes">&lt;? printFooter(); ?></xsl:text>
  </xsl:template>

</xsl:stylesheet>

