<!-- Revision.xsl -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:param name="newValue" select="0" />

  <!-- this template copies your input XML unchanged -->
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*" />
    </xsl:copy>
  </xsl:template>

  <!-- this template changes one single value -->
  <xsl:template match="Revision/text()">
    <xsl:value-of select="$newValue" />
  </xsl:template>
</xsl:stylesheet>
