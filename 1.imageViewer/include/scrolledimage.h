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
     * Display the image in the image placeholder
     * @param image pointer to wxImage instance
     */
    void setImage(std::shared_ptr<wxImage> image);

  private:
    /**
     * Starts the image drag event.
     * @param event - left mouse click
     */
    void mouseClick(wxMouseEvent &event);

    /**
     * Stops the dragging event. Once the mouse button is released the custom drag event stops and
     * the image is no longer scrolling in cursor direction.
     * @param event
     */
    void mouseRelease(wxMouseEvent &event);

    /**
     * Handles the mouse move event. If the user is holding the left mouse button (dragging), image
     * is moving into the same direction as the mouse cursor.
     * @param event
     */
    void mouseMove(wxMouseEvent &event);

    /**
     * Handles user scrollbar click events.
     * @param event
     */
    void thumbtrackScroll(wxScrollWinEvent &event);

    /**
     * Handles user mouse scroll event. Image is moving in the direction of the mouse scroll wheel
     * @param event
     */
    void mouseWheelScroll(wxMouseEvent &event);

    /**
     * Helper method for handling mouse vertical scroll
     * @param event
     */
    void mouseVerticalScroll(wxMouseEvent &event);

    /**
     * Helper method for handling mouse horizontal scroll (when horizontal scrollbar is in focus)
     * @param event
     */
    void mouseHorizontalScroll(wxMouseEvent &event);

    /**
     * Handles user keypress event. If the image window is focused the user can move the image with
     * cursor keys.
     * @param event - key press
     */
    void keypressScroll(wxKeyEvent &event);

    /**
     * Handles image zoom event while scrolling with mouse wheel. This method should not be executed
     * directly atm as it's called within the mouseWheelScroll event handler
     *
     * @param event - mouse scroll event
     */
    void imageZoom(wxMouseEvent &event);

    /**
     * Scroll helper method that ensures you can't scroll past the scrolled window boundaries.
     */
    void smoothScroll();

    // -------------------------------------------------------------------------------------------
    // Member variables
    //--------------------------------------------------------------------------------------------

    // image container/placeholder
    wxStaticBitmap *m_imgPlaceholder;

    // pointer to image
    std::shared_ptr<wxImage> m_image;

    // image zoom in percentages (100% means actual image height and width)
    int m_zoom = 100;

    // captures the mouse drag state
    bool m_mouseDrag = false;

    // storing new cursor position to calculate the mouse drag (dx, dy)
    wxSize m_newCursorPos{0, 0};

    // pixels representing amount of image scroll in x,y direction, this number changes depending on
    // component size
    wxSize m_currentScroll{0, 0};

    // defines how much pixels represents each scrollbar unit {x, y}
    wxSize m_pxPerUnit{1, 1};
    void imageZoom();
};

#endif // SCROLLEDIMAGE_H
