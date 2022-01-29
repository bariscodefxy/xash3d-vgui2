#include <cdll_int.h>

typedef int (*INITIALIZE_FUNC)	( struct cl_enginefuncs_s*, int );
typedef void (*HUD_INIT_FUNC)		( void );
typedef int (*HUD_VIDINIT_FUNC)	( void );
typedef int (*HUD_REDRAW_FUNC)	( float, int );
typedef int (*HUD_UPDATECLIENTDATA_FUNC) ( struct client_data_s*, float );
typedef void (*HUD_RESET_FUNC)    ( void );
typedef void (*HUD_CLIENTMOVE_FUNC)( struct playermove_s *ppmove, qboolean server );
typedef void (*HUD_CLIENTMOVEINIT_FUNC)( struct playermove_s *ppmove );
typedef char (*HUD_TEXTURETYPE_FUNC)( char *name );
typedef void (*HUD_IN_ACTIVATEMOUSE_FUNC) ( void );
typedef void (*HUD_IN_DEACTIVATEMOUSE_FUNC)		( void );
typedef void (*HUD_IN_MOUSEEVENT_FUNC)		( int mstate );
typedef void (*HUD_IN_CLEARSTATES_FUNC)		( void );
typedef void (*HUD_IN_ACCUMULATE_FUNC ) ( void );
typedef void (*HUD_CL_CREATEMOVE_FUNC)		( float frametime, struct usercmd_s *cmd, int active );
typedef int (*HUD_CL_ISTHIRDPERSON_FUNC) ( void );
typedef void (*HUD_CL_GETCAMERAOFFSETS_FUNC )( float *ofs );
typedef struct kbutton_s * (*HUD_KB_FIND_FUNC) ( const char *name );
typedef void ( *HUD_CAMTHINK_FUNC )( void );
typedef void ( *HUD_CALCREF_FUNC ) ( struct ref_params_s *pparams );
typedef int	 ( *HUD_ADDENTITY_FUNC ) ( int type, struct cl_entity_s *ent, const char *modelname );
typedef void ( *HUD_CREATEENTITIES_FUNC ) ( void );
typedef void ( *HUD_DRAWNORMALTRIS_FUNC ) ( void );
typedef void ( *HUD_DRAWTRANSTRIS_FUNC ) ( void );
typedef void ( *HUD_STUDIOEVENT_FUNC ) ( const struct mstudioevent_s *event, const struct cl_entity_s *entity );
typedef void ( *HUD_POSTRUNCMD_FUNC ) ( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );
typedef void ( *HUD_SHUTDOWN_FUNC ) ( void );
typedef void ( *HUD_TXFERLOCALOVERRIDES_FUNC )( struct entity_state_s *state, const struct clientdata_s *client );
typedef void ( *HUD_PROCESSPLAYERSTATE_FUNC )( struct entity_state_s *dst, const struct entity_state_s *src );
typedef void ( *HUD_TXFERPREDICTIONDATA_FUNC ) ( struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd );
typedef void ( *HUD_DEMOREAD_FUNC ) ( int size, unsigned char *buffer );
typedef int ( *HUD_CONNECTIONLESS_FUNC )( const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size );
typedef	int	( *HUD_GETHULLBOUNDS_FUNC ) ( int hullnumber, float *mins, float *maxs );
typedef void (*HUD_FRAME_FUNC)		( double );
typedef int (*HUD_KEY_EVENT_FUNC ) ( int eventcode, int keynum, const char *pszCurrentBinding );
typedef void (*HUD_TEMPENTUPDATE_FUNC) ( double frametime, double client_time, double cl_gravity, struct tempent_s **ppTempEntFree, struct tempent_s **ppTempEntActive, 	int ( *Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ),	void ( *Callback_TempEntPlaySound )( struct tempent_s *pTemp, float damp ) );
typedef struct cl_entity_s *(*HUD_GETUSERENTITY_FUNC ) ( int index );
typedef void (*HUD_VOICESTATUS_FUNC)(int entindex, qboolean bTalking);
typedef void (*HUD_DIRECTORMESSAGE_FUNC)( int iSize, void *pbuf );
typedef int ( *HUD_STUDIO_INTERFACE_FUNC )( int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio );
typedef void (*HUD_CHATINPUTPOSITION_FUNC)( int *x, int *y );
typedef int (*HUD_GETPLAYERTEAM)(int iplayer);
typedef void *(*CLIENTFACTORY)(); // this should be CreateInterfaceFn but that means including interface.h
									// which is a C++ file and some of the client files a C only... 
									// so we return a void * which we then do a typecast on later.


