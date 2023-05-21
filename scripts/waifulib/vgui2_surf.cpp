#include "port.h"

#include "vgui_surf.h" // Must include it before in order to replace IEngineSurface

#include "IBaseUI.h"
#include "IClientVGUI.h"
#include "VGui2Interfaces.h"
#include "Panel.h"
#include "Cursor.h"
#include "IChromeHTMLWrapper.h"

#include <VGUI_Dar.h>

#include <string.h>
#include <stdio.h>

class RootPanel : public vgui2::Panel
{
public:
	RootPanel( vgui2::Panel *parent, const char *panelName ) : vgui2::Panel( parent, panelName ) { }

	virtual vgui2::VPANEL IsWithinTraverse( int x, int y, bool traversePopups )
	{
		auto panel = vgui2::Panel::IsWithinTraverse( x, y, traversePopups );
		if ( panel == GetVPanel() )
			return NULL;

		return panel;
	}
};

class BaseUISurface : public vgui2::ISurface
{
public:
	virtual void Shutdown();
	virtual void RunFrame();
	virtual vgui2::VPANEL GetEmbeddedPanel();
	virtual void SetEmbeddedPanel( vgui2::VPANEL panel );
	virtual void PushMakeCurrent( vgui2::VPANEL panel, bool useInsets );
	virtual void PopMakeCurrent( vgui2::VPANEL panel );
	virtual void DrawSetColor( int r, int g, int b, int a );
	virtual void DrawSetColor( Color col );
	virtual void DrawFilledRect( int x0, int y0, int x1, int y1 );
	virtual void DrawOutlinedRect( int x0, int y0, int x1, int y1 );
	virtual void DrawLine( int x0, int y0, int x1, int y1 );
	virtual void DrawPolyLine( int *px, int *py, int numPoints );
	virtual void DrawSetTextFont( vgui2::HFont font );
	virtual void DrawSetTextColor( int r, int g, int b, int a );
	virtual void DrawSetTextColor( Color col );
	virtual void DrawSetTextPos( int x, int y );
	virtual void DrawGetTextPos( int &x, int &y );
	virtual void DrawPrintText( const wchar_t *text, int textLen );
	virtual void DrawUnicodeChar( wchar_t wch );
	virtual void DrawUnicodeCharAdd( wchar_t wch );
	virtual void DrawFlushText();
	virtual vgui2::IHTML *CreateHTMLWindow( vgui2::IHTMLEvents *events, vgui2::VPANEL context );
	virtual void PaintHTMLWindow( vgui2::IHTML *htmlwin );
	virtual void DeleteHTMLWindow( vgui2::IHTML *htmlwin );
	virtual void DrawSetTextureFile( int id, const char *filename, int hardwareFilter, bool forceReload );
	virtual void DrawSetTextureRGBA( int id, const unsigned char *rgba, int wide, int tall, int hardwareFilter, bool forceReload );
	virtual void DrawSetTexture( int id );
	virtual void DrawGetTextureSize( int id, int &wide, int &tall );
	virtual void DrawTexturedRect( int x0, int y0, int x1, int y1 );
	virtual bool IsTextureIDValid( int id );
	virtual int CreateNewTextureID( bool procedural );
	virtual void GetScreenSize( int &wide, int &tall );
	virtual void SetAsTopMost( vgui2::VPANEL panel, bool state );
	virtual void BringToFront( vgui2::VPANEL panel );
	virtual void SetForegroundWindow( vgui2::VPANEL panel );
	virtual void SetPanelVisible( vgui2::VPANEL panel, bool state );
	virtual void SetMinimized( vgui2::VPANEL panel, bool state );
	virtual bool IsMinimized( vgui2::VPANEL panel );
	virtual void FlashWindow( vgui2::VPANEL panel, bool state );
	virtual void SetTitle( vgui2::VPANEL panel, const wchar_t *title );
	virtual void SetAsToolBar( vgui2::VPANEL panel, bool state );
	virtual void CreatePopup( vgui2::VPANEL panel, bool minimised, bool showTaskbarIcon, bool disabled, bool mouseInput, bool kbInput );
	virtual void SwapBuffers( vgui2::VPANEL panel );
	virtual void Invalidate( vgui2::VPANEL panel );
	virtual void SetCursor( vgui2::HCursor cursor );
	virtual bool IsCursorVisible();
	virtual void ApplyChanges();
	virtual bool IsWithin( int x, int y );
	virtual bool HasFocus();
	virtual bool SupportsFeature( SurfaceFeature_e feature );
	virtual void RestrictPaintToSinglePanel( vgui2::VPANEL panel );
	virtual void SetModalPanel( vgui2::VPANEL panel );
	virtual vgui2::VPANEL GetModalPanel();
	virtual void UnlockCursor();
	virtual void LockCursor();
	virtual void SetTranslateExtendedKeys( bool state );
	virtual vgui2::VPANEL GetTopmostPopup();
	virtual void SetTopLevelFocus( vgui2::VPANEL panel );
	virtual vgui2::HFont CreateFont();
	virtual bool AddGlyphSetToFont( vgui2::HFont font, const char *fontName, int tall, int weight, int blur, int scanlines, int flags, int lowRange, int highRange );
	virtual bool AddCustomFontFile( const char *fontFileName );
	virtual int GetFontTall( vgui2::HFont font );
	virtual void GetCharABCwide( vgui2::HFont font, int ch, int &a, int &b, int &c );
	virtual int GetCharacterWidth( vgui2::HFont font, int ch );
	virtual void GetTextSize( vgui2::HFont font, const wchar_t *text, int &wide, int &tall );
	virtual vgui2::VPANEL GetNotifyPanel();
	virtual void SetNotifyIcon( vgui2::VPANEL context, vgui2::HTexture icon, vgui2::VPANEL panelToReceiveMessages, const char *text );
	virtual void PlaySound( const char *fileName );
	virtual int GetPopupCount();
	virtual vgui2::VPANEL GetPopup( int index );
	virtual bool ShouldPaintChildPanel( vgui2::VPANEL panel );
	virtual bool RecreateContext( vgui2::VPANEL panel );
	virtual void AddPanel( vgui2::VPANEL panel );
	virtual void ReleasePanel( vgui2::VPANEL panel );
	virtual void MovePopupToFront( vgui2::VPANEL panel );
	virtual void MovePopupToBack( vgui2::VPANEL panel );
	virtual void SolveTraverse( vgui2::VPANEL panel, bool forceApplySchemeSettings );
	virtual void PaintTraverse( vgui2::VPANEL panel );
	virtual void EnableMouseCapture( vgui2::VPANEL panel, bool state );
	virtual void GetWorkspaceBounds( int &x, int &y, int &wide, int &tall );
	virtual void GetAbsoluteWindowBounds( int &x, int &y, int &wide, int &tall );
	virtual void GetProportionalBase( int &width, int &height );
	virtual void CalculateMouseVisible();
	virtual bool NeedKBInput();
	virtual bool HasCursorPosFunctions();
	virtual void SurfaceGetCursorPos( int &x, int &y );
	virtual void SurfaceSetCursorPos( int x, int y );
	virtual void DrawTexturedPolygon( vgui2::VGuiVertex *pVertices, int n );
	virtual int GetFontAscent( vgui2::HFont font, wchar_t wch );
	virtual void SetAllowHTMLJavaScript( bool state );
	virtual void SetLanguage( const char *pchLang );
	virtual const char *GetLanguage();
	virtual bool DeleteTextureByID( int id );
	virtual void DrawUpdateRegionTextureBGRA( int nTextureID, int x, int y, const unsigned char *pchData, int wide, int tall );
	virtual void DrawSetTextureBGRA( int id, const unsigned char *bgra, int wide, int tall );
	virtual void CreateBrowser( vgui2::VPANEL panel, IHTMLResponses *pBrowser, bool bPopupWindow, const char *pchUserAgentIdentifier );
	virtual void RemoveBrowser( vgui2::VPANEL panel, IHTMLResponses *pBrowser );
	virtual IHTMLChromeController *AccessChromeHTMLController();

