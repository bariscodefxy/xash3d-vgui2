#ifndef VGUI2INTERFACES_H
#define VGUI2INTERFACES_H

#include "interface.h"
#include "IKeyValues.h"
#include "IVGui.h"
#include "ILocalize.h"
#include "FileSystem.h"
#include "IPanel.h"
#include "ISurface.h"
#include "IScheme.h"
#include "ISystem.h"
#include "IInput.h"
#include "IInputInternal.h"

IKeyValues *keyvalues();

namespace vgui2
{

IVGui *ivgui();
ILocalize *localize();
IFileSystem *filesystem();
IPanel *ipanel();
ISurface *surface();
ISchemeManager *scheme();
ISystem *system();
IInput *input();
IInputInternal *inputinternal();

bool InitializeVGui2Interfaces(const char *moduleName, CreateInterfaceFn *factories, int factoryCount);
const char *GetModuleName();

};

#endif // VGUI2INTERFACES_H