// Pointers to the exported client functions themselves
typedef struct
{
	INITIALIZE_FUNC						pInitFunc;
	HUD_INIT_FUNC						pHudInitFunc;
	HUD_VIDINIT_FUNC					pHudVidInitFunc;
	HUD_REDRAW_FUNC						pHudRedrawFunc;
	HUD_UPDATECLIENTDATA_FUNC			pHudUpdateClientDataFunc;
	HUD_RESET_FUNC						pHudResetFunc;
	HUD_CLIENTMOVE_FUNC					pClientMove;
	HUD_CLIENTMOVEINIT_FUNC				pClientMoveInit;
	HUD_TEXTURETYPE_FUNC				pClientTextureType;
	HUD_IN_ACTIVATEMOUSE_FUNC			pIN_ActivateMouse;
	HUD_IN_DEACTIVATEMOUSE_FUNC			pIN_DeactivateMouse;
	HUD_IN_MOUSEEVENT_FUNC				pIN_MouseEvent;
	HUD_IN_CLEARSTATES_FUNC				pIN_ClearStates;
	HUD_IN_ACCUMULATE_FUNC				pIN_Accumulate;
	HUD_CL_CREATEMOVE_FUNC				pCL_CreateMove;
	HUD_CL_ISTHIRDPERSON_FUNC			pCL_IsThirdPerson;
	HUD_CL_GETCAMERAOFFSETS_FUNC		pCL_GetCameraOffsets;
	HUD_KB_FIND_FUNC					pFindKey;
	HUD_CAMTHINK_FUNC					pCamThink;
	HUD_CALCREF_FUNC					pCalcRefdef;
	HUD_ADDENTITY_FUNC					pAddEntity;
	HUD_CREATEENTITIES_FUNC				pCreateEntities;
	HUD_DRAWNORMALTRIS_FUNC				pDrawNormalTriangles;
	HUD_DRAWTRANSTRIS_FUNC				pDrawTransparentTriangles;
	HUD_STUDIOEVENT_FUNC				pStudioEvent;
	HUD_POSTRUNCMD_FUNC					pPostRunCmd;
	HUD_SHUTDOWN_FUNC					pShutdown;
	HUD_TXFERLOCALOVERRIDES_FUNC		pTxferLocalOverrides;
	HUD_PROCESSPLAYERSTATE_FUNC			pProcessPlayerState;
	HUD_TXFERPREDICTIONDATA_FUNC		pTxferPredictionData;
	HUD_DEMOREAD_FUNC					pReadDemoBuffer;
	HUD_CONNECTIONLESS_FUNC				pConnectionlessPacket;
	HUD_GETHULLBOUNDS_FUNC				pGetHullBounds;
	HUD_FRAME_FUNC						pHudFrame;
	HUD_KEY_EVENT_FUNC					pKeyEvent;
	HUD_TEMPENTUPDATE_FUNC				pTempEntUpdate;
	HUD_GETUSERENTITY_FUNC				pGetUserEntity;
	HUD_VOICESTATUS_FUNC				pVoiceStatus;		// Possibly null on old client dlls.
	HUD_DIRECTORMESSAGE_FUNC			pDirectorMessage;	// Possibly null on old client dlls.
	HUD_STUDIO_INTERFACE_FUNC			pStudioInterface;	// Not used by all clients
	HUD_CHATINPUTPOSITION_FUNC			pChatInputPosition;	// Not used by all clients
	HUD_GETPLAYERTEAM					pGetPlayerTeam; // Not used by all clients
	CLIENTFACTORY						pClientFactory;
} cldll_func_t;

