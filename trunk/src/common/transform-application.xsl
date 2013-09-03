<?xml version="1.0" encoding="UTF-8"?>

<!-- $Id$ -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <!-- <xsl:output method="xml" indent="yes" encoding="UTF-8" omit-xml-declaration="no" /> -->
  <xsl:strip-space elements="*" />

  <xsl:template match="/application">
    <html>
      <head>
        <title><xsl:value-of select="project/data[@name='application-name']/@value" /></title>
        <meta charset="utf-8" />
        <link href="../../css/standard.css" rel="stylesheet" type="text/css" />
      </head>
      <body>
        <xsl:call-template name="breadcrumbs" />
        <h1><xsl:value-of select="project/data[@name='application-name']/@value" /></h1>
        <xsl:call-template name="summary" />
        <xsl:apply-templates select="dictionary/group[@lang='en_US']/string[@number='2']" />
        <xsl:call-template name="authors" />
        <xsl:call-template name="translators" />
        <xsl:call-template name="changes" />
        <xsl:call-template name="screenshots" />
      </body>
    </html>
  </xsl:template>

  <xsl:template name="summary">
    <h2>Summary</h2>
    <p>Version: <xsl:value-of select="project/data[@name='application-version']/@value" /><br />
Maintainer: <xsl:element name="a"><xsl:attribute name="href">mailto:<xsl:value-of select="dictionary/group[@lang='en_US']/string[@number='4']" /></xsl:attribute>
      <xsl:value-of select="dictionary/group[@lang='en_US']/string[@number='3']" />
    </xsl:element><br />
Status: <xsl:if test="properties/property[@name='stable']='true'">Experimental</xsl:if><xsl:if test="not(properties/property[@name='stable']='true')">Stable</xsl:if><br />
License: <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License</a> Version 3 or later</p>
  </xsl:template>

  <xsl:template name="authors">
    <h2>Authors</h2>
    <p>
      <xsl:for-each select="/application/authors/entry">
        <xsl:sort data-type="text" order="ascending" case-order="upper-first" select="@name" />
        <xsl:apply-templates select="." />
      </xsl:for-each>
    </p>
  </xsl:template>

  <xsl:template name="translators">
    <h2>Translators</h2>
    <p>
      <xsl:for-each select="/application/translators/entry">
        <xsl:sort data-type="text" order="ascending" case-order="upper-first" select="@name" />
        <xsl:apply-templates select="." />
      </xsl:for-each>
    </p>
  </xsl:template>

  <xsl:template name="changes">
    <h2>Changes</h2>
    <p>
      <xsl:for-each select="/application/changes/change">
        <xsl:sort data-type="text" order="descending" case-order="upper-first" select="@date" />
        <xsl:apply-templates select="." />
      </xsl:for-each>
    </p>
  </xsl:template>

  <xsl:template name="screenshots">
    <h2>Screenshots</h2>
    <p></p>
  </xsl:template>

  <xsl:template name="breadcrumbs">
    <p><a href="../../">Open E-Government</a>
    <xsl:text disable-output-escaping="yes"> </xsl:text>
      <strong>/</strong>
    <xsl:text disable-output-escaping="yes"> </xsl:text>
    <xsl:element name="a">
      <xsl:attribute name="href">../../categories/<xsl:value-of select="/application/@category" />.html</xsl:attribute><xsl:value-of select="/application/@category" /></xsl:element>
    <xsl:text disable-output-escaping="yes"> </xsl:text>
      <strong>/</strong>
    <xsl:text disable-output-escaping="yes"> </xsl:text>
    <xsl:value-of select="project/data[@name='application-name']/@value" /></p>
  </xsl:template>

  <xsl:template match="string">
    <h2>Description</h2>
    <p><xsl:value-of select="." /></p>
  </xsl:template>

  <xsl:template match="authors/entry | translators/entry">
    <xsl:element name="a">
      <xsl:attribute name="href">mailto:<xsl:value-of select="@email" /></xsl:attribute><xsl:value-of select="@name" /></xsl:element>
    <xsl:text disable-output-escaping="yes"> </xsl:text>
    <xsl:if test="not(@comment='')"><xsl:value-of select="@comment" /></xsl:if>
    <br />
  </xsl:template>

  <xsl:template match="changes/change">
    <strong><xsl:value-of select="@date" /></strong>
    <xsl:text disable-output-escaping="yes"> </xsl:text>
    <xsl:element name="a">
      <xsl:attribute name="href">mailto:<xsl:value-of select="@email" /></xsl:attribute><xsl:value-of select="@name" /></xsl:element>
    <xsl:text disable-output-escaping="yes"> </xsl:text>
    <xsl:value-of select="." />
    <br />
  </xsl:template>
</xsl:stylesheet>

