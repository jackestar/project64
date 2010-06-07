#include "stdafx.h"
#include "Settings Page.h"
#include "Settings Page - Game - Status.h"

CGameStatusPage::CGameStatusPage (HWND hParent, const RECT & rcDispay )
{
	if (!Create(hParent,rcDispay))
	{
		return;
	}

	CIniFile RomIniFile  (_Settings->LoadString(SupportFile_RomDatabase).c_str());
	strlist Keys;
	RomIniFile.GetKeyList("Rom Status",Keys);
	stdstr Status = _Settings->LoadString(Rdb_Status);

	CModifiedComboBoxTxt * ComboBox;
	ComboBox = AddModComboBoxTxt(GetDlgItem(IDC_STATUS_TYPE),Rdb_Status);
	if (ComboBox)
	{
		for (strlist::iterator item = Keys.begin(); item != Keys.end(); item++ ) 
		{
			if (strstr(item->c_str(),".Sel") != NULL) { continue; }
			if (strstr(item->c_str(),".Auto") != NULL) { continue; }
			ComboBox->AddItem(item->c_str(), item->c_str());
		}
		ComboBox->SetTextField(GetDlgItem(IDC_STATUS_TEXT));
	}
	CModifiedEditBox * TxtBox;
	TxtBox = AddModTextBox(GetDlgItem(IDC_NOTES_CORE),Rdb_NotesCore,true);
	TxtBox->SetTextField(GetDlgItem(IDC_NOTES_CORE_TEXT));
	TxtBox = AddModTextBox(GetDlgItem(IDC_NOTES_PLUGIN),Rdb_NotesPlugin,true);
	TxtBox->SetTextField(GetDlgItem(IDC_NOTES_PLUGIN_TEXT));

	UpdatePageSettings();
}

void CGameStatusPage::ShowPage()
{
	ShowWindow(SW_SHOW);
}

void CGameStatusPage::HidePage()
{
	ShowWindow(SW_HIDE);
}

void CGameStatusPage::ApplySettings( bool UpdateScreen )
{
	CSettingsPageImpl<CGameStatusPage>::ApplySettings(UpdateScreen);
}

bool CGameStatusPage::EnableReset ( void )
{
	if (CSettingsPageImpl<CGameStatusPage>::EnableReset()) { return true; }
	return false;
}

void CGameStatusPage::ResetPage()
{
	CSettingsPageImpl<CGameStatusPage>::ResetPage();
}