	BaseUISurface();
	void Init( vgui2::VPANEL _embeddedPanel, IEngineSurface *pEngineSurface, IHTMLChromeController *pChromeController );
	void SetScreenBounds( int x, int y, int wide, int tall );
	void SetIgnoreMouseVisCalc( bool state );
	void InternalSchemeSettingsTraverse( vgui2::VPANEL panel, bool forceApplySchemeSettings );
	void InternalThinkTraverse( vgui2::VPANEL panel );
	void InternalSolveTraverse( vgui2::VPANEL panel );

private:
	vgui2::VPANEL embeddedPanel;
	vgui2::VPANEL restrictedPanel;
	char language[32];
	IEngineSurface *engineSurface;
	IHTMLChromeController *chromeController;
	int surfaceBounds[4];
	vgui::Dar<vgui2::VPANEL> popups;
	bool allowJavaScript;
	bool needKB;
	bool needMouse;
	bool cursorLocked;
	bool translateExtendedKeys;
	bool ignoreMouseVisCalc;
};

EXPOSE_SINGLE_INTERFACE( BaseUISurface, ISurface, VGUI_SURFACE_INTERFACE_VERSION );

class BaseUI : public IBaseUI
{
public:
	BaseUI() : initialized( 0 ), numFactories( 0 ) { }
	virtual void Initialize( CreateInterfaceFn *factories, int count );
	virtual void Start( IEngineSurface *engineSurface, int interfaceVersion );
	virtual void Shutdown();
	virtual int Key_Event( int down, int keynum, const char *pszCurrentBinding );
	virtual void CallEngineSurfaceAppHandler( void *event, void *userData );
	virtual void Paint( int x, int y, int right, int bottom );
	virtual void HideGameUI();
	virtual void ActivateGameUI();
	virtual void HideConsole();
	virtual void ShowConsole();

private:
	static constexpr int MAX_NUM_FACTORIES = 6;

