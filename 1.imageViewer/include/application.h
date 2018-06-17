#ifndef APPLICATION_H
#define APPLICATION_H

#include "scrolledwindow.h"
#include <vector>
#include <wx/wx.h>

class Application : public wxFrame
{
  public:
    /**
     * Class constructor of the main application window
     * @param title of the application window
     */
    Application(const wxString &title);

  private:
    // main application window that scrolls if the window is too small for content
    ScrolledWindow *m_mainWindow;

    /**
     * Handles open file menu click, that loads the image in the scrolling image placeholder
     * @param event
     */
    void fileOpen(wxCommandEvent &event);

    /**
     * Load image from provided path into image container
     * @param imagePath - path to the image
     */
    void loadImage(wxString &imagePath);

    /**
     * Creates an application toolbar on the bottom of the application window
     */
    void createToolbar();

    /**
     * Shows image before the currently displayed in the directory. If we are already watching the
     * first image in the directory, it will go around and display the last image in the directory
     * @param event - toolbar icon previous click event
     */
    void showPrevImage(wxCommandEvent &event);
    /**
     * Shows next image in the image placeholder, if the next image exists, otherwise it will
     * start with the first image in the directory we are viewing.
     * @param event - toolbar icon next click event
     */
    void showNextImage(wxCommandEvent &event);

    /**
     * Find all images in current directory
     * @param filepath of the directory where we are viewing our images
     * @param imageName name of the image we are trying to open. Image name is necessary to set the
     * correct image iterator (without setting the iterator, images will always be displayed from
     * initial iterator position == 0)
     */
    void findImagesInDir(wxString &directory, wxString &imageName);

    /**
     * Find all images in current directory. This method does not set image iterator (images will
     * be shown from initial iterator position)
     * @param filepath of the selected directory
     */
    void findImagesInDir(wxString &filepath);

    /**
     * Quits the application
     * @param event
     */
    void quit(wxCommandEvent &event);

    // holds array of image absolute paths
    std::shared_ptr<std::vector<wxString>> m_imageFilenames;

    // holding position of the current image in the array of image filenames
    int64_t m_imageIterator = 0;
};

#endif // APPLICATION_H
