<?xml version="1.0" encoding="iso-8859-1"?>

<!-- Id: -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" indent="yes" encoding="iso-8859-1" omit-xml-declaration="yes" />
  <xsl:strip-space elements="*" />


  <xsl:template match="function">
    <xsl:variable name="filename"><xsl:value-of select="@name" />.php</xsl:variable>

    <xsl:document href="{$filename}" method="xml" indent="yes" encoding="iso-8859-1" omit-xml-declaration="yes">
      <xsl:text disable-output-escaping="yes">&lt;? include("../../functions.php"); printHeader(_("Funktion </xsl:text>
        <xsl:value-of select="@name" />
      <xsl:text disable-output-escaping="yes">")); ?></xsl:text>

        <h2>Deklaration</h2>

        <p class="justify">
          <xsl:if test="not(declaration/return/@type='')">
            <xsl:value-of select="declaration/return/@type" />
          </xsl:if>

          <xsl:text disable-output-escaping="yes"> </xsl:text>

          <strong><xsl:value-of select="@name" /></strong>

          <xsl:text disable-output-escaping="yes"> </xsl:text>

          <xsl:if test="count(declaration/parameters/parameter)=0">
            ()
          </xsl:if>
          <xsl:if test="not(count(declaration/parameters/parameter)=0)">
            (
            <xsl:for-each select="declaration/parameters/parameter">
              <xsl:if test="not(position()=1)">, </xsl:if>
              <xsl:value-of select="@type" />
              <xsl:text disable-output-escaping="yes"> </xsl:text>
              <xsl:value-of select="@name" />
            </xsl:for-each>
            )
          </xsl:if>
        </p>

        <h2>Beschreibung</h2>

        <p class="justify">
          <xsl:if test="description=''">
            Keine Beschreibung vorhanden.
          </xsl:if>
          <xsl:if test="not(description='')">
            <xsl:value-of select="description" />
          </xsl:if>
        </p>

        <h2>Beispiele</h2>

        <p class="justify">
          <xsl:if test="count(examples)=0">
            Keine Beispiele vorhanden.
          </xsl:if>
          <xsl:if test="not(count(examples)=0)">
            xxx
          </xsl:if>
        </p>

        <h2>Gehört zu</h2>

        <p class="justify">
          <xsl:if test="count(related)=0">
            Keine Verknüpfungen vorhanden.
          </xsl:if>
          <xsl:if test="not(count(related)=0)">
            xxx
          </xsl:if>
        </p>

      <xsl:text disable-output-escaping="yes">&lt;? printFooter(); ?></xsl:text>
    </xsl:document>
  </xsl:template>


  <xsl:template match="/">
    <xsl:apply-templates select="/api/functions/function" />
  </xsl:template>

</xsl:stylesheet>

