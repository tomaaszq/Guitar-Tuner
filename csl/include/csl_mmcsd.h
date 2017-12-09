/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2008
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *  ===========================================================================
 */

/** @defgroup CSL_MMCSD_API MMCSD
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this document is to identify a set of common CSL APIs for
 * the MMCSD module across various devices. The CSL developer is expected to
 * refer to this document while designing APIs for these modules. Some of the
 * listed APIs may not be applicable to a given MMCSD module. While other cases
 * this list of APIs may not be sufficient to cover all the features of a
 * particular MMCSD Module. The CSL developer should use his discretion
 * designing new APIs or extending the existing ones to cover these.
 *
 * @subsection aaa Terms and Abbreviations
 *   -# CSL:  Chip Support Library
 *   -# API:  Application Programmer Interface
 *
 * @subsection References
 *    -# TMS320VC5505 MMCSD DRAFT USERS GUIDE.pdf
 *
 */

/** @file csl_mmcsd.h
 *
 *  @brief Functional layer API header file for MMC/SD CSL
 *
 *  Path: \(CSLPATH)/inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 16-Sep-2008 Added Header File of MMC/SD CSL.
 * 16-Jun-2009 Added DMA mode support
 * 26-Jun-2009 Code modified as per review comments
 * 26-Jun-2009 Added SDHC card support
 * 20-Dec-2009 Added support for little and big endian data transfers
 * ============================================================================
 */

#ifndef _CSL_MMCSD_H_
#define _CSL_MMCSD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <soc.h>
#include <csl_types.h>
#include <csl_error.h>
#include <csl_dma.h>
#include <tistdtypes.h>
#include <csl_general.h>

/**
\defgroup CSL_MMCSD_API MMCSD
   \internal Based on <b>BCG MMC/SD Controller Module Specification </b>
*/
/**
@defgroup CSL_MMCSD_SYMBOL MMC/SD Symbols Defined
@ingroup CSL_MMCSD_API
*/

/**
@defgroup CSL_MMCSD_DATASTRUCT MMC/SD Data Structures
@ingroup CSL_MMCSD_API
*/

/**
@defgroup CSL_MMCSD_ENUM  MMC/SD Enumerated Data Types
@ingroup CSL_MMCSD_API
*/

/**
@defgroup CSL_MMCSD_FUNCTION  MMC/SD Functions
@ingroup CSL_MMCSD_API
*/

/**
@defgroup CSL_MMCSDC_INLINE_FUNCTION  MMC/SD Inline Functions
@ingroup CSL_MMCSD_API
*/

/*****************************************************************************\
          MMCSD global macro declarations
\*****************************************************************************/

/** \addtogroup CSL_MMCSD_SYMBOL
* @{ */

/** stuff bits value for 16 bit variable                                     */
#define CSL_MMCSD_STUFF_BITS      		   0x0000
/** Card Echo pattern for SD high capacity card                              */
#define CSL_SD_HC_ECHO_PATTERN             (0xAAu)
/** Max shift value for Uint16 data type variable                            */
#define CSL_MMCSD_SHIFT_MAX                    (16)
/** Max Mask value for Uint16 data type variable                             */
#define CSL_MMCSD_MASK_MAX                    (0xFFFF)
/** bit value in PCGCR for activate the mmcsd controller                     */
#define CSL_MMCSD_ACTIVE                  (Uint16)(0x0)
/** reset mmcsd bit field                                                    */
#define CSL_MMCSD_RESET                  (Uint16)(0x1)
/** reset count for mmcsd                                                    */
#define CSL_MMCSD_RESET_COUNT           (Uint16)(0x4)
/** hash define value for enabling the particular bit                        */
#define CSL_MMCSD_ENABLE                  (Uint16)(0x1)
/** hash define value for disabling the particular bit                       */
#define CSL_MMCSD_DISABLE                 (Uint16)(0x0)
/** ISR function ID for MMCSD0 Transmitting the data                         */
#define CSL_MMCSD_ISR_TXMT                  (0x0)
/** ISR function ID for MMCSD0 Receiving the data                            */
#define CSL_MMCSD_ISR_RCV                   (0x1)
/** Time delay                                                               */
#define CSL_MMCSD_DELAY_TIME                (100U)
/** Time out duration for response                                           */
#define CSL_MMCSD_RESPONSE_TIMEOUT         (0xFFFF)
/** Time out duration for data read/write                                    */
#define CSL_MMCSD_DATA_RW_TIMEOUT          (0xFFFF)
/** minimum clock division for which both card can respond                   */
#define CSL_MMCSD_CLK_DIV_INIT              (70)
/** This bit is used to check whether the MMCSD is in busy state             */
#define CSL_MMCSD_BUSY_STATE 	            (0x01)
/** This bit is used to check whether the MMCSD FIFO is empty                */
#define CSL_MMCSD_FIFO_EMPTY 			    0x20
/** These bits are used to check whether the MMCSD is in reset state         */
#define CSL_MMCSD_CMDDAT_RESET		        0x03
/** The response for card detection when SD Card is detected                 */
#define CSL_SD_CARD_DETECTED	            0x0120
/** The response for card detection when a MMC Card is detected              */
#define CSL_MMC_CARD_DETECTED	            0x8000
/** This bit is used to check whether the MMCSD has responded to a command   */
#define CSL_MMCSD_RESP_DONE		            0x04
/** Number of bytes in block of mmc or Sd card                               */
#define CSL_MMCSD_BLOCK_LENGTH            (512u)
/** max value of block length for MMCSD                                      */
#define CSL_MMCSD_BLOCK_LEN_MAX		      (0x0FFFu)
/** Bits that are used to check whether data can be read from the card       */
#define CSL_MMCSD_READ_READY              (0x0400)
/** Bits that are used to check whether data can be written to the card      */
#define CSL_MMCSD_WRITE_READY             (0x0200)
/**Size of dispatch table for MMCSD Interrupts  						     */
#define CSL_MMCSD_DISPATCH_TABLE_SIZE	  (12U)
/** Macro to compare the NULL values                                         */
#define CSL_MMCSD_NULL                    (0)
/** Maximum clock rate value accepted by the MMC clock control register      */
#define CSL_MMC_MAX_CLOCK_RATE            (0xFFu)

/** Write initialize command                                                 */
#define CSL_MMCSD_WRITE_INIT_CMD		   0x0210
/** Write block command                                                      */
#define CSL_MMCSD_WRITE_BLOCK_CMD		   0x2A18
/** Read single block command                                                */
#define CSL_MMCSD_READ_BLOCK_CMD	   0xA211
/** Write multiple block command                                             */
#define CSL_MMCSD_WRITE_MULTIPLE_BLOCK_CMD 0x2A19
/** Read multiple block command                                              */
#define CSL_MMCSD_READ_MULTIPLE_BLOCK_CMD  0xA212
/** All send CID  command                                                    */
#define CSL_MMCSD_ALL_SEND_CID_CMD		   0x0402
/** init card  command                                                       */
#define CSL_MMCSD_CARD_INIT0_CMD		   0x4000
/** select card command for SD HC                                            */
#define CSL_MMCSD_SDHC_CARD_INIT_CMD	   0x0608
/** select card command for SD                                               */
#define CSL_MMCSD_SD_CARD_INIT_CMD		   0x0237
/** select card command for MMC                                              */
#define CSL_MMCSD_MMCS_CARD_INIT_CMD	   0x0601
/** Set block length command                                                 */
#define CSL_MMCSD_SET_BLKLEN_CMD		   0x0210
/** MMCSD stop command                                                       */
#define CSL_MMCSD_STOP_CMD		           0x038C
/** MMCCMD1 recommended value for command 0                                  */
#define CSL_MMCSD_CMD_0                    0x0000
/** MMCCMD1 recommended value for command 1                                  */
#define CSL_MMCSD_CMD_1              	   0x0601
/** MMCCMD1 recommended value for command 2                                  */
#define CSL_MMCSD_CMD_2              	   0x0402
/** MMCCMD1 recommended value for command 3                                  */
#define CSL_MMCSD_CMD_3              	   0x0203
/** MMCCMD1 recommended value for command 6                                  */
#define CSL_MMCSD_CMD_6              	   0x0206
/** MMCCMD1 recommended value for command 7                                  */
#define CSL_MMCSD_CMD_7              	   0x0307
/** MMCCMD1 recommended value for command 8                                  */
#define CSL_MMCSD_CMD_8              	   0x0608
/** MMCCMD1 recommended value for command 9                                  */
#define CSL_MMCSD_CMD_9              	   0x0409
/** MMCCMD1 recommended value for command 41                                 */
#define CSL_MMCSD_CMD_41             	   0x0229
/** MMCCMD1 recommended value for command 55                                 */
#define CSL_MMCSD_CMD_55              	   0x0237
/** MMCSD response for ACMD41                                                */
#define CSL_MMCSD_CMD41_RESP          	   (0x80FFu)
/** MMCSD response for SDHC card                                             */
#define CSL_MMCSD_SDHC_RESP          	   (0x4000u)

/** Number of cycles required to detect the card type                        */
#define CSL_MMCSD_CARDCHECK_COUNT          (3u)
/** Response for the command1                                                */
#define CSL_MMCSD_CMD1_RESP                (0x8000u)

/**
@} */

/*****************************************************************************\
          MMCSD global typedef declarations
\*****************************************************************************/

/**\addtogroup CSL_MMCSD_ENUM
@{*/

/**
 *  \brief  Hardware Instance Id to select the MMCSD IO registers
 */
