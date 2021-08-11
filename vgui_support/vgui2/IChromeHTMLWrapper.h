#ifndef ICHROMEHTMLWRAPPER_H
#define ICHROMEHTMLWRAPPER_H

#include "interface.h"
#include <stdint.h>

class CUtlString;
class IHTMLResponses;
class HTMLCommandBuffer_t;
class IHTMLSerializer;
class IHTMLResponses_HL1;

enum EHTMLCommands;

class IHTMLChromeController : public IBaseInterface
{
public:
    virtual bool Init(const char *pchHTMLCacheDir, const char *pchCookiePath);
    virtual void Shutdown();
    virtual bool RunFrame();
    virtual void SetWebCookie(const char *pchHostname, const char *pchKey, const char *pchValue, const char *pchPath, int nExpires);
    virtual void GetWebCookiesForURL(CUtlString *pstrValue, const char *pchURL, const char *pchName);
    virtual void SetClientBuildID(uint64_t ulBuildID);
    virtual bool BHasPendingMessages();
    virtual void CreateBrowser(IHTMLResponses *pBrowser, bool bPopupWindow, const char *pchUserAgentIdentifier);
    virtual void RemoveBrowser(IHTMLResponses *pBrowser);
    virtual void WakeThread();
    virtual HTMLCommandBuffer_t *GetFreeCommandBuffer(EHTMLCommands eCmd, int iBrowser);
    virtual void PushCommand(HTMLCommandBuffer_t *pCmd);
    virtual void SetCefThreadTargetFrameRate(uint32_t nFPS);
    virtual IHTMLSerializer *CreateSerializer(IHTMLResponses_HL1 *pResponseTarget);
};

#define CHROME_HTML_CONTROLLER_INTERFACE_VERSION "ChromeHTML_Controller_001"

#endif // ICHROMEHTMLWRAPPER_H
