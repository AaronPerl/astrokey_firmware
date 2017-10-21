//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8UB1_Register_Enums.h>
#include "InitDevice.h"

// USER PROTOTYPES
// USER FUNCTIONS


// $[Library Includes]
#include "efm8_usb.h"
#include "descriptors.h"
// [Library Includes]$

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	// Save the SFRPAGE
	uint8_t SFRPAGE_save = SFRPAGE;
	WDT_0_enter_DefaultMode_from_RESET();
	VREG_0_enter_DefaultMode_from_RESET();
	PORTS_0_enter_DefaultMode_from_RESET();
	PBCFG_0_enter_DefaultMode_from_RESET();
	CLOCK_0_enter_DefaultMode_from_RESET();
	CIP51_0_enter_DefaultMode_from_RESET();
	INTERRUPT_0_enter_DefaultMode_from_RESET();
	USBLIB_0_enter_DefaultMode_from_RESET();
	// Restore the SFRPAGE
	SFRPAGE = SFRPAGE_save;
	// [Config Calls]$


}


//================================================================================
// WDT_0_enter_DefaultMode_from_RESET
//================================================================================
extern void WDT_0_enter_DefaultMode_from_RESET(void) {
	// $[WDTCN - Watchdog Timer Control]
	//Disable Watchdog with key sequence
	WDTCN = 0xDE; //First key
	WDTCN = 0xAD; //Second key
	// [WDTCN - Watchdog Timer Control]$


}

//================================================================================
// VREG_0_enter_DefaultMode_from_RESET
//================================================================================
extern void VREG_0_enter_DefaultMode_from_RESET(void) {
	// $[REG0CN - Voltage Regulator 0 Control]
	// [REG0CN - Voltage Regulator 0 Control]$

	// $[REG1CN - Voltage Regulator 1 Control]
	/*
	// REG1ENB (Voltage Regulator 1 Disable) = ENABLED (Regulator is
	//     enabled.)
	// BIASENB (Regulator Bias Disable) = DISABLED (Regulator bias is
	//     disabled.)
	// SUSEN (Voltage Regulator 1 Suspend Enable) = NORMAL (The 5V regulator
	//     is in normal power mode. Normal mode is the highest performance mode
	//     for the regulator.)
	*/
	SFRPAGE = 0x20;
	REG1CN = REG1CN_REG1ENB__ENABLED | REG1CN_BIASENB__DISABLED | REG1CN_SUSEN__NORMAL;
	// [REG1CN - Voltage Regulator 1 Control]$


}

//================================================================================
// PORTS_0_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTS_0_enter_DefaultMode_from_RESET(void) {
	// $[P0 - Port 0 Pin Latch]
	// [P0 - Port 0 Pin Latch]$

	// $[P0MDOUT - Port 0 Output Mode]
	// [P0MDOUT - Port 0 Output Mode]$

	// $[P0MDIN - Port 0 Input Mode]
	// [P0MDIN - Port 0 Input Mode]$

	// $[P0SKIP - Port 0 Skip]
	// [P0SKIP - Port 0 Skip]$

	// $[P0MASK - Port 0 Mask]
	/*
	// B0 (Port 0 Bit 0 Mask Value) = IGNORED (P0.0 pin logic value is
	//     ignored and will not cause a port mismatch event.)
	// B1 (Port 0 Bit 1 Mask Value) = IGNORED (P0.1 pin logic value is
	//     ignored and will not cause a port mismatch event.)
	// B2 (Port 0 Bit 2 Mask Value) = COMPARED (P0.2 pin logic value is
	//     compared to P0MAT.2.)
	// B3 (Port 0 Bit 3 Mask Value) = COMPARED (P0.3 pin logic value is
	//     compared to P0MAT.3.)
	// B4 (Port 0 Bit 4 Mask Value) = IGNORED (P0.4 pin logic value is
	//     ignored and will not cause a port mismatch event.)
	// B5 (Port 0 Bit 5 Mask Value) = IGNORED (P0.5 pin logic value is
	//     ignored and will not cause a port mismatch event.)
	// B6 (Port 0 Bit 6 Mask Value) = IGNORED (P0.6 pin logic value is
	//     ignored and will not cause a port mismatch event.)
	// B7 (Port 0 Bit 7 Mask Value) = IGNORED (P0.7 pin logic value is
	//     ignored and will not cause a port mismatch event.)
	*/
	SFRPAGE = 0x00;
	P0MASK = P0MASK_B0__IGNORED | P0MASK_B1__IGNORED | P0MASK_B2__COMPARED
		 | P0MASK_B3__COMPARED | P0MASK_B4__IGNORED | P0MASK_B5__IGNORED
		 | P0MASK_B6__IGNORED | P0MASK_B7__IGNORED;
	// [P0MASK - Port 0 Mask]$

	// $[P0MAT - Port 0 Match]
	// [P0MAT - Port 0 Match]$


}