typedef enum {
    CSL_MMCSD0_INST  = (0U),
    CSL_MMCSD1_INST  = (1U),
    CSL_MMCSD_INST_INV
} CSL_MmcsdInstId;

/**
 *  \brief  Response type from MMCSD
 *
 *  Depending on the command value sent to the card, the card responds with
 *  different response values.The type of response is defined in the structure.
 */
typedef enum {
    CSL_MMCSD_RESPTYPE_NO   = 0,
    CSL_MMCSD_RESPTYPE_R1   = 1U,
    CSL_MMCSD_RESPTYPE_R2   = 2U,
    CSL_MMCSD_RESPTYPE_R3   = 3U,
    CSL_MMCSD_RESPTYPE_R4   = 4U,
    CSL_MMCSD_RESPTYPE_R5   = 5U,
    CSL_MMCSD_RESPTYPE_R6   = 6U
} CSL_MmcsdRespType;

/**
 *  \brief  Response busy signal from the card.
 */
typedef enum {
    CSL_MMCSD_RESPBUSY_NO   = 0U,
    CSL_MMCSD_RESPBUSY_YES  = 1U
} CSL_MmcsdRespBusy;

/**
 *  \brief  Hardware mode of operation of the device.
 *
 *  MMC/SD operates in two modes as defined by this structure
 */
typedef enum {
    CSL_MMCSD_LINECHR_PUSHPULL  = (0U),
    CSL_MMCSD_LINECHR_OPENDRAIN = (1U)
} CSL_MmcsdLineChr;

/**
 *  \brief  Different command types in MMCSD standard
 *
 *  This structure identifies the type of command that is sent to the MMC/SD Controller
 */
typedef enum {
    CSL_MMCSD_CMDTYPE_BC    = 0U,
    CSL_MMCSD_CMDTYPE_BCR   = 1U,
    CSL_MMCSD_CMDTYPE_AC    = 2U,
    CSL_MMCSD_CMDTYPE_ADTC  = 3U
} CSL_MmcsdCmdType;

/**
 *  \brief  Command Index for MMC and SD Cards.
 * NOTE: Commands specific to SD card are aligned with SD_CARD suffixes,
 *       commands specific to MMC card are aligned with MMC_CARD suffixes
 *       and all others are applicable for MMC and SD card both.
 */
typedef enum {
    CSL_MMCSD_GO_IDLE_STATE = 0U,
    CSL_MMCSD_SEND_OP_COND_MMC_CARD,
    CSL_MMCSD_ALL_SEND_CID,
    CSL_MMCSD_RELATIVE_ADDR,
    CSL_MMCSD_SET_DSR,
    CSL_MMCSD_CMD_IDX_RSV_5,
    CSL_MMCSD_CMD_IDX_RSV_6,
    CSL_MMCSD_SELECT_DESELECT_CARD,
    CSL_MMCSD_CMD_IDX_RSV_8,
    CSL_MMCSD_SEND_CSD,
    CSL_MMCSD_SEND_CID,
    CSL_MMCSD_READ_DAT_UNTIL_STOP_MMC_CARD,
    CSL_MMCSD_STOP_TRANSMISSION,
    CSL_MMCSD_SEND_STATUS,
    CSL_MMCSD_CMD_IDX_RSV_14,
    CSL_MMCSD_GO_INACTIVE_STATE,
    CSL_MMCSD_SET_BLOCKLEN,
    CSL_MMCSD_READ_SINGLE_BLOCK,
    CSL_MMCSD_READ_MULTIPLE_BLOCK,
    CSL_MMCSD_CMD_IDX_RSV_19,
    CSL_MMCSD_WRITE_DAT_UNTIL_STOP_MMC_CARD,
    CSL_MMCSD_CMD_IDX_RSV_21,
    CSL_MMCSD_CMD_IDX_RSV_22,
    CSL_MMCSD_SET_BLOCK_COUNT_MMC_CARD,
    CSL_MMCSD_WRITE_BLOCK,
    CSL_MMCSD_WRITE_MULTIPLE_BLOCK,
    CSL_MMCSD_PROGRAM_CID_MMC_CARD,
    CSL_MMCSD_PROGRAM_CSD,
    CSL_MMCSD_SET_WRITE_PROT,
    CSL_MMCSD_CLR_WRITE_PROT,
    CSL_MMCSD_SEND_WRITE_PROT,
    CSL_MMCSD_CMD_IDX_RSV_31,
    CSL_MMCSD_ERASE_WR_BLK_START_SD_CARD,
    CSL_MMCSD_ERASE_WR_BLK_END_SD_CARD,
    CSL_MMCSD_CMD_IDX_RSV_34,
    CSL_MMCSD_ERASE_GROUP_START_MMC_CARD,
    CSL_MMCSD_ERASE_GROUP_END_MMC_CARD,
    CSL_MMCSD_CMD_IDX_RSV_37,
    CSL_MMCSD_ERASE,
    CSL_MMCSD_FAST_IO_MMC_CARD_MMC_CARD,
    CSL_MMCSD_GO_IRQ_STATE_MMC_CARD,
    CSL_MMCSD_CMD_IDX_RSV_41,
    CSL_MMCSD_LOCK_UNLOCK,
    CSL_MMCSD_CMD_IDX_RSV_43,
    CSL_MMCSD_CMD_IDX_RSV_44,
    CSL_MMCSD_CMD_IDX_RSV_45,
    CSL_MMCSD_CMD_IDX_RSV_46,
    CSL_MMCSD_CMD_IDX_RSV_47,
    CSL_MMCSD_CMD_IDX_RSV_48,
    CSL_MMCSD_CMD_IDX_RSV_49,
    CSL_MMCSD_CMD_IDX_RSV_50,
    CSL_MMCSD_CMD_IDX_RSV_51,
    CSL_MMCSD_CMD_IDX_RSV_52,
    CSL_MMCSD_CMD_IDX_RSV_53,
    CSL_MMCSD_CMD_IDX_RSV_54,
    CSL_MMCSD_APP_CMD,
    CSL_MMCSD_GEN_CMD,
    CSL_MMCSD_CMD_IDX_RSV_57,
    CSL_MMCSD_CMD_IDX_RSV_58,
    CSL_MMCSD_CMD_IDX_RSV_59,
    CSL_MMCSD_CMD_IDX_RSV_60,
    CSL_MMCSD_CMD_IDX_RSV_61,
    CSL_MMCSD_CMD_IDX_RSV_62,
    CSL_MMCSD_CMD_IDX_RSV_63
} CSL_MmcsdCmdIndex;

/**
 *  \brief  Direction of data transfer
 *
 */
typedef enum {
    CSL_MMCSD_DIR_WRITE     = 0U,
    CSL_MMCSD_DIR_READ      = 1U,
    CSL_MMCSD_DIR_DONTCARE  = 2U
} CSL_MmcsdDir;

/**
 *  \brief  Exit time out enabled or disabled
 *
 */
typedef enum {
    CSL_MMCSD_EXTTIMEOUT_NO  = 0U,
    CSL_MMCSD_EXTTIMEOUT_YES = 1U
} CSL_MmcsdExtTimeout;

/**
 *  \brief  Type of card that is inserted
 *
 */
typedef enum
{
    CSL_CARD_NONE = 0,
    /**< No card detected                                                    */
    CSL_SD_CARD,
    /**< SD card detected                                                    */
    CSL_MMC_CARD
    /**< MMC card detected                                                   */
} CSL_CardType;

/**
 *  \brief  Event responses in MMCSD
 *
 */
typedef enum {
    CSL_MMCSD_EVENT_EOFCMD              = (1U << 2U),
    /**< for commands with response, an end of
     * Command + Response; for commands without response,
     * an end of Command                                                     */
    CSL_MMCSD_EVENT_READ                = (1U << 10U),
    /**< data available with controller for reading                          */

    CSL_MMCSD_EVENT_WRITE               = (1U << 9U),
    /**< data required by controller for writing                             */

    CSL_MMCSD_EVENT_ERROR_CMDCRC        = (1U << 7U),
    /**< Error detected in the CRC during command
     * - response phase                                                      */

    CSL_MMCSD_EVENT_ERROR_DATACRC       = ((1U << 6U)|(1 << 5U)),
    /**< Error detected in the CRC during data transfer                      */

    CSL_MMCSD_EVENT_ERROR_CMDTIMEOUT    = ((1U) << (4U)),
    /**< Timeout detected during command - response phase                    */

    CSL_MMCSD_EVENT_ERROR_DATATIMEOUT   = ((1U) << (3U)),
    /**< Timeout detected during data transfer                               */

    CSL_MMCSD_EVENT_CARD_EXITBUSY       = ((1U) << (1U)),
    /**< Card has exited busy state                                          */

    CSL_MMCSD_EVENT_BLOCK_XFERRED       = 1U
    /**< block transfer done                                                 */
} CSL_MmcsdEvent;

/**
 *\brief
 *   enum variable for the selection of mmcsd interrupts.
 */
