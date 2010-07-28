// $Id$

// Einfache Nachprogrammierung der QWinWidget-Klasse:
// http://doc.trolltech.com/solutions/qtwinmigrate/qwinwidget.html

#include <QtGui>

#include "WinWidget.h"

WinWidget::WinWidget(const WId parent)
 : QWidget(0, Qt::FramelessWindowHint | Qt::Window)
{
  setParentWindow(parent);

  resize(200, 150);
  move(10, 10);
  setWindowTitle("Test");
}

WinWidget::WinWidget(const WCHAR *classname, const WCHAR *title)
 : QWidget(0, Qt::FramelessWindowHint | Qt::Window)
{

  //setAttribute(Qt::WA_TranslucentBackground);
  //setAttribute(Qt::WA_NoSystemBackground);
  setAttribute(Qt::WA_TransparentForMouseEvents);
  //setAttribute(Qt::WA_DeleteOnClose);
  //setAttribute(Qt::WA_QuitOnClose);

  //setWindowState(windowState() | Qt::WindowMaximized);

  const HWND win = ::FindWindow(classname, title);
  if (win != NULL && ::IsWindow(win) == TRUE) {
    qWarning() << "Window found.";

    setParentWindow(win);
  }

  resize(200, 150);
  move(10, 10);
  setWindowTitle("Test");
}

void WinWidget::setParentWindow(const WId parent)
{
  DWORD style = ::GetWindowLong(winId(), GWL_STYLE);
  style = (style | WS_CHILD | WS_VISIBLE);
  if (style & WS_POPUP)
    style = style & ~WS_POPUP;
  ::SetWindowLong(winId(), GWL_STYLE, style);

  // http://msdn.microsoft.com/en-us/library/ms633541(VS.85).aspx
  ::SetParent(winId(), parent);

  m_parent_window = parent;
}

WId WinWidget::parentWindow () const
{
  return m_parent_window;
}

void WinWidget::closeEvent(QCloseEvent *event)
{
  qWarning() << "close event";

  event->accept();
  //event->ignore();
}

void WinWidget::changeEvent(QEvent *event)
{
  QString t;

  switch (event->type()) {
    case QEvent::ToolBarChange:       t = "ToolBarChange"; break;
    case QEvent::ActivationChange:    t = "ActivationChange"; break;
    case QEvent::EnabledChange:       t = "EnabledChange"; break;
    case QEvent::FontChange:          t = "FontChange"; break;
    case QEvent::StyleChange:         t = "StyleChange"; break;
    case QEvent::PaletteChange:       t = "PaletteChange"; break;
    case QEvent::WindowTitleChange:   t = "WindowTitleChange"; break;
    case QEvent::IconTextChange:      t = "IconTextChange"; break;
    case QEvent::ModifiedChange:      t = "ModifiedChange"; break;
    case QEvent::MouseTrackingChange: t = "MouseTrackingChange"; break;
    case QEvent::ParentChange:        t = "ParentChange"; break;
    case QEvent::WindowStateChange:   t = "WindowStateChange"; break;
    case QEvent::LanguageChange:      t = "LanguageChange"; break;
    case QEvent::LocaleChange:        t = "LocaleChange"; break;
    case QEvent::LayoutDirectionChange: t = "LayoutDirectionChange"; break;
    default: t = "unknown: " + QString::number(event->type());
  }
  
  qWarning() << "WinWidget: change event: " << t;

  QWidget::changeEvent(event);
}

void WinWidget::hideEvent(QHideEvent *event)
{
  qWarning() << "WinWidget: hide event";

  QWidget::hideEvent(event);
}

void WinWidget::showEvent(QShowEvent *event)
{
  qWarning() << "WinWidget: show event";

  QWidget::showEvent(event);
}

void WinWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
  qWarning() << "WinWidget: mouse double click event";

  QWidget::mouseDoubleClickEvent(event);
}

void WinWidget::mouseMoveEvent(QMouseEvent *event)
{
  qWarning() << "WinWidget: mouse move event";

  QWidget::mouseMoveEvent(event);
}

void WinWidget::mousePressEvent(QMouseEvent *event)
{
  qWarning() << "WinWidget: mouse press event";

  QWidget::mousePressEvent(event);
}

void WinWidget::mouseReleaseEvent(QMouseEvent *event)
{
  qWarning() << "WinWidget: mouse release event";

  QWidget::mouseReleaseEvent(event);
}

void WinWidget::destroy(bool destroyWindow /*=true*/, bool destroySubWindows /*=true*/)
{
  qWarning() << "WinWidget: destroy event";

  QWidget::destroy(destroyWindow, destroySubWindows);
}

