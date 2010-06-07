#include "stdafx.h"
#include "Settings Page.h"

COptionsDirectoriesPage::COptionsDirectoriesPage (HWND hParent, const RECT & rcDispay ) :
	m_InUpdateSettings(false)
{
	Create(hParent);
	if (m_hWnd == NULL)
	{
		return;
	}
	SetWindowPos(HWND_TOP,&rcDispay,SWP_HIDEWINDOW);

	m_PluginGroup.Attach(GetDlgItem(IDC_DIR_FRAME1));
	m_AutoSaveGroup.Attach(GetDlgItem(IDC_DIR_FRAME3));
	m_InstantSaveGroup.Attach(GetDlgItem(IDC_DIR_FRAME4));
	m_ScreenShotGroup.Attach(GetDlgItem(IDC_DIR_FRAME5));
	m_TextureGroup.Attach(GetDlgItem(IDC_DIR_TEXTURE_FRAME));

	m_PluginDir.Attach(GetDlgItem(IDC_PLUGIN_DIR));
	m_AutoSaveDir.Attach(GetDlgItem(IDC_AUTO_DIR));
	m_InstantSaveDir.Attach(GetDlgItem(IDC_INSTANT_DIR));
	m_ScreenShotDir.Attach(GetDlgItem(IDC_SNAP_DIR));
	m_TextureDir.Attach(GetDlgItem(IDC_TEXTURE_DIR));

	m_PluginDefault.Attach(GetDlgItem(IDC_PLUGIN_DEFAULT));
	m_PluginSelected.Attach(GetDlgItem(IDC_PLUGIN_OTHER));
	m_AutoSaveDefault.Attach(GetDlgItem(IDC_AUTO_DEFAULT));
	m_AutoSaveSelected.Attach(GetDlgItem(IDC_AUTO_OTHER));
	m_InstantDefault.Attach(GetDlgItem(IDC_INSTANT_DEFAULT));
	m_InstantSelected.Attach(GetDlgItem(IDC_INSTANT_OTHER));
	m_ScreenShotDefault.Attach(GetDlgItem(IDC_SNAP_DEFAULT));
	m_ScreenShotSelected.Attach(GetDlgItem(IDC_SNAP_OTHER));
	m_TextureDefault.Attach(GetDlgItem(IDC_TEXTURE_DEFAULT));
	m_TextureSelected.Attach(GetDlgItem(IDC_TEXTURE_OTHER));

	//Set Text language for the dialog box
	m_PluginGroup.SetWindowText(GS(DIR_PLUGIN));
	m_AutoSaveGroup.SetWindowText(GS(DIR_AUTO_SAVE));
	m_InstantSaveGroup.SetWindowText(GS(DIR_INSTANT_SAVE));
	m_ScreenShotGroup.SetWindowText(GS(DIR_SCREEN_SHOT));
	m_TextureGroup.SetWindowText(GS(DIR_TEXTURE));

	UpdatePageSettings();
}

int CALLBACK COptionsDirectoriesPage::SelectDirCallBack (HWND hwnd,DWORD uMsg,DWORD lp, DWORD lpData) 
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		// WParam is TRUE since you are passing a path.
		// It would be FALSE if you were passing a pidl.
		if (lpData)
		{
			SendMessage((HWND)hwnd,BFFM_SETSELECTION,TRUE,lpData);
		}
		break;
	} 
	return 0;
}

void COptionsDirectoriesPage::SelectDirectory( LanguageStringID Title, CModifiedEditBox & EditBox, CModifiedButton & Default, CModifiedButton & selected )
{
	char Buffer[MAX_PATH], Directory[MAX_PATH];
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	stdstr InitialDir = EditBox.GetWindowText();

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = GS(Title);
	bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
	bi.lpfn = (BFFCALLBACK)SelectDirCallBack;
	bi.lParam = (DWORD)InitialDir.c_str();
	if ((pidl = SHBrowseForFolder(&bi)) != NULL) 
	{
		if (SHGetPathFromIDList(pidl, Directory)) 
		{
			CPath SelectedDir(Directory,"");
			EditBox.SetChanged(true);
			EditBox.SetWindowText(SelectedDir);
			Default.SetChanged(true);
			Default.SetCheck(BST_UNCHECKED);
			selected.SetCheck(BM_SETCHECK);
			SendMessage(GetParent(),PSM_CHANGED,(WPARAM)m_hWnd,0);
		}
	}
}

