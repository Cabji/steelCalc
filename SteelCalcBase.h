///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class Main
///////////////////////////////////////////////////////////////////////////////
class Main : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar;
		wxStatusBar* m_statusBar;
		wxStaticText* m_lblHeaderText;
		wxCheckBox* m_chbCircularInput;
		wxGrid* m_gridLValues;
		wxGrid* m_gridCircularLValues;
		wxStaticText* m_lblInputSizerHeader;
		wxStaticText* m_lblBarGrade;
		wxChoice* m_specsGandD;
		wxStaticText* m_lblCalculatedHeader;
		wxStaticText* m_lblCalculatedTotalBarLength;
		wxStaticText* m_lblCalculatedBarArea;
		wxStaticText* m_lblCalculatedProcessingType;
		wxStaticText* m_lblCalculatedCostPerMg;
		wxStaticText* m_lblWeightPerBar;

	public:

		Main( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Steel Calculator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1046,481 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Main();

};

