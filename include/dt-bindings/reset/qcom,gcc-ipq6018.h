/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2018, The LinaOS Foundation. All rights reserved.
 */

#ifndef _DT_BINDINGS_RESET_IPQ_GCC_6018_H
#define _DT_BINDINGS_RESET_IPQ_GCC_6018_H

#define GCC_BLSP1_BCR				0
#define GCC_BLSP1_QUP1_BCR			1
#define GCC_BLSP1_UART1_BCR			2
#define GCC_BLSP1_QUP2_BCR			3
#define GCC_BLSP1_UART2_BCR			4
#define GCC_BLSP1_QUP3_BCR			5
#define GCC_BLSP1_UART3_BCR			6
#define GCC_BLSP1_QUP4_BCR			7
#define GCC_BLSP1_UART4_BCR			8
#define GCC_BLSP1_QUP5_BCR			9
#define GCC_BLSP1_UART5_BCR			10
#define GCC_BLSP1_QUP6_BCR			11
#define GCC_BLSP1_UART6_BCR			12
#define GCC_IMEM_BCR				13
#define GCC_SMMU_BCR				14
#define GCC_APSS_TCU_BCR			15
#define GCC_SMMU_XPU_BCR			16
#define GCC_PCNOC_TBU_BCR			17
#define GCC_SMMU_CFG_BCR			18
#define GCC_PRNG_BCR				19
#define GCC_BOOT_ROM_BCR			20
#define GCC_CRYPTO_BCR				21
#define GCC_WCSS_BCR				22
#define GCC_WCSS_Q6_BCR				23
#define GCC_NSS_BCR				24
#define GCC_SEC_CTRL_BCR			25
#define GCC_DDRSS_BCR				26
#define GCC_SYSTEM_NOC_BCR			27
#define GCC_PCNOC_BCR				28
#define GCC_TCSR_BCR				29
#define GCC_QDSS_BCR				30
#define GCC_DCD_BCR				31
#define GCC_MSG_RAM_BCR				32
#define GCC_MPM_BCR				33
#define GCC_SPDM_BCR				34
#define GCC_RBCPR_BCR				35
#define GCC_RBCPR_MX_BCR			36
#define GCC_TLMM_BCR				37
#define GCC_RBCPR_WCSS_BCR			38
#define GCC_USB0_PHY_BCR			39
#define GCC_USB3PHY_0_PHY_BCR			40
#define GCC_USB0_BCR				41
#define GCC_USB1_BCR				42
#define GCC_QUSB2_0_PHY_BCR			43
#define GCC_QUSB2_1_PHY_BCR			44
#define GCC_SDCC1_BCR				45
#define GCC_SNOC_BUS_TIMEOUT0_BCR		46
#define GCC_SNOC_BUS_TIMEOUT1_BCR		47
#define GCC_SNOC_BUS_TIMEOUT2_BCR		48
#define GCC_PCNOC_BUS_TIMEOUT0_BCR		49
#define GCC_PCNOC_BUS_TIMEOUT1_BCR		50
#define GCC_PCNOC_BUS_TIMEOUT2_BCR		51
#define GCC_PCNOC_BUS_TIMEOUT3_BCR		52
#define GCC_PCNOC_BUS_TIMEOUT4_BCR		53
#define GCC_PCNOC_BUS_TIMEOUT5_BCR		54
#define GCC_PCNOC_BUS_TIMEOUT6_BCR		55
#define GCC_PCNOC_BUS_TIMEOUT7_BCR		56
#define GCC_PCNOC_BUS_TIMEOUT8_BCR		57
#define GCC_PCNOC_BUS_TIMEOUT9_BCR		58
#define GCC_UNIPHY0_BCR				59
#define GCC_UNIPHY1_BCR				60
#define GCC_CMN_12GPLL_BCR			61
#define GCC_QPIC_BCR				62
#define GCC_MDIO_BCR				63
#define GCC_WCSS_CORE_TBU_BCR			64
#define GCC_WCSS_Q6_TBU_BCR			65
#define GCC_USB0_TBU_BCR			66
#define GCC_PCIE0_TBU_BCR			67
#define GCC_PCIE0_BCR				68
#define GCC_PCIE0_PHY_BCR			69
#define GCC_PCIE0PHY_PHY_BCR			70
#define GCC_PCIE0_LINK_DOWN_BCR			71
#define GCC_DCC_BCR				72
#define GCC_APC0_VOLTAGE_DROOP_DETECTOR_BCR	73
#define GCC_SMMU_CATS_BCR			74
#define GCC_UBI0_AXI_ARES			75
#define GCC_UBI0_AHB_ARES			76
#define GCC_UBI0_NC_AXI_ARES			77
#define GCC_UBI0_DBG_ARES			78
#define GCC_UBI0_CORE_CLAMP_ENABLE		79
#define GCC_UBI0_CLKRST_CLAMP_ENABLE		80
#define GCC_UBI0_UTCM_ARES			81
#define GCC_NSS_CFG_ARES			82
#define GCC_NSS_NOC_ARES			83
#define GCC_NSS_CRYPTO_ARES			84
#define GCC_NSS_CSR_ARES			85
#define GCC_NSS_CE_APB_ARES			86
#define GCC_NSS_CE_AXI_ARES			87
#define GCC_NSSNOC_CE_APB_ARES			88
#define GCC_NSSNOC_CE_AXI_ARES			89
#define GCC_NSSNOC_UBI0_AHB_ARES		90
#define GCC_NSSNOC_SNOC_ARES			91
#define GCC_NSSNOC_CRYPTO_ARES			92
#define GCC_NSSNOC_ATB_ARES			93
#define GCC_NSSNOC_QOSGEN_REF_ARES		94
#define GCC_NSSNOC_TIMEOUT_REF_ARES		95
#define GCC_PCIE0_PIPE_ARES			96
#define GCC_PCIE0_SLEEP_ARES			97
#define GCC_PCIE0_CORE_STICKY_ARES		98
#define GCC_PCIE0_AXI_MASTER_ARES		99
#define GCC_PCIE0_AXI_SLAVE_ARES		100
#define GCC_PCIE0_AHB_ARES			101
#define GCC_PCIE0_AXI_MASTER_STICKY_ARES	102
#define GCC_PCIE0_AXI_SLAVE_STICKY_ARES		103
#define GCC_PPE_FULL_RESET			104
#define GCC_UNIPHY0_SOFT_RESET			105
#define GCC_UNIPHY0_XPCS_RESET			106
#define GCC_UNIPHY1_SOFT_RESET			107
#define GCC_UNIPHY1_XPCS_RESET			108
#define GCC_EDMA_HW_RESET			109
#define GCC_ADSS_BCR				110
#define GCC_NSS_NOC_TBU_BCR			111
#define GCC_NSSPORT1_RESET			112
#define GCC_NSSPORT2_RESET			113
#define GCC_NSSPORT3_RESET			114
#define GCC_NSSPORT4_RESET			115
#define GCC_NSSPORT5_RESET			116
#define GCC_UNIPHY0_PORT1_ARES			117
#define GCC_UNIPHY0_PORT2_ARES			118
#define GCC_UNIPHY0_PORT3_ARES			119
#define GCC_UNIPHY0_PORT4_ARES			120
#define GCC_UNIPHY0_PORT5_ARES			121
#define GCC_UNIPHY0_PORT_4_5_RESET		122
#define GCC_UNIPHY0_PORT_4_RESET		123
#define GCC_LPASS_BCR				124
#define GCC_UBI32_TBU_BCR			125
#define GCC_LPASS_TBU_BCR			126
#define GCC_WCSSAON_RESET			127
#define GCC_LPASS_Q6_AXIM_ARES			128
#define GCC_LPASS_Q6SS_TSCTR_1TO2_ARES		129
#define GCC_LPASS_Q6SS_TRIG_ARES		130
#define GCC_LPASS_Q6_ATBM_AT_ARES		131
#define GCC_LPASS_Q6_PCLKDBG_ARES		132
#define GCC_LPASS_CORE_AXIM_ARES		133
#define GCC_LPASS_SNOC_CFG_ARES			134
#define GCC_WCSS_DBG_ARES			135
#define GCC_WCSS_ECAHB_ARES			136
#define GCC_WCSS_ACMT_ARES			137
#define GCC_WCSS_DBG_BDG_ARES			138
#define GCC_WCSS_AHB_S_ARES			139
#define GCC_WCSS_AXI_M_ARES			140
#define GCC_Q6SS_DBG_ARES			141
#define GCC_Q6_AHB_S_ARES			142
#define GCC_Q6_AHB_ARES				143
#define GCC_Q6_AXIM2_ARES			144
#define GCC_Q6_AXIM_ARES			145
#define GCC_UBI0_CORE_ARES			146

#endif