//================================================================================
// PORTS_1_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTS_1_enter_DefaultMode_from_RESET(void) {
	// $[P1 - Port 1 Pin Latch]
	// [P1 - Port 1 Pin Latch]$

	// $[P1MDOUT - Port 1 Output Mode]
	/*
	// B0 (Port 1 Bit 0 Output Mode) = PUSH_PULL (P1.0 output is push-pull.)
	// B1 (Port 1 Bit 1 Output Mode) = OPEN_DRAIN (P1.1 output is open-
	//     drain.)
	// B2 (Port 1 Bit 2 Output Mode) = OPEN_DRAIN (P1.2 output is open-
	//     drain.)
	// B3 (Port 1 Bit 3 Output Mode) = OPEN_DRAIN (P1.3 output is open-
	//     drain.)
	// B4 (Port 1 Bit 4 Output Mode) = PUSH_PULL (P1.4 output is push-pull.)
	// B5 (Port 1 Bit 5 Output Mode) = PUSH_PULL (P1.5 output is push-pull.)
	// B6 (Port 1 Bit 6 Output Mode) = PUSH_PULL (P1.6 output is push-pull.)
	// B7 (Port 1 Bit 7 Output Mode) = OPEN_DRAIN (P1.7 output is open-
	//     drain.)
	*/
	P1MDOUT = P1MDOUT_B0__PUSH_PULL | P1MDOUT_B1__OPEN_DRAIN | P1MDOUT_B2__OPEN_DRAIN
		 | P1MDOUT_B3__OPEN_DRAIN | P1MDOUT_B4__PUSH_PULL | P1MDOUT_B5__PUSH_PULL
		 | P1MDOUT_B6__PUSH_PULL | P1MDOUT_B7__OPEN_DRAIN;
	// [P1MDOUT - Port 1 Output Mode]$

	// $[P1MDIN - Port 1 Input Mode]
	/*
	// B0 (Port 1 Bit 0 Input Mode) = DIGITAL (P1.0 pin is configured for
	//     digital mode.)
	// B1 (Port 1 Bit 1 Input Mode) = DIGITAL (P1.1 pin is configured for
	//     digital mode.)
	// B2 (Port 1 Bit 2 Input Mode) = DIGITAL (P1.2 pin is configured for
	//     digital mode.)
	// B3 (Port 1 Bit 3 Input Mode) = DIGITAL (P1.3 pin is configured for
	//     digital mode.)
	// B4 (Port 1 Bit 4 Input Mode) = DIGITAL (P1.4 pin is configured for
	//     digital mode.)
	// B5 (Port 1 Bit 5 Input Mode) = DIGITAL (P1.5 pin is configured for
	//     digital mode.)
	// B6 (Port 1 Bit 6 Input Mode) = DIGITAL (P1.6 pin is configured for
	//     digital mode.)
	// B7 (Port 1 Bit 7 Input Mode) = ANALOG (P1.7 pin is configured for
	//     analog mode.)
	*/
	P1MDIN = P1MDIN_B0__DIGITAL | P1MDIN_B1__DIGITAL | P1MDIN_B2__DIGITAL
		 | P1MDIN_B3__DIGITAL | P1MDIN_B4__DIGITAL | P1MDIN_B5__DIGITAL
		 | P1MDIN_B6__DIGITAL | P1MDIN_B7__ANALOG;
	// [P1MDIN - Port 1 Input Mode]$

	// $[P1SKIP - Port 1 Skip]
	/*
	// B0 (Port 1 Bit 0 Skip) = NOT_SKIPPED (P1.0 pin is not skipped by the
	//     crossbar.)
	// B1 (Port 1 Bit 1 Skip) = SKIPPED (P1.1 pin is skipped by the
	//     crossbar.)
	// B2 (Port 1 Bit 2 Skip) = SKIPPED (P1.2 pin is skipped by the
	//     crossbar.)
	// B3 (Port 1 Bit 3 Skip) = SKIPPED (P1.3 pin is skipped by the
	//     crossbar.)
	// B4 (Port 1 Bit 4 Skip) = NOT_SKIPPED (P1.4 pin is not skipped by the
	//     crossbar.)
	// B5 (Port 1 Bit 5 Skip) = NOT_SKIPPED (P1.5 pin is not skipped by the
	//     crossbar.)
	// B6 (Port 1 Bit 6 Skip) = NOT_SKIPPED (P1.6 pin is not skipped by the
	//     crossbar.)
	// B7 (Port 1 Bit 7 Skip) = SKIPPED (P1.7 pin is skipped by the
	//     crossbar.)
	*/
	P1SKIP = P1SKIP_B0__NOT_SKIPPED | P1SKIP_B1__SKIPPED | P1SKIP_B2__SKIPPED
		 | P1SKIP_B3__SKIPPED | P1SKIP_B4__NOT_SKIPPED | P1SKIP_B5__NOT_SKIPPED
		 | P1SKIP_B6__NOT_SKIPPED | P1SKIP_B7__SKIPPED;
	// [P1SKIP - Port 1 Skip]$

	// $[P1MASK - Port 1 Mask]
	// [P1MASK - Port 1 Mask]$

	// $[P1MAT - Port 1 Match]
	// [P1MAT - Port 1 Match]$


}

