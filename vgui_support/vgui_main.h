/*
vgui_main.h - vgui main header
Copyright (C) 2011 Uncle Mike

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

In addition, as a special exception, the author gives permission
to link the code of this program with VGUI library developed by
Valve, L.L.C ("Valve"). You must obey the GNU General Public License
in all respects for all of the code used other than VGUI library.
If you modify this file, you may extend this exception to your
version of the file, but you are not obligated to do so. If
you do not wish to do so, delete this exception statement
from your version.

*/
#ifndef VGUI_MAIN_H
#define VGUI_MAIN_H

#ifdef _WIN32
#include <windows.h>
#else
#include <string.h>
#endif

#include <assert.h>

#include <VGUI.h>
#include <VGUI_App.h>
#include <VGUI_Font.h>
#include <VGUI_Panel.h>
#include <VGUI_Cursor.h>
#include <VGUI_SurfaceBase.h>
#include <VGUI_InputSignal.h>
#include <VGUI_MouseCode.h>
#include <VGUI_KeyCode.h>

#include "vgui_surf.h"

namespace vgui_support
{

using namespace vgui;

// initialize VGUI::App as external (part of engine)
class CEngineApp : public App
{
public:
	CEngineApp( bool externalMain = true ) : App( externalMain ) { }
	virtual void main( int argc, char *argv[] ) { } // stub
};

//
// vgui_input.cpp
//
void *VGui_GetPanel( void );
void VGui_Paint( void );
void VGUI_Mouse( VGUI_MouseAction action, int code );
void VGUI_Key( VGUI_KeyAction action, VGUI_KeyCode code );
void VGUI_MouseMove( int x, int y );
//
// vgui_clip.cpp
//
void EnableScissor( qboolean enable );
void SetScissorRect( int left, int top, int right, int bottom );
qboolean ClipRect( const vpoint_t &inUL, const vpoint_t &inLR, vpoint_t *pOutUL, vpoint_t *pOutLR );

extern CEngineSurface *surface;
extern Panel *root;
} // namespace vgui_support
using namespace vgui_support;
#endif //VGUI_MAIN_H