// Function type declarations for client destination functions
typedef void (*DST_INITIALIZE_FUNC)	( struct cl_enginefuncs_s**, int *);
typedef void (*DST_HUD_INIT_FUNC)		( void );
typedef void (*DST_HUD_VIDINIT_FUNC)	( void );
typedef void (*DST_HUD_REDRAW_FUNC)	( float*, int* );
typedef void (*DST_HUD_UPDATECLIENTDATA_FUNC) ( struct client_data_s**, float* );
typedef void (*DST_HUD_RESET_FUNC)    ( void );
typedef void (*DST_HUD_CLIENTMOVE_FUNC)( struct playermove_s **, qboolean * );
typedef void (*DST_HUD_CLIENTMOVEINIT_FUNC)( struct playermove_s ** );
typedef void (*DST_HUD_TEXTURETYPE_FUNC)( char ** );
typedef void (*DST_HUD_IN_ACTIVATEMOUSE_FUNC) ( void );
typedef void (*DST_HUD_IN_DEACTIVATEMOUSE_FUNC)		( void );
typedef void (*DST_HUD_IN_MOUSEEVENT_FUNC)		( int * );
typedef void (*DST_HUD_IN_CLEARSTATES_FUNC)		( void );
typedef void (*DST_HUD_IN_ACCUMULATE_FUNC ) ( void );
typedef void (*DST_HUD_CL_CREATEMOVE_FUNC)		( float *, struct usercmd_s **, int * );
typedef void (*DST_HUD_CL_ISTHIRDPERSON_FUNC) ( void );
typedef void (*DST_HUD_CL_GETCAMERAOFFSETS_FUNC )( float ** );
typedef void (*DST_HUD_KB_FIND_FUNC) ( const char ** );
typedef void (*DST_HUD_CAMTHINK_FUNC )( void );
typedef void (*DST_HUD_CALCREF_FUNC ) ( struct ref_params_s ** );
typedef void (*DST_HUD_ADDENTITY_FUNC ) ( int *, struct cl_entity_s **, const char ** );
typedef void (*DST_HUD_CREATEENTITIES_FUNC ) ( void );
typedef void (*DST_HUD_DRAWNORMALTRIS_FUNC ) ( void );
typedef void (*DST_HUD_DRAWTRANSTRIS_FUNC ) ( void );
typedef void (*DST_HUD_STUDIOEVENT_FUNC ) ( const struct mstudioevent_s **, const struct cl_entity_s ** );
typedef void (*DST_HUD_POSTRUNCMD_FUNC ) ( struct local_state_s **, struct local_state_s **, struct usercmd_s **, int *, double *, unsigned int * );
typedef void (*DST_HUD_SHUTDOWN_FUNC ) ( void );
typedef void (*DST_HUD_TXFERLOCALOVERRIDES_FUNC )( struct entity_state_s **, const struct clientdata_s ** );
typedef void (*DST_HUD_PROCESSPLAYERSTATE_FUNC )( struct entity_state_s **, const struct entity_state_s ** );
typedef void (*DST_HUD_TXFERPREDICTIONDATA_FUNC ) ( struct entity_state_s **, const struct entity_state_s **, struct clientdata_s **, const struct clientdata_s **, struct weapon_data_s **, const struct weapon_data_s ** );
typedef void (*DST_HUD_DEMOREAD_FUNC ) ( int *, unsigned char ** );
typedef void (*DST_HUD_CONNECTIONLESS_FUNC )( const struct netadr_s **, const char **, char **, int ** );
typedef void (*DST_HUD_GETHULLBOUNDS_FUNC ) ( int *, float **, float ** );
typedef void (*DST_HUD_FRAME_FUNC)		( double * );
typedef void (*DST_HUD_KEY_EVENT_FUNC ) ( int *, int *, const char ** );
typedef void (*DST_HUD_TEMPENTUPDATE_FUNC) ( double *, double *, double *, struct tempent_s ***, struct tempent_s ***, int ( **Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ),	void ( **Callback_TempEntPlaySound )( struct tempent_s *pTemp, float damp ) );
typedef void (*DST_HUD_GETUSERENTITY_FUNC ) ( int * );
typedef void (*DST_HUD_VOICESTATUS_FUNC)(int *, qboolean *);
typedef void (*DST_HUD_DIRECTORMESSAGE_FUNC)( int *, void ** );
typedef void (*DST_HUD_STUDIO_INTERFACE_FUNC ) ( int *, struct r_studio_interface_s ***, struct engine_studio_api_s ** );
typedef void (*DST_HUD_CHATINPUTPOSITION_FUNC)( int **, int ** );
typedef void (*DST_HUD_GETPLAYERTEAM)(int);

