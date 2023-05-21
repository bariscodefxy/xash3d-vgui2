#ifndef FS_INT_H
#define FS_INT_H

#include "xash3d_types.h"

#define FS_GAMEDIRONLY_SEARCH_FLAGS ( FS_GAMEDIR_PATH | FS_CUSTOM_PATH | FS_GAMERODIR_PATH )

typedef struct fs_api_s
{
	void (*FS_AddGameDirectory)( const char *dir, uint flags );
	
	qboolean (*FS_Delete)( const char *path );

	void (*FS_CreatePath)( char *path );

	int (*FS_FileExists)( const char *filename, int gamedironly );
	
	file_t *(*FS_Open)( const char *filepath, const char *mode, qboolean gamedironly );
	int (*FS_Close)( file_t *file );
	
	int (*FS_Seek)( file_t *file, fs_offset_t offset, int whence );
	fs_offset_t (*FS_Tell)( file_t *file );

	fs_offset_t (*FS_FileSize)( const char *filename, qboolean gamedironly );
	int (*FS_FileTime)( const char *filename, qboolean gamedironly );
	
	qboolean (*FS_Eof)( file_t *file );

	fs_offset_t (*FS_Read)( file_t *file, void *buffer, size_t buffersize );
	fs_offset_t (*FS_Write)( file_t *file, const void *data, size_t datasize );

	int (*FS_Getc)( file_t *file );

	int (*FS_VPrintf)( file_t *file, const char *format, va_list ap );

	search_t *(*FS_Search)( const char *pattern, int caseinsensitive, int gamedironly );

	const char *(*FS_GetDiskPath)( const char *name, qboolean gamedironly );

	void (*Msg)( const char *format, ... );

	void *(*_Mem_Alloc)( poolhandle_t poolptr, size_t size, qboolean clear, const char *filename, int fileline );
	void (*_Mem_Free)( void *data, const char *filename, int fileline );
} fs_api_t;

// function exported from engine
// returns 0 on no error otherwise error
typedef int (*pfnFS_GetAPI)( fs_api_t *g_api );

#endif // FS_INT_H
