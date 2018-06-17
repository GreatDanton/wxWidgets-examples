#include "scrolledwindow.h"
//#include "scrolledimage.h"

ScrolledWindow::ScrolledWindow(wxFrame *parent) : wxScrolledWindow(parent, -1)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    m_scrolledImage = new ScrolledImage(this);
    // set minimum height of the image box, width is limited by width of its container
    m_scrolledImage->SetMinSize(wxSize(-1, 300));
    sizer->Add(m_scrolledImage, 1, wxALL | wxEXPAND, 10);

    // set a reasonable scroll rate
    this->SetScrollRate(20, 20);
    this->SetSizer(sizer);
    this->FitInside();
}

void ScrolledWindow::setImage(std::shared_ptr<wxImage> image)
{
    m_scrolledImage->setImage(image);
}
