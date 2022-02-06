/*
vgui_surf.h - vgui surface header
Copyright (C) 2022 FWGS

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

#ifndef VGUI_SURF_H
#define VGUI_SURF_H

#include "vgui_api.h"

#include <VGUI_Font.h>
#include <VGUI_Panel.h>
#include <VGUI_Cursor.h>
#include <VGUI_SurfaceBase.h>

#include <VGuiVertex.h>

#ifdef CreateFont
#undef CreateFont
#endif

namespace vgui_support
{

extern vguiapi_t *g_api;

struct PaintStack
{
	int iTranslateX;
	int iTranslateY;
	int iScissorLeft;
	int iScissorRight;
	int iScissorTop;
	int iScissorBottom;
};

class CEngineSurface : public vgui::SurfaceBase
{
private:
	// point translation for current panel
	int _translateX;
	int _translateY;

	// the size of the window to draw into
	int _surfaceExtents[4];

	void SetupPaintState( const PaintStack *paintState );
	void InitVertex( vpoint_t &vertex, int x, int y, float u, float v );

public:
	CEngineSurface( vgui::Panel *embeddedPanel );
	~CEngineSurface();

public:
	virtual vgui::Panel *getEmbeddedPanel( void );
	virtual bool setFullscreenMode( int wide, int tall, int bpp );
	virtual void setWindowedMode( void );
	virtual void setTitle( const char *title ) { }
	virtual void createPopup( vgui::Panel *embeddedPanel ) { }
	virtual bool isWithin( int x, int y ) { return true; }
	virtual bool hasFocus( void );
	// now it's not abstract class, yay
	virtual void GetMousePos( int &x, int &y )
	{
		g_api->GetCursorPos( &x, &y );
	}
	void drawPrintChar( int x, int y, int wide, int tall, float s0, float t0, float s1, float t1, int color[], bool additive );

protected:
	virtual int createNewTextureID( void );
	virtual void drawSetColor( int r, int g, int b, int a );
	virtual void drawSetTextColor( int r, int g, int b, int a );
	virtual void drawFilledRect( int x0, int y0, int x1, int y1 );
	virtual void drawOutlinedRect( int x0, int y0, int x1, int y1 );
	virtual void drawSetTextFont( vgui::Font *font );
	virtual void drawSetTextPos( int x, int y );
	virtual void drawPrintText( const char *text, int textLen );
	virtual void drawSetTextureRGBA( int id, const char *rgba, int wide, int tall );
	virtual void drawSetTexture( int id );
	virtual void drawTexturedRect( int x0, int y0, int x1, int y1 );
	virtual bool createPlat( void ) { return false; }
	virtual bool recreateContext( void ) { return false; }
	virtual void setCursor( vgui::Cursor *cursor );
	virtual void pushMakeCurrent( vgui::Panel *panel, bool useInsets );
	virtual void popMakeCurrent( vgui::Panel *panel );

	// not used in engine instance
	virtual void enableMouseCapture( bool state ) { }
	virtual void invalidate( vgui::Panel *panel ) { }
	virtual void setAsTopMost( bool state ) { }
	virtual void applyChanges( void ) { }
	virtual void swapBuffers( void ) { }

public:
	// IEngineSurface methods
	virtual void PushMakeCurrent( int insets[4], int absExtents[4], int clipRect[4] );
	virtual void PopMakeCurrent();
	virtual void DrawSetColor( int r, int g, int b, int a );
	virtual void DrawFilledRect( int x0, int y0, int x1, int y1 );
	virtual void DrawOutlinedRect( int x0, int y0, int x1, int y1 );
	virtual void DrawSetTextFont( int font );
	virtual void DrawSetTextColor( int r, int g, int b, int a );
	virtual void DrawGetTextColor( int &r, int &g, int &b, int &a );
	virtual void DrawSetTextPos( int x, int y );
	virtual void DrawGetTextPos( int &x, int &y );
	virtual void DrawPrintText( const wchar_t *text, int textLen );
	virtual void DrawUnicodeChar( wchar_t wch, bool additive );
	virtual void DrawSetTextureFile( int id, const char *filename );
	virtual void DrawSetTextureRGBA( int id, const unsigned char *rgba, int wide, int tall );
	virtual void DrawSetTexture( int id );
	virtual void DrawGetTextureSize( int id, int &wide, int &tall );
	virtual void DrawTexturedRect( int x0, int y0, int x1, int y1 );
	virtual void DrawTexturedPolygon( vgui2::VGuiVertex *pVertices, int n );
	virtual int CreateNewTextureID();
	virtual bool DeleteTextureByID( int id );
	virtual void DrawUpdateRegionTextureBGRA( int nTextureID, int x, int y, const unsigned char *pchData, int wide, int tall );
	virtual void DrawSetTextureBGRA( int id, const unsigned char *bgra, int wide, int tall );
	virtual int CreateFont();
	virtual bool AddGlyphSetToFont( int font, const char *fontName, int tall, int weight, bool italic, bool underline, bool strikeout, bool symbol );
	virtual bool AddCustomFontFile( const char *fontFileName );
	virtual int GetFontTall( int font );
	virtual void GetCharABCwide( int font, int ch, int &a, int &b, int &c );
	virtual int GetCharacterWidth( int font, int ch );
	virtual void GetTextSize( int font, const wchar_t *text, int &wide, int &tall );
	virtual void GetScreenSize( int &wide, int &tall );
	virtual void SetCursor( int cursor );
	virtual int GetCursor();
	virtual void GetCursorPos( int &x, int &y );

protected:
	int _drawTextPos[2];
	int _drawColor[4];
	int _drawTextColor[4];
	int _currentTexture;
	friend class vgui::App;
	friend class vgui::Panel;
	friend class BaseUISurface;
};

} // namespace vgui_support

#define IEngineSurface vgui_support::CEngineSurface

#endif // VGUI_SURF_H
