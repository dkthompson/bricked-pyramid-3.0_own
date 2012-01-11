/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef __PMIC8901_H__
#define __PMIC8901_H__
/*
 * Qualcomm PMIC8901 driver header file
 *
 */

#include <linux/irq.h>
#include <linux/mfd/core.h>
#include <linux/mfd/pm8xxx/irq.h>
#include <linux/mfd/pm8xxx/mpp.h>
#include <linux/mfd/pm8xxx/tm.h>
#include <linux/regulator/pmic8901-regulator.h>
#include <linux/mfd/pm8xxx/misc.h>

/* PM8901 interrupt numbers */
#define PM8901_IRQ_BLOCK_BIT(block, bit) ((block) * 8 + (bit))

#define PM8901_NR_IRQS			72

/* PM8901 MPP */
#define PM8901_MPP_BLOCK_START		6
#define PM8901_MPPS			4

/* PM8901 IRQs */
#define PM8901_MPP_IRQ(mpp)		PM8901_IRQ_BLOCK_BIT(6, (mpp))
#define PM8901_TEMPSTAT_IRQ		PM8901_IRQ_BLOCK_BIT(6, 4)
#define PM8901_OVERTEMP_IRQ		PM8901_IRQ_BLOCK_BIT(6, 5)

struct pm8901_chip;

struct pm8901_platform_data {
	struct pm8xxx_irq_platform_data		*irq_pdata;
	struct pm8xxx_mpp_platform_data		*mpp_pdata;
	struct pm8xxx_misc_platform_data	*misc_pdata;
	struct pm8901_vreg_pdata		*regulator_pdatas;
	int					num_regulators;
	/* This table is only needed for misc interrupts. */
	int		irq_base;
#ifdef CONFIG_MSM_SSBI
	int 		irq;
#endif
};

struct pm8901_gpio_platform_data {
	int	gpio_base;
	int	irq_base;
};

/* chip revision */
#define PM_8901_REV_1p0			0xF1
#define PM_8901_REV_1p1			0xF2
#define PM_8901_REV_2p0			0xF3

int pm8901_read(struct pm8901_chip *pm_chip, u16 addr, u8 *values,
		unsigned int len);
int pm8901_write(struct pm8901_chip *pm_chip, u16 addr, u8 *values,
		 unsigned int len);

int pm8901_rev(struct pm8901_chip *pm_chip);

int pm8901_irq_get_rt_status(struct pm8901_chip *pm_chip, int irq);

int pm8901_reset_pwr_off(int reset);
#endif /* __PMIC8901_H__ */
