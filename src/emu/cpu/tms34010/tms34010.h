/***************************************************************************

    TMS34010: Portable Texas Instruments TMS34010 emulator

    Copyright Alex Pasadyn/Zsolt Vasvari
    Parts based on code by Aaron Giles

***************************************************************************/

#pragma once

#ifndef __TMS34010_H__
#define __TMS34010_H__


/* register indexes for get_reg and set_reg */
enum
{
	TMS34010_PC,
	TMS34010_SP,
	TMS34010_ST,
	TMS34010_A0,
	TMS34010_A1,
	TMS34010_A2,
	TMS34010_A3,
	TMS34010_A4,
	TMS34010_A5,
	TMS34010_A6,
	TMS34010_A7,
	TMS34010_A8,
	TMS34010_A9,
	TMS34010_A10,
	TMS34010_A11,
	TMS34010_A12,
	TMS34010_A13,
	TMS34010_A14,
	TMS34010_B0,
	TMS34010_B1,
	TMS34010_B2,
	TMS34010_B3,
	TMS34010_B4,
	TMS34010_B5,
	TMS34010_B6,
	TMS34010_B7,
	TMS34010_B8,
	TMS34010_B9,
	TMS34010_B10,
	TMS34010_B11,
	TMS34010_B12,
	TMS34010_B13,
	TMS34010_B14,

	TMS34010_GENPC = STATE_GENPC,
	TMS34010_GENSP = STATE_GENSP,
	TMS34010_GENPCBASE = STATE_GENPCBASE
};


/***************************************************************************
    INTERNAL I/O CONSTANTS
***************************************************************************/

enum
{
	REG_HESYNC = 0,
	REG_HEBLNK,
	REG_HSBLNK,
	REG_HTOTAL,
	REG_VESYNC,
	REG_VEBLNK,
	REG_VSBLNK,
	REG_VTOTAL,
	REG_DPYCTL,
	REG_DPYSTRT,
	REG_DPYINT,
	REG_CONTROL,
	REG_HSTDATA,
	REG_HSTADRL,
	REG_HSTADRH,
	REG_HSTCTLL,

	REG_HSTCTLH,
	REG_INTENB,
	REG_INTPEND,
	REG_CONVSP,
	REG_CONVDP,
	REG_PSIZE,
	REG_PMASK,
	REG_UNK23,
	REG_UNK24,
	REG_UNK25,
	REG_UNK26,
	REG_DPYTAP,
	REG_HCOUNT,
	REG_VCOUNT,
	REG_DPYADR,
	REG_REFCNT
};

enum
{
	REG020_VESYNC,
	REG020_HESYNC,
	REG020_VEBLNK,
	REG020_HEBLNK,
	REG020_VSBLNK,
	REG020_HSBLNK,
	REG020_VTOTAL,
	REG020_HTOTAL,
	REG020_DPYCTL,      /* matches 010 */
	REG020_DPYSTRT,     /* matches 010 */
	REG020_DPYINT,      /* matches 010 */
	REG020_CONTROL,     /* matches 010 */
	REG020_HSTDATA,     /* matches 010 */
	REG020_HSTADRL,     /* matches 010 */
	REG020_HSTADRH,     /* matches 010 */
	REG020_HSTCTLL,     /* matches 010 */

	REG020_HSTCTLH,     /* matches 010 */
	REG020_INTENB,      /* matches 010 */
	REG020_INTPEND,     /* matches 010 */
	REG020_CONVSP,      /* matches 010 */
	REG020_CONVDP,      /* matches 010 */
	REG020_PSIZE,       /* matches 010 */
	REG020_PMASKL,
	REG020_PMASKH,
	REG020_CONVMP,
	REG020_CONTROL2,
	REG020_CONFIG,
	REG020_DPYTAP,      /* matches 010 */
	REG020_VCOUNT,
	REG020_HCOUNT,
	REG020_DPYADR,      /* matches 010 */
	REG020_REFADR,

	REG020_DPYSTL,
	REG020_DPYSTH,
	REG020_DPYNXL,
	REG020_DPYNXH,
	REG020_DINCL,
	REG020_DINCH,
	REG020_RES0,
	REG020_HESERR,
	REG020_RES1,
	REG020_RES2,
	REG020_RES3,
	REG020_RES4,
	REG020_SCOUNT,
	REG020_BSFLTST,
	REG020_DPYMSK,
	REG020_RES5,

