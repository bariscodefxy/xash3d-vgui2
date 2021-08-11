#ifndef IENGINESURFACE_H
#define IENGINESURFACE_H

#ifdef CreateFont
#undef CreateFont
#endif

class IEngineSurface
{
public:
	enum EFontFlags
	{
		FONTFLAG_NONE,
		FONTFLAG_ITALIC			= 0x001,
		FONTFLAG_UNDERLINE		= 0x002,
		FONTFLAG_STRIKEOUT		= 0x004,
		FONTFLAG_SYMBOL			= 0x008,
	};

	virtual void PushMakeCurrent(int insets[4], int absExtents[4], int clipRect[4]) = 0;
	virtual void PopMakeCurrent() = 0;
	virtual void DrawSetColor(int r, int g, int b, int a) = 0;
	virtual void DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawSetTextFont(int font) = 0;
	virtual void DrawSetTextColor(int r, int g, int b, int a) = 0;
	virtual void DrawGetTextColor(int &r, int &g, int &b, int &a) = 0;
	virtual void DrawSetTextPos(int x, int y) = 0;
	virtual void DrawGetTextPos(int &x, int &y) = 0;
	virtual void DrawPrintText(const wchar_t *text, int textLen) = 0;
	virtual void DrawUnicodeChar(wchar_t wch, bool additive) = 0;
	virtual void DrawSetTextureFile(int id, const char *filename) = 0;
	virtual void DrawSetTextureRGBA(int id, const unsigned char *rgba, int wide, int tall) = 0;
	virtual void DrawSetTexture(int id) = 0;
	virtual void DrawGetTextureSize(int id, int &wide, int &tall) = 0;
	virtual void DrawTexturedRect(int x0, int y0, int x1, int y1) = 0;
	virtual int CreateNewTextureID() = 0;
    virtual bool DeleteTextureByID(int id) = 0;
    virtual void DrawUpdateRegionTextureBGRA(int nTextureID, int x, int y, const unsigned char *pchData, int wide, int tall) = 0;
    virtual void DrawSetTextureBGRA(int id, const unsigned char *bgra, int wide, int tall) = 0;
    virtual int CreateFont() = 0;
    virtual bool AddGlyphSetToFont(int font, const char *fontName, int tall, int weight, int flags) = 0;
    virtual bool AddCustomFontFile(const char *fontFileName) = 0;
	virtual int GetFontTall(int font) = 0;
    virtual void GetCharABCwide(int font, int ch, int &a, int &b, int &c) = 0;
    virtual int GetCharacterWidth(int font, int ch) = 0;
    virtual void GetTextSize(int font, const wchar_t *text, int &wide, int &tall) = 0;
	virtual void GetScreenSize(int &wide, int &tall) = 0;
	virtual void SetCursor(int cursor) = 0;
	virtual int GetCursor() = 0;
	virtual void GetCursorPos(int &x, int &y) = 0;
};

#endif // IENGINESURFACE_H