	int initialized;
	CreateInterfaceFn factoryList[MAX_NUM_FACTORIES];
	int numFactories;
	CSysModule *vgui2Module;
	CSysModule *chromeModule;
};

static const auto VPANEL_NORMAL = ( (vgui2::SurfacePlat *)NULL );
static const auto VPANEL_MINIMIZED = ( (vgui2::SurfacePlat *)0x00000001 );

static RootPanel *rootPanel;
static IClientVGUI *clientVGUI;
static BaseUISurface *baseUISurface;

EXPOSE_SINGLE_INTERFACE( BaseUI, IBaseUI, BASEUI_INTERFACE_VERSION );

void BaseUISurface::Shutdown()
{
	if ( chromeController )
		chromeController->Shutdown();
}

void BaseUISurface::RunFrame()
{
	if ( chromeController )
		chromeController->RunFrame();
}

vgui2::VPANEL BaseUISurface::GetEmbeddedPanel()
{
	return embeddedPanel;
}

void BaseUISurface::SetEmbeddedPanel( vgui2::VPANEL panel )
{
	embeddedPanel = panel;
}

void BaseUISurface::PushMakeCurrent( vgui2::VPANEL panel, bool useInsets )
{
	int insets[4] = { 0, 0, 0, 0 };
	int absExtents[4];
	int clipRect[4];
	int wide, tall;

	if ( useInsets )
		vgui2::ipanel()->GetInset( panel, insets[0], insets[1], insets[2], insets[3] );

	vgui2::ipanel()->GetAbsPos( panel, absExtents[0], absExtents[1] );
	vgui2::ipanel()->GetSize( panel, wide, tall );
	absExtents[2] = absExtents[0] + wide;
	absExtents[3] = absExtents[1] + tall;

	vgui2::ipanel()->GetClipRect( panel, clipRect[0], clipRect[1], clipRect[2], clipRect[3] );

	engineSurface->PushMakeCurrent( insets, absExtents, clipRect );
}

void BaseUISurface::PopMakeCurrent( vgui2::VPANEL panel )
{
	engineSurface->PopMakeCurrent();
}

void BaseUISurface::DrawSetColor( int r, int g, int b, int a )
{
	engineSurface->DrawSetColor( r, g, b, a );
}

void BaseUISurface::DrawSetColor( Color col )
{
	engineSurface->DrawSetColor( col[0], col[1], col[2], col[3] );
}

void BaseUISurface::DrawFilledRect( int x0, int y0, int x1, int y1 )
{
	engineSurface->DrawFilledRect( x0, y0, x1, y1 );
}

void BaseUISurface::DrawOutlinedRect( int x0, int y0, int x1, int y1 )
{
	engineSurface->DrawOutlinedRect( x0, y0, x1, y1 );
}

void BaseUISurface::DrawLine( int x0, int y0, int x1, int y1 )
{
	// engineSurface sucks
}

void BaseUISurface::DrawPolyLine( int *px, int *py, int numPoints )
{
	// engineSurface sucks
}

void BaseUISurface::DrawSetTextFont( vgui2::HFont font )
{
	engineSurface->DrawSetTextFont( font );
}

void BaseUISurface::DrawSetTextColor( int r, int g, int b, int a )
{
	engineSurface->DrawSetTextColor( r, g, b, a );
}

void BaseUISurface::DrawSetTextColor( Color col )
{
	engineSurface->DrawSetTextColor( col[0], col[1], col[2], col[3] );
}

void BaseUISurface::DrawSetTextPos( int x, int y )
{
	engineSurface->DrawSetTextPos( x, y );
}