// Pointers to the client destination functions
typedef struct
{
	DST_INITIALIZE_FUNC						pInitFunc;
	DST_HUD_INIT_FUNC						pHudInitFunc;
	DST_HUD_VIDINIT_FUNC					pHudVidInitFunc;
	DST_HUD_REDRAW_FUNC						pHudRedrawFunc;
	DST_HUD_UPDATECLIENTDATA_FUNC			pHudUpdateClientDataFunc;
	DST_HUD_RESET_FUNC						pHudResetFunc;
	DST_HUD_CLIENTMOVE_FUNC					pClientMove;
	DST_HUD_CLIENTMOVEINIT_FUNC				pClientMoveInit;
	DST_HUD_TEXTURETYPE_FUNC				pClientTextureType;
	DST_HUD_IN_ACTIVATEMOUSE_FUNC			pIN_ActivateMouse;
	DST_HUD_IN_DEACTIVATEMOUSE_FUNC			pIN_DeactivateMouse;
	DST_HUD_IN_MOUSEEVENT_FUNC				pIN_MouseEvent;
	DST_HUD_IN_CLEARSTATES_FUNC				pIN_ClearStates;
	DST_HUD_IN_ACCUMULATE_FUNC				pIN_Accumulate;
	DST_HUD_CL_CREATEMOVE_FUNC				pCL_CreateMove;
	DST_HUD_CL_ISTHIRDPERSON_FUNC			pCL_IsThirdPerson;
	DST_HUD_CL_GETCAMERAOFFSETS_FUNC		pCL_GetCameraOffsets;
	DST_HUD_KB_FIND_FUNC					pFindKey;
	DST_HUD_CAMTHINK_FUNC					pCamThink;
	DST_HUD_CALCREF_FUNC					pCalcRefdef;
	DST_HUD_ADDENTITY_FUNC					pAddEntity;
	DST_HUD_CREATEENTITIES_FUNC				pCreateEntities;
	DST_HUD_DRAWNORMALTRIS_FUNC				pDrawNormalTriangles;
	DST_HUD_DRAWTRANSTRIS_FUNC				pDrawTransparentTriangles;
	DST_HUD_STUDIOEVENT_FUNC				pStudioEvent;
	DST_HUD_POSTRUNCMD_FUNC					pPostRunCmd;
	DST_HUD_SHUTDOWN_FUNC					pShutdown;
	DST_HUD_TXFERLOCALOVERRIDES_FUNC		pTxferLocalOverrides;
	DST_HUD_PROCESSPLAYERSTATE_FUNC			pProcessPlayerState;
	DST_HUD_TXFERPREDICTIONDATA_FUNC		pTxferPredictionData;
	DST_HUD_DEMOREAD_FUNC					pReadDemoBuffer;
	DST_HUD_CONNECTIONLESS_FUNC				pConnectionlessPacket;
	DST_HUD_GETHULLBOUNDS_FUNC				pGetHullBounds;
	DST_HUD_FRAME_FUNC						pHudFrame;
	DST_HUD_KEY_EVENT_FUNC					pKeyEvent;
	DST_HUD_TEMPENTUPDATE_FUNC				pTempEntUpdate;
	DST_HUD_GETUSERENTITY_FUNC				pGetUserEntity;
	DST_HUD_VOICESTATUS_FUNC				pVoiceStatus;	// Possibly null on old client dlls.
	DST_HUD_DIRECTORMESSAGE_FUNC			pDirectorMessage;	// Possibly null on old client dlls.
	DST_HUD_STUDIO_INTERFACE_FUNC			pStudioInterface;  // Not used by all clients
	DST_HUD_CHATINPUTPOSITION_FUNC			pChatInputPosition;  // Not used by all clients
	DST_HUD_GETPLAYERTEAM					pGetPlayerTeam; // Not used by all clients
} cldll_func_dst_t;