	REG020_SETVCNT,
	REG020_SETHCNT,
	REG020_BSFLTDL,
	REG020_BSFLTDH,
	REG020_RES6,
	REG020_RES7,
	REG020_RES8,
	REG020_RES9,
	REG020_IHOST1L,
	REG020_IHOST1H,
	REG020_IHOST2L,
	REG020_IHOST2H,
	REG020_IHOST3L,
	REG020_IHOST3H,
	REG020_IHOST4L,
	REG020_IHOST4H
};

/* Interrupts that are generated by the processor internally */
#define TMS34010_INT1       0x0002      /* External Interrupt 1 */
#define TMS34010_INT2       0x0004      /* External Interrupt 2 */
#define TMS34010_HI         0x0200      /* Host Interrupt */
#define TMS34010_DI         0x0400      /* Display Interrupt */
#define TMS34010_WV         0x0800      /* Window Violation Interrupt */


/* Configuration structure */
struct tms34010_display_params
{
	UINT16  vcount;                             /* most recent VCOUNT */
	UINT16  veblnk, vsblnk;                     /* start/end of VBLANK */
	UINT16  heblnk, hsblnk;                     /* start/end of HBLANK */
	UINT16  rowaddr, coladdr;                   /* row/column addresses */
	UINT8   yoffset;                            /* y offset from addresses */
	UINT8   enabled;                            /* video enabled */
};


struct tms34010_config
{
	UINT8   halt_on_reset;                      /* /HCS pin, which determines HALT state after reset */
	const char *screen_tag;                     /* the screen operated on */
	UINT32  pixclock;                           /* the pixel clock (0 means don't adjust screen size) */
	int     pixperclock;                        /* pixels per clock */
	void    (*scanline_callback_ind16)(screen_device &screen, bitmap_ind16 &bitmap, int scanline, const tms34010_display_params *params);
	void    (*scanline_callback_rgb32)(screen_device &screen, bitmap_rgb32 &bitmap, int scanline, const tms34010_display_params *params);
	void    (*output_int)(device_t *device, int state);         /* output interrupt callback */
	void    (*to_shiftreg)(address_space &space, offs_t, UINT16 *); /* shift register write */
	void    (*from_shiftreg)(address_space &space, offs_t, UINT16 *);   /* shift register read */
};


/* PUBLIC FUNCTIONS - 34010 */
void tms34010_get_display_params(device_t *cpu, tms34010_display_params *params);

class tms34010_device : public legacy_cpu_device
{
public:
	tms34010_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, UINT32 clock);
	tms34010_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, UINT32 clock, cpu_get_info_func get_info);

	UINT32 tms340x0_ind16(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 tms340x0_rgb32(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	/* Reads & writes to the 34010 I/O registers; place at 0xc0000000 */
	DECLARE_WRITE16_MEMBER( io_register_w );
	DECLARE_READ16_MEMBER( io_register_r );
	
	DECLARE_WRITE16_MEMBER(host_w);
	DECLARE_READ16_MEMBER(host_r);
};

extern const device_type TMS34010;

class tms34020_device : public tms34010_device
{
public:
	tms34020_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, UINT32 clock);
	/* Reads & writes to the 34010 I/O registers; place at 0xc0000000 */
	DECLARE_WRITE16_MEMBER( io_register_w );
	DECLARE_READ16_MEMBER( io_register_r );
};

extern const device_type TMS34020;



/* Host control interface */
#define TMS34010_HOST_ADDRESS_L     0
#define TMS34010_HOST_ADDRESS_H     1
#define TMS34010_HOST_DATA          2
#define TMS34010_HOST_CONTROL       3

/* Use this macro in the memory definitions to specify bit-based addresses */
#define TOBYTE(bitaddr) ((offs_t)(bitaddr) >> 3)
#define TOWORD(bitaddr) ((offs_t)(bitaddr) >> 4)


CPU_DISASSEMBLE( tms34010 );
CPU_DISASSEMBLE( tms34020 );

#endif /* __TMS34010_H__ */