void BaseUISurface::DrawGetTextPos( int &x, int &y )
{
	engineSurface->DrawGetTextPos( x, y );
}

void BaseUISurface::DrawPrintText( const wchar_t *text, int textLen )
{
	engineSurface->DrawPrintText( text, textLen );
}

void BaseUISurface::DrawUnicodeChar( wchar_t wch )
{
	engineSurface->DrawUnicodeChar( wch, false );
}

void BaseUISurface::DrawUnicodeCharAdd( wchar_t wch )
{
	engineSurface->DrawUnicodeChar( wch, true );
}

void BaseUISurface::DrawFlushText()
{
}

vgui2::IHTML *BaseUISurface::CreateHTMLWindow( vgui2::IHTMLEvents *events, vgui2::VPANEL context )
{
	return nullptr;
}

void BaseUISurface::PaintHTMLWindow( vgui2::IHTML *htmlwin )
{
}

void BaseUISurface::DeleteHTMLWindow( vgui2::IHTML *htmlwin )
{
}

void BaseUISurface::DrawSetTextureFile( int id, const char *filename, int hardwareFilter, bool forceReload )
{
	engineSurface->DrawSetTextureFile( id, filename );
}

void BaseUISurface::DrawSetTextureRGBA( int id, const unsigned char *rgba, int wide, int tall, int hardwareFilter, bool forceReload )
{
	engineSurface->DrawSetTextureRGBA( id, rgba, wide, tall );
}

void BaseUISurface::DrawSetTexture( int id )
{
	engineSurface->DrawSetTexture( id );
}

void BaseUISurface::DrawGetTextureSize( int id, int &wide, int &tall )
{
	engineSurface->DrawGetTextureSize( id, wide, tall );
}

void BaseUISurface::DrawTexturedRect( int x0, int y0, int x1, int y1 )
{
	engineSurface->DrawTexturedRect( x0, y0, x1, y1 );
}

bool BaseUISurface::IsTextureIDValid( int id )
{
	return true;
}

int BaseUISurface::CreateNewTextureID( bool procedural )
{
	return engineSurface->CreateNewTextureID();
}

void BaseUISurface::GetScreenSize( int &wide, int &tall )
{
	engineSurface->GetScreenSize( wide, tall );
}

void BaseUISurface::SetAsTopMost( vgui2::VPANEL panel, bool state )
{
}

void BaseUISurface::BringToFront( vgui2::VPANEL panel )
{
	vgui2::ipanel()->MoveToFront( panel );

	if ( vgui2::ipanel()->IsPopup( panel ) )
		MovePopupToFront( panel );
}

void BaseUISurface::SetForegroundWindow( vgui2::VPANEL panel )
{
	BringToFront( panel );
}

void BaseUISurface::SetPanelVisible( vgui2::VPANEL panel, bool state )
{
}

void BaseUISurface::SetMinimized( vgui2::VPANEL panel, bool state )
{
	if ( !state )
	{
		vgui2::ipanel()->SetPlat( panel, VPANEL_NORMAL );
		return;
	}

	vgui2::ipanel()->SetPlat( panel, VPANEL_MINIMIZED );
	vgui2::ipanel()->SetVisible( panel, false );
}

bool BaseUISurface::IsMinimized( vgui2::VPANEL panel )
{
	return vgui2::ipanel()->Plat( panel ) == VPANEL_MINIMIZED;
}

void BaseUISurface::FlashWindow( vgui2::VPANEL panel, bool state )
{
}

void BaseUISurface::SetTitle( vgui2::VPANEL panel, const wchar_t *title )
{
}

void BaseUISurface::SetAsToolBar( vgui2::VPANEL panel, bool state )
{
}

void BaseUISurface::CreatePopup( vgui2::VPANEL panel, bool minimised, bool showTaskbarIcon, bool disabled, bool mouseInput, bool kbInput )
{
	if ( vgui2::ipanel()->GetParent( panel ) == NULL )
		vgui2::ipanel()->SetParent( panel, GetEmbeddedPanel() );

	vgui2::ipanel()->SetPopup( panel, true );
	vgui2::ipanel()->SetKeyBoardInputEnabled( panel, kbInput );
	vgui2::ipanel()->SetMouseInputEnabled( panel, mouseInput );

	if ( !popups.hasElement( panel ) )
		popups.addElement( panel );
}

void BaseUISurface::SwapBuffers( vgui2::VPANEL panel )
{
}

void BaseUISurface::Invalidate( vgui2::VPANEL panel )
{
}