void COptionsDirectoriesPage::PluginDirChanged ( UINT Code, int id, HWND ctl )
{
	if (m_InUpdateSettings)  { return; }
	m_PluginDir.SetChanged(true);
	SendMessage(GetParent(),PSM_CHANGED,(WPARAM)m_hWnd,0);
}

void COptionsDirectoriesPage::AutoSaveDirChanged ( UINT Code, int id, HWND ctl )
{
	if (m_InUpdateSettings)  { return; }
	m_AutoSaveDir.SetChanged(true);
	SendMessage(GetParent(),PSM_CHANGED,(WPARAM)m_hWnd,0);
}

void COptionsDirectoriesPage::InstantSaveDirChanged ( UINT Code, int id, HWND ctl )
{
	if (m_InUpdateSettings)  { return; }
	m_InstantSaveDir.SetChanged(true);
	SendMessage(GetParent(),PSM_CHANGED,(WPARAM)m_hWnd,0);
}

void COptionsDirectoriesPage::SnapShotDirChanged ( UINT Code, int id, HWND ctl )
{
	if (m_InUpdateSettings)  { return; }
	m_ScreenShotDir.SetChanged(true);
	SendMessage(GetParent(),PSM_CHANGED,(WPARAM)m_hWnd,0);
}

void COptionsDirectoriesPage::TextureDirChanged ( UINT Code, int id, HWND ctl )
{
	if (m_InUpdateSettings)  { return; }
	m_TextureDir.SetChanged(true);
	SendMessage(GetParent(),PSM_CHANGED,(WPARAM)m_hWnd,0);
}

void COptionsDirectoriesPage::SelectPluginDir ( UINT Code, int id, HWND ctl )
{
	SelectDirectory(DIR_SELECT_PLUGIN,m_PluginDir,m_PluginDefault, m_PluginSelected);
}

void COptionsDirectoriesPage::SelectAutoDir ( UINT Code, int id, HWND ctl )
{
	SelectDirectory(DIR_SELECT_AUTO,m_AutoSaveDir,m_AutoSaveDefault, m_AutoSaveSelected);
}

void COptionsDirectoriesPage::SelectInstantDir ( UINT Code, int id, HWND ctl )
{
	SelectDirectory(DIR_SELECT_INSTANT,m_InstantSaveDir,m_InstantDefault, m_InstantSelected);
}

void COptionsDirectoriesPage::SelectSnapShotDir ( UINT Code, int id, HWND ctl )
{
	SelectDirectory(DIR_SELECT_SCREEN,m_ScreenShotDir,m_ScreenShotDefault, m_ScreenShotSelected);
}

void COptionsDirectoriesPage::SelectTextureDir ( UINT Code, int id, HWND ctl )
{
	SelectDirectory(DIR_SELECT_TEXTURE,m_TextureDir,m_TextureDefault, m_TextureSelected);
}