void DstINITIALIZE( struct cl_enginefuncs_s**, int *){}
void DstHUD_INIT( void ){}
void DstHUD_VIDINIT( void ){}
void DstHUD_REDRAW( float*, int* ){}
void DstHUD_UPDATECLIENTDATA( struct client_data_s**, float* ){}
void DstHUD_RESET( void ){}
void DstHUD_CLIENTMOVE( struct playermove_s **, qboolean * ){}
void DstHUD_CLIENTMOVEINIT( struct playermove_s ** ){}
void DstHUD_TEXTURETYPE( char ** ){}
void DstHUD_IN_ACTIVATEMOUSE( void ){}
void DstHUD_IN_DEACTIVATEMOUSE( void ){}
void DstHUD_IN_MOUSEEVENT( int * ){}
void DstHUD_IN_CLEARSTATES( void ){}
void DstHUD_IN_ACCUMULATE ( void ){}
void DstHUD_CL_CREATEMOVE( float *, struct usercmd_s **, int * ){}
void DstHUD_CL_ISTHIRDPERSON( void ){}
void DstHUD_CL_GETCAMERAOFFSETS ( float ** ){}
void DstHUD_KB_FIND( const char ** ){}
void DstHUD_CAMTHINK ( void ){}
void DstHUD_CALCREF ( struct ref_params_s ** ){}
void DstHUD_ADDENTITY ( int *, struct cl_entity_s **, const char ** ){}
void DstHUD_CREATEENTITIES ( void ){}
void DstHUD_DRAWNORMALTRIS ( void ){}
void DstHUD_DRAWTRANSTRIS ( void ){}
void DstHUD_STUDIOEVENT ( const struct mstudioevent_s **, const struct cl_entity_s ** ){}
void DstHUD_POSTRUNCMD ( struct local_state_s **, struct local_state_s **, struct usercmd_s **, int *, double *, unsigned int * ){}
void DstHUD_SHUTDOWN ( void ){}
void DstHUD_TXFERLOCALOVERRIDES ( struct entity_state_s **, const struct clientdata_s ** ){}
void DstHUD_PROCESSPLAYERSTATE ( struct entity_state_s **, const struct entity_state_s ** ){}
void DstHUD_TXFERPREDICTIONDATA ( struct entity_state_s **, const struct entity_state_s **, struct clientdata_s **, const struct clientdata_s **, struct weapon_data_s **, const struct weapon_data_s ** ){}
void DstHUD_DEMOREAD ( int *, unsigned char ** ){}
void DstHUD_CONNECTIONLESS ( const struct netadr_s **, const char **, char **, int ** ){}
void DstHUD_GETHULLBOUNDS ( int *, float **, float ** ){}
void DstHUD_FRAME( double * ){}
void DstHUD_KEY_EVENT ( int *, int *, const char ** ){}
void DstHUD_TEMPENTUPDATE( double *, double *, double *, struct tempent_s ***, struct tempent_s ***, int ( **Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ), void ( **Callback_TempEntPlaySound )( struct tempent_s *pTemp, float damp ) ){}
void DstHUD_GETUSERENTITY ( int * ){}
void DstHUD_VOICESTATUS(int *, qboolean *){}
void DstHUD_DIRECTORMESSAGE( int *, void ** ){}
void DstHUD_STUDIO_INTERFACE ( int *, struct r_studio_interface_s ***, struct engine_studio_api_s ** ){}
void DstHUD_CHATINPUTPOSITION( int **, int ** ){}
void DstHUD_GETPLAYERTEAM(int){}

