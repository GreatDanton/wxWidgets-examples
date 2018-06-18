#include "application.h"
#include "scrolledwindow.h"
#include <memory>
#include <wx/artprov.h>
#include <wx/dir.h>
#include <wx/filename.h>

Application::Application(const wxString &title)
    : wxFrame(nullptr, -1, title, wxDefaultPosition, wxSize(500, 500))
{
    wxMenuBar *menubar = new wxMenuBar();

    // File menu
    wxMenu *file = new wxMenu();
    wxMenuItem *open = new wxMenuItem(file, -1, wxT("&Open"));
    wxMenuItem *close = new wxMenuItem(file, -1, wxT("&Quit"));

    file->Append(open);
    file->AppendSeparator();
    file->Append(close);

    // file/open command
    Connect(open->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(Application::fileOpen));
    // file/quit command
    Connect(close->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Application::quit));

    menubar->Append(file, wxT("&File"));
    SetMenuBar(menubar);

    // ensures we handle every possible image format. Without this initializer the application will
    // crash on any image load
    wxInitAllImageHandlers();

    // set up scrolled container for displaying image
    m_mainWindow = new ScrolledWindow(this);

    // creates toolbar at the bottom of the application window
    this->createToolbar();

    // center app window
    Centre();
}

void Application::fileOpen(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog dialog(m_mainWindow, wxT("Load image"), "", "",
                        "Images (*.png;*.jpg;*.jpeg;*.bmp)|*.png;*.jpg;*.jpeg;*.bmp",
                        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    int userClick = dialog.ShowModal();

    if (userClick == wxID_OK)
    {
        wxString filePath = dialog.GetPath();
        this->loadImage(filePath);

        // find all images in directory
        wxString dir = dialog.GetDirectory();
        wxString fileName = dialog.GetFilename();
        this->findImagesInDir(dir, fileName);
    }
    else
    {
        std::cout << "File dialog canceled" << std::endl;
    }
}

void Application::loadImage(wxString &imagePath)
{
    std::shared_ptr<wxImage> image = std::make_shared<wxImage>();
    bool loadOk = image->LoadFile(imagePath, wxBITMAP_TYPE_ANY);
    // check if file is actually image
    if (image->IsOk() && loadOk)
    {
        m_mainWindow->setImage(image);
    }
}

void Application::createToolbar()
{
    // create toolbar with actions
    wxToolBar *toolbar =
        new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_BOTTOM);

    // add space to move every icon to the right of the window
    toolbar->AddStretchableSpace();

    // previous image icon and handler
    wxBitmap prevImageBitmap = wxArtProvider::GetBitmap(wxART_GO_BACK);
    wxToolBarToolBase *prevImage = toolbar->AddTool(-1, wxT("Previous image"), prevImageBitmap);
    Connect(prevImage->GetId(), wxEVT_COMMAND_TOOL_CLICKED,
            wxCommandEventHandler(Application::showPrevImage));

    // next image icon and handler
    wxBitmap nextImageBitmap = wxArtProvider::GetBitmap(wxART_GO_FORWARD);
    wxToolBarToolBase *nextImage = toolbar->AddTool(-1, wxT("Next image"), nextImageBitmap);
    Connect(nextImage->GetId(), wxEVT_COMMAND_TOOL_CLICKED,
            wxCommandEventHandler(Application::showNextImage));

    // display the tools and toolbar
    toolbar->Realize();
    this->SetToolBar(toolbar);
}

void Application::showPrevImage(wxCommandEvent &WXUNUSED(event))
{
    // early return if only one image present in directory
    if (m_imageFilenames.size() <= 1)
    {
        return;
    }

    // if we are viewing first image in directory, rotate around and display the last image in the
    // directory
    if (m_imageIterator == 0)
    {
        m_imageIterator = m_imageFilenames.size() - 1; // set iterator to last array position
    }
    else
    {
        m_imageIterator--;
    }

    wxString &imageName = m_imageFilenames.at(m_imageIterator);
    this->loadImage(imageName);
}

void Application::showNextImage(wxCommandEvent &WXUNUSED(event))
{
    // early return if only one image is present in directory
    if (m_imageFilenames.size() <= 1)
    {
        return;
    }

    m_imageIterator++;

    if (m_imageIterator >= m_imageFilenames.size())
    {
        m_imageIterator = 0;
    }

    wxString &imageName = m_imageFilenames.at(m_imageIterator);
    this->loadImage(imageName);
}

void Application::findImagesInDir(wxString &directory, wxString &imageName)
{
    wxDir dir(directory);
    if (!dir.IsOpened())
    {
        std::cout << "Directory is not opened" << std::endl;
        return;
    }

    m_imageFilenames.clear();
    wxString filename;
    const wxString &currentDir = wxGetCwd();
    bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);

    size_t i = 0;
    while (cont)
    {
        wxFileName fname(currentDir, filename);
        const wxString &ending = fname.GetExt();

        // check if filename is actually an image
        if (ending == wxT("png") || ending == wxT("jpg") || ending == wxT("jpeg") ||
            ending == wxT("bmp"))
        {
            // store absolute path to the image
            // TODO: filenames could be stored with a separate absolute directory path. This way we
            // can lower memory consumption
            m_imageFilenames.push_back(dir.GetNameWithSep() + filename);

            // If image with certain filename is opened we have to set the correct image array
            // iterator here. Without this check here, clicking on next/prev buttons will start
            // showing images from initial iterator position 0 (instead from the middle of the
            // array)
            if (!imageName.empty() && imageName == filename)
            {
                m_imageIterator = i;
            }
        }

        // get the next file
        cont = dir.GetNext(&filename);
        i++;
    }
}

void Application::findImagesInDir(wxString &filepath)
{
    wxString imageName = wxT("");
    this->findImagesInDir(filepath, imageName);
}

void Application::quit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}
