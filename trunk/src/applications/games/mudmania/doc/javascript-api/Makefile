# $Id$

# Erstellt die automatisch generierten Webseiten.

all:
	@echo "Los geht's ..."
	xsltproc -o ../htdocs/javascript/index.php api.xsl mudmania-js-api.xml
	xsltproc -o ../htdocs/javascript/functions/ --stringparam base.dir ../htdocs/javascript/functions/ functions.xsl mudmania-js-api.xml
	xsltproc -o ../htdocs/javascript/objects/ --stringparam base.dir ../htdocs/javascript/objects/ objects.xsl mudmania-js-api.xml
	@sync

