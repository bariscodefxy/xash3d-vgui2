#include "IBaseUI.h"
#include "VGui2Interfaces.h"
#include "IEngineSurface.h"

#include <vgui_api.h>

static CSysModule *fileSystemModule;
static IFileSystem *fileSystem;
static IBaseUI *baseUI;

void VGui2_Startup()
{
    if (baseUI != nullptr)
        return;

    fileSystemModule = Sys_LoadModule("cstrike/filesystem_stdio.dll");    
    CreateInterfaceFn factories[2];
    factories[0] = Sys_GetFactoryThis();
    factories[1] = Sys_GetFactory(fileSystemModule);

    fileSystem = (IFileSystem *)factories[1](FILESYSTEM_INTERFACE_VERSION, nullptr);
    fileSystem->Mount();
    fileSystem->AddSearchPath(".", "ROOT");
    fileSystem->AddSearchPath(".", "BASE");
	fileSystem->AddSearchPath("platform", "PLATFORM");
	fileSystem->AddSearchPath("cstrike", "GAME");
	fileSystem->AddSearchPath("cstrike", "GAMECONFIG");
	fileSystem->AddSearchPath("valve", "GAME_FALLBACK");

    baseUI = (IBaseUI *)factories[0](BASEUI_INTERFACE_VERSION, nullptr);
    baseUI->Initialize(factories, 2);
}

void VGui2_PostClientInit(IEngineSurface *engineSurface)
{
    baseUI->Start(engineSurface, 0);
}

void VGui2_Shutdown()
{
    if (baseUI == nullptr)
        return;

    baseUI->Shutdown();
    baseUI = nullptr;
    fileSystem->Unmount();
    fileSystem = nullptr;
    Sys_UnloadModule(fileSystemModule);
    fileSystemModule = nullptr;
}

void VGui2_Paint()
{
    if (baseUI == nullptr)
        return;

    int wide, tall;
    vgui2::surface()->GetScreenSize(wide, tall);
    baseUI->Paint(0, 0, wide, tall);
}

int VGui2_DrawCharacter(int x, int y, int ch, int r, int g, int b, unsigned int font, qboolean additive)
{
    vgui2::surface()->PushMakeCurrent(vgui2::surface()->GetEmbeddedPanel(), false);
    vgui2::surface()->DrawSetTextFont(font);
    vgui2::surface()->DrawSetTextPos(x, y);
    vgui2::surface()->DrawSetTextColor(r, g, b, 255);

    if (additive)
        vgui2::surface()->DrawUnicodeCharAdd(ch);
    else
        vgui2::surface()->DrawUnicodeChar(ch);

    vgui2::surface()->DrawFlushText();
    int width = vgui2::surface()->GetCharacterWidth(font, ch);
    vgui2::surface()->PopMakeCurrent(vgui2::surface()->GetEmbeddedPanel());
    return width;
}

void VGui2_Key(VGUI_KeyAction action, VGUI_KeyCode code)
{
    if (baseUI == nullptr)
        return;

    if (!baseUI->Key_Event(action == KA_PRESSED, code + 1, ""))
        return;

	switch (action)
	{
    case KA_PRESSED:
        vgui2::inputinternal()->InternalKeyCodePressed((vgui2::KeyCode)(code + 1));
        vgui2::inputinternal()->InternalKeyCodeTyped((vgui2::KeyCode)(code + 1));
        vgui2::inputinternal()->InternalKeyTyped(vgui2::system()->KeyCode_VGUIToVirtualKey((vgui2::KeyCode)(code + 1)));
        break;
    case KA_RELEASED:
        vgui2::inputinternal()->InternalKeyCodeReleased((vgui2::KeyCode)(code + 1));
        break;
    case KA_TYPED:
        break;
	}
}

void VGui2_Mouse(VGUI_MouseAction action, int code)
{
    if (baseUI == nullptr)
        return;

    if (!vgui2::surface()->IsCursorVisible())
        return;

	switch( action )
	{
    case MA_PRESSED:
        vgui2::inputinternal()->InternalMousePressed((vgui2::MouseCode)code);
        break;
    case MA_RELEASED:
        vgui2::inputinternal()->InternalMouseReleased((vgui2::MouseCode)code);
        break;
    case MA_DOUBLE:
        vgui2::inputinternal()->InternalMouseDoublePressed((vgui2::MouseCode)code);
        break;
    case MA_WHEEL:
        vgui2::inputinternal()->InternalMouseWheeled(code);
        break;
	}
}

void VGui2_MouseMove(int x, int y)
{
    if (baseUI == nullptr)
        return;

    vgui2::inputinternal()->InternalCursorMoved(x, y);
}

qboolean VGui2_NeedMouse()
{
    return vgui2::surface()->IsCursorVisible();
}

qboolean VGui2_NeedKeyboard()
{
    return vgui2::surface()->NeedKBInput();
}
