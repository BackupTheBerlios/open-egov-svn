
#include <OEG/Common.h>
#include <OEG/Qt/Application.h>
#include <OEG/Crypt/AES.h>

#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <QString>
#include <QStringList>

//#include "MainWindow.h"
#include <windows.h>
int main(int argc, char *argv[])
{
  QCoreApplication app_core(argc, argv);
  QStringList arguments = QCoreApplication::arguments();
  QString programName = arguments.at(0);

#ifdef Q_WS_X11
  bool useGUI = getenv("DISPLAY") != 0;
#else
  bool useGUI = TRUE;
#endif

  if ((arguments.count() == 1) && useGUI) {
    OEG::Qt::Application app(argc, argv);

    app.setApplicationName(_("AEScrypt"));
    app.setOrganizationName(_("G.A.S.I."));
    app.setOrganizationDomain(_("open-egov.de"));

    //QSettings settings(app.organizationName(), app.applicationName());
    //if (settings.status() != QSettings::NoError) {
    //  qDebug() << __FILE__ ": settings error: " << settings.status();
    //}

    //MainWindow *mw = new MainWindow();
    //mw->show();

    return app.exec();
  }
  else {
    QString inputFileName, outputFileName, password;
    QString argument;
    bool encrypt = true;

    if ((arguments.contains("-d")) || (arguments.contains("--decrypt")))
      encrypt = false;

    qDebug() << "count: " << arguments.count();
    qDebug() << "encrypt: " << encrypt;

    for (int i=0; i<arguments.count(); i++) {
      argument = arguments[i];
      qDebug() << "arg " << i << " " << arguments[i];

      if (argument.startsWith('-')) {
        argument = argument.toLower();
        if (((argument == "--inputfile") || (argument == "-i")) && (i+1 < arguments.count()))
          inputFileName = arguments[i+1];
        if (((argument == "--outputfile") || (argument == "-o")) && (i+1 < arguments.count()))
          outputFileName = arguments[i+1];
        if (((argument == "--password") || (argument == "-p")) && (i+1 < arguments.count()))
          password = arguments[i+1];
      }
    }

    qDebug() << "i: " << inputFileName;
    qDebug() << "o: " << outputFileName;
    qDebug() << "p: " << password;

    if (inputFileName.length() <= 0) {
      qDebug() << "No input file name given.";
      return -1;
    }

    if (outputFileName.length() <= 0) {
      outputFileName = inputFileName + ".out";
    }

    inputFileName  = QFileInfo(inputFileName).absoluteFilePath();
    outputFileName = QFileInfo(outputFileName).absoluteFilePath();

    qDebug() << "i: " << inputFileName;
    qDebug() << "o: " << outputFileName;

    Sleep(1000);

    return 0;
  }
}