//================================================================================
// PORTS_2_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTS_2_enter_DefaultMode_from_RESET(void) {
	// $[P2 - Port 2 Pin Latch]
	// [P2 - Port 2 Pin Latch]$

	// $[P2MDOUT - Port 2 Output Mode]
	/*
	// B0 (Port 2 Bit 0 Output Mode) = OPEN_DRAIN (P2.0 output is open-
	//     drain.)
	// B1 (Port 2 Bit 1 Output Mode) = OPEN_DRAIN (P2.1 output is open-
	//     drain.)
	// B2 (Port 2 Bit 2 Output Mode) = OPEN_DRAIN (P2.2 output is open-
	//     drain.)
	// B3 (Port 2 Bit 3 Output Mode) = PUSH_PULL (P2.3 output is push-pull.)
	*/
	P2MDOUT = P2MDOUT_B0__OPEN_DRAIN | P2MDOUT_B1__OPEN_DRAIN | P2MDOUT_B2__OPEN_DRAIN
		 | P2MDOUT_B3__PUSH_PULL;
	// [P2MDOUT - Port 2 Output Mode]$

	// $[P2MDIN - Port 2 Input Mode]
	// [P2MDIN - Port 2 Input Mode]$

	// $[P2SKIP - Port 2 Skip]
	/*
	// B0 (Port 2 Bit 0 Skip) = NOT_SKIPPED (P2.0 pin is not skipped by the
	//     crossbar.)
	// B1 (Port 2 Bit 1 Skip) = NOT_SKIPPED (P2.1 pin is not skipped by the
	//     crossbar.)
	// B2 (Port 2 Bit 2 Skip) = NOT_SKIPPED (P2.2 pin is not skipped by the
	//     crossbar.)
	// B3 (Port 2 Bit 3 Skip) = SKIPPED (P2.3 pin is skipped by the
	//     crossbar.)
	*/
	SFRPAGE = 0x20;
	P2SKIP = P2SKIP_B0__NOT_SKIPPED | P2SKIP_B1__NOT_SKIPPED | P2SKIP_B2__NOT_SKIPPED
		 | P2SKIP_B3__SKIPPED;
	// [P2SKIP - Port 2 Skip]$

	// $[P2MASK - Port 2 Mask]
	// [P2MASK - Port 2 Mask]$

	// $[P2MAT - Port 2 Match]
	// [P2MAT - Port 2 Match]$


}

