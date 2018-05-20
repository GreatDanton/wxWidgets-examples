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
};

#endif // SCROLLEDIMAGE_H
