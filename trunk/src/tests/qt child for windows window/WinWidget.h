// $Id$

#pragma once

#include <QWidget>

#include <windows.h>

class QMouseEvent;
class QHideEvent;
class QCloseEvent;
class QEvent;

class WinWidget : public QWidget
{
    Q_OBJECT

  public:
    WinWidget(const WId parent);
    WinWidget(const WCHAR *classname, const WCHAR *title);

  protected:
    WinWidget() {};

    void setParentWindow(const WId parent);
    WId parentWindow() const;

    virtual void closeEvent(QCloseEvent *event);
    virtual void changeEvent(QEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    void destroy(bool destroyWindow = true, bool destroySubWindows = true);

#ifdef Q_WS_WIN
    virtual bool winEvent(MSG *message, long *result);
#endif

  private:
    WId m_parent_window;
};

