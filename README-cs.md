# How to run CS 1.6 with this fork

1. Build & install the engine to a directory using the instructions in README.md
2. Copy `valve` and `cstrike` folder from CS 1.6 to engine install dir
3. Copy `platform/resource/*` from CS 1.6 to `valve/resource/` in engine install dir
4. Delete `valve/cl_dlls/gameui.dll` from engine install dir
5. Copy these files from CS 1.6 to engine install dir:

```
vgui2.dll
steam_api.dll
tier0.dll
vgui.dll
vstdlib.dll
chromehtml.dll
icudt.dll
libcef.dll
```

6. Copy `SDL2.dll` from your SDL2 package to engine install dir
7. Download & install Xash Extras for the main menu
8. Create `steam_appid.txt`, put `10` inside the file, then save in engine install dir
9. Run `xash3d.exe -game cstrike` to launch CS 1.6

Note that your Steam account must own CS 1.6 and Steam must be running for this to work.