typedef enum
{
    CSL_MMCSD_EDATDNE_INTERRUPT,  /* Data done (DATDNE) interrupt enable.                    */
    CSL_MMCSD_EBSYDNE_INTERRUPT,  /* Busy done (BSYDNE) interrupt enable.                    */
    CSL_MMCSD_ERSPDNE_INTERRUPT,  /* Command/response done (RSPDNE) interrupt enable.        */
    CSL_MMCSD_ETOUTRD_INTERRUPT,  /* Read-data time-out event (TOUTRD) interrupt enable.     */
    CSL_MMCSD_ETOUTRS_INTERRUPT,  /* Response time-out event (TOUTRS) interrupt enable.      */
    CSL_MMCSD_ECRCWR_INTERRUPT,   /* Write-data CRC error (CRCWR) interrupt enable.          */
    CSL_MMCSD_ECRCRD_INTERRUPT,   /* Read-data CRC error (CRCRD) interrupt enable.           */
    CSL_MMCSD_ECRCRS_INTERRUPT,   /* Response CRC error (CRCRS) interrupt enable.            */
    CSL_MMCSD_RSV_BIT,            /* this bit is reserved.                                   */
    CSL_MMCSD_EDXRDY_INTERRUPT,   /* Data transmit register (MMCDXR) ready interrupt enable. */
    CSL_MMCSD_EDRRDY_INTERRUPT,   /* Data receive register ready (DRRDY) interrupt enable.   */
    CSL_MMCSD_EDATED_INTERRUPT,   /* DAT3 edge detect (DATED) interrupt enable.              */
    CSL_MMCSD_ETRNDNE_INTERRUPT,  /* Transfer done (TRNDNE) interrupt enable.                */
	CSL_MMCSD_INTERRUPT_NONE      /*  No interrupt enable                                    */
} CSL_MMCSDEventType;

/**
 * \brief
 *  Enum to select the operating mode of the CSL MMCSD module
 */
typedef enum
{
    CSL_MMCSD_OPMODE_POLLED,    /* MMCSD operates in poll mode                      */
    CSL_MMCSD_OPMODE_INTERRUPT, /* MMCSD operates in interrupt mode (not supported) */
    CSL_MMCSD_OPMODE_DMA,       /* MMCSD operates in DMA mode                       */
	CSL_MMCSD_OPMODE_NONE       /* Invalid Enum value for boundary checking         */
} CSL_MMCSDOpMode;

/**
 *  \brief  MMC/SD endianness
 *
 *  This enum holds the values to set endianness of the MMC/SD controller
 */
typedef enum {
	CSL_MMCSD_ENDIAN_LITTLE = 0U,
    CSL_MMCSD_ENDIAN_BIG    = 1U
} CSL_MmcsdEndianMode;

/**
 *  \brief  Error type as received by the MMC on response for a command
 */
#define CSL_MMCSD_EVENT_ERROR   (CSL_MMCSD_EVENT_ERROR_CMDCRC |     \
                                 CSL_MMCSD_EVENT_ERROR_DATACRC |    \
                                 CSL_MMCSD_EVENT_ERROR_CMDTIMEOUT | \
                                 CSL_MMCSD_EVENT_ERROR_DATATIMEOUT)
/**
@} */

/**
\addtogroup CSL_MMCSD_DATASTRUCT
@{*/

/**
 *  \brief  Command structure for the card.
 *
 *	This structure has parameters that is used to send a command to the
 *  MMC/SD device.
 */
typedef struct {
    Uint16                   idx;
    /**< index of the command                                                */
    CSL_MmcsdRespType       respType;
    /**< response expected for the command                                   */
    CSL_MmcsdRespBusy       busy;
    /**< response expected for the command is of type busy                   */
    CSL_MmcsdCmdType        type;
    /**< protocol type of the command                                        */
    CSL_MmcsdDir            dir;
    /**< direction for the data if accompanying the command                  */
    CSL_MmcsdLineChr        lineChr;
    /**< line characteristics of the command                                 */
} CSL_MmcsdCmd;

/**
 *  \brief  Response array received from the controller
 *
 *	This object holds the information the response that is received for a command
 *	sent to the card.
 */
typedef struct {
    Uint16                  response[8];
    /**< The response will interpreted as:
     * response[0] - R2[15:0]
     * response[1] - R2[31:16]
     * response[2] - R2[47:32]
     * response[3] - R2[63:48]
     * response[4] - R2[79:64]
     * response[5] - R2[95:80]
     * response[6] - R2[111:96] or R1/R1B/R3/R4/R5/R6[23:8]
     * response[7] - R2[127:112] or R1/R1B/R3/R4/R5/R6[39:24]
     * */
} CSL_MmcsdResponse;

/**
* \brief Structure to store the some default configuration for MMC and SD card.
*
*/
typedef struct {
  Uint16 dmaEnable;            /**< Enable/disable DMA for data read/write          */
  Uint16 dat3EdgeDetection;    /**< Set level of edge detection for DAT3 pin        */
  Uint16 enableClkPin;         /**< Memory clk reflected on CLK Pin                 */
  Uint16 cdiv;                 /**< MMC function clk to memory clk divide down      */
  Uint16 rspTimeout;           /**< No. memory clks to wait before response timeout */
  Uint16 dataTimeout;          /**< No. memory clks to wait before data timeout     */
  Uint16 blockLen;             /**< Block Length must be same as CSD                */
} CSL_MMCSetupNative;

/**
* \brief MMC config structure for setting MMC/SD Control register.
*
*/
typedef struct {
  Uint16 mmcctl;  /**< MMCSD control register value                          */
  Uint16 mmcclk;  /**< MMCSD clock control register value                    */
  Uint16 mmcim;   /**< required interrupt field for MMCSD                    */
  Uint16 mmctor;  /**< mmc response time out register                        */
  Uint16 mmctod;  /**< mmc data read time out register                       */
  Uint16 mmcblen; /**< no of bytes in a block of mmc or sd card              */
  Uint16 mmcnblk; /**< total no of blocks for read or write                  */
} CSL_MMCConfig;

/**
* \brief Structure to store the CID Information for MMC and SD card.
*
*/
typedef struct
{
    Uint16 slice127_112;  /**< MMCSD Response Register 7                     */
    Uint16 slice111_96;   /**< MMCSD Response Register 6                     */
    Uint16 slice95_80;    /**< MMCSD Response Register 5                     */
    Uint16 slice79_64;    /**< MMCSD Response Register 4                     */
    Uint16 slice63_48;    /**< MMCSD Response Register 3                     */
    Uint16 slice47_32;    /**< MMCSD Response Register 2                     */
    Uint16 slice31_16;    /**< MMCSD Response Register 1                     */
    Uint16 slice15_0;     /**< MMCSD Response Register 0                     */
} CSL_MMCSDCidStruct;

/**
* \brief Card Identification object.
*
*/
typedef struct {
  Uint16 mfgId;            /**< 8 bit Manufacturer ID                        */
  Uint16 oemAppId;         /**< 16 bit OEM and application ID                */
  char   productName[6];   /**< 40 or 48 bit Product name                    */
  Uint16 productRev;       /**< 8 bit Product Revision Number                */
  Uint32 serialNumber;     /**< 32 bit Serial Number                         */
  Uint16 month;            /**< 4 bit Manufacturing Date (Month)             */
  Uint16 year;             /**< 4 bit Manufacturing Date (Year)
  in case of MMC (Year 0 = 1997). SD has an 8 bit year field.(Year 0 = 2000) */
  Uint16 checksum;         /**< 7 bit crc                                    */
} CSL_MMCCardIdObj;

/**
* \brief Structure to store the CSD Information for MMC and SD card.
*
*/
typedef struct
{
    Uint16 slice127_112; /**< MMCSD Response Register 7                      */
    Uint16 slice111_96;  /**< MMCSD Response Register 6                      */
    Uint16 slice95_80;   /**< MMCSD Response Register 5                      */
    Uint16 slice79_64;   /**< MMCSD Response Register 4                      */
    Uint16 slice63_48;   /**< MMCSD Response Register 3                      */
    Uint16 slice47_32;   /**< MMCSD Response Register 2                      */
    Uint16 slice31_16;   /**< MMCSD Response Register 1                      */
    Uint16 slice15_0;    /**< MMCSD Response Register 0                      */
} CSL_MMCSDCsdStruct;

/**
* \brief CSD Information for MMC and SD card.
*
*/
typedef struct {
  Uint16 csdStruct;        /**< CSD version; 0 - 1.0, 1 - 2.0                   */
  Uint16 mmcProt;          /**< 2 bit MMC protocol                              */
  Uint16 taac;             /**< 8 bit TAAC                                      */
  Uint16 nsac;             /**< 8 bit NSAC                                      */
  Uint16 tranSpeed;        /**< 8 bit max data transmission speed               */
  Uint16 ccc;              /**< 12 bit card command classes                     */
  Uint16 readBlLen;        /**< 4 bit maximum Read Block Length                 */
  Uint16 readBlPartial;    /**< 1 bit indicates if partial read blocks allowed  */
  Uint16 writeBlkMisalign; /**< 1 bit flag indicates write block misalignment   */
  Uint16 readBlkMisalign;  /**< 1 bit flag indicates read block misalignment    */
  Uint16 dsrImp;           /**< 1 bit flag indicates whether card has DSR reg   */
  Uint16 cSize;            /**< 12 bit device size                              */
  Uint16 vddRCurrMin;      /**< 3 bit Max. Read Current @ Vdd Min               */
  Uint16 vddRCurrMax;      /**< 3 bit Max. Read Current @ Vdd Max               */
  Uint16 vddWCurrMin;      /**< 3 bit Max. Write Current @ Vdd Min              */
  Uint16 vddWCurrMax;      /**< 3 bit Max. Write Current @ Vdd Max              */
  Uint16 cSizeMult;        /**< 3 bit device size multiplier                    */
  Uint16 eraseBlkEnable;   /**< 1 bit erase single block enable                 */
  Uint16 eraseGrpSize;     /**< 5-7 bit erase sector size                       */
  Uint16 eraseGrpMult;     /**< 5 bit erase group multiplier                    */
  Uint16 wpGrpSize;        /**< 5 bit write protect group size                  */
  Uint16 wpGrpEnable;      /**< 1 bit write protect enable flag                 */
  Uint16 defaultEcc;       /**< 2 bit Manufacturer Default ECC                  */
  Uint16 r2wFactor;        /**< 3 bit stream write factor                       */
  Uint16 writeBlLen;       /**< 4 bit maximum write block length                */
  Uint16 writeBlPartial;   /**< 1 bit indicates if partial write blocks allowed */
  Uint16 fileFmtGrp;       /**< 1 bit file format group                         */
  Uint16 copyFlag;         /**< 1 bit copy flag                                 */
  Uint16 permWriteProtect; /**< 1 bit to dis/en-able permanent write protection */
  Uint16 tmpWriteProtect;  /**< 1 bit to dis/en-able temporary write protection */
  Uint16 fileFmt;          /**< 2 bit file format                               */
  Uint16 ecc;              /**< 2 bit ECC code                                  */
  Uint16 crc;              /**< 7 bit r/w/e redundancy check                    */
} CSL_MMCCardCsdObj;

