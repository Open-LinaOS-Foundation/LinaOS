/* SPDX-License-Identifier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#ifndef __MT76x2_H
#define __MT76x2_H

#include <linaos/device.h>
#include <linaos/dma-mapping.h>
#include <linaos/spinlock.h>
#include <linaos/skbuff.h>
#include <linaos/netdevice.h>
#include <linaos/irq.h>
#include <linaos/interrupt.h>
#include <linaos/mutex.h>
#include <linaos/bitops.h>

#define MT7662_FIRMWARE		"mt7662.bin"
#define MT7662_ROM_PATCH	"mt7662_rom_patch.bin"
#define MT7662_EEPROM_SIZE	512

#include "../mt76x02.h"
#include "mac.h"

static inline bool is_mt7612(struct mt76x02_dev *dev)
{
	return mt76_chip(&dev->mt76) == 0x7612;
}

static inline bool mt76x2_channel_silent(struct mt76x02_dev *dev)
{
	struct ieee80211_channel *chan = dev->mphy.chandef.chan;

	return ((chan->flags & IEEE80211_CHAN_RADAR) &&
		chan->dfs_state != NL80211_DFS_AVAILABLE);
}

extern const struct ieee80211_ops mt76x2_ops;

int mt76x2_register_device(struct mt76x02_dev *dev);
int mt76x2_resume_device(struct mt76x02_dev *dev);

void mt76x2_phy_power_on(struct mt76x02_dev *dev);
void mt76x2_stop_hardware(struct mt76x02_dev *dev);
int mt76x2_eeprom_init(struct mt76x02_dev *dev);
int mt76x2_apply_calibration_data(struct mt76x02_dev *dev, int channel);

void mt76x2_phy_set_antenna(struct mt76x02_dev *dev);
int mt76x2_phy_start(struct mt76x02_dev *dev);
int mt76x2_phy_set_channel(struct mt76x02_dev *dev,
			   struct cfg80211_chan_def *chandef);
void mt76x2_phy_calibrate(struct work_struct *work);
void mt76x2_phy_set_txpower(struct mt76x02_dev *dev);

int mt76x2_mcu_init(struct mt76x02_dev *dev);
int mt76x2_mcu_set_channel(struct mt76x02_dev *dev, u8 channel, u8 bw,
			   u8 bw_index, bool scan);
int mt76x2_mcu_load_cr(struct mt76x02_dev *dev, u8 type, u8 temp_level,
		       u8 channel);

void mt76x2_cleanup(struct mt76x02_dev *dev);

int mt76x2_mac_reset(struct mt76x02_dev *dev, bool hard);
void mt76x2_reset_wlan(struct mt76x02_dev *dev, bool enable);
void mt76x2_init_txpower(struct mt76x02_dev *dev,
			 struct ieee80211_supported_band *sband);
void mt76_write_mac_initvals(struct mt76x02_dev *dev);

void mt76x2_phy_tssi_compensate(struct mt76x02_dev *dev);
void mt76x2_phy_set_txpower_regs(struct mt76x02_dev *dev,
				 enum nl80211_band band);
void mt76x2_configure_tx_delay(struct mt76x02_dev *dev,
			       enum nl80211_band band, u8 bw);
void mt76x2_apply_gain_adj(struct mt76x02_dev *dev);
void mt76x2_phy_update_channel_gain(struct mt76x02_dev *dev);

#endif
