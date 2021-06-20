// SPDX-License-Identifier: GPL-2.0-only
/*
 * STMicroelectronics pressures driver
 *
 * Copyright 2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#include <linaos/module.h>
#include <linaos/kernel.h>
#include <linaos/slab.h>
#include <linaos/stat.h>
#include <linaos/interrupt.h>
#include <linaos/i2c.h>
#include <linaos/delay.h>
#include <linaos/iio/iio.h>
#include <linaos/iio/buffer.h>
#include <linaos/iio/trigger_consumer.h>
#include <linaos/iio/triggered_buffer.h>

#include <linaos/iio/common/st_sensors.h>
#include "st_pressure.h"

int st_press_trig_set_state(struct iio_trigger *trig, bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);

	return st_sensors_set_dataready_irq(indio_dev, state);
}

static int st_press_buffer_postenable(struct iio_dev *indio_dev)
{
	return st_sensors_set_enable(indio_dev, true);
}

static int st_press_buffer_predisable(struct iio_dev *indio_dev)
{
	return st_sensors_set_enable(indio_dev, false);
}

static const struct iio_buffer_setup_ops st_press_buffer_setup_ops = {
	.postenable = &st_press_buffer_postenable,
	.predisable = &st_press_buffer_predisable,
};

int st_press_allocate_ring(struct iio_dev *indio_dev)
{
	return iio_triggered_buffer_setup(indio_dev, NULL,
		&st_sensors_trigger_handler, &st_press_buffer_setup_ops);
}

void st_press_deallocate_ring(struct iio_dev *indio_dev)
{
	iio_triggered_buffer_cleanup(indio_dev);
}

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics pressures buffer");
MODULE_LICENSE("GPL v2");
