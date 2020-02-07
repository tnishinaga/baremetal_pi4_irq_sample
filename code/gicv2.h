#pragma once

#ifndef __ASSEMBLER__
    #include <stdint.h>
    #include <stdbool.h>
    
    typedef struct {
        volatile uint32_t GICD_CTLR;
        volatile uint32_t GICD_TYPER;
        volatile uint32_t GICD_IIDR;
        volatile uint32_t __RESERVED_0[5];
        volatile uint32_t __IMPREMENTATION_DEFINED_0[8];
        volatile uint32_t __RESERVED_1[16];
        volatile uint32_t GICD_IGROUPR[32];
        volatile uint32_t GICD_ISENABLER[32];
        volatile uint32_t GICD_ICENABLER[32];
        volatile uint32_t GICD_ISPENDR[32];
        volatile uint32_t GICD_ICPENDR[32];
        volatile uint32_t GICD_ISACTIVER[32];
        volatile uint32_t GICD_ICACTIVER[32];
        volatile uint32_t GICD_IPRIORITYR[255];
        volatile uint32_t __RESERVED_2;
        volatile uint32_t GICD_ITARGETSR[255];
        volatile uint32_t __RESERVED_3;
        volatile uint32_t GICD_ICFGR[64];
        volatile uint32_t __IMPREMENTATION_DEFINED_1[64];
        volatile uint32_t GICD_NSACR[64];
        volatile uint32_t GICD_SGIR;
        volatile uint32_t __RESERVED4[3];
        volatile uint32_t GICD_CPENDSGIR[4];
        volatile uint32_t GICD_SPENDSGIR[4];
        volatile uint32_t __RESERVED5[40];
        volatile uint32_t __IMPREMENTATION_DEFINED_2[12];
    } __attribute__ ((packed)) __attribute__ ((aligned (4))) GIC_V2_DISTRIBUTOR_Type;

    typedef struct {
        volatile uint32_t GICC_CTLR;
        volatile uint32_t GICC_PMR;
        volatile uint32_t GICC_BMR;
        volatile uint32_t GICC_IAR;
        volatile uint32_t GICC_EOIR;
        volatile uint32_t GICC_RPR;
        volatile uint32_t GICC_HPPIR;
        volatile uint32_t GICC_ABPR;
        volatile uint32_t GICC_AIAR;
        volatile uint32_t GICC_AEOIR;
        volatile uint32_t GICC_AHPPIR;
        volatile uint32_t __RESERVED_0[5];
        volatile uint32_t __IMPREMENTATION_DEFINED_0[36];
        volatile uint32_t GICC_APR[4];
        volatile uint32_t GICC_NSAPR[4];
        volatile uint32_t __RESERVED_1[2];
        volatile uint32_t GICC_IIDR;
        volatile uint32_t __RESERVED_2[960];
        volatile uint32_t GICC_DIR;
    } __attribute__ ((packed)) __attribute__ ((aligned (4))) GIC_V2_CPU_INTERFACE_Type;

    typedef struct {
        volatile uint32_t GICH_HCR;
        volatile uint32_t GICH_VTR;
        volatile uint32_t GICH_VMCR;
        volatile uint32_t __RESERVED_0;
        volatile uint32_t GICH_MISR;
        volatile uint32_t __RESERVED_1[3];
        volatile uint32_t GICH_EISR0;
        volatile uint32_t GICH_EISR1;
        volatile uint32_t __RESERVED_2[2];
        volatile uint32_t GICH_ELSR0;
        volatile uint32_t GICH_ELSR1;
        volatile uint32_t __RESERVED_3[46];
        volatile uint32_t GICH_APR;
        volatile uint32_t __RESERVED_4[3];
        volatile uint32_t GICH_LR[64];
    } __attribute__ ((packed)) __attribute__ ((aligned (4))) GIC_V2_HYPERVISOR_Type;

    typedef struct {
        volatile uint32_t GICV_CTLR;
        volatile uint32_t GICV_PMR;
        volatile uint32_t GICV_BMR;
        volatile uint32_t GICV_IAR;
        volatile uint32_t GICV_EOIR;
        volatile uint32_t GICV_RPR;
        volatile uint32_t GICV_HPPIR;
        volatile uint32_t GICV_ABPR;
        volatile uint32_t GICV_AIAR;
        volatile uint32_t GICV_AEOIR;
        volatile uint32_t GICV_AHPPIR;
        volatile uint32_t __RESERVED_0[5];
        volatile uint32_t __IMPREMENTATION_DEFINED_0[36];
        volatile uint32_t GICV_APR[4];
        volatile uint32_t __RESERVED_1[4];
        volatile uint32_t __RESERVED_2[2];
        volatile uint32_t GICV_IIDR;
        volatile uint32_t __RESERVED_3[960];
        volatile uint32_t GICV_DIR;
        volatile uint32_t __RESERVED_4[1024];
    } __attribute__ ((packed)) __attribute__ ((aligned (4))) GIC_V2_VIRTUAL_CPU_Type;

    // D: Distributor
    // C: CPU Interface
    // H: Hypervisor(Virtual Interface Control)
    // V: Virtual CPU

    typedef struct {
        volatile GIC_V2_DISTRIBUTOR_Type *D;
        volatile GIC_V2_CPU_INTERFACE_Type *C;
        volatile GIC_V2_HYPERVISOR_Type *H;
        volatile GIC_V2_VIRTUAL_CPU_Type *V;
    } GIC_V2_Type;
#endif


#define GICD_CTLR_NON_SECURE_ENABLE (1 << 0)

#define GICD_CTLR_SECURE_ENABLE_GROUP1 (1 << 1)
#define GICD_CTLR_SECURE_ENABLE_GROUP0 (1 << 0)

#define GICD_TYPER_CPU_NUMBER_MASK (0x07 << 5)
#define GICD_TYPER_IT_LINES_NUMBER_MASK (0x1f << 0)



#define GICC_CTLR_NON_SECURE_EOI_MODE_NS   (1 << 9)
#define GICC_CTLR_NON_SECURE_IRQ_BYP_DIS_GRP1   (1 << 6)
#define GICC_CTLR_NON_SECURE_FIQ_BYP_DIS_GRP1   (1 << 5)
#define GICC_CTLR_NON_SECURE_ENABLE_GRP1   (1 << 0)

#define GICC_CTLR_SECURE_EOI_MODE_NS   (1 << 10)
#define GICC_CTLR_SECURE_EOI_MODE_S   (1 << 9)
#define GICC_CTLR_SECURE_IRQ_BYP_DIS_GRP1   (1 << 8)
#define GICC_CTLR_SECURE_FIQ_BYP_DIS_GRP1   (1 << 7)
#define GICC_CTLR_SECURE_IRQ_BYP_DIS_GRP0   (1 << 6)
#define GICC_CTLR_SECURE_FIQ_BYP_DIS_GRP0   (1 << 5)
#define GICC_CTLR_SECURE_CBPR   (1 << 4)
#define GICC_CTLR_SECURE_FIQEn   (1 << 3)
#define GICC_CTLR_SECURE_ACK_CTL   (1 << 2)
#define GICC_CTLR_SECURE_ENABLE_GRP1   (1 << 1)
#define GICC_CTLR_SECURE_ENABLE_GRP0   (1 << 0)