/**
* \brief structure for extra feature of MMC and SD Object.
*
*/
typedef struct {
  Uint16 securitySysId;           /**< Security System ID                    */
  Uint16 securitySysVers;         /**< Security System Version               */
  Uint16 maxLicenses;             /**< Maximum number of storable licenses   */
  Uint32 xStatus;                 /**< Extended status bits                  */
} CSL_MMCCardXCsdObj;

/**
* \brief structure for card specific information.
*
*/
typedef struct {
  Uint16 rca;                  /**< User assigned relative card address (RCA)
                                MMC mode or GPIO pin mapping associated with
                                Chip Select in SPI mode                      */
  Uint16 ST0;                  /**< Last read ST0 register value             */
  Uint16 ST1;                  /**< Last read ST1 register value             */
  Uint16 cardIndex;            /**< MMC module assigned index for card       */
  Uint32 maxXfrRate;           /**< Maximum transfer rate                    */
  Uint32 readAccessTime;       /**< TAAC - exp * mantissa                    */
  Uint32 cardCapacity;
  /**< Total memory available on card
       Note: For CSD Version 1.0 (CSL_MMCCardCsdObj.csdStruct = 0) capacity
             will be in bytes
             For CSD Version 2.0 (CSL_MMCCardCsdObj.csdStruct = 0) capacity
             will be in KBytes   */
  Uint32 blockLength;          /**< Block length of card                     */
  Uint32 totalSectors;         /**< Total no of sector on card               */
  Uint32 lastAddrRead;         /**< Last Address Read from memory card       */
  Uint32 lastAddrWritten;      /**< Last Address written to on memory card   */
  CSL_CardType       cardType; /**< MMC or SD                                */
  CSL_MMCCardIdObj   *cid;     /**< Manufacturers Card ID                    */
  CSL_MMCCardCsdObj  *csd;     /**< Card specific data                       */
  CSL_MMCCardXCsdObj *xcsd;    /**< Extended CSD                             */
  Bool    sdHcDetected;        /**< Flag to indicate detection of SD HC card */
} CSL_MMCCardObj;

/**
 * \brief  call back function for MMCSD.
 *
 */
typedef void (* CSL_MMCCallBackPtr)(void);

/**
 * \brief  DMA call back function pointer.
 *
 */
typedef void (* CSL_MMCDmaCallBackPtr)(void *mmcsdHandle, void *dmaHandle);

/**
* \brief structure array of isr function for MMCSD.
*
*/
typedef struct {
/**< Isr function for MMCSD  */
   CSL_MMCCallBackPtr isr[CSL_MMCSD_DISPATCH_TABLE_SIZE];
} CSL_MMCCallBackObj;

/**
 * \brief DMA configuration structure for MMCSD module.
 *
 * Contains configuration parameters for DMA hardware registers.
 */
typedef struct
{
    CSL_DMAAutoReloadMode     autoMode;    /**< Auto reloadmode bit          */
    CSL_DMATxBurstLen         burstLen;    /**< Length of the transmit burst */
    CSL_DMAInterruptState     dmaInt;      /**< state of DMA interrupt       */
    CSL_DMAChanDir            chanDir;     /**< Channel direction - Rd/Wr    */
} CSL_MmcsdDmaConfig;

/**
 * \brief structure for card specific information.
 *
 */
typedef struct {
   CSL_MmcsdRegsOvly     mmcRegs;        /**< Pointer to MMC regs structure  */
   CSL_MMCCardObj        *cardObj;       /**< Pointer to card Objects        */
   Uint16                numCardsActive; /**< Number of cards active/ready   */
   CSL_MMCCallBackObj    *callBackTbl;   /**< Pointer to call back table obj */
   CSL_MMCSDOpMode       opMode;         /**< Operating mode of MMCSD        */
   CSL_DMA_Handle        hDmaWrite;      /**< Handle to DMA write channel    */
   CSL_DMA_Handle        hDmaRead;       /**< Handle to DMA read channel     */
   CSL_DMA_Config        dmaWriteCfg;    /**< DMA config structure for write */
   CSL_DMA_Config        dmaReadCfg;     /**< DMA config structure for read  */
   CSL_MMCDmaCallBackPtr dmaCallback;    /**< Call back function for DMA     */
   Bool                  isCallbackSet;  /**< Flag to enable callback request*/
   CSL_MMCSDCidStruct    cidSliceInfo;   /**< CID slice information strcuture */
   CSL_MMCSDCsdStruct    csdSliceInfo;   /**< CSD slice information strcuture */
   CSL_MmcsdEndianMode   readEndianMode; /**< Endian mode for read operation  */
   CSL_MmcsdEndianMode   writeEndianMode;/**< Endian mode for write operation */
} CSL_MMCControllerObj;

/**
 * \brief MMCSD Handle
 *
 */
typedef CSL_MMCControllerObj 	*CSL_MmcsdHandle;

/**
@} */

/******************************************************************************
 * CSL MMCSD function declarations
 *****************************************************************************/
/** @addtogroup CSL_MMCSD_FUNCTION
 @{ */

/** ===========================================================================
 *   @n@b MMC_init
 *
 *   @b Description
 *   @n This is the initialization function for the MMCSD CSL. The function
 *      must be called before calling any other API from this CSL. This
 *      function is for enabling the clock to the MMCSD Controller.
 *      Currently, the function just return status CSL_SOK. as of now no
 *      checking is done inside the definition of function , but in near
 *      future it can be implemented.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  This should be call first before calling any other MMCSD Function.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_status       status;

            status = MMC_init();
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_init (void);

/** ===========================================================================
 *   @n@b MMC_open
 *
 *   @b Description
 *   @n This function opens the CSL MMCSD module and returns the handle to the
 *      MMCSD object structure. Parameter 'opMode' is provided to select the
 *      operating mode of the MMCSD module. No configurations related to opmode
 *      are done in this API. opmode information is stored in the MMCSD handle
 *      and is used in data transfer APIs.
 *
 *      NOTE: THIS API SETS THE ENDIAN MODE OF MMCSD READ AND WRITE OPERATIONS
 *            TO LITTLE ENDIAN. USE MMC_setEndianMode() TO CHANGE ENDIAN MODE.
 *
 *   @b Arguments
 *   @verbatim
            pMmcsdContObj    MMCSD Controller object structure
            instId           Instance number for MMCSD
            opMode           Operating mode of the MMCSD module
            status           Status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_MmmcsdHandle
 *   @n                     Valid MMCSD handle will be returned if
 *                          status value is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_init() API should be called before MMC_open().
 *
 *   <b> Post Condition </b>
 *   @n   1.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK            - Valid MMCSD handle is returned
 *   @li            CSL_ESYS_INVPARAMS - resource is already in use
 *   @n   2.    CSL_MmmcsdObj object structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. CSL_MmmcsdObj object structure
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;
               status =  MMC_init();
            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);
            ...
    @endverbatim
 *  ===========================================================================
 */
CSL_MmcsdHandle MMC_open (CSL_MMCControllerObj    *pMmcsdContObj,
                          CSL_MmcsdInstId         instId,
                          CSL_MMCSDOpMode         opMode,
                          CSL_Status              *status);