//================================================================================
// PBCFG_0_enter_DefaultMode_from_RESET
//================================================================================
extern void PBCFG_0_enter_DefaultMode_from_RESET(void) {
	// $[XBR2 - Port I/O Crossbar 2]
	/*
	// WEAKPUD (Port I/O Weak Pullup Disable) = PULL_UPS_ENABLED (Weak
	//     Pullups enabled (except for Ports whose I/O are configured for analog
	//     mode).)
	// XBARE (Crossbar Enable) = ENABLED (Crossbar enabled.)
	// URT1E (UART1 I/O Enable) = DISABLED (UART1 I/O unavailable at Port
	//     pin.)
	// URT1RTSE (UART1 RTS Output Enable) = DISABLED (UART1 RTS1 unavailable
	//     at Port pin.)
	// URT1CTSE (UART1 CTS Input Enable) = DISABLED (UART1 CTS1 unavailable
	//     at Port pin.)
	*/
	XBR2 = XBR2_WEAKPUD__PULL_UPS_ENABLED | XBR2_XBARE__ENABLED | XBR2_URT1E__DISABLED
		 | XBR2_URT1RTSE__DISABLED | XBR2_URT1CTSE__DISABLED;
	// [XBR2 - Port I/O Crossbar 2]$

	// $[PRTDRV - Port Drive Strength]
	// [PRTDRV - Port Drive Strength]$

	// $[XBR0 - Port I/O Crossbar 0]
	// [XBR0 - Port I/O Crossbar 0]$

	// $[XBR1 - Port I/O Crossbar 1]
	// [XBR1 - Port I/O Crossbar 1]$


}

//================================================================================
// ADC_0_enter_DefaultMode_from_RESET
//================================================================================
extern void ADC_0_enter_DefaultMode_from_RESET(void) {
	// $[ADC0CN1 - ADC0 Control 1]
	// [ADC0CN1 - ADC0 Control 1]$

	// $[ADC0MX - ADC0 Multiplexer Selection]
	/*
	// ADC0MX (AMUX0 Positive Input Selection) = ADC0P15 (Select ADC0.15.)
	*/
	ADC0MX = ADC0MX_ADC0MX__ADC0P15;
	// [ADC0MX - ADC0 Multiplexer Selection]$

	// $[ADC0CF - ADC0 Configuration]
	/*
	// ADSC (SAR Clock Divider) = 0x07
	// AD8BE (8-Bit Mode Enable) = NORMAL (ADC0 operates in 10-bit or 12-bit
	//     mode (normal operation).)
	// ADGN (Gain Control) = GAIN_1 (The on-chip PGA gain is 1.)
	// ADTM (Track Mode) = TRACK_NORMAL (Normal Track Mode. When ADC0 is
	//     enabled, conversion begins immediately following the start-of-
	//     conversion signal.)
	*/
	ADC0CF = (0x07 << ADC0CF_ADSC__SHIFT) | ADC0CF_AD8BE__NORMAL | ADC0CF_ADGN__GAIN_1
		 | ADC0CF_ADTM__TRACK_NORMAL;
	// [ADC0CF - ADC0 Configuration]$

	// $[ADC0AC - ADC0 Accumulator Configuration]
	// [ADC0AC - ADC0 Accumulator Configuration]$

	// $[ADC0TK - ADC0 Burst Mode Track Time]
	// [ADC0TK - ADC0 Burst Mode Track Time]$

	// $[ADC0PWR - ADC0 Power Control]
	// [ADC0PWR - ADC0 Power Control]$

	// $[ADC0GTH - ADC0 Greater-Than High Byte]
	// [ADC0GTH - ADC0 Greater-Than High Byte]$

	// $[ADC0GTL - ADC0 Greater-Than Low Byte]
	// [ADC0GTL - ADC0 Greater-Than Low Byte]$

	// $[ADC0LTH - ADC0 Less-Than High Byte]
	// [ADC0LTH - ADC0 Less-Than High Byte]$

	// $[ADC0LTL - ADC0 Less-Than Low Byte]
	// [ADC0LTL - ADC0 Less-Than Low Byte]$

	// $[ADC0CN0 - ADC0 Control 0]
	/*
	// ADEN (ADC Enable) = ENABLED (Enable ADC0 (active and ready for data
	//     conversions).)
	// ADCM (Start of Conversion Mode Select) = TIMER3 (ADC0 conversion
	//     initiated on overflow of Timer 3.)
	*/
	ADC0CN0 &= ~ADC0CN0_ADCM__FMASK;
	ADC0CN0 |= ADC0CN0_ADEN__ENABLED
		 | ADC0CN0_ADCM__TIMER3;
	// [ADC0CN0 - ADC0 Control 0]$


}