void BaseUISurface::SetCursor( vgui2::HCursor cursor )
{
	engineSurface->SetCursor( cursor );
}

bool BaseUISurface::IsCursorVisible()
{
	return engineSurface->GetCursor() != vgui2::dc_none;
}

void BaseUISurface::ApplyChanges()
{
}

bool BaseUISurface::IsWithin( int x, int y )
{
	return true;
}

bool BaseUISurface::HasFocus()
{
	return true;
}

bool BaseUISurface::SupportsFeature( SurfaceFeature_e feature )
{
	return false;
}

void BaseUISurface::RestrictPaintToSinglePanel( vgui2::VPANEL panel )
{
	restrictedPanel = panel;
	vgui2::input()->SetAppModalSurface( panel );
}

void BaseUISurface::SetModalPanel( vgui2::VPANEL panel )
{
}

vgui2::VPANEL BaseUISurface::GetModalPanel()
{
	return restrictedPanel;
}

void BaseUISurface::UnlockCursor()
{
	cursorLocked = false;
}

void BaseUISurface::LockCursor()
{
	cursorLocked = true;
}

void BaseUISurface::SetTranslateExtendedKeys( bool state )
{
	translateExtendedKeys = state;
}

vgui2::VPANEL BaseUISurface::GetTopmostPopup()
{
	if ( popups.getCount() > 0 )
		return popups[popups.getCount() - 1];

	return NULL;
}

void BaseUISurface::SetTopLevelFocus( vgui2::VPANEL panel )
{
	while ( panel )
	{
		if ( vgui2::ipanel()->IsPopup( panel ) && vgui2::ipanel()->IsMouseInputEnabled( panel ) )
		{
			BringToFront( panel );
			break;
		}

		panel = vgui2::ipanel()->GetParent( panel );
	}
}

vgui2::HFont BaseUISurface::CreateFont()
{
	return engineSurface->CreateFont();
}

bool BaseUISurface::AddGlyphSetToFont( vgui2::HFont font, const char *fontName, int tall, int weight, int blur, int scanlines, int flags, int lowRange, int highRange )
{
	return engineSurface->AddGlyphSetToFont( font, fontName, tall, weight, flags & FONTFLAG_ITALIC, flags & FONTFLAG_UNDERLINE, flags & FONTFLAG_STRIKEOUT, flags & FONTFLAG_SYMBOL );
}

bool BaseUISurface::AddCustomFontFile( const char *fontFileName )
{
	return engineSurface->AddCustomFontFile( fontFileName );
}

int BaseUISurface::GetFontTall( vgui2::HFont font )
{
	return engineSurface->GetFontTall( font );
}

void BaseUISurface::GetCharABCwide( vgui2::HFont font, int ch, int &a, int &b, int &c )
{
	engineSurface->GetCharABCwide( font, ch, a, b, c );
}

int BaseUISurface::GetCharacterWidth( vgui2::HFont font, int ch )
{
	return engineSurface->GetCharacterWidth( font, ch );
}

void BaseUISurface::GetTextSize( vgui2::HFont font, const wchar_t *text, int &wide, int &tall )
{
	return engineSurface->GetTextSize( font, text, wide, tall );
}

vgui2::VPANEL BaseUISurface::GetNotifyPanel()
{
	return NULL;
}

void BaseUISurface::SetNotifyIcon( vgui2::VPANEL context, vgui2::HTexture icon, vgui2::VPANEL panelToReceiveMessages, const char *text )
{
}

void BaseUISurface::PlaySound( const char *fileName )
{
	vgui_support::g_api->PlaySound( fileName );
}

int BaseUISurface::GetPopupCount()
{
	return popups.getCount();
}

vgui2::VPANEL BaseUISurface::GetPopup( int index )
{
	if ( 0 <= index && index < popups.getCount() )
		return popups[index];

	return NULL;
}

bool BaseUISurface::ShouldPaintChildPanel( vgui2::VPANEL panel )
{
	if ( restrictedPanel != NULL && vgui2::ipanel()->HasParent( panel, restrictedPanel ) )
		return false;

	if ( !vgui2::ipanel()->IsPopup( panel ) )
		return true;

	if ( popups.hasElement( panel ) )
		vgui2::ipanel()->Render_SetPopupVisible( panel, true );

	return false;
}

bool BaseUISurface::RecreateContext( vgui2::VPANEL panel )
{
	return true;
}

void BaseUISurface::AddPanel( vgui2::VPANEL panel )
{
	if ( !vgui2::ipanel()->IsPopup( panel ) )
		return;

	CreatePopup( panel, false, false, false, true, true );
}

