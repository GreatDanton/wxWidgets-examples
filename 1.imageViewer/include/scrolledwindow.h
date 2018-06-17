#ifndef SCROLLEDWINDOW_H
#define SCROLLEDWINDOW_H

#include "scrolledimage.h"
#include <memory>
#include <wx/wx.h>

/**
 * Sets up the layout for the left and right panel in the main application window and makes the
 * main frame scrollable.
 */
class ScrolledWindow : public wxScrolledWindow
{
  public:
    /**
     * Class constructor that sets up the layout of the application main frame
     * @param parent window
     */
    ScrolledWindow(wxFrame *parent);

    /**
     * Set image of the image placeholder in the main application window
     * @param image - pointer to wxImage instance
     */
    void setImage(std::shared_ptr<wxImage> image);

  private:
    // placeholder for the image
    ScrolledImage *m_scrolledImage;
};

#endif // SCROLLEDWINDOW_H
