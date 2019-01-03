#include <citro2d.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "globals.h"
#include "player.h"
#include "sprite.h"

int main(int argc, char* argv[])
{
	// Init libs
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	// Load graphics
	C2D_SpriteSheet spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	C2D_SpriteSheet mapSheetBG = C2D_SpriteSheetLoad("romfs:/gfx/map1bg.t3x");
	C2D_SpriteSheet mapSheetFG = C2D_SpriteSheetLoad("romfs:/gfx/map1fg.t3x");

	if (!spriteSheet || !mapSheetBG || !mapSheetFG) svcBreak(USERBREAK_PANIC);

	// Initialize sprites
	Player* plyr = new Player(spriteSheet, 0);
	Sprite* bg = new Sprite(mapSheetBG, 0);
	Sprite* fg = new Sprite(mapSheetFG, 0);

	bg->setPos(-416.f, -300.f);
	fg->setPos(-416.f, -300.f);

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		u32 kUp = hidKeysUp();

		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		if (kHeld & KEY_DRIGHT || kHeld & KEY_CPAD_RIGHT)
		{
			plyr->moveRight();
		}

		if (kHeld & KEY_DLEFT || kHeld & KEY_CPAD_LEFT)
		{
			plyr->moveLeft();
		}

		// Render console on bottom screen
		printf("\x1b[1;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[2;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[3;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(top);

		/* Begin frame */
		C2D_DrawSprite(bg->getSpr());

		plyr->draw();

		C2D_DrawSprite(fg->getSpr());
		/* End frame */

		C3D_FrameEnd(0);
	}

	// Delete objects
	delete bg;
	delete fg;
	delete plyr;

	// Delete graphics
	C2D_SpriteSheetFree(spriteSheet);

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}