void BaseUISurface::ReleasePanel( vgui2::VPANEL panel )
{
	popups.removeElement( panel );

	if ( restrictedPanel == panel )
		restrictedPanel = NULL;
}

void BaseUISurface::MovePopupToFront( vgui2::VPANEL panel )
{
	if ( popups.hasElement( panel ) )
	{
		popups.removeElement( panel );
		popups.addElement( panel );
	}
}

void BaseUISurface::MovePopupToBack( vgui2::VPANEL panel )
{
	if ( popups.hasElement( panel ) )
	{
		popups.removeElement( panel );
		popups.insertElementAt( panel, 0 );
	}
}

void BaseUISurface::SolveTraverse( vgui2::VPANEL panel, bool forceApplySchemeSettings )
{
	InternalSchemeSettingsTraverse( panel, forceApplySchemeSettings );
	InternalThinkTraverse( panel );
	InternalSolveTraverse( panel );
}

void BaseUISurface::PaintTraverse( vgui2::VPANEL panel )
{
	if ( !vgui2::ipanel()->IsVisible( panel ) )
		return;

	if ( panel != GetEmbeddedPanel() )
	{
		vgui2::ipanel()->PaintTraverse( panel, true, true );
		return;
	}

	if ( restrictedPanel )
		panel = restrictedPanel;

	for ( int i = 0; i < popups.getCount(); ++i )
		vgui2::ipanel()->Render_SetPopupVisible( popups[i], false );

	vgui2::ipanel()->PaintTraverse( panel, true, true );

	for ( int i = 0; i < popups.getCount(); ++i )
	{
		if ( vgui2::ipanel()->Render_GetPopupVisible( popups[i] ) )
			vgui2::ipanel()->PaintTraverse( popups[i], true, true );
	}
}

void BaseUISurface::EnableMouseCapture( vgui2::VPANEL panel, bool state )
{
}

void BaseUISurface::GetWorkspaceBounds( int &x, int &y, int &wide, int &tall )
{
	x = 0;
	y = 0;
	vgui2::ipanel()->GetSize( embeddedPanel, wide, tall );
}

void BaseUISurface::GetAbsoluteWindowBounds( int &x, int &y, int &wide, int &tall )
{
	x = surfaceBounds[0];
	y = surfaceBounds[1];
	wide = surfaceBounds[2];
	tall = surfaceBounds[3];
}

void BaseUISurface::GetProportionalBase( int &width, int &height )
{
	width = 640;
	height = 480;
}

void BaseUISurface::CalculateMouseVisible()
{
	if ( ignoreMouseVisCalc )
		return;

	needMouse = false;
	needKB = false;

	for ( int i = 0; i < popups.getCount(); ++i )
	{
		bool visible = vgui2::ipanel()->IsVisible( popups[i] );
		vgui2::VPANEL parent = vgui2::ipanel()->GetParent( popups[i] );

		while ( parent != NULL && visible )
		{
			if ( !vgui2::ipanel()->IsVisible( parent ) )
			{
				visible = false;
				break;
			}

			parent = vgui2::ipanel()->GetParent( parent );
		}

		if ( !visible )
			continue;

		needMouse = needMouse || vgui2::ipanel()->IsMouseInputEnabled( popups[i] );
		needKB = needKB || vgui2::ipanel()->IsKeyBoardInputEnabled( popups[i] );
	}

	UnlockCursor();

	if ( needMouse )
	{
		SetCursor( vgui2::dc_arrow );
	}
	else
	{
		SetCursor( vgui2::dc_none );
		LockCursor();
	}
}

bool BaseUISurface::NeedKBInput()
{
	return needKB;
}

bool BaseUISurface::HasCursorPosFunctions()
{
	return true;
}

void BaseUISurface::SurfaceGetCursorPos( int &x, int &y )
{
	engineSurface->GetCursorPos( x, y );
}

void BaseUISurface::SurfaceSetCursorPos( int x, int y )
{
	vgui_support::g_api->SetCursorPos( x, y );
}

void BaseUISurface::DrawTexturedPolygon( vgui2::VGuiVertex *pVertices, int n )
{
	engineSurface->DrawTexturedPolygon( pVertices, n );
}

int BaseUISurface::GetFontAscent( vgui2::HFont font, wchar_t wch )
{
	// return some arbitrary number for now
	return 0;
}

void BaseUISurface::SetAllowHTMLJavaScript( bool state )
{
	allowJavaScript = state;
}

