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
    ScrolledWindow(wxWindow *parent);

    /**
     * Set image of the image placeholder in the main application window
     * @param image - pointer to bitmap image
     */
    void setImage(std::shared_ptr<wxBitmap> image);

  private:
    /**
     * Create layout of the left panel in the main application frame
     * @param leftPanel
     */
    void set_leftPanel(wxPanel *leftPanel);

    /**
     * An example of button click event handler
     * @param event button click event
     */
    void btnClicked(wxCommandEvent &event);

    // placeholder for the image
    ScrolledImage *m_scrolledImage;
    // left half of the app frame
    wxPanel *m_left;
    // right half of the app frame
    wxPanel *m_right;
};

#endif // SCROLLEDWINDOW_H