void COptionsDirectoriesPage::UpdatePageSettings()
{
	stdstr Directory;

	m_InUpdateSettings = true;
	m_PluginDir.SetChanged(_Settings->LoadString(Directory_PluginSelected,Directory));
	m_PluginDir.SetWindowText(Directory.c_str());
	m_AutoSaveDir.SetChanged(_Settings->LoadString(Directory_NativeSaveSelected,Directory));
	m_AutoSaveDir.SetWindowText(Directory.c_str());
	m_InstantSaveDir.SetChanged(_Settings->LoadString(Directory_InstantSaveSelected,Directory));
	m_InstantSaveDir.SetWindowText(Directory.c_str());
	m_ScreenShotDir.SetChanged(_Settings->LoadString(Directory_SnapShotSelected,Directory));
	m_ScreenShotDir.SetWindowText(Directory.c_str());
	m_TextureDir.SetChanged(_Settings->LoadString(Directory_TextureSelected,Directory));
	m_TextureDir.SetWindowText(Directory.c_str());

	bool UseSelected;
	m_PluginDefault.SetChanged(_Settings->LoadBool(Directory_PluginUseSelected,UseSelected));
	m_PluginDefault.SetCheck(!UseSelected);
	m_PluginSelected.SetCheck(UseSelected);

	m_AutoSaveDefault.SetChanged(_Settings->LoadBool(Directory_NativeSaveUseSelected,UseSelected));
	m_AutoSaveDefault.SetCheck(!UseSelected);
	m_AutoSaveSelected.SetCheck(UseSelected);

	m_InstantDefault.SetChanged(_Settings->LoadBool(Directory_InstantSaveUseSelected,UseSelected));
	m_InstantDefault.SetCheck(!UseSelected);
	m_InstantSelected.SetCheck(UseSelected);

	m_ScreenShotDefault.SetChanged(_Settings->LoadBool(Directory_SnapShotUseSelected,UseSelected));
	m_ScreenShotDefault.SetCheck(!UseSelected);
	m_ScreenShotSelected.SetCheck(UseSelected);

	m_TextureDefault.SetChanged(_Settings->LoadBool(Directory_TextureUseSelected,UseSelected));
	m_TextureDefault.SetCheck(!UseSelected);
	m_TextureSelected.SetCheck(UseSelected);

	m_InUpdateSettings = false;
}

void COptionsDirectoriesPage::UseSelectedClicked ( UINT Code, int id, HWND ctl )
{
	CModifiedButton * Button = NULL;
	switch (id)
	{
	case IDC_PLUGIN_DEFAULT: Button = &m_PluginDefault; break;
	case IDC_PLUGIN_OTHER: Button = &m_PluginDefault; break;
	case IDC_AUTO_DEFAULT: Button = &m_AutoSaveDefault; break;
	case IDC_AUTO_OTHER: Button = &m_AutoSaveDefault; break;
	case IDC_INSTANT_DEFAULT: Button = &m_InstantDefault; break;
	case IDC_INSTANT_OTHER: Button = &m_InstantDefault; break;
	case IDC_SNAP_DEFAULT: Button = &m_ScreenShotDefault; break;
	case IDC_SNAP_OTHER: Button = &m_ScreenShotDefault; break;
	case IDC_TEXTURE_DEFAULT: Button = &m_TextureDefault; break;
	case IDC_TEXTURE_OTHER: Button = &m_TextureDefault; break;
	}

	if (Button == NULL)
	{
		return;
	}

	if (!Button->IsChanged() || Button->IsReset())
	{
		if ((int)Button->GetMenu() == id)
		{
			return;
		}
	}
	Button->SetChanged(true);
	SendMessage(GetParent(),PSM_CHANGED,(WPARAM)m_hWnd,0);
}

void COptionsDirectoriesPage::HidePage()
{
	ShowWindow(SW_HIDE);
}

void COptionsDirectoriesPage::ShowPage()
{
	ShowWindow(SW_SHOW);
}

void COptionsDirectoriesPage::ResetDirectory( CModifiedEditBox & EditBox, SettingID Type )
{
	if (!EditBox.IsChanged())
	{
		return;
	}
	stdstr dir;
	_Settings->LoadDefaultString(Type,dir);
	EditBox.SetWindowText(dir.c_str());
	EditBox.SetReset(true);
}

void COptionsDirectoriesPage::ResetDefaultSelected ( CModifiedButton & ButtonDefault, CModifiedButton & ButtonSelected, SettingID Type )
{
	if (!ButtonDefault.IsChanged())
	{
		return;
	}
	bool UseSelected;
	_Settings->LoadDefaultBool(Type,UseSelected);
	ButtonDefault.SetCheck(!UseSelected);
	ButtonSelected.SetCheck(UseSelected);
	ButtonDefault.SetReset(true);
}