void BaseUISurface::SetLanguage( const char *pchLang )
{
	if ( pchLang != nullptr )
	{
		strncpy( language, pchLang, sizeof( language ) );
		language[sizeof( language ) - 1] = '\0';
	}
	else
	{
		strcpy( language, "english" );
	}
}

const char *BaseUISurface::GetLanguage()
{
	return language;
}

bool BaseUISurface::DeleteTextureByID( int id )
{
	return engineSurface->DeleteTextureByID( id );
}

void BaseUISurface::DrawUpdateRegionTextureBGRA( int nTextureID, int x, int y, const unsigned char *pchData, int wide, int tall )
{
	engineSurface->DrawUpdateRegionTextureBGRA( nTextureID, x, y, pchData, wide, tall );
}

void BaseUISurface::DrawSetTextureBGRA( int id, const unsigned char *bgra, int wide, int tall )
{
	engineSurface->DrawSetTextureBGRA( id, bgra, wide, tall );
}

void BaseUISurface::CreateBrowser( vgui2::VPANEL panel, IHTMLResponses *pBrowser, bool bPopupWindow, const char *pchUserAgentIdentifier )
{
	if ( chromeController )
		chromeController->CreateBrowser( pBrowser, false, "Valve Half-Life" );
}

void BaseUISurface::RemoveBrowser( vgui2::VPANEL panel, IHTMLResponses *pBrowser )
{
	if ( chromeController )
		chromeController->RemoveBrowser( pBrowser );
}

IHTMLChromeController *BaseUISurface::AccessChromeHTMLController()
{
	return chromeController;
}

BaseUISurface::BaseUISurface()
{
	embeddedPanel = NULL;
	restrictedPanel = NULL;
	engineSurface = nullptr;
	chromeController = nullptr;
	allowJavaScript = false;
	needKB = true;
	needMouse = true;
	cursorLocked = false;
	translateExtendedKeys = true;
	ignoreMouseVisCalc = false;
}

void BaseUISurface::Init( vgui2::VPANEL _embeddedPanel, IEngineSurface *pEngineSurface, IHTMLChromeController *pChromeController )
{
	engineSurface = pEngineSurface;
	SetEmbeddedPanel( _embeddedPanel );

	chromeController = pChromeController;
	if ( chromeController )
	{
		chromeController->Init( "htmlcache", "htmlcookies" );
		chromeController->SetCefThreadTargetFrameRate( 60 );
	}
}

void BaseUISurface::SetScreenBounds( int x, int y, int wide, int tall )
{
	surfaceBounds[0] = x;
	surfaceBounds[1] = y;
	surfaceBounds[2] = wide;
	surfaceBounds[3] = tall;
}

void BaseUISurface::SetIgnoreMouseVisCalc( bool state )
{
	ignoreMouseVisCalc = state;
}

void BaseUISurface::InternalSchemeSettingsTraverse( vgui2::VPANEL panel, bool forceApplySchemeSettings )
{
	for ( int i = 0; i < vgui2::ipanel()->GetChildCount( panel ); ++i )
	{
		vgui2::VPANEL child = vgui2::ipanel()->GetChild( panel, i );
		if ( forceApplySchemeSettings || vgui2::ipanel()->IsVisible( child ) )
			InternalSchemeSettingsTraverse( child, forceApplySchemeSettings );
	}

	vgui2::ipanel()->PerformApplySchemeSettings( panel );
}

void BaseUISurface::InternalThinkTraverse( vgui2::VPANEL panel )
{
	vgui2::ipanel()->Think( panel );

	for ( int i = 0; i < vgui2::ipanel()->GetChildCount( panel ); ++i )
	{
		vgui2::VPANEL child = vgui2::ipanel()->GetChild( panel, i );
		if ( vgui2::ipanel()->IsVisible( child ) )
			InternalThinkTraverse( child );
	}
}

void BaseUISurface::InternalSolveTraverse( vgui2::VPANEL panel )
{
	vgui2::ipanel()->Solve( panel );

	for ( int i = 0; i < vgui2::ipanel()->GetChildCount( panel ); ++i )
	{
		vgui2::VPANEL child = vgui2::ipanel()->GetChild( panel, i );
		if ( vgui2::ipanel()->IsVisible( child ) )
			InternalSolveTraverse( child );
	}
}