typedef void (*PFN_LOADMOD)(char *pchModule);
typedef void (*PFN_CLOSEMOD)(void);
typedef int (*PFN_NCALL)(int ijump, int cnArg, ...);

typedef void (*PFN_GETCLDSTADDRS)(cldll_func_dst_t *pcldstAddrs);
typedef void (*PFN_GETENGDSTADDRS)(void *pengdstAddrs);
typedef void (*PFN_MODULELOADED)(void);

typedef void (*PFN_PROCESSOUTGOINGNET)(struct netchan_s *pchan, struct sizebuf_s *psizebuf);
typedef qboolean (*PFN_PROCESSINCOMINGNET)(struct netchan_s *pchan, struct sizebuf_s *psizebuf);

typedef void (*PFN_TEXTURELOAD)(char *pszName, int dxWidth, int dyHeight, char *pbData);
typedef void (*PFN_MODELLOAD)(struct model_s *pmodel, void *pvBuf);

typedef void (*PFN_FRAMEBEGIN)(void);
typedef void (*PFN_FRAMERENDER1)(void);
typedef void (*PFN_FRAMERENDER2)(void);

typedef void (*PFN_SETMODSHELPERS)(void *pmodshelpers);
typedef void (*PFN_SETMODCHELPERS)(void *pmodchelpers);
typedef void (*PFN_SETENGDATA)(void *pengdata);

typedef void (*PFN_CONNECTCLIENT)(int iPlayer);
typedef void (*PFN_RECORDIP)(unsigned int pnIP);
typedef void (*PFN_PLAYERSTATUS)(unsigned char *pbData, int cbData);

typedef void (*PFN_SETENGINEVERSION)(int nVersion);

// typedef class CMachine *(*PFN_PCMACHINE)(void);
typedef int (*PFN_PCMACHINE)(void);
typedef void (*PFN_SETIP)(int ijump);
typedef void (*PFN_EXECUTE)(void);