//================================================================================
// VREF_0_enter_DefaultMode_from_RESET
//================================================================================
extern void VREF_0_enter_DefaultMode_from_RESET(void) {
	// $[REF0CN - Voltage Reference Control]
	/*
	// TEMPE (Temperature Sensor Enable) = TEMP_DISABLED (Disable the
	//     Temperature Sensor.)
	// GNDSL (Analog Ground Reference) = GND_PIN (The ADC0 ground reference
	//     is the GND pin.)
	// IREFLVL (Internal Voltage Reference Level) = 1P65 (The internal
	//     reference operates at 1.65 V nominal.)
	// REFSL (Voltage Reference Select) = VDD_PIN (The ADC0 voltage reference
	//     is the VDD pin.)
	*/
	REF0CN = REF0CN_TEMPE__TEMP_DISABLED | REF0CN_GNDSL__GND_PIN | REF0CN_IREFLVL__1P65
		 | REF0CN_REFSL__VDD_PIN;
	// [REF0CN - Voltage Reference Control]$


}

//================================================================================
// LFOSC_0_enter_DefaultMode_from_RESET
//================================================================================
extern void LFOSC_0_enter_DefaultMode_from_RESET(void) {
	// $[LFO0CN - Low Frequency Oscillator Control]
	/*
	// OSCLEN (Internal L-F Oscillator Enable) = ENABLED (Internal L-F
	//     Oscillator Enabled.)
	*/
	LFO0CN |= LFO0CN_OSCLEN__ENABLED;
	// [LFO0CN - Low Frequency Oscillator Control]$

	// $[Wait for LFOSC Ready]
	while ((LFO0CN & LFO0CN_OSCLRDY__BMASK) != LFO0CN_OSCLRDY__SET);
	// [Wait for LFOSC Ready]$


}

//================================================================================
// CLOCK_0_enter_DefaultMode_from_RESET
//================================================================================
extern void CLOCK_0_enter_DefaultMode_from_RESET(void) {
	// $[HFOSC1 Setup]
	// Ensure SYSCLK is > 24 MHz before switching to HFOSC1
	CLKSEL = CLKSEL_CLKSL__HFOSC0 | CLKSEL_CLKDIV__SYSCLK_DIV_1;
	CLKSEL = CLKSEL_CLKSL__HFOSC0 | CLKSEL_CLKDIV__SYSCLK_DIV_1;
	while(CLKSEL & CLKSEL_DIVRDY__BMASK == CLKSEL_DIVRDY__NOT_READY);
	// [HFOSC1 Setup]$

	// $[CLKSEL - Clock Select]
	/*
	// CLKSL (Clock Source Select) = HFOSC1 (Clock derived from the Internal
	//     High Frequency Oscillator 1.)
	// CLKDIV (Clock Source Divider) = SYSCLK_DIV_1 (SYSCLK is equal to
	//     selected clock source divided by 1.)
	// CLKSL (Clock Source Select) = HFOSC1 (Clock derived from the Internal
	//     High Frequency Oscillator 1.)
	// CLKDIV (Clock Source Divider) = SYSCLK_DIV_1 (SYSCLK is equal to
	//     selected clock source divided by 1.)
	*/
	CLKSEL = CLKSEL_CLKSL__HFOSC1 | CLKSEL_CLKDIV__SYSCLK_DIV_1;
	CLKSEL = CLKSEL_CLKSL__HFOSC1 | CLKSEL_CLKDIV__SYSCLK_DIV_1;
	while(CLKSEL & CLKSEL_DIVRDY__BMASK == CLKSEL_DIVRDY__NOT_READY);
	// [CLKSEL - Clock Select]$


}

//================================================================================
// CIP51_0_enter_DefaultMode_from_RESET
//================================================================================
extern void CIP51_0_enter_DefaultMode_from_RESET(void) {
	// $[PFE0CN - Prefetch Engine Control]
	/*
	// PFEN (Prefetch Enable) = ENABLED (Enable the prefetch engine (SYSCLK >
	//     25 MHz).)
	// FLRT (Flash Read Timing) = SYSCLK_BELOW_50_MHZ (SYSCLK < 50 MHz.)
	*/
	SFRPAGE = 0x10;
	PFE0CN = PFE0CN_PFEN__ENABLED | PFE0CN_FLRT__SYSCLK_BELOW_50_MHZ;
	// [PFE0CN - Prefetch Engine Control]$


}

