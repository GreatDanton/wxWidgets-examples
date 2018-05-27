#include "application.h"
#include "scrolledwindow.h"
#include <memory>

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

    // MAIN FRAME: display main application window
    m_mainWindow = new ScrolledWindow(this);

    // center app window
    Centre();
}

void Application::fileOpen(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog dialog(m_mainWindow, wxT("Load image"));
    int userClick = dialog.ShowModal();

    if (userClick == wxID_OK)
    {
        wxString filePath = dialog.GetPath();
        // load image
        std::shared_ptr<wxImage> opened_image = std::make_shared<wxImage>();
        opened_image->LoadFile(filePath, wxBITMAP_TYPE_ANY);
        m_mainWindow->setImage(opened_image);
    }
    else
    {
        std::cout << "File dialog canceled" << std::endl;
    }
}

void Application::quit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}
