#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "scrolledwindow.h"
#include <wx/wx.h>

class MainFrame : public wxFrame
{
  public:
    /**
     * Class constructor of the main application window
     * @param title of the application window
     */
    MainFrame(const wxString &title);

  private:
    // main application window that scrolls if the window is too small for content
    ScrolledWindow *m_mainWindow;

    /**
     * Handles open file menu click, that loads the image in the scrolling image placeholder
     * @param event
     */
    void fileOpen(wxCommandEvent &event);

    /**
     * Quits the applicaiton
     * @param event
     */
    void quit(wxCommandEvent &event);
};

#endif // MAINFRAME_H