//================================================================================
// INTERRUPT_0_enter_DefaultMode_from_RESET
//================================================================================
extern void INTERRUPT_0_enter_DefaultMode_from_RESET(void) {
	// $[EIE1 - Extended Interrupt Enable 1]
	/*
	// EADC0 (ADC0 Conversion Complete Interrupt Enable) = DISABLED (Disable
	//     ADC0 Conversion Complete interrupt.)
	// EWADC0 (ADC0 Window Comparison Interrupt Enable) = DISABLED (Disable
	//     ADC0 Window Comparison interrupt.)
	// ECP0 (Comparator0 (CP0) Interrupt Enable) = DISABLED (Disable CP0
	//     interrupts.)
	// ECP1 (Comparator1 (CP1) Interrupt Enable) = DISABLED (Disable CP1
	//     interrupts.)
	// EMAT (Port Match Interrupts Enable) = ENABLED (Enable interrupt
	//     requests generated by a Port Match.)
	// EPCA0 (Programmable Counter Array (PCA0) Interrupt Enable) = DISABLED
	//     (Disable all PCA0 interrupts.)
	// ESMB0 (SMBus (SMB0) Interrupt Enable) = DISABLED (Disable all SMB0
	//     interrupts.)
	// ET3 (Timer 3 Interrupt Enable) = DISABLED (Disable Timer 3
	//     interrupts.)
	*/
	SFRPAGE = 0x00;
	EIE1 = EIE1_EADC0__DISABLED | EIE1_EWADC0__DISABLED | EIE1_ECP0__DISABLED
		 | EIE1_ECP1__DISABLED | EIE1_EMAT__ENABLED | EIE1_EPCA0__DISABLED
		 | EIE1_ESMB0__DISABLED | EIE1_ET3__DISABLED;
	// [EIE1 - Extended Interrupt Enable 1]$

	// $[EIE2 - Extended Interrupt Enable 2]
	// [EIE2 - Extended Interrupt Enable 2]$

	// $[EIP1H - Extended Interrupt Priority 1 High]
	// [EIP1H - Extended Interrupt Priority 1 High]$

	// $[EIP1 - Extended Interrupt Priority 1 Low]
	// [EIP1 - Extended Interrupt Priority 1 Low]$

	// $[EIP2 - Extended Interrupt Priority 2]
	// [EIP2 - Extended Interrupt Priority 2]$

	// $[EIP2H - Extended Interrupt Priority 2 High]
	// [EIP2H - Extended Interrupt Priority 2 High]$

	// $[IE - Interrupt Enable]
	/*
	// EA (All Interrupts Enable) = ENABLED (Enable each interrupt according
	//     to its individual mask setting.)
	// EX0 (External Interrupt 0 Enable) = DISABLED (Disable external
	//     interrupt 0.)
	// EX1 (External Interrupt 1 Enable) = DISABLED (Disable external
	//     interrupt 1.)
	// ESPI0 (SPI0 Interrupt Enable) = DISABLED (Disable all SPI0
	//     interrupts.)
	// ET0 (Timer 0 Interrupt Enable) = DISABLED (Disable all Timer 0
	//     interrupt.)
	// ET1 (Timer 1 Interrupt Enable) = DISABLED (Disable all Timer 1
	//     interrupt.)
	// ET2 (Timer 2 Interrupt Enable) = DISABLED (Disable Timer 2 interrupt.)
	// ES0 (UART0 Interrupt Enable) = DISABLED (Disable UART0 interrupt.)
	*/
	IE = IE_EA__ENABLED | IE_EX0__DISABLED | IE_EX1__DISABLED | IE_ESPI0__DISABLED
		 | IE_ET0__DISABLED | IE_ET1__DISABLED | IE_ET2__DISABLED | IE_ES0__DISABLED;
	// [IE - Interrupt Enable]$

	// $[IP - Interrupt Priority]
	// [IP - Interrupt Priority]$

	// $[IPH - Interrupt Priority High]
	// [IPH - Interrupt Priority High]$


}

//================================================================================
// USBLIB_0_enter_DefaultMode_from_RESET
//================================================================================
extern void USBLIB_0_enter_DefaultMode_from_RESET(void) {
	// $[USBD Init]
	USBD_Init( &initstruct);
	// [USBD Init]$


}


