#include "MyApp.h"
#include "SteelCalcMain.h"
#include <wx/wx.h>
#include <wx/image.h>
#include <iostream>

#ifdef __WXMSW__
#include <windows.h> // Required for AttachConsole
#endif

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    // data initialization
    SteelCalcMain *frame = new SteelCalcMain(nullptr, wxID_ANY, "Steel Calculator", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE);
    frame->Show(true);
    return true;
}