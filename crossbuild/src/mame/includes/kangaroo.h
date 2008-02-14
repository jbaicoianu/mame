/***************************************************************************

    Sun Electronics Kangaroo hardware

    driver by Ville Laitinen

***************************************************************************/

/*----------- defined in video/kangaroo.c -----------*/

extern UINT8 *kangaroo_video_control;

PALETTE_INIT( kangaroo );
VIDEO_START( kangaroo );
VIDEO_UPDATE( kangaroo );

WRITE8_HANDLER( kangaroo_blitter_w );
WRITE8_HANDLER( kangaroo_videoram_w );
WRITE8_HANDLER( kangaroo_video_control_w );
