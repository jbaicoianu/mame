/*************************************************************************

    Atari Return of the Jedi hardware

*************************************************************************/

/*----------- defined in video/jedi.c -----------*/

extern UINT8 *jedi_foregroundram;
extern UINT8 *jedi_backgroundram;
extern UINT8 *jedi_spriteram;
extern UINT8 *jedi_paletteram;
extern UINT8 *jedi_foreground_bank;

VIDEO_START( jedi );
VIDEO_UPDATE( jedi );

WRITE8_HANDLER( jedi_vscroll_w );
WRITE8_HANDLER( jedi_hscroll_w );
WRITE8_HANDLER( jedi_video_off_w );
WRITE8_HANDLER( jedi_PIXIRAM_w );
