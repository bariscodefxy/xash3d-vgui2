#include "IGameUIFuncs.h"
#include <vgui_api.h>

namespace vgui_support
{
extern vguiapi_t *g_api;
};

class GameUIFuncs : public IGameUIFuncs
{
public:
    virtual bool IsKeyDown(const char *keyname, bool &isdown);
    virtual const char *Key_NameForKey(int keynum);
    virtual const char *Key_BindingForKey(int keynum);
    virtual vgui2::KeyCode GetVGUI2KeyCodeForBind(const char *bind);
    virtual void GetVideoModes(vmode_t **liststart, int *count);
    virtual void GetCurrentVideoMode(int *wide, int *tall, int *bpp);
    virtual void GetCurrentRenderer(char *name, int namelen, int *windowed, int *hdmodels, int *addons_folder, int *vid_level);
    virtual bool IsConnectedToVACSecureServer();
    virtual int Key_KeyStringToKeyNum(const char *pchKey);
};

EXPOSE_SINGLE_INTERFACE(GameUIFuncs, IGameUIFuncs, VENGINE_GAMEUIFUNCS_VERSION);

bool GameUIFuncs::IsKeyDown(const char *keyname, bool &isdown)
{
    isdown = false;
    return false;
}

const char *GameUIFuncs::Key_NameForKey(int keynum)
{
    return "";
}

const char *GameUIFuncs::Key_BindingForKey(int keynum)
{
    return "";
}

vgui2::KeyCode GameUIFuncs::GetVGUI2KeyCodeForBind(const char *bind)
{
    return (vgui2::KeyCode)(vgui_support::g_api->KeyForBind(bind) + 1);
}

void GameUIFuncs::GetVideoModes(vmode_t **liststart, int *count)
{

}

void GameUIFuncs::GetCurrentVideoMode(int *wide, int *tall, int *bpp)
{

}

void GameUIFuncs::GetCurrentRenderer(char *name, int namelen, int *windowed, int *hdmodels, int *addons_folder, int *vid_level)
{

}

bool GameUIFuncs::IsConnectedToVACSecureServer()
{
    return false;
}

int GameUIFuncs::Key_KeyStringToKeyNum(const char *pchKey)
{
    return 0;
}
