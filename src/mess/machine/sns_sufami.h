#ifndef __SNS_SUFAMI_H
#define __SNS_SUFAMI_H

#include "machine/sns_slot.h"
#include "machine/sns_rom.h"


// ======================> sns_rom_sufami_device

class sns_rom_sufami_device : public sns_rom_device
{
public:
	// construction/destruction
	sns_rom_sufami_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	
	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete() { m_shortname = "sns_rom_sufami"; }
	virtual machine_config_constructor device_mconfig_additions() const;
	
	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);

private:
	required_device<sns_sufami_cart_slot_device> m_slot1;
	required_device<sns_sufami_cart_slot_device> m_slot2;
};

// ======================> sns_rom_strom_device

class sns_rom_strom_device : public sns_rom_device
{
public:
	// construction/destruction
	sns_rom_strom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	
	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete() { m_shortname = "sns_strom"; }
	
	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);	// used for ROM
	virtual DECLARE_READ8_MEMBER(read_h);	// used for ROM
	virtual DECLARE_WRITE8_MEMBER(write_l);	// used for RAM
	virtual DECLARE_WRITE8_MEMBER(write_h);	// used for RAM
};


// device type definition
extern const device_type SNS_LOROM_SUFAMI;
extern const device_type SNS_STROM;

#endif
