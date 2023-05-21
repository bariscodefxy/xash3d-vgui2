#include "port.h"

#include "vgui_surf.h"

#include "IBaseUI.h"
#include "VGui2Interfaces.h"

static CSysModule *fileSystemModule;
static IFileSystem *fileSystem;
static IBaseUI *baseUI;

void VGui2_Startup( const char *clientlib, IEngineSurface *engineSurface )
{
	if ( baseUI != nullptr )
		return;

	if ( clientlib == nullptr )
		return;

	fileSystemModule = Sys_LoadModule( "filesystem_stdio." OS_LIB_EXT );
	auto fileSystemFactory = Sys_GetFactory( fileSystemModule );
	fileSystem = (IFileSystem *)fileSystemFactory( FILESYSTEM_INTERFACE_VERSION, nullptr );

	char szClientLib[MAX_OSPATH];
	fileSystem->GetLocalPath( clientlib, szClientLib, sizeof( szClientLib ) );
	CSysModule *clientModule = Sys_LoadModule( szClientLib );

	CreateInterfaceFn factories[3];
	factories[0] = Sys_GetFactoryThis();
	factories[1] = fileSystemFactory;
	factories[2] = Sys_GetFactory( clientModule );

	baseUI = (IBaseUI *)factories[0]( BASEUI_INTERFACE_VERSION, nullptr );
	baseUI->Initialize( factories, 3 );
	baseUI->Start( engineSurface, 0 );
}

void VGui2_Shutdown()
{
	if ( baseUI == nullptr )
		return;

	baseUI->Shutdown();
	baseUI = nullptr;
	Sys_UnloadModule( fileSystemModule );
	fileSystemModule = nullptr;
	fileSystem = nullptr;
}

void VGui2_Paint()
{
	if ( baseUI == nullptr )
		return;

	int wide, tall;
	vgui2::surface()->GetScreenSize( wide, tall );
	baseUI->Paint( 0, 0, wide, tall );
}

int VGui2_DrawCharacter( int x, int y, int ch, int r, int g, int b, unsigned int font, qboolean additive )
{
	vgui2::surface()->PushMakeCurrent( vgui2::surface()->GetEmbeddedPanel(), false );
	vgui2::surface()->DrawSetTextFont( font );
	vgui2::surface()->DrawSetTextPos( x, y );
	vgui2::surface()->DrawSetTextColor( r, g, b, 255 );

	if ( additive )
		vgui2::surface()->DrawUnicodeCharAdd( ch );
	else
		vgui2::surface()->DrawUnicodeChar( ch );

	vgui2::surface()->DrawFlushText();
	int width = vgui2::surface()->GetCharacterWidth( font, ch );
	vgui2::surface()->PopMakeCurrent( vgui2::surface()->GetEmbeddedPanel() );
	return width;
}

void VGui2_Key( VGUI_KeyAction action, VGUI_KeyCode code )
{
	if ( baseUI == nullptr )
		return;

	if ( !baseUI->Key_Event( action == KA_PRESSED, code + 1, "" ) )
		return;

	switch ( action )
	{
	case KA_PRESSED:
		vgui2::inputinternal()->InternalKeyCodePressed( ( vgui2::KeyCode )( code + 1 ) );
		vgui2::inputinternal()->InternalKeyCodeTyped( ( vgui2::KeyCode )( code + 1 ) );
		vgui2::inputinternal()->InternalKeyTyped( vgui2::system()->KeyCode_VGUIToVirtualKey( ( vgui2::KeyCode )( code + 1 ) ) );
		break;
	case KA_RELEASED:
		vgui2::inputinternal()->InternalKeyCodeReleased( ( vgui2::KeyCode )( code + 1 ) );
		break;
	case KA_TYPED:
		break;
	}
}

void VGui2_Mouse( VGUI_MouseAction action, int code )
{
	if ( baseUI == nullptr )
		return;

	if ( !vgui2::surface()->IsCursorVisible() )
		return;

	switch ( action )
	{
	case MA_PRESSED:
		vgui2::inputinternal()->InternalMousePressed( (vgui2::MouseCode)code );
		break;
	case MA_RELEASED:
		vgui2::inputinternal()->InternalMouseReleased( (vgui2::MouseCode)code );
		break;
	case MA_DOUBLE:
		vgui2::inputinternal()->InternalMouseDoublePressed( (vgui2::MouseCode)code );
		break;
	case MA_WHEEL:
		vgui2::inputinternal()->InternalMouseWheeled( code );
		break;
	}
}

void VGui2_MouseMove( int x, int y )
{
	if ( baseUI == nullptr )
		return;

	vgui2::inputinternal()->InternalCursorMoved( x, y );
}

qboolean VGui2_NeedKeyboard()
{
	vgui2::surface()->CalculateMouseVisible();
	return vgui2::surface()->NeedKBInput();
}