/** ===========================================================================
 *   @n@b MMC_close
 *
 *   @b Description
 *   @n This function closes the specified handle to MMCSD.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called successfully before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n MMCSD Object will be assigned to NULL.
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_close(hMmcsd);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_close(
               CSL_MmcsdHandle     hMmcsd);

/** ===========================================================================
 *   @n@b MMC_setCardType
 *
 *   @b Description
 *   @n Function is used to set the card type in the MMCSD Card Obj.
 *      Implementation is limited only at the software layer.
 *
 *   @b Arguments
 *   @verbatim
            pCardObj          pointer to the card object.
            cardType          type of card MMC or SD.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim

            CSL_MMCCardObj        pCardObj;
            CSL_CardType          cardType;

               cardType = CSL_SD_CARD;

            status = MMC_setCardType(&pCardObj, cardType);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setCardType(
               CSL_MMCCardObj       *pCardObj,
               CSL_CardType          cardType );

/** ===========================================================================
 *   @n@b MMC_setCardPtr
 *
 *   @b Description
 *   @n This function will set the Card Object information address into the
 *          MMCSD handle. Implementation is limited only at the software layer.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            CSL_MMCCardObj    Pointer to the MMCSD Card Object.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called successfully before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            CSL_MMCCardObj        pMmcCardObj;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_setCardPtr(hMmcsd, &pMmcCardObj);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setCardPtr(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardObj      *pMmcCardObj);

/** ===========================================================================
 *   @n@b MMC_setCallBack
 *
 *   @b Description
 *   @n This function set the address of ISR function for Call back.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd           Handle to the MMCSD.
            pFunction        Pointer to the isr function.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None.
 *
 *   @b Example
 *   @verbatim
#define MMCSD_ISR_FUNCTION_MAX 4
void mmcsd0_tx_isr(void);
void mmcsd0_rcv_isr(void);
void mmcsd1_tx_isr(void);
void mmcsd1_rcv_isr(void);

CSL_MMCCallBackPtr isr_fun[MMCSD_ISR_FUNCTION_MAX];

			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MMCCallBackObj    pFunction;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;
            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

    isr_fun[0] = mmcsd_tx_isr;
    isr_fun[1] = mmcsd_rcv_isr;

       pFunction =  isr_fun ;
            status = MMC_setCallBack(hMmcsd, &pFunction);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setCallBack(
               CSL_MmcsdHandle      hMmcsd,
               CSL_MMCCallBackObj   *pFunction);

 /** ===========================================================================
 *   @n@b MMC_getNumberOfCards
 *
 *   @b Description
 *   @n Get the no of cards information from the Handler.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            pActiveNoCard     pointer to store no of active card Info.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MMCCallBackObj    pFunction;
            Uint16                pActiveNoCard;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;
            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

     status = MMC_getNumberOfCards(hMmcsd, &pActiveNoCard);

     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_getNumberOfCards(
               CSL_MmcsdHandle       hMmcsd,
               Uint16                *pActiveNoCard );

/** ===========================================================================
 *   @n@b MMC_clearResponse
 *
 *   @b Description
 *   @n This function will clear all eight response register of MMCSD.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called successfully before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Response Register will be reset.
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_clearResponse(hMmcsd);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_clearResponse(
               CSL_MmcsdHandle     hMmcsd);

/** ===========================================================================
 *   @n@b MMC_intEnable
 *
 *   @b Description
 *   @n This function will enable or disable interrupt for MMCSD as per passed
 *      mask value for interrupt.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            maskValue         mask value to specify the interrupt state.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called successfully before this.
 *
 *   <b> Post Condition </b>
 *   @n  Before enabling interrupt of any type make sure the isr function
 *        is plugged in ISR.
 *
 *   @b Modifies
 *   @n Interrupt will be enable for particular event.
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            Uint16                maskValue;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);
NOTE: Interrupt mask value refer the cslr_mmcsd.h file under MMCIM Field
               maskValue = CSL_MMCSD_MMCIM_ETRNDNE_MASK |
                               CSL_MMCSD_MMCIM_EDATED_MASK ;

            status = MMC_intEnable(hMmcsd, maskValue);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_intEnable(
               CSL_MmcsdHandle      hMmcsd,
               Uint16               maskValue);

/** ===========================================================================
 *   @n@b MMC_eventEnable
 *
 *   @b Description
 *   @n This function will enable the event for passed parameter.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            mmcsdEvent        event type.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called successfully before this.
 *
 *   <b> Post Condition </b>
 *   @n  Before enabling interrupt of any type make sure the isr function
 *        is plugged in ISR.
 *
 *   @b Modifies
 *   @n Interrupt will be enable for particular event.
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_MMCSDEventType    mmcsdEvent;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);
            eventType = CSL_MMCSD_EDATDNE_INTERRUPT;

            status = MMC_eventEnable(hMmcsd, mmcsdEvent);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_eventEnable(
               CSL_MmcsdHandle      hMmcsd,
               CSL_MMCSDEventType   mmcsdEvent);

/** ===========================================================================
 *   @n@b MMC_eventDisable
 *
 *   @b Description
 *   @n This function will disable the event for passed parameter.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            mmcsdEvent        event type.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called successfully before this.
 *
 *   <b> Post Condition </b>
 *   @n  Before enabling interrupt of any type make sure the isr function
 *        is plugged in ISR.
 *
 *   @b Modifies
 *   @n Interrupt will be enable for particular event.
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_MMCSDEventType    mmcsdEvent;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);
            eventType = CSL_MMCSD_EDATDNE_INTERRUPT;

            status = MMC_eventDisable(hMmcsd, mmcsdEvent);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_eventDisable(
               CSL_MmcsdHandle      hMmcsd,
               CSL_MMCSDEventType   mmcsdEvent);

/** ===========================================================================
 *   @n@b MMC_drrdy
 *
 *   @b Description
 *   @n This function return status of data, which is available to read or not
 *      by the CPU.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            pStatus           status of API success of Failed.
     @endverbatim
 *
 *   <b> Return Value </b>  Bool
 *   @li                    TRUE     - MMCDRR is ready.
 *   @li                    FALSE    - MMCDRR is not ready.
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_status            pstatus;
            Bool                  status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &pstatus);

            status = MMC_drrdy(hMmcsd, &pStatus);
     @endverbatim
 *  ===========================================================================
 */
Bool MMC_drrdy(
         CSL_MmcsdHandle      hMmcsd,
         CSL_Status           *pStatus);

/** ===========================================================================
 *   @n@b MMC_dxrdy
 *
 *   @b Description
 *   @n This function return status of data, which is available to write or not
 *      by the CPU.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            pStatus           status of API success of Failed.
     @endverbatim
 *
 *   <b> Return Value </b>  Bool
 *   @li                    TRUE     - MMCDXR is ready.
 *   @li                    FALSE    - MMCDXR is not ready.
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            Uint16                maskValue;
            CSL_status            pstatus;
            Bool                  status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &pstatus);

            status = MMC_dxrdy(hMmcsd, &pStatus);
     @endverbatim
 *  ===========================================================================
 */
Bool MMC_dxrdy(
         CSL_MmcsdHandle      hMmcsd,
         CSL_Status           *pStatus);

/** ===========================================================================
 *   @n@b MMC_saveStatus
 *
 *   @b Description
 *   @n This function return the MMCST0 register value.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            Uint16                maskValue;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_saveStatus(hMmcsd);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_saveStatus(
               CSL_MmcsdHandle     hMmcsd);

/** ===========================================================================
 *   @n@b MMC_getStatus
 *
 *   @b Description
 *   @n This function return the status of particular field of MMCST0 register
 *       according to the passed mask  value.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            maskValue         mask value to specify the field.
            pStatus           status of API success of Failed.
     @endverbatim
 *
 *   <b> Return Value </b>  Uint16
 *   @li                   status  - MMCST0 register value.
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            Uint16                maskValue;
            CSL_status            pStatus;
            Uint32                status;
            Uint32                maskValue;

               instId = CSL_MMCSD0_INST;
            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &pStatus);
                 maskValue = 0x0000000;
            status = MMC_getStatus(hMmcsd, maskValue, &pStatus);
     @endverbatim
 *  ===========================================================================
 */
Uint32 MMC_getStatus(
               CSL_MmcsdHandle     hMmcsd,
               Uint32               maskValue,
               CSL_Status           *pStatus );