void BaseUI::Initialize( CreateInterfaceFn *factories, int count )
{
	if ( initialized )
		return;

	vgui2Module = Sys_LoadModule( "vgui2." OS_LIB_EXT );
	chromeModule = Sys_LoadModule( "chromehtml." OS_LIB_EXT );

	factoryList[numFactories++] = factories[0];
	factoryList[numFactories++] = Sys_GetFactory( vgui2Module );
	factoryList[numFactories++] = factories[1];
	factoryList[numFactories++] = Sys_GetFactory( chromeModule );

	if ( factories[2] != nullptr )
	{
		factoryList[numFactories++] = factories[2];
		clientVGUI = (IClientVGUI *)factoryList[4]( VCLIENTVGUI_INTERFACE_VERSION, nullptr );
	}

	vgui2::InitializeVGui2Interfaces( "BaseUI", factoryList, numFactories );
	baseUISurface = (BaseUISurface *)vgui2::surface();

	initialized = 1;
}

void BaseUI::Start( IEngineSurface *engineSurface, int interfaceVersion )
{
	if ( !initialized )
		return;

	rootPanel = new RootPanel( nullptr, "RootPanel" );
	rootPanel->SetCursor( vgui2::dc_none );
	rootPanel->SetBounds( 0, 0, 40, 30 );
	rootPanel->SetPaintBorderEnabled( false );
	rootPanel->SetPaintBackgroundEnabled( false );
	rootPanel->SetPaintEnabled( false );
	rootPanel->SetVisible( true );
	rootPanel->SetZPos( 0 );

	auto chromeController = (IHTMLChromeController *)factoryList[3]( CHROME_HTML_CONTROLLER_INTERFACE_VERSION, nullptr );
	baseUISurface->Init( rootPanel->GetVPanel(), engineSurface, chromeController );
	baseUISurface->SetIgnoreMouseVisCalc( true );

	vgui2::scheme()->LoadSchemeFromFile( "resource/trackerscheme.res", "BaseUI" );

	vgui2::localize()->AddFile( vgui2::filesystem(), "resource/valve_%language%.txt" );

	char szMod[32];
	vgui2::system()->GetCommandLineParamValue( "-game", szMod, sizeof( szMod ) );
	char szLocalizeFile[260];
	snprintf( szLocalizeFile, sizeof( szLocalizeFile ), "resource/%s_%%language%%.txt", szMod );
	szLocalizeFile[sizeof( szLocalizeFile ) - 1] = '\0';
	vgui2::localize()->AddFile( vgui2::filesystem(), szLocalizeFile );

	vgui2::ivgui()->Start();
	vgui2::ivgui()->SetSleep( false );

	if ( clientVGUI )
		clientVGUI->Initialize( factoryList, numFactories );

	rootPanel->SetScheme( "ClientScheme" );

	if ( clientVGUI )
	{
		clientVGUI->Start();
		clientVGUI->SetParent( rootPanel->GetVPanel() );
	}

	int wide, tall;
	vgui2::surface()->GetScreenSize( wide, tall );
	rootPanel->SetBounds( 0, 0, wide, tall );

	baseUISurface->SetIgnoreMouseVisCalc( false );
}

void BaseUI::Shutdown()
{
	if ( !initialized )
		return;

	vgui2::ivgui()->RunFrame();
	vgui2::ivgui()->Shutdown();

	if ( clientVGUI )
	{
		clientVGUI->Shutdown();
		clientVGUI = nullptr;
	}

	vgui2::system()->SaveUserConfigFile();
	vgui2::surface()->Shutdown();

	Sys_UnloadModule( chromeModule );
	chromeModule = nullptr;
	Sys_UnloadModule( vgui2Module );
	vgui2Module = nullptr;
}

int BaseUI::Key_Event( int down, int keynum, const char *pszCurrentBinding )
{
	if ( !initialized )
		return 0;

	return vgui2::surface()->NeedKBInput();
}

void BaseUI::CallEngineSurfaceAppHandler( void *event, void *userData )
{
	vgui2::ivgui()->DPrintf( "BaseUI::CallEngineSurfaceAppHandler called\n" );
}

void BaseUI::Paint( int x, int y, int right, int bottom )
{
	if ( !initialized )
		return;

	vgui2::VPANEL panel = vgui2::surface()->GetEmbeddedPanel();
	if ( panel == NULL )
		return;

	vgui2::ivgui()->RunFrame();
	baseUISurface->SetScreenBounds( x, y, right - x, bottom - y );
	rootPanel->SetBounds( 0, 0, right, bottom );
	rootPanel->Repaint();
	vgui2::surface()->PaintTraverse( panel );
}

void BaseUI::HideGameUI()
{
}

void BaseUI::ActivateGameUI()
{
}

void BaseUI::HideConsole()
{
}

void BaseUI::ShowConsole()
{
}