void COptionsDirectoriesPage::UpdateDirectory( CModifiedEditBox & EditBox, SettingID Type )
{
	if (EditBox.IsChanged())
	{
		stdstr dir = EditBox.GetWindowText();
		_Settings->SaveString(Type,dir.c_str());
	}
	if (EditBox.IsReset())
	{
		_Settings->DeleteSetting(Type);
	}
}

void COptionsDirectoriesPage::UpdateDefaultSelected ( CModifiedButton & Button, SettingID Type )
{
	if (Button.IsChanged())
	{
		bool bUseSelected = (Button.GetCheck() & BST_CHECKED) == 0;
		_Settings->SaveBool(Type,bUseSelected);
		
		if (Type == Directory_TextureUseSelected && !bUseSelected)
		{
			_Settings->DeleteSetting(Directory_TextureSelected);
		}
	}
	if (Button.IsReset())
	{
		_Settings->DeleteSetting(Type);
	}
}

void COptionsDirectoriesPage::ApplySettings( bool UpdateScreen )
{
	UpdateDirectory(m_PluginDir,Directory_PluginSelected);
	UpdateDirectory(m_AutoSaveDir,Directory_NativeSaveSelected);
	UpdateDirectory(m_InstantSaveDir,Directory_InstantSaveSelected);
	UpdateDirectory(m_ScreenShotDir,Directory_SnapShotSelected);
	UpdateDirectory(m_TextureDir,Directory_TextureSelected);

	UpdateDefaultSelected(m_PluginDefault,Directory_PluginUseSelected);
	UpdateDefaultSelected(m_AutoSaveDefault,Directory_NativeSaveUseSelected);
	UpdateDefaultSelected(m_InstantDefault,Directory_InstantSaveUseSelected);
	UpdateDefaultSelected(m_ScreenShotDefault,Directory_SnapShotUseSelected);
	UpdateDefaultSelected(m_TextureDefault,Directory_TextureUseSelected);
	
	if (UpdateScreen)
	{
		UpdatePageSettings();
	}
}

bool COptionsDirectoriesPage::EnableReset ( void )
{
	if (m_PluginDir.IsChanged()) { return true; }
	if (m_AutoSaveDir.IsChanged()) { return true; }
	if (m_InstantSaveDir.IsChanged()) { return true; }
	if (m_ScreenShotDir.IsChanged()) { return true; }
	if (m_TextureDir.IsChanged()) { return true; }
	if (m_PluginDefault.IsChanged()) { return true; }
	if (m_AutoSaveDefault.IsChanged()) { return true; }
	if (m_InstantDefault.IsChanged()) { return true; }
	if (m_ScreenShotDefault.IsChanged()) { return true; }
	if (m_TextureDefault.IsChanged()) { return true; }
	return false;
}

void COptionsDirectoriesPage::ResetPage()
{
	ResetDirectory(m_PluginDir,Directory_PluginSelected);
	ResetDirectory(m_AutoSaveDir,Directory_NativeSaveSelected);
	ResetDirectory(m_InstantSaveDir,Directory_InstantSaveSelected);
	ResetDirectory(m_ScreenShotDir,Directory_SnapShotSelected);
	ResetDirectory(m_TextureDir,Directory_TextureSelected);

	ResetDefaultSelected(m_PluginDefault,m_PluginSelected,Directory_PluginUseSelected);
	ResetDefaultSelected(m_AutoSaveDefault,m_AutoSaveSelected,Directory_NativeSaveUseSelected);
	ResetDefaultSelected(m_InstantDefault,m_InstantSelected,Directory_InstantSaveUseSelected);
	ResetDefaultSelected(m_ScreenShotDefault,m_ScreenShotSelected,Directory_SnapShotUseSelected);
	ResetDefaultSelected(m_TextureDefault,m_TextureSelected,Directory_TextureUseSelected);

	SendMessage(GetParent(),PSM_CHANGED,(WPARAM)m_hWnd,0);
}