/** ===========================================================================
 *   @n@b MMC_setupNative
 *
 *   @b Description
 *   @n This function will set initial configuration to the all registers.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd        Handle to the MMCSD.
            pMmcInit      Pointer to CSL_MMCSetupNative state variable.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n MMCSD Registers will be populated.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            CSL_MMCConfig         pMmcInit

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);
  Note: CSL_MMCConfig field are following.
  pMmcInit.dmaEnable          = CSL_MMCSD_MMCCMD2_DMATRIG_NO ;
  pMmcInit.dat3EdgeDetection  = CSL_MMCSD_MMCCTL_DATEG_DISABLE;
  pMmcInit.cdiv          = CSL_MMCSD_CLK_DIV_INIT;
  pMmcInit.rspTimeout   = CSL_MMCSD_RESPONSE_TIMEOUT;
  pMmcInit.dataTimeout  = CSL_MMCSD_DATA_RW_TIMEOUT;
  pMmcInit.blockLen     = CSL_MMCSD_MIN_BLOCK_LENGTH;

            status = MMC_setupNative(hMmcsd, &pMmcInit);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setupNative(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCSetupNative  *pMmcInit);

/** ===========================================================================
 *   @n@b MMC_config
 *
 *   @b Description
 *   @n This function will set value to the control and clock control
 *        register of MMCSD as per passed config parameter.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pMmcConfig        Pointer to the MMCSD config Parameter.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n MMCSD Register will be populated.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            CSL_MMCConfig         pMmcConfig

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);
  Note: CSL_MMCConfig field are following.
  pMmcConfig.mmcctl  = .... ;
  pMmcConfig.mmcclk  = CSL_MMCSD_MMCCLK_CLKEN_ENABLE | CSL_MMCSD_CLK_DIV_INIT;
  pMmcConfig.mmcim   = CSL_MMCSD_MMCIM_ETRNDNE_MASK;
  pMmcConfig.mmctor  = CSL_MMCSD_RESP_DONE;
  pMmcConfig.mmctod  = CSL_MMCSD_RESP_DONE;
  pMmcConfig.mmcblen = CSL_MMCSD_MIN_BLOCK_LENGTH;
  pMmcConfig.mmcnblk = 1;

            status = MMC_config(hMmcsd, &pMmcConfig);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_config(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCConfig       *pMmcConfig);

/** ===========================================================================
 *   @n@b MMC_getConfig
 *
 *   @b Description
 *   @n This function will fetch the information present in the control and
 *      clock control register and update to passed the config parameter.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pMmcConfig        Pointer to the MMCSD config Parameter.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            CSL_MMCConfig         pMmcConfig)

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_getConfig(hMmcsd, &pMmcConfig);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_getConfig(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCConfig       *pMmcConfig);

 /** ===========================================================================
 *   @n@b MMC_sendCmd
 *
 *   @b Description
 *   @n This is used to send command to the card by MMCSD Controller.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd           Handle to the MMCSD
            cmd              command type.
            arg              argument.
            waitForRsp       wait cycle for response.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint32                cmd;
            Uint32                arg;
            Uint16                waitForRsp;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

       cmd        = CSL_MMCSD_WRITE_INIT_CMD;
       arg        = CSL_MMCSD_ARG_RESET;
       waitForRsp = CSL_MMCSD_RESPONSE_TIMEOUT;

            status = MMC_sendCmd(hMmcsd, cmd, arg, waitForRsp);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_sendCmd(
               CSL_MmcsdHandle    hMmcsd,
               Uint32             cmd,
               Uint32             arg,
               Uint16             waitForRsp);

/** ===========================================================================
 *   @n@b MMC_sendGoIdle
 *
 *   @b Description
 *   @n This function broadcast Go Idle command for Setting all cards
 *      to the idle state.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n This should be called just after MMC_open() API.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_sendGoIdle(hMmcsd);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_sendGoIdle(
               CSL_MmcsdHandle     hMmcsd);

/** ===========================================================================
 *   @n@b MMC_stop
 *
 *   @b Description
 *   @n This function will stop the transfer and receive event.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *   @n  Card should be addressed.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_stop(hMmcsd);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_stop(
               CSL_MmcsdHandle     hMmcsd);

/** ===========================================================================
 *   @n@b MMC_deselectCard
 *
 *   @b Description
 *   @n This function will send command for deselecting particular card which
 *      is assigned in card object.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pMmcCardObj       Pointer to the MMCSD Card Info.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *   @n  RCA value should be properly stored in handle hMmcsd.
 *   @n  RCA value 0 will deselect all cards.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n MMCSD Object will be assigned to NULL.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pMmcCardObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_deselectCard(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardObj      *pMmcCardObj);

/** ===========================================================================
 *   @n@b MMC_selectCard
 *
 *   @b Description
 *   @n This function will used to get the information about the card which
 *      card is inserted and update to the card object structure.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pMmcCardObj       Pointer to the MMCSD Card Info.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pMmcCardObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_selectCard(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardObj      *pMmcCardObj);

/** ===========================================================================
 *   @n@b MMC_sendOpCond
 *
 *   @b Description
 *   @n This function will set the clock to the SD or MMC Card according to
 *     passed parameter of Card Type.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            clkDivValue       clock Div value for MMC or SD card.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *       some need ful work for particular card detected.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pMmcCardObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16               clkDivValue;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_MMC_CARD;

   clkDivValue = 0x4 //as MMC clock max is 20MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_sendOpCond(
               CSL_MmcsdHandle     hMmcsd,
               Uint16              clkDivValue);

/** ===========================================================================
 *   @n@b MMC_setRca
 *
 *   @b Description
 *   @n This function set the relative card address for MMC Card and update in
 *      CSL_MMCCardObj which can used for read or write operation to the card.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pMmcCardObj       Pointer to the MMC Card Info.
            rCardAddr         relative card address .
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *         some need ful work for particular card detected.
 *   @n  3: if Card detected is MMC then MMC_sendOpCond()for specific to MMC.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pMmcCardObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16                clkDivValue;
            Uint16                rCardAddr;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_MMC_CARD;
   clkDivValue = 0x4 //as MMC clock max is 20MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);
            rCardAddr = 0x100;

            status = MMC_setRca(hMmcsd, &pMmcCardObj, rCardAddr);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setRca(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardObj      *pMmcCardObj,
               Uint16              rCardAddr    );

/** ===========================================================================
 *   @n@b SD_sendRca
 *
 *   @b Description
 *   @n This function send the relative card address for SD Card and update
 *   in CSL_MMCCardObj which can used for read or write operation to the card.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pSdCardObj        Pointer to the SD Card Info.
            pRCardAddr         relative card address .
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *         some need ful work for particular card detected.
 *   @n  3: if Card detected is SD then MMC_sendOpCond()for specific to SD.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n pRCardAddr variable will be populated.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pSdCardObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16                clkDivValue;
            Uint16                pRCardAddr;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_SD_CARD;
   clkDivValue = 0x1 //as SD clock max is 50MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);
            status = SD_setRca(hMmcsd, &pSdCardObj, &pRCardAddr);
         pRCardAddr = 0x100;
     @endverbatim
 *  ===========================================================================
 */
CSL_Status SD_sendRca(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardObj      *pSdCardObj,
               Uint16              *pRCardAddr    );

/** ===========================================================================
 *   @n@b MMC_sendAllCID
 *
 *   @b Description
 *   @n This will fetch the Information about MMC Card Id and update into the
 *       passed id structure.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pMmcCardIdObj     Pointer to the MMC Card ID Info.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *         some need ful work for particular card detected.
 *   @n  3: if Card detected is MMC then MMC_sendOpCond()for specific to MMC.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n pMmcCardIdObj will be populated.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pMmcCardObj;
            CSL_MMCCardIdObj      pMmcCardIdObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16                clkDivValue;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_MMC_CARD;
   clkDivValue = 0x4 //as MMC clock max is 20MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);

            status = MMC_sendAllCID(hMmcsd, &pMmcCardIdObj);
   For example following value will be populated.
    pMmcCardIdObj->mfgId         = ;
    pMmcCardIdObj->serialNumber  = ;
    pMmcCardIdObj->monthCode     = ;
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_sendAllCID(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardIdObj    *pMmcCardIdObj);

/** ===========================================================================
 *   @n@b SD_sendAllCID
 *
 *   @b Description
 *   @n This will fetch the Information about SD Card Id and update into the
 *       passed id structure.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pSdCardIdObj     Pointer to the SD Card ID Info.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *         some need ful work for particular card detected.
 *   @n  3: if Card detected is SD then MMC_sendOpCond()for specific to SD.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n pSdCardIdObj object will be populated.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pSdCardObj;
            CSL_MMCCardIdObj      pSdCardIdObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16                clkDivValue;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_SD_CARD;
   clkDivValue = 0x1 //as SD clock max is 50MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);

            status = SD_sendAllCID(hMmcsd, &pSdCardIdObj);

   For example following value will be populated.
    pSdCardIdObj->mfgId         = ;
    pSdCardIdObj->serialNumber  = ;
    pSdCardIdObj->monthCode     = ;
     @endverbatim
 *  ===========================================================================
 */
CSL_Status SD_sendAllCID(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardIdObj     *pSdCardIdObj);

/** ===========================================================================
 *   @n@b MMC_getCardCsd
 *
 *   @b Description
 *   @n This function will update the CSD Structure info of MMC Card.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pMmcCardCsdObj    Pointer to the MMC Card CSD Info.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *         some need ful work for particular card detected.
 *   @n  3: if Card detected is MMC then MMC_sendOpCond()for specific to MMC.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pMmcCardObj;
            CSL_MMCCardCsdObj     pMmcCardCsdObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16                clkDivValue;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_MMC_CARD;
   clkDivValue = 0x4 //as MMC clock max is 20MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);

            status = MMC_getCardCsd(hMmcsd, &pMmcCardCsdObj);

   For example following value will be populated.
    pMmcCardCsdObj->readBlLen         = ;
    pMmcCardCsdObj->cSize  = ;
    These value will be useful to fetch the card specific information
     like these-----
    These figure are tested with 256Mbyte MMC Card
    blockLength      = 512 Bytes
    cardCapacity     = 0x260636672 Bytes
    totalSectors     = 0x509056 sector

     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_getCardCsd(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardCsdObj   *pMmcCardCsdObj);

/** ===========================================================================
 *   @n@b SD_getCardCsd
 *
 *   @b Description
 *   @n This function will update the CSD Structure info of SD Card.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD.
            pSdCardCsdObj     Pointer to the SD Card CSD Info.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *         some need ful work for particular card detected.
 *   @n  3: if Card detected is SD then MMC_sendOpCond()for specific to SD.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pSdCardObj;
            CSL_MMCCardCsdObj     pSdCardCsdObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16                clkDivValue;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_SD_CARD;
   clkDivValue = 0x1 //as SD clock max is 50MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);

            status = SD_getCardCsd(hMmcsd, &pSdCardCsdObj);
   For example following value will be populated.
    pSdCardCsdObj->readBlLen         = ;
    pSdCardCsdObj->cSize  = ;
    These value will be useful to fetch the card specific information
     like these-----
    These figure are tested with 1GB Ultra SD Card
    blockLength      = 512 Bytes
    cardCapacity     = 0x1015808000 Bytes
    totalSectors     = 0x1984000 sector
     @endverbatim
 *  ===========================================================================
 */
CSL_Status SD_getCardCsd(
               CSL_MmcsdHandle     hMmcsd,
               CSL_MMCCardCsdObj   *pSdCardCsdObj);