typedef struct modfuncs_s
{
	// Functions for the pcode interpreter
	PFN_LOADMOD m_pfnLoadMod;
	PFN_CLOSEMOD m_pfnCloseMod;
	PFN_NCALL m_pfnNCall;

	// API destination functions
	PFN_GETCLDSTADDRS m_pfnGetClDstAddrs;
	PFN_GETENGDSTADDRS m_pfnGetEngDstAddrs;

	// Miscellaneous functions
	PFN_MODULELOADED m_pfnModuleLoaded;     // Called right after the module is loaded

	// Functions for processing network traffic
	PFN_PROCESSOUTGOINGNET m_pfnProcessOutgoingNet;   // Every outgoing packet gets run through this
	PFN_PROCESSINCOMINGNET m_pfnProcessIncomingNet;   // Every incoming packet gets run through this

	// Resource functions
	PFN_TEXTURELOAD m_pfnTextureLoad;     // Called as each texture is loaded
	PFN_MODELLOAD m_pfnModelLoad;         // Called as each model is loaded

	// Functions called every frame
	PFN_FRAMEBEGIN m_pfnFrameBegin;       // Called at the beginning of each frame cycle
	PFN_FRAMERENDER1 m_pfnFrameRender1;   // Called at the beginning of the render loop
	PFN_FRAMERENDER2 m_pfnFrameRender2;   // Called at the end of the render loop

	// Module helper transfer
	PFN_SETMODSHELPERS m_pfnSetModSHelpers;
	PFN_SETMODCHELPERS m_pfnSetModCHelpers;
	PFN_SETENGDATA m_pfnSetEngData;

	// Which version of the module is this?
	int m_nVersion;

	// Miscellaneous game stuff
	PFN_CONNECTCLIENT m_pfnConnectClient;	// Called whenever a new client connects
	PFN_RECORDIP m_pfnRecordIP;				// Secure master has reported a new IP for us
	PFN_PLAYERSTATUS m_pfnPlayerStatus;		// Called whenever we receive a PlayerStatus packet

	// Recent additions
	PFN_SETENGINEVERSION m_pfnSetEngineVersion;	// 1 = patched engine

	// reserved for future expansion
	int m_nVoid2;
	int m_nVoid3;
	int m_nVoid4;
	int m_nVoid5;
	int m_nVoid6;
	int m_nVoid7;
	int m_nVoid8;
	int m_nVoid9;
} modfuncs_t;

cldll_func_dst_t dllFuncDst = {
    DstINITIALIZE,
    DstHUD_INIT,
    DstHUD_VIDINIT,
    DstHUD_REDRAW,
    DstHUD_UPDATECLIENTDATA,
    DstHUD_RESET,
    DstHUD_CLIENTMOVE,
    DstHUD_CLIENTMOVEINIT,
    DstHUD_TEXTURETYPE,
    DstHUD_IN_ACTIVATEMOUSE,
    DstHUD_IN_DEACTIVATEMOUSE,
    DstHUD_IN_MOUSEEVENT,
    DstHUD_IN_CLEARSTATES,
    DstHUD_IN_ACCUMULATE ,
    DstHUD_CL_CREATEMOVE,
    DstHUD_CL_ISTHIRDPERSON,
    DstHUD_CL_GETCAMERAOFFSETS ,
    DstHUD_KB_FIND,
    DstHUD_CAMTHINK ,
    DstHUD_CALCREF ,
    DstHUD_ADDENTITY ,
    DstHUD_CREATEENTITIES ,
    DstHUD_DRAWNORMALTRIS ,
    DstHUD_DRAWTRANSTRIS ,
    DstHUD_STUDIOEVENT ,
    DstHUD_POSTRUNCMD ,
    DstHUD_SHUTDOWN ,
    DstHUD_TXFERLOCALOVERRIDES ,
    DstHUD_PROCESSPLAYERSTATE ,
    DstHUD_TXFERPREDICTIONDATA ,
    DstHUD_DEMOREAD ,
    DstHUD_CONNECTIONLESS ,
    DstHUD_GETHULLBOUNDS ,
    DstHUD_FRAME,
    DstHUD_KEY_EVENT ,
    DstHUD_TEMPENTUPDATE,
    DstHUD_GETUSERENTITY ,
    DstHUD_VOICESTATUS,
    DstHUD_DIRECTORMESSAGE,
    DstHUD_STUDIO_INTERFACE ,
    DstHUD_CHATINPUTPOSITION,
    DstHUD_GETPLAYERTEAM
};

void CallClientF( void (*F)(void *pv) )
{
    modfuncs_t modFunc;
    memset(&modFunc, 0, sizeof(modFunc));

    cldll_func_t dllFunc;
    memset(&dllFunc, 0, sizeof(dllFunc));
    *(void **)(&dllFunc.pInitFunc) = (void *)&modFunc;
    *(void **)(&dllFunc.pHudVidInitFunc) = (void *)&dllFuncDst;
    F(&dllFunc);
}
