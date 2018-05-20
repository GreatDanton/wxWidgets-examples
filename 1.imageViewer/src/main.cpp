#include "main.h"
#include "mainframe.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame *mf = new MainFrame(wxT("Simple Image Viewer"));
    mf->Show(true);

    return true;
}