/** ===========================================================================
 *   @n@b MMC_read
 *
 *   @b Description
 *   @n This function will update the read buffer by present value
 *       in the card for passed valid location  and length of data .
 *
 *      'cardAddr' represents the adrress location in the card to be accessed.
 *      For the standard capacity cards this parameter will be a value in
 *      multiples of 512. That means to read a sector number 1 cardAddr
 *      will be 1*512, to read a sector number 2 cardAddr will be 2*512
 *      and so on.
 *      For the high capacity cards 'cardAddr' parameter will be same as the
 *      sector number. That means to read a sector number 1 cardAddr will be
 *      1, to read a sector number 2 cardAddr will be 2 and so on.
 *      Reason for this is high capacity cards uses BLOCK addressing instead
 *      of the BYTE addressing used by the standard capacty cards to increase
 *      the addressible memory capacity.
 *
 *      Detection of high capacity cards can be verified using the flag
 *      'sdHcDetected' in the MMCSD card object structure.
 *      sdHcDetected = TRUE      - SD card is high capacity card
 *      sdHcDetected = FALSE     - SD card is standard capacity card
 *
 *      NOTE: CARE SHOULD BE TAKEN WHILE PASSING THE 'cardAddr' PARAMETER.
 *      USING BYTE ADDRESSING WITH HIGH CAPACITY CARDS WILL LEAD TO OUT OF
 *      SECTOR BOUNDARY ACCESS AND RESULTS IN CODE HANGING FOR MMCSD RESPONSE.
 *
 *      NOTE: Endian mode of the data transfer depends on the parameter
 *      'readEndianMode' in the MMC handle. Default value for the endian mode
 *      is 'LITTLE ENDIAN' which will be set during MMC open. Endian mode can
 *      be configured using MMC_setEndianMode(). DO NOT CHANGE THE ENDIAN MODE
 *      WITH OUT USING THIS API.
 *
 *      NOTE: When transferring data in DMA mode, word swap will be done for
 *      the data buffer on PG1.4 and earlier versions of C5505 DSP.
 *      No word swap is required in upper layers.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            cardAddr          location to read from.
            noOfBytes         no of bytes to read.
            pReadBuffer       pointer to a buffer.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *         some need ful work for particular card detected.
 *   @n  3: MMC_sendOpCond()for specific to card .
 *   @n  4: if Card detected is SD then call SD_getCardCsd()for specific to SD
 *      or if Card detected is SD then call MMC_getCardCsd()for specific to MMC
 *
 *   <b> Post Condition </b>
 *   @n  noofBytes parameter must be the multiple of 512.
 *
 *   @b Modifies
 *   @n readBuffer will be populated.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pSdCardObj;
            CSL_MMCCardCsdObj     pSdCardCsdObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16                clkDivValue;
            Uint16                noOfBytes;
            Uint16                cardAddr;
            Uint16                pReadBuffer;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_SD_CARD;
   clkDivValue = 0x1 //as SD clock max is 50MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);

            status = SD_getCardCsd(hMmcsd, &pSdCardCsdObj);
   For example following value will be populated.
    pSdCardCsdObj->readBlLen         = ;
    pSdCardCsdObj->cSize  = ;
    These value will be useful to fetch the card specific information
     like these-----
    These figure are tested with 1GB Ultra SD Card
    blockLength      = 512 Bytes
    cardCapacity     = 0x1015808000 Bytes
    totalSectors     = 0x1984000 sector

          cardAddr = 0x100;
          noOfBytes = 512;

            status = MMC_read(hMmcsd, cardAddr, noOfBytes, &pReadBuffer);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_read(
               CSL_MmcsdHandle    hMmcsd,
               Uint32             cardAddr,
               Uint16             noOfBytes,
               Uint16             *pReadBuffer);

/** ===========================================================================
 *   @n@b MMC_write
 *
 *   @b Description
 *   @n This function is used for write operation to the card according to the
 *      passed write buffer, valid location and length of data.
 *
 *      'cardAddr' represents the adrress location in the card to be accessed.
 *      For the standard capacity cards this parameter will be a value in
 *      multiples of 512. That means to write a sector number 1 cardAddr
 *      will be 1*512, to write a sector number 2 cardAddr will be 2*512
 *      and so on.
 *      For the high capacity cards 'cardAddr' parameter will be same as the
 *      sector numebr. That means to write a sector number 1 cardAddr will be
 *      1, to write a sector number 2 cardAddr will be 2 and so on.
 *      Reason for this is high capacity cards uses BLOCK addressing instead
 *      of the BYTE addressing used by the standard capacty cards to increase
 *      the addressible memory capacity.
 *
 *      Detection of high capacity cards can be verified using the flag
 *      'sdHcDetected' in the MMCSD card object structure.
 *      sdHcDetected = TRUE      - SD card is high capacity card
 *      sdHcDetected = FALSE     - SD card is standard capacity card
 *
 *      NOTE: CARE SHOULD BE TAKEN WHILE PASSING THE 'cardAddr' PARAMETER.
 *      USING BYTE ADDRESSING WITH HIGH CAPACITY CARDS WILL LEAD TO OUT OF
 *      SECTOR BOUNDARY ACCESS AND RESULTS IN CODE HANGING FOR MMCSD RESPONSE.
 *
 *      NOTE: Endian mode of the data transfer depends on the parameter
 *      'writeEndianMode' in the MMC handle. Default value for the endian mode
 *      is 'LITTLE ENDIAN' which will be set during MMC open. Endian mode can
 *      be configured using MMC_setEndianMode(). DO NOT CHANGE THE ENDIAN MODE
 *      WITH OUT USING THIS API.
 *
 *      NOTE: When transferring data in DMA mode, word swap will be done for
 *      the data buffer on PG1.4 and earlier versions of C5505 DSP.
 *      No word swap is required in upper layers.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            cardAddr          location to read from.
            noOfBytes         no of bytes to read.
            pWriteBuffer      pointer to a buffer.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *   @li                    CSL_EMMCSD_TIMEOUT  - card Response time out
 *
 *   <b> Pre Condition </b>
 *   @n  1:MMC_open() API should be called successfully.
 *   @n  2:MMC_selectCard() API should be called before this so that it will do
 *         some need ful work for particular card detected.
 *   @n  3: MMC_sendOpCond()for specific to card .
 *   @n  4: if Card detected is SD then call SD_getCardCsd()for specific to SD
 *      or if Card detected is SD then call MMC_getCardCsd()for specific to MMC
 *
 *   <b> Post Condition </b>
 *   @n  noofBytes parameter must be the multiple of 512.
 *
 *   @b Modifies
 *   @n MMC/SD card will populated with the passed buffer values.
 *
 *   @b Example
 *   @verbatim
            CSL_MmcsdHandle       hMmcsd;
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MMCCardObj        pSdCardObj;
            CSL_MMCCardCsdObj     pSdCardCsdObj;
            CSL_MmcsdInstId       instId;
            CSL_status            status;
            Uint16                clkDivValue;
            Uint16                noOfBytes;
            Uint16                cardAddr;
            Uint16                pWriteBuffer;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            status = MMC_selectCard(hMmcsd, &pMmcCardObj);

 pMmmcCardObj-> cardType = CSL_SD_CARD;
   clkDivValue = 0x1 //as SD clock max is 50MHz and Function clock is 100MHz
            status = MMC_sendOpCond(hMmcsd, clkDivValue);

            status = SD_getCardCsd(hMmcsd, &pSdCardCsdObj);
   For example following value will be populated.
    pSdCardCsdObj->readBlLen         = ;
    pSdCardCsdObj->cSize  = ;
    These value will be useful to fetch the card specific information
     like these-----
    These figure are tested with 1GB Ultra SD Card
    blockLength      = 512 Bytes
    cardCapacity     = 0x1015808000 Bytes
    totalSectors     = 0x1984000 sector

          cardAddr = 0x100;
          noOfBytes = 512;

            status = MMC_write(hMmcsd, cardAddr, noOfBytes, &pWriteBuffer);
     @endverbatim
 *  ===========================================================================
 */
 CSL_Status MMC_write(
               CSL_MmcsdHandle   hMmcsd,
               Uint32             cardAddr,
               Uint16             noOfBytes,
               Uint16             *pWriteBuffer);

