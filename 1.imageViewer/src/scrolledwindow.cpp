#include "scrolledwindow.h"
//#include "scrolledimage.h"

ScrolledWindow::ScrolledWindow(wxWindow *parent) : wxScrolledWindow(parent, -1)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    m_left = new wxPanel(this);
    set_leftPanel(m_left);

    // right pane
    m_right = new wxPanel(this);
    wxStaticText *rst1 = new wxStaticText(m_right, -1, wxT("Text on right panel"));

    // add panels to main sizer
    sizer->Add(m_left, 1, wxALL, 10);
    sizer->Add(m_right, 1, wxALL, 10);

    this->SetSizer(sizer);
    // show up the scrollbars
    this->FitInside();
    // set a reasonable scroll rate
    this->SetScrollRate(20, 20);
}

void ScrolledWindow::setImage(std::shared_ptr<wxImage> image)
{
    m_scrolledImage->setImage(image);
}

void ScrolledWindow::set_leftPanel(wxPanel *leftPanel)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_scrolledImage = new ScrolledImage(leftPanel);
    // set minimum height of the image box, width is limited by width of its container
    m_scrolledImage->SetMinSize(wxSize(-1, 300));

    wxButton *btn = new wxButton(leftPanel, -1, wxT("Button on left panel"));
    btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ScrolledWindow::btnClicked, this);

    sizer->Add(m_scrolledImage, 1, wxALL | wxEXPAND, 10);
    sizer->Add(btn, 0, wxALL, 10);
    leftPanel->SetSizer(sizer);
}

void ScrolledWindow::btnClicked(wxCommandEvent &WXUNUSED(event))
{
    std::cout << "Button clicked" << std::endl;
}
