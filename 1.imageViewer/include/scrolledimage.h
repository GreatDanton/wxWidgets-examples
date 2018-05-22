#ifndef SCROLLEDIMAGE_H
#define SCROLLEDIMAGE_H

#include <memory>
#include <wx/wx.h>

/**
 * This class is used to display image in the scrolling container, that has the width of the
 * cointainer's parent
 */
class ScrolledImage : public wxScrolled<wxPanel>
{
  public:
    /**
     * Class constructor
     * @param parent of the scrolling image container
     */
    ScrolledImage(wxPanel *parent);

    /**
     * Display the image in image placeholder
     * @param image pointer to bitmap image
     */
    void setImage(std::shared_ptr<wxBitmap> image);

  private:
    wxStaticBitmap *m_imgPlaceholder;

    /**
     * On mouse left click handler
     * @param event
     */
    void mouseClick(wxMouseEvent &event);

    /**
     * On mouse left click release handler
     * @param event
     */
    void mouseRelease(wxMouseEvent &event);

    /**
     * On mouse move handler
     * @param event
     */
    void mouseMove(wxMouseEvent &event);

    // capture mouse drag
    bool m_mouseDrag = false;
    // storing cursor positions so we can calculate the image drag (dx, dy)
    // old cursor position
    wxSize m_oldCursorPos;
    // new cursor position
    wxSize m_newCursorPos;
};

#endif // SCROLLEDIMAGE_H
