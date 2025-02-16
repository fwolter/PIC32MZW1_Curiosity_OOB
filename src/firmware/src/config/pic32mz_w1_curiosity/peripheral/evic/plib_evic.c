/*******************************************************************************
  EVIC PLIB Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    plib_evic.c

  Summary:
    EVIC PLIB Source File

  Description:
    None

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#include "device.h"
#include "plib_evic.h"


// *****************************************************************************
// *****************************************************************************
// Section: IRQ Implementation
// *****************************************************************************
// *****************************************************************************

void EVIC_Initialize( void )
{
    INTCONSET = _INTCON_MVEC_MASK;

    /* Set up priority and subpriority of enabled interrupts */
    IPC0SET = 0x4 | 0x0;  /* CORE_TIMER:  Priority 1 / Subpriority 0 */
    IPC2SET = 0x400 | 0x0;  /* TIMER_2:  Priority 1 / Subpriority 0 */
    IPC3SET = 0x40000 | 0x0;  /* TIMER_3:  Priority 1 / Subpriority 0 */
    IPC8SET = 0x400 | 0x0;  /* RTCC:  Priority 1 / Subpriority 0 */
    IPC8SET = 0x40000 | 0x0;  /* USB:  Priority 1 / Subpriority 0 */
    IPC9SET = 0x4 | 0x0;  /* SPI1_RX:  Priority 1 / Subpriority 0 */
    IPC9SET = 0x400 | 0x0;  /* SPI1_TX:  Priority 1 / Subpriority 0 */
    IPC9SET = 0x40000 | 0x0;  /* UART1_FAULT:  Priority 1 / Subpriority 0 */
    IPC9SET = 0x4000000 | 0x0;  /* UART1_RX:  Priority 1 / Subpriority 0 */
    IPC10SET = 0x4 | 0x0;  /* UART1_TX:  Priority 1 / Subpriority 0 */
    IPC14SET = 0x4000000 | 0x0;  /* I2C2_BUS:  Priority 1 / Subpriority 0 */
    IPC15SET = 0x400 | 0x0;  /* I2C2_MASTER:  Priority 1 / Subpriority 0 */
    IPC20SET = 0x4000000 | 0x0;  /* RFSMC:  Priority 1 / Subpriority 0 */
    IPC21SET = 0x4 | 0x0;  /* RFMAC:  Priority 1 / Subpriority 0 */
    IPC21SET = 0x40000 | 0x0;  /* RFTM0:  Priority 1 / Subpriority 0 */
    IPC30SET = 0x400 | 0x0;  /* ADC_DATA15:  Priority 1 / Subpriority 0 */


}

void EVIC_SourceEnable( INT_SOURCE source )
{
    volatile uint32_t *IECx = (volatile uint32_t *) (&IEC0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t *IECxSET = (volatile uint32_t *)(IECx + 2);

    *IECxSET = 1 << (source & 0x1f);
}

void EVIC_SourceDisable( INT_SOURCE source )
{
    volatile uint32_t *IECx = (volatile uint32_t *) (&IEC0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t *IECxCLR = (volatile uint32_t *)(IECx + 1);

    *IECxCLR = 1 << (source & 0x1f);
}

bool EVIC_SourceIsEnabled( INT_SOURCE source )
{
    volatile uint32_t *IECx = (volatile uint32_t *) (&IEC0 + ((0x10 * (source / 32)) / 4));

    return (bool)((*IECx >> (source & 0x1f)) & 0x01);
}

bool EVIC_SourceStatusGet( INT_SOURCE source )
{
    volatile uint32_t *IFSx = (volatile uint32_t *)(&IFS0 + ((0x10 * (source / 32)) / 4));

    return (bool)((*IFSx >> (source & 0x1f)) & 0x1);
}

void EVIC_SourceStatusSet( INT_SOURCE source )
{
    volatile uint32_t *IFSx = (volatile uint32_t *) (&IFS0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t *IFSxSET = (volatile uint32_t *)(IFSx + 2);

    *IFSxSET = 1 << (source & 0x1f);
}

void EVIC_SourceStatusClear( INT_SOURCE source )
{
    volatile uint32_t *IFSx = (volatile uint32_t *) (&IFS0 + ((0x10 * (source / 32)) / 4));
    volatile uint32_t *IFSxCLR = (volatile uint32_t *)(IFSx + 1);

    *IFSxCLR = 1 << (source & 0x1f);
}


/* End of file */
