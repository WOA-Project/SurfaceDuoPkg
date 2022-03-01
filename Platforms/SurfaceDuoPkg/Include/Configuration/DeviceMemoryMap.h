#ifndef _DEVICE_MEMORY_MAP_H_
#define _DEVICE_MEMORY_MAP_H_

#include <Library/ArmLib.h>

#define MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT 128

/* Below flag is used for system memory */
#define SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES                               \
  EFI_RESOURCE_ATTRIBUTE_PRESENT | EFI_RESOURCE_ATTRIBUTE_INITIALIZED |        \
      EFI_RESOURCE_ATTRIBUTE_TESTED | EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |     \
      EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |                               \
      EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |                         \
      EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |                            \
      EFI_RESOURCE_ATTRIBUTE_EXECUTION_PROTECTABLE

typedef enum { NoHob, AddMem, AddDev, MaxMem } DeviceMemoryAddHob;

#define MEMORY_REGION_NAME_MAX_LENGTH 32

typedef struct {
  CHAR8                        Name[MEMORY_REGION_NAME_MAX_LENGTH];
  EFI_PHYSICAL_ADDRESS         Address;
  UINT64                       Length;
  DeviceMemoryAddHob           HobOption;
  EFI_RESOURCE_TYPE            ResourceType;
  EFI_RESOURCE_ATTRIBUTE_TYPE  ResourceAttribute;
  EFI_MEMORY_TYPE              MemoryType;
  ARM_MEMORY_REGION_ATTRIBUTES ArmAttributes;
} ARM_MEMORY_REGION_DESCRIPTOR_EX, *PARM_MEMORY_REGION_DESCRIPTOR_EX;

