#include "scrolledimage.h"

ScrolledImage::ScrolledImage(wxPanel *parent) : wxScrolled<wxPanel>(parent, -1)
{
    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);

    m_imgPlaceholder =
        new wxStaticBitmap(this, -1, wxNullBitmap, wxDefaultPosition, wxSize(-1, -1));

    // TODO: remove this, currently loads image on start up for testing purposes
    // wxBitmap m_bmp = wxBitmap(wxT("testImage.jpg"), wxBITMAP_TYPE_ANY);
    // m_imgPlaceholder->SetBitmap(m_bmp);

    // placeholder should be able to grow
    panelSizer->Add(m_imgPlaceholder, 1);

    this->SetSizer(panelSizer);
    // display scrollbars
    this->FitInside();
    this->SetScrollRate(10, 10);
}

void ScrolledImage::setImage(std::shared_ptr<wxBitmap> image)
{
    m_imgPlaceholder->SetBitmap(*image);
}