#ifdef Q_WS_WIN

// Unknown constants for the MinGW gcc compiler.

#define WM_CHANGEUISTATE 0x127 /* 295 */
#define WM_UPDATEUISTATE 0x128 /* 296 */
#define WM_QUERYUISTATE  0x129 /* 297 */

bool WinWidget::winEvent(MSG *message, long *result)
{
  QString t;

  switch (message->message) {
    case WM_ACTIVATE:              t = "WM_ACTIVATE"; break;
    case WM_ACTIVATEAPP:           t = "WM_ACTIVATEAPP"; break;
    case WM_ASKCBFORMATNAME:       t = "WM_ASKCBFORMATNAME"; break;
    case WM_CANCELJOURNAL:         t = "WM_CANCELJOURNAL"; break;
    case WM_CANCELMODE:            t = "WM_CANCELMODE"; break;
    case WM_CHANGECBCHAIN:         t = "WM_CHANGECBCHAIN"; break;
    case WM_CHAR:                  t = "WM_CHAR"; break;
    case WM_CHARTOITEM:            t = "WM_CHARTOITEM"; break;
    case WM_CHILDACTIVATE:         t = "WM_CHILDACTIVATE"; break;
    case WM_CHOOSEFONT_GETLOGFONT: t = "WM_CHOOSEFONT_GETLOGFONT, WM_PSD_FULLPAGERECT"; break;
    case WM_CHOOSEFONT_SETFLAGS:   t = "WM_CHOOSEFONT_SETFLAGS"; break;
    case WM_CHOOSEFONT_SETLOGFONT: t = "WM_CHOOSEFONT_SETLOGFONT"; break;
    case WM_CLEAR:                 t = "WM_CLEAR"; break;
    case WM_CLOSE:                 t = "WM_CLOSE"; break;
    case WM_COMMAND:               t = "WM_COMMAND"; break;
    case WM_COMMNOTIFY:            t = "WM_COMMNOTIFY"; break;
    case WM_COMPACTING:            t = "WM_COMPACTING"; break;
    case WM_COMPAREITEM:           t = "WM_COMPAREITEM"; break;
    case WM_CONVERTREQUESTEX:      t = "WM_CONVERTREQUESTEX, WM_KEYLAST"; break;
    case WM_COPY:                  t = "WM_COPY"; break;
    case WM_COPYDATA:              t = "WM_COPYDATA"; break;
    case WM_CREATE:                t = "WM_CREATE"; break;
    case WM_CTLCOLORBTN:           t = "WM_CTLCOLORBTN"; break;
    case WM_CTLCOLORDLG:           t = "WM_CTLCOLORDLG"; break;
    case WM_CTLCOLOREDIT:          t = "WM_CTLCOLOREDIT"; break;
    case WM_CTLCOLORLISTBOX:       t = "WM_CTLCOLORLISTBOX"; break;
    case WM_CTLCOLORMSGBOX:        t = "WM_CTLCOLORMSGBOX"; break;
    case WM_CTLCOLORSCROLLBAR:     t = "WM_CTLCOLORSCROLLBAR"; break;
    case WM_CTLCOLORSTATIC:        t = "WM_CTLCOLORSTATIC"; break;
    case WM_CUT:                   t = "WM_CUT"; break;
    case WM_DDE_FIRST:             t = "WM_DDE_FIRST"; break;
    case WM_DDE_ACK:               t = "WM_DDE_ACK"; break;
    case WM_DDE_ADVISE:            t = "WM_DDE_ADVISE"; break;
    case WM_DDE_DATA:              t = "WM_DDE_DATA"; break;
    case WM_DDE_EXECUTE:           t = "WM_DDE_EXECUTE"; break;
    //case WM_DDE_INITIATE:          t = "WM_DDE_INITIATE"; break;
    //case WM_DDE_LAST:              t = "WM_DDE_LAST"; break;
    case WM_DDE_POKE:              t = "WM_DDE_POKE"; break;
    case WM_DDE_REQUEST:           t = "WM_DDE_REQUEST"; break;
    case WM_DDE_TERMINATE:         t = "WM_DDE_TERMINATE"; break;
    case WM_DDE_UNADVISE:          t = "WM_DDE_UNADVISE"; break;
    case WM_DEADCHAR:              t = "WM_DEADCHAR"; break;
    case WM_DELETEITEM:            t = "WM_DELETEITEM"; break;
    case WM_DESTROY:               t = "WM_DESTROY"; close(); break;
    case WM_DESTROYCLIPBOARD:      t = "WM_DESTROYCLIPBOARD"; break;
    case WM_DEVMODECHANGE:         t = "WM_DEVMODECHANGE"; break;
    case WM_DRAWCLIPBOARD:         t = "WM_DRAWCLIPBOARD"; break;
    case WM_DRAWITEM:              t = "WM_DRAWITEM"; break;
    case WM_DROPFILES:             t = "WM_DROPFILES"; break;
    case WM_ENABLE:                t = "WM_ENABLE"; break;
    case WM_ENDSESSION:            t = "WM_ENDSESSION"; break;
    case WM_ENTERIDLE:             t = "WM_ENTERIDLE"; break;
    case WM_ENTERMENULOOP:         t = "WM_ENTERMENULOOP"; break;
    case WM_ERASEBKGND:            t = "WM_ERASEBKGND"; break;
    case WM_EXITMENULOOP:          t = "WM_EXITMENULOOP"; break;
    case WM_FONTCHANGE:            t = "WM_FONTCHANGE"; break;
    case WM_GETFONT:               t = "WM_GETFONT"; break;
    case WM_GETDLGCODE:            t = "WM_GETDLGCODE"; break;
    case WM_GETHOTKEY:             t = "WM_GETHOTKEY"; break;
    case WM_GETMINMAXINFO:         t = "WM_GETMINMAXINFO"; break;
    case WM_GETTEXT:               t = "WM_GETTEXT"; break;
    case WM_GETTEXTLENGTH:         t = "WM_GETTEXTLENGTH"; break;
    case WM_HOTKEY:                t = "WM_HOTKEY"; break;
    case WM_HSCROLL:               t = "WM_HSCROLL"; break;
    case WM_HSCROLLCLIPBOARD:      t = "WM_HSCROLLCLIPBOARD"; break;
    case WM_ICONERASEBKGND:        t = "WM_ICONERASEBKGND"; break;
    case WM_IME_CHAR:              t = "WM_IME_CHAR"; break;
    case WM_IME_COMPOSITION:       t = "WM_IME_COMPOSITION"; break;
    case WM_IME_COMPOSITIONFULL:   t = "WM_IME_COMPOSITIONFULL"; break;
    case WM_IME_CONTROL:           t = "WM_IME_CONTROL"; break;
    case WM_IME_ENDCOMPOSITION:    t = "WM_IME_ENDCOMPOSITION"; break;
    case WM_IME_KEYDOWN:           t = "WM_IME_KEYDOWN"; break;
    //case WM_IME_KEYLAST:           t = "WM_IME_KEYLAST"; break;
    case WM_IME_KEYUP:             t = "WM_IME_KEYUP"; break;
    case WM_IME_NOTIFY:            t = "WM_IME_NOTIFY"; break;
    case WM_IME_SELECT:            t = "WM_IME_SELECT"; break;
    case WM_IME_SETCONTEXT:        t = "WM_IME_SETCONTEXT"; break;
    case WM_IME_STARTCOMPOSITION:  t = "WM_IME_STARTCOMPOSITION"; break;
    case WM_INITDIALOG:            t = "WM_INITDIALOG"; break;
    case WM_INITMENU:              t = "WM_INITMENU"; break;
    case WM_INITMENUPOPUP:         t = "WM_INITMENUPOPUP"; break;
    case WM_KEYDOWN:               t = "WM_KEYDOWN, WM_KEYFIRST"; break;
    case WM_KEYUP:                 t = "WM_KEYUP"; break;
    case WM_KILLFOCUS:             t = "WM_KILLFOCUS"; break;
    case WM_LBUTTONDBLCLK:         t = "WM_LBUTTONDBLCLK"; break;
    case WM_LBUTTONDOWN:           t = "WM_LBUTTONDOWN"; break;
    case WM_LBUTTONUP:             t = "WM_LBUTTONUP"; break;
    case WM_MBUTTONDBLCLK:         t = "WM_MBUTTONDBLCLK"; break;
    case WM_MBUTTONDOWN:           t = "WM_MBUTTONDOWN"; break;
    case WM_MBUTTONUP:             t = "WM_MBUTTONUP"; break;
    case WM_MDIACTIVATE:           t = "WM_MDIACTIVATE"; break;
    case WM_MDICASCADE:            t = "WM_MDICASCADE"; break;
    case WM_MDICREATE:             t = "WM_MDICREATE"; break;
    case WM_MDIDESTROY:            t = "WM_MDIDESTROY"; break;
    case WM_MDIGETACTIVE:          t = "WM_MDIGETACTIVE"; break;
    case WM_MDIICONARRANGE:        t = "WM_MDIICONARRANGE"; break;
    case WM_MDIMAXIMIZE:           t = "WM_MDIMAXIMIZE"; break;
    case WM_MDINEXT:               t = "WM_MDINEXT"; break;
    case WM_MDIREFRESHMENU:        t = "WM_MDIREFRESHMENU"; break;
    case WM_MDIRESTORE:            t = "WM_MDIRESTORE"; break;
    case WM_MDISETMENU:            t = "WM_MDISETMENU"; break;
    case WM_MDITILE:               t = "WM_MDITILE"; break;
    case WM_MEASUREITEM:           t = "WM_MEASUREITEM"; break;
    case WM_MENUCHAR:              t = "WM_MENUCHAR"; break;
    case WM_MENUSELECT:            t = "WM_MENUSELECT"; break;
    case WM_MOUSEACTIVATE:         t = "WM_MOUSEACTIVATE"; break;
    case WM_MOUSELAST:             t = "WM_MOUSELAST"; break;
    case WM_MOUSEMOVE:             t = "WM_MOUSEMOVE, WM_MOUSEFIRST"; break;
    case WM_MOVE:                  t = "WM_MOVE"; break;
    case WM_NCACTIVATE:            t = "WM_NCACTIVATE"; break;
    case WM_NCCALCSIZE:            t = "WM_NCCALCSIZE"; break;
    case WM_NCCREATE:              t = "WM_NCCREATE"; break;
    case WM_NCDESTROY:             t = "WM_NCDESTROY"; break;
    case WM_NCHITTEST:             t = "WM_NCHITTEST"; break;
    case WM_NCLBUTTONDBLCLK:       t = "WM_NCLBUTTONDBLCLK"; break;
    case WM_NCLBUTTONDOWN:         t = "WM_NCLBUTTONDOWN"; break;
    case WM_NCLBUTTONUP:           t = "WM_NCLBUTTONUP"; break;
    case WM_NCMBUTTONDBLCLK:       t = "WM_NCMBUTTONDBLCLK"; break;
    case WM_NCMBUTTONDOWN:         t = "WM_NCMBUTTONDOWN"; break;
    case WM_NCMBUTTONUP:           t = "WM_NCMBUTTONUP"; break;
    case WM_NCMOUSEMOVE:           t = "WM_NCMOUSEMOVE"; break;
    case WM_NCPAINT:               t = "WM_NCPAINT"; break;
    case WM_NCRBUTTONDBLCLK:       t = "WM_NCRBUTTONDBLCLK"; break;
    case WM_NCRBUTTONDOWN:         t = "WM_NCRBUTTONDOWN"; break;
    case WM_NCRBUTTONUP:           t = "WM_NCRBUTTONUP"; break;
    case WM_NEXTDLGCTL:            t = "WM_NEXTDLGCTL"; break;
    case WM_NULL:                  t = "WM_NULL"; break;
    //case WM_OTHERWINDOWCREATED:    t = "WM_OTHERWINDOWCREATED"; break;
    //case WM_OTHERWINDOWDESTROYED:  t = "WM_OTHERWINDOWDESTROYED"; break;
    case WM_PAINT:                 t = "WM_PAINT"; break;
    case WM_PAINTCLIPBOARD:        t = "WM_PAINTCLIPBOARD"; break;
    case WM_PAINTICON:             t = "WM_PAINTICON"; break;
    case WM_PALETTECHANGED:        t = "WM_PALETTECHANGED"; break;
    case WM_PALETTEISCHANGING:     t = "WM_PALETTEISCHANGING"; break;
    case WM_PASTE:                 t = "WM_PASTE"; break;
    case WM_PARENTNOTIFY:          t = "WM_PARENTNOTIFY"; break;
    case WM_PENWINFIRST:           t = "WM_PENWINFIRST"; break;
    case WM_PENWINLAST:            t = "WM_PENWINLAST"; break;
    case WM_POWER:                 t = "WM_POWER"; break;
    case WM_PSD_ENVSTAMPRECT:      t = "WM_PSD_ENVSTAMPRECT"; break;
    case WM_PSD_GREEKTEXTRECT:     t = "WM_PSD_GREEKTEXTRECT"; break;
    case WM_PSD_MARGINRECT:        t = "WM_PSD_MARGINRECT"; break;
    case WM_PSD_MINMARGINRECT:     t = "WM_PSD_MINMARGINRECT"; break;
    case WM_PSD_PAGESETUPDLG:      t = "WM_USER, WM_PSD_PAGESETUPDLG"; break;
    case WM_PSD_YAFULLPAGERECT:    t = "WM_PSD_YAFULLPAGERECT"; break;
    case WM_QUERYDRAGICON:         t = "WM_QUERYDRAGICON"; break;
    case WM_QUERYENDSESSION:       t = "WM_QUERYENDSESSION"; break;
    case WM_QUERYNEWPALETTE:       t = "WM_QUERYNEWPALETTE"; break;
    case WM_QUERYOPEN:             t = "WM_QUERYOPEN"; break;
    case WM_QUEUESYNC:             t = "WM_QUEUESYNC"; break;
    case WM_QUIT:                  t = "WM_QUIT"; break;
    case WM_RBUTTONDBLCLK:         t = "WM_RBUTTONDBLCLK"; break;
    case WM_RBUTTONDOWN:           t = "WM_RBUTTONDOWN"; break;
    case WM_RBUTTONUP:             t = "WM_RBUTTONUP"; break;
    case WM_RENDERALLFORMATS:      t = "WM_RENDERALLFORMATS"; break;
    case WM_RENDERFORMAT:          t = "WM_RENDERFORMAT"; break;
    case WM_SETCURSOR:             t = "WM_SETCURSOR"; break;
    case WM_SETFOCUS:              t = "WM_SETFOCUS"; break;
    case WM_SETFONT:               t = "WM_SETFONT"; break;
    case WM_SETHOTKEY:             t = "WM_SETHOTKEY"; break;
    case WM_SETREDRAW:             t = "WM_SETREDRAW"; break;
    case WM_SETTEXT:               t = "WM_SETTEXT"; break;
    case WM_SHOWWINDOW:            t = "WM_SHOWWINDOW"; break;
    case WM_SIZE:                  t = "WM_SIZE"; break;
    case WM_SIZECLIPBOARD:         t = "WM_SIZECLIPBOARD"; break;
    case WM_SPOOLERSTATUS:         t = "WM_SPOOLERSTATUS"; break;
    case WM_STYLECHANGING:         t = "WM_STYLECHANGING"; break;
    case WM_STYLECHANGED:          t = "WM_STYLECHANGED"; break;
    case WM_SYSCHAR:               t = "WM_SYSCHAR"; break;
    case WM_SYSCOLORCHANGE:        t = "WM_SYSCOLORCHANGE"; break;
    case WM_SYSCOMMAND:            t = "WM_SYSCOMMAND"; break;
    case WM_SYSDEADCHAR:           t = "WM_SYSDEADCHAR"; break;
    case WM_SYSKEYDOWN:            t = "WM_SYSKEYDOWN"; break;
    case WM_SYSKEYUP:              t = "WM_SYSKEYUP"; break;
    case WM_TIMECHANGE:            t = "WM_TIMECHANGE"; break;
    case WM_TIMER:                 t = "WM_TIMER"; break;
    case WM_UNDO:                  t = "WM_UNDO"; break;
    case WM_VKEYTOITEM:            t = "WM_VKEYTOITEM"; break;
    case WM_VSCROLL:               t = "WM_VSCROLL"; break;
    case WM_VSCROLLCLIPBOARD:      t = "WM_VSCROLLCLIPBOARD"; break;
    case WM_WINDOWPOSCHANGED:      t = "WM_WINDOWPOSCHANGED"; break;
    case WM_WINDOWPOSCHANGING:     t = "WM_WINDOWPOSCHANGING"; break;
    case WM_WININICHANGE:          t = "WM_WININICHANGE"; break;
    case WM_CAPTURECHANGED:        t = "WM_CAPTURECHANGED"; break;
    case WM_MOUSELEAVE:            t = "WM_MOUSELEAVE"; break;
    case WM_SETICON:               t = "WM_SETICON"; break;
    case WM_SYNCPAINT:             t = "WM_SYNCPAINT"; break;
    case WM_SIZING:                t = "WM_SIZING"; break;
    case WM_CONTEXTMENU:           t = "WM_CONTEXTMENU"; break;
    case WM_UPDATEUISTATE:         t = "WM_UPDATEUISTATE"; break;
    case WM_CHANGEUISTATE:         t = "WM_CHANGEUISTATE"; break;
    case WM_QUERYUISTATE:          t = "WM_QUERYUISTATE"; break;
    default:                       t = "unknown: " + QString::number(message->message);
  }

  //char* param1 = (char*)(msg->wParam);
  //char* param2 = (char*)(msg->lParam);

  qWarning() << "WinWidget: winEvent event" << &message << ": " << t;

  return QWidget::winEvent(message, result);
}

#endif