#define SMEM_ADDR_BASE 0x86000000
#define SMEM_ADDR_SIZE 0x00200000

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* Address,	  Length,     ResourceType, Resource Attribute, ARM MMU
       Attribute,                  HobOption, EFI Memory Type */

    /* DDR Regions */
    /* Kernel */
    {"Kernel", 0x80000000, 0x02A00000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* Display Reserved */
    /*{"Display Reserved", 0x80600000, 0x02400000, AddMem,
     EFI_RESOURCE_MEMORY_RESERVED, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiReservedMemoryType, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH},*/
    /* DBI Dump */
    {"DBI Dump", 0x82A00000, 0x00D22000, NoHob, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_INITIALIZED, EfiConventionalMemory,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* HLOS 1 */
    {"HLOS 1", 0x83722000, 0x01FDE000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* Hypervisor */
    {"Hypervisor", 0x85700000, 0x00600000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* MPSS_EFS */
    {"MPSS_EFS", 0x85D00000, 0x00200000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* AOP */
    {"AOP", 0x85F00000, 0x00020000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* AOP CMD DB */
    {"AOP CMD DB", 0x85F20000, 0x00020000, AddMem, EFI_RESOURCE_MEMORY_RESERVED,
     EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* GPU PRR */
    {"GPU PRR", 0x85F40000, 0x00010000, AddMem, EFI_RESOURCE_MEMORY_RESERVED,
     EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* HLOS 2 */
    {"HLOS 2", 0x85F50000, 0x000B0000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* SMEM */
    {"SMEM", SMEM_ADDR_BASE, SMEM_ADDR_SIZE, AddMem, EFI_RESOURCE_MEMORY_RESERVED,
     EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* TZ */
    {"TZ", 0x86200000, 0x01800000, AddMem, EFI_RESOURCE_MEMORY_RESERVED,
     EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* TZApps */
    {"TZApps", 0x87A00000, 0x02100000, NoHob, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* HLOS */
    {"RAM Partition", 0x89B00000, 0x01C00000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* PIL_REGION */
    {"PIL_REGION", 0x8B700000, 0x0F400000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* DXE Heap */
    /*{"DXE Heap", 0x9AB00000, 0x03500000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiConventionalMemory,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},*/
    /* Sched Heap */
    /*{"Sched Heap", 0x9E000000, 0x00400000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},*/
    /* DXE Heap */
    {"DXE Heap", 0x9AB00000, 0x01100000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiConventionalMemory,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* Sched Heap */
    {"Sched Heap", 0x9BC00000, 0x00400000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* Display Reserved */
    {"Display Reserved", 0x9C000000, 0x02400000, AddMem,
     EFI_RESOURCE_MEMORY_RESERVED, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiReservedMemoryType, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH},
    /* TGCM */
    {"TGCM", 0x9E400000, 0x01400000, AddMem, EFI_RESOURCE_MEMORY_RESERVED,
     EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE, EfiReservedMemoryType,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* FV Region */
    {"FV Region", 0x9F800000, 0x00400000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* UEFI FD */
    {"UEFI FD", 0x9FC00000, 0x00300000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* SEC Heap */
    {"SEC Heap", 0x9FF00000, 0x0008C000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* CPU Vectors */
    {"CPU Vectors", 0x9FF8C000, 0x00001000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* MMU PageTables */
    {"MMU PageTables", 0x9FF8D000, 0x00003000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiBootServicesData, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* USB UCSI Temp */
    {"USB UCSI Temp", 0x9FF90000, 0x00002000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiReservedMemoryType, ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* HLOS */
    {"RAM Partition", 0x9FF92000, 0x0001E000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* UEFI Stack */
    {"UEFI Stack", 0x9FFB0000, 0x00020000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiBootServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* RSRV1 */
    {"RSRV1", 0x9FFD0000, 0x0000A000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiRuntimeServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* TPMControl */
    {"TPMControl", 0x9FFDA000, 0x00003000, AddMem, EFI_RESOURCE_MEMORY_RESERVED,
     EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE, EfiRuntimeServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* Reset Data */
    {"Reset Data", 0x9FFDD000, 0x00004000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiRuntimeServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* RSRV3 */
    {"RSRV3", 0x9FFE1000, 0x00001000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiRuntimeServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* Capsule Header */
    {"Capsule Header", 0x9FFE2000, 0x00001000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiRuntimeServicesData, ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED},
    /* RSRV2 */
    {"RSRV2", 0x9FFE3000, 0x00014000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiRuntimeServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* Log Buffer */
    {"Log Buffer", 0x9FFF7000, 0x00008000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiRuntimeServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* Info Blk */
    {"Info Blk", 0x9FFFF000, 0x00001000, AddMem, EFI_RESOURCE_SYSTEM_MEMORY,
     SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, EfiRuntimeServicesData,
     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    /* RAM partition regions */
    /* HLOS */
    {"RAM Partition", 0xA0000000, 0x1CC00000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* Memory hole */
    /* 0xBCC00000 - 0xBFFFFFFF */
    /* HLOS */
    {"RAM Partition", 0xC0000000, 0x80000000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
#if USE_MEMORY_FOR_SERIAL_OUTPUT == 1
    /* HLOS */
    {"RAM Partition", 0x140000000, 0x3FE00000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
    /* PStore Log Buffer */
    {"PStore", 0x17FE00000, 0x00200000, AddMem,
     EFI_RESOURCE_MEMORY_RESERVED, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiReservedMemoryType, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH},
    /* HLOS */
    {"RAM Partition", 0x180000000, 0x80000000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
#else
    /* HLOS */
    {"RAM Partition", 0x140000000, 0xC0000000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},
#endif

    /* Other memory regions */
    /* AOP_SS_MSG_RAM */
    {"AOP_SS_MSG_RAM", 0x0C300000, 0x00100000, NoHob,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_INITIALIZED,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* IMEM Base */
    {"IMEM Base", 0x14680000, 0x00040000, NoHob, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_INITIALIZED, EfiConventionalMemory,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},

    /* Register regions */
    /* GCC_CLK_CTL */
    {"GCC_CLK_CTL", 0x00100000, 0x00200000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* MMCX_CPR3 */
    {"MMCX_CPR3", 0x00630000, 0x00004000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* SECURITY CONTROL */
    {"SECURITY CONTROL", 0x00780000, 0x00007000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* QUPV3_0_GSI */
    {"QUPV3_0_GSI", 0x00800000, 0x000D0000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* QUPV3_1_GSI */
    {"QUPV3_1_GSI", 0x00A00000, 0x000D0000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* QUPV3_2_GSI */
    {"QUPV3_2_GSI", 0x00C00000, 0x000D0000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PRNG_CFG_PRNG */
    {"PRNG_CFG_PRNG", 0x00790000, 0x00010000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* UFS2 UFS REGS */
    {"UFS2 UFS REGS", 0x01D60000, 0x00020000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* UFS UFS REGS */
    {"UFS UFS REGS", 0x01D80000, 0x00020000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* CRYPTO0 CRYPTO */
    {"CRYPTO0 CRYPTO", 0x01DC0000, 0x00040000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TCSR_TCSR_REGS */
    {"TCSR_TCSR_REGS", 0x01FC0000, 0x00030000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* GPU_GMU_CX_BLK */
    {"GPU_GMU_CX_BLK", 0x02C7D000, 0x00002000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* GPU_CC */
    {"GPU_CC", 0x02C90000, 0x0000A000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* GPU_CPR */
    {"GPU_CPR", 0x02C9A000, 0x00004000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TLMM_WEST */
    {"TLMM_WEST", 0x03100000, 0x00300000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TLMM_EAST */
    {"TLMM_EAST", 0x03500000, 0x00700000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TLMM_SOUTH */
    {"TLMM_SOUTH", 0x03D00000, 0x00300000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* QUPV3_SSC_GSI */
    {"QUPV3_SSC_GSI", 0x05A00000, 0x000D0000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PERIPH_SS */
    {"PERIPH_SS", 0x08800000, 0x00200000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* MCCC_MCCC_MSTR */
    {"MCCC_MCCC_MSTR", 0x090B0000, 0x00001000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* NPU_CC */
    {"NPU_CC", 0x09910000, 0x00010000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* USB30_PRIM */
    {"USB30_PRIM", 0x0A600000, 0x0011B000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* USB_RUMI */
    {"USB_RUMI", 0x0A720000, 0x00010000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* USB30_SEC */
    {"USB30_SEC", 0x0A800000, 0x0011B000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* USB30_MP */
    {"USB30_MP", 0x0A400000, 0x0011B000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* USB_MP_RUMI1 */
    {"USB_MP_RUMI1", 0x0A520000, 0x00010000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* USB_MP_RUMI2 */
    {"USB_MP_RUMI2", 0x0A522000, 0x00010000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* VIDEO_CC */
    {"VIDEO_CC", 0x0AB00000, 0x00020000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TITAN_A_CCI */
    {"TITAN_A_CCI", 0x0AC4A000, 0x00004000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TITAN_CAM_CC */
    {"TITAN_CAM_CC", 0x0AD00000, 0x00020000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* DISP_CC */
    {"DISP_CC", 0x0AF00000, 0x00020000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PDC_DISPLAY */
    {"PDC_DISPLAY", 0x0B290000, 0x00020000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PDC_DISP_SEQ */
    {"PDC_DISP_SEQ", 0x0B490000, 0x00020000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* RPMH_BCM_BCM_TOP */
    {"RPMH_BCM_BCM_TOP", 0x0BA00000, 0x00200000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* RPMH_CPRF_CPRF */
    {"RPMH_CPRF_CPRF", 0x0C200000, 0x00010000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* SLP_CNTR */
    {"SLP_CNTR", 0x0C221000, 0x00001000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TSENS0 */
    {"TSENS0", 0x0C222000, 0x00001000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TSENS1 */
    {"TSENS1", 0x0C223000, 0x00001000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TSENS0_TM */
    {"TSENS0_TM", 0x0C263000, 0x00001000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PSHOLD */
    {"PSHOLD", 0x0C264000, 0x00001000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* TSENS1_TM */
    {"TSENS1_TM", 0x0C265000, 0x00001000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PMIC ARB SPMI */
    {"PMIC ARB SPMI", 0x0C400000, 0x02800000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* SILVER_CLK_CTL */
    {"SILVER_CLK_CTL", 0x18280000, 0x00001000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* GOLD_CLK_CTL */
    {"GOLD_CLK_CTL", 0x18282000, 0x00001000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* L3_CLK_CTL */
    {"L3_CLK_CTL", 0x18284000, 0x00001000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* APSS_RSC_APPS_RSCC */
    {"APSS_RSC_APPS_RSCC", 0x18200000, 0x00030000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* APSS_ACTPM_WRAP */
    {"APSS_ACTPM_WRAP", 0x18300000, 0x000B0000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* APSS_GIC500_GICD */
    {"APSS_GIC500_GICD", 0x17A00000, 0x00010000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* APSS_GIC500_GICR */
    {"APSS_GIC500_GICR", 0x17A60000, 0x00100000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* APSS_IPC_INT */
    {"APSS_IPC_INT", 0x17C00000, 0x00001000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* APSS_WDT_TMR1 */
    {"APSS_WDT_TMR1", 0x17C10000, 0x00001000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* QTIMER */
    {"QTIMER", 0x17C20000, 0x00110000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PCIE_0_WRAPPER_AXI */
    {"PCIE_0_WRAPPER_AXI", 0x60000000, 0x02000000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PCIE_1_WRAPPER_AXI */
    {"PCIE_1_WRAPPER_AXI", 0x40000000, 0x02000000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PCIE_2_WRAPPER_AXI */
    {"PCIE_2_WRAPPER_AXI", 0x68000000, 0x02000000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PCIE_3_WRAPPER_AXI */
    {"PCIE_3_WRAPPER_AXI", 0x70000000, 0x02000000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PCIE_0_WRAPPER_AHB */
    {"PCIE_0_WRAPPER_AHB", 0x01C00000, 0x00008000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PCIE_1_WRAPPER_AHB */
    {"PCIE_1_WRAPPER_AHB", 0x01C08000, 0x00008000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PCIE_2_WRAPPER_AHB */
    {"PCIE_2_WRAPPER_AHB", 0x01C10000, 0x00008000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* PCIE_3_WRAPPER_AHB */
    {"PCIE_3_WRAPPER_AHB", 0x01C18000, 0x00008000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* REFGEN_GEN3X2_AHB */
    {"REFGEN_GEN3X2_AHB", 0x088E5000, 0x00004000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* MDSS */
    {"MDSS", 0x0AE00000, 0x00134000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},
    /* SMMU */
    {"SMMU", 0x15000000, 0x000D0000, AddDev, EFI_RESOURCE_MEMORY_MAPPED_IO,
     EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, EfiMemoryMappedIO,
     ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},

    /* Terminator for MMU */
    {"Terminator", 0, 0, 0, 0, 0, 0, 0}};

#endif