/** ===========================================================================
 *   @n@b MMC_setDmaHandle
 *
 *   @b Description
 *   @n This function stores the DMA handles sent by the application program.
 *      DMA handle stored in MMCSD handle will be used by the MMC read/write
 *      APIs to transfer the data in DMA mode. This API requires that MMCSD
 *      operating mode should be set to DMA using MMC_open function.
 *      DMA channel handles should be sent by the application in proper order.
 *      DMA channel needs to opened before calling this API. This channels
 *      will be closed by the MMC_close API.
 *
 *      NOTE:This API should not be called when MMCSD is operating Polled mode.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd       MMCSD handle
            hDmaWrite    Handle to DMA channel used for MMCSD write operation
            hDmaRead     Handle to DMA channel used for MMCSD read operation
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li            CSL_SOK            - Returned for Success
 *   @li            CSL_ESYS_BADHANDLE - Invalid MMSDC handle
 *   @li            CSL_ESYS_INVPARAMS - Invalid DMA handle
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() and DMA_open() functions should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n   Stores the DMA handle in MMC handle
 *
 *   @b Modifies
 *   @n    MMC handle
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_DMA_Handle        dmaWrHandle;
            CSL_DMA_Handle        dmaRdHandle;
            CSL_DMA_ChannelObj    dmaWrChanObj;
            CSL_DMA_ChannelObj    dmaRdChanObj;

            CSL_MmcsdInstId       instId;
            CSL_status            status;

            instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_DMA,
                              &status);

            dmaWrHandle = DMA_open(&dmaWrChanObj, CSL_DMA_CHAN0);

            dmaRdHandle = DMA_open(&dmaRdChanObj, CSL_DMA_CHAN1);

            // Set DMA handle
            status = MMC_setDmaHandle(hMmcsd, dmaWrHandle, dmaRdHandle);
            ...
    @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setDmaHandle (CSL_MmcsdHandle    hMmcsd,
                             CSL_DMA_Handle     hDmaWrite,
                             CSL_DMA_Handle     hDmaRead);

/** ===========================================================================
 *   @n@b MMC_setDmaCallback
 *
 *   @b Description
 *   @n This function stores the DMA call back function pointer in the MMCSD
 *      handle. This callback pointer is used by the MMCSD read/write APIs to
 *      issue callback after starting the DMA data transfer.This is to
 *      facilitate application/driver programs handle DMA transfer completion
 *      interrupt in their own way depending on their requirements.
 *      Call back function will be called from the MMCSD read/write APIs
 *      provided that the callback is set using this API.
 *      In case of not calling this API, no callback will be issued and DMA
 *      transfer completion is verified by the MMCSD read/write APIs using
 *      DMA_getStatus function.
 *      Call back function is having two parameters: First parameter is handle
 *      to the MMCSD module and second parameter is handle to the DMA channel
 *      on which data transfer has started by the MMCSD module.
 *
 *      NOTE: Same callback pointer will be used by both read and write APIs.
 *            No need to call this API when MMCSD is operation in polled mode.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd         MMCSD handle
            dmaCallback    DMA callback pointer
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li            CSL_SOK            - Returned for Success
 *   @li            CSL_ESYS_BADHANDLE - Invalid MMSDC handle
 *   @li            CSL_ESYS_INVPARAMS - Invalid input parameters
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n   Stores the DMA callback pointer in MMC handle
 *
 *   @b Modifies
 *   @n    MMC handle
 *
 *   @b Example
 *   @verbatim
 			void dmaCallbackFunction(void *mmcsdHandle, void *dmaHandle);
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_DMA_Handle        dmaHandle;
            CSL_DMA_ChannelObj    dmaChanObj;
            CSL_DMA_Config        dmaConfig;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

            instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_DMA,
                              &status);

            status = MMC_setDmaCallback(hMmcsd, dmaCallbackFunction);
            ...
    @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setDmaCallback (CSL_MmcsdHandle          hMmcsd,
                               CSL_MMCDmaCallBackPtr    dmaCallback);

/** ===========================================================================
 *   @n@b MMC_setDmaChanConfig
 *
 *   @b Description
 *   @n This function is used to set the DMA channel configurations.
 *      DMA channel configuration values sent by the application are stored
 *      in the MMCSD handle and used by the MMC write and read functions.
 *      DMA read and write channel configurations can be set independently
 *      and only one channel at a time using this function. Direction of
 *      the DMA channel is identified using the member 'chanDir' of
 *      CSL_MMCDmaConfig structure. Operating mode of the MMCSD module
 *      needs to be set to DMA mode for using this API.
 *
 *      Members of CSL_MMCDmaConfig structure are subset of CSL_DMA_Config
 *      structure. Other configuration values DMA sorce address, destination
 *      address, DMA data length etc are not configurable by MMCSD application
 *      program and are set by the MMCSD read/write API depending on the
 *      request from file system.
 *
 *      Only 4word and 8word DMA burst length is allowed for MMCSD (burstLen).
 *      Any other burst length will be ingnored and DMA will be configured to
 *      8word burst length by defualt.
 *
 *      This API is an optional one. Default DMA configurations are assigned by
 *      the MMC_open function. No need to call this API until and unless
 *      a different DMA configurations are required by the application.
 *
 *      NOTE:This API should not be called when MMCSD is operating Polled mode.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd       MMCSD handle
            dmaConfig    DMA configuration structure
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li            CSL_SOK            - Returned for Success
 *   @li            CSL_ESYS_BADHANDLE - Invalid MMSDC handle
 *   @li            CSL_ESYS_INVPARAMS - Invalid configuration parameters
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n   Stores the DMA configuration values in MMC handle
 *
 *   @b Modifies
 *   @n    MMC handle
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj    pMmcsdContObj;
            CSL_MmcsdHandle         hMmcsd;;
            CSL_MmcsdDmaConfig      dmaWriteCfg;
            CSL_MmcsdDmaConfig      dmaReadCfg;
            CSL_MmcsdInstId         instId;
            CSL_status              status;

            instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_DMA,
                              &status);

			dmaWriteCfg.autoMode     = CSL_DMA_AUTORELOAD_DISABLE;
			dmaWriteCfg.burstLen     = CSL_DMA_TXBURST_8WORD;
			dmaWriteCfg.chanDir      = CSL_DMA_WRITE;
			dmaWriteCfg.dmaInt       = CSL_DMA_INTERRUPT_ENABLE;

			// Set the DMA write channel configuration
            status = MMC_setDmaChanConfig(hMmcsd, dmaWriteCfg);

			dmaReadCfg.autoMode     = CSL_DMA_AUTORELOAD_DISABLE;
			dmaReadCfg.burstLen     = CSL_DMA_TXBURST_8WORD;
			dmaReadCfg.chanDir      = CSL_DMA_READ;
			dmaReadCfg.dmaInt       = CSL_DMA_INTERRUPT_ENABLE;

			// Set the DMA read channel configuration
            status = MMC_setDmaChanConfig(hMmcsd, dmaReadCfg);

    @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setDmaChanConfig (CSL_MmcsdHandle       hMmcsd,
                                 CSL_MmcsdDmaConfig    dmaConfig);

/** ===========================================================================
 *   @n@b MMC_setEndianMode
 *
 *   @b Description
 *   @n This function is used to set endian mode of the MMC/SD controller.
 *      Endian mode set using this API decides the way in which data is
 *      transferred from FIFO to storage device.
 *
 *      Default endianness of MMCSD controller:
 *      Chip C5504 and C5505: LITTLE ENDIAN.
 *      Chip C5514 and C5515: BIG ENDIAN.
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd             MMCSD handle
            writeEndianMode    Endian mode for MMC/SD write operation
            readEndianMode     Endian mode for MMC/SD read operation
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li            CSL_SOK            - Returned for Success
 *   @li            CSL_ESYS_BADHANDLE - Invalid MMSDC handle
 *   @li            CSL_ESYS_INVPARAMS - Invalid input parameters
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n   Sets MMC/SD endian mode for write and operations
 *
 *   @b Modifies
 *   @n    MMC/SD control register
 *
 *   @b Example
 *   @verbatim

			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_status            status;

            instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_DMA,
                              &status);

            status = MMC_setEndianMode(hMmcsd, CSL_MMCSD_ENDIAN_LITTLE,
                                       CSL_MMCSD_ENDIAN_LITTLE);
            ...
    @endverbatim
 *  ===========================================================================
 */
CSL_Status MMC_setEndianMode (CSL_MmcsdHandle        hMmcsd,
	                          CSL_MmcsdEndianMode    writeEndianMode,
                              CSL_MmcsdEndianMode    readEndianMode);
/**
@} */

/******************************************************************************
 * CSL MMCSD Inline function
 *****************************************************************************/
/** @addtogroup CSL_MMCSDC_INLINE_FUNCTION
 @{ */

/** ===========================================================================
 *   @n@b MMC_getEventId
 *
 *   @b Description
 *   @n Function return the events of MMCSD(Status of MMCSD Event).
 *
 *   @b Arguments
 *   @verbatim
            hMmcsd            Handle to the MMCSD
            maskValue         mask value to specify the interrupt state.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  MMC_open() API should be called successfully before this.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_MMCControllerObj  pMmcsdContObj;
            CSL_MmcsdHandle       hMmcsd;
            CSL_MmcsdInstId       instId;
            CSL_MMCSDEventType    eventId;
            CSL_status            status;

               instId = CSL_MMCSD0_INST;

            hMmcsd = MMC_open(&pMmcsdContObj, instId, CSL_MMCSD_OPMODE_POLLED,
                              &status);

            eventId = MMC_getEventId(hMmcsd);
     @endverbatim
 *  ===========================================================================
 */
static inline
CSL_MMCSDEventType MMC_getEventId(
                          CSL_MmcsdHandle     hMmcsd)
{

    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_DATDNE_MASK)
        return CSL_MMCSD_EDATDNE_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_BSYDNE_MASK)
        return CSL_MMCSD_EBSYDNE_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_RSPDNE_MASK)
        return CSL_MMCSD_ERSPDNE_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_TOUTRD_MASK)
        return CSL_MMCSD_ETOUTRD_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_TOUTRS_MASK)
        return CSL_MMCSD_ETOUTRS_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_CRCWR_MASK)
        return CSL_MMCSD_ECRCWR_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_CRCRD_MASK)
        return CSL_MMCSD_ECRCRD_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_CRCRS_MASK)
        return CSL_MMCSD_ECRCRS_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_DXRDY_MASK)
        return CSL_MMCSD_EDXRDY_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_DRRDY_MASK)
        return CSL_MMCSD_EDRRDY_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_DATED_MASK)
        return CSL_MMCSD_EDATED_INTERRUPT;
    if(hMmcsd->mmcRegs->MMCST0 & CSL_MMCSD_MMCST0_TRNDNE_MASK)
        return CSL_MMCSD_ETRNDNE_INTERRUPT;

    return CSL_MMCSD_INTERRUPT_NONE;
}
/**
@} */

#ifdef __cplusplus
}
#endif
#endif /* _CSL_MMCSD_H_ */

