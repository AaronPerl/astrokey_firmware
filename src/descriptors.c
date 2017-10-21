/*******************************************************************************
* @file descriptors.c
* @brief USB descriptors.
* @author PLACEHOLDER
* @version PLACEHOLDER
*******************************************************************************/
//LICENSE PLACEHOLDER


//=============================================================================
// src/descriptors.c: generated by Hardware Configurator
//
// This file is only generated if it does not exist. Modifications in this file
// will persist even if Configurator generates code. To refresh this file,
// you must first delete it and then regenerate code.
//=============================================================================

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <si_toolchain.h>
#include <endian.h>
#include <stdlib.h>
#include <string.h>
#include <efm8_usb.h>
#include "descriptors.h"


#ifdef __cplusplus
extern "C" {
#endif



// HID Report Descriptor for Interface 0
SI_SEGMENT_VARIABLE(ReportDescriptor0[69],
                    const uint8_t,
                    SI_SEG_CODE) =
{

  0x05, 0x01,                      // USAGE_PAGE (Generic Desktop)
  0x09, 0x06,                      // USAGE (Keyboard)
  0xa1, 0x01,                      // COLLECTION (Application)
  0x05, 0x07,                      // USAGE_PAGE (Keyboard)
  0x19, 0xe0,                      // USAGE_MINIMUM (Keyboard LeftControl)
  0x29, 0xe7,                      // USAGE_MAXIMUM (Keyboard Right GUI)
  0x15, 0x00,                      // LOGICAL_MINIMUM (0)
  0x25, 0x01,                      // LOGICAL_MAXIMUM (1)
  0x75, 0x01,                      // REPORT_SIZE (1)
  0x95, 0x08,                      // REPORT_COUNT (8)
  0x81, 0x02,                      // INPUT (Data,Var,Abs)
  0x15, 0x00,                      // LOGICAL_MINIMUM (0)
  0x25, 0x01,                      // LOGICAL_MAXIMUM (1)
  0x75, 0x01,                      // REPORT_SIZE (1)
  0x95, 0x08,                      // REPORT_COUNT (8)
  0x81, 0x01,                      // INPUT (Cnst,Ary,Abs)
  0x19, 0x00,                      // USAGE_MINIMUM (Reserved (no event indicated))
  0x29, 0x65,                      // USAGE_MAXIMUM (Keyboard Application)
  0x15, 0x00,                      // LOGICAL_MINIMUM (0)
  0x25, 0x65,                      // LOGICAL_MAXIMUM (101)
  0x75, 0x08,                      // REPORT_SIZE (8)
  0x95, 0x06,                      // REPORT_COUNT (6)
  0x81, 0x00,                      // INPUT (Data,Ary,Abs)
  0x05, 0x08,                      // USAGE_PAGE (LEDs)
  0x19, 0x01,                      // USAGE_MINIMUM (Num Lock)
  0x29, 0x03,                      // USAGE_MAXIMUM (Scroll Lock)
  0x15, 0x00,                      // LOGICAL_MINIMUM (0)
  0x25, 0x01,                      // LOGICAL_MAXIMUM (1)
  0x75, 0x01,                      // REPORT_SIZE (1)
  0x95, 0x03,                      // REPORT_COUNT (3)
  0x91, 0x02,                      // OUTPUT (Data,Var,Abs)
  0x75, 0x01,                      // REPORT_SIZE (1)
  0x95, 0x05,                      // REPORT_COUNT (5)
  0x91, 0x01,                      // OUTPUT (Cnst,Ary,Abs)
  0xc0                             // END_COLLECTION

};

SI_SEGMENT_VARIABLE(deviceDesc[],
                    const USB_DeviceDescriptor_TypeDef,
                    SI_SEG_CODE) =
{
  USB_DEVICE_DESCSIZE,             // bLength
  USB_DEVICE_DESCRIPTOR,           // bLength
  htole16(0x0201),                 // bcdUSB
  0,                               // bDeviceClass
  0,                               // bDeviceSubClass
  0,                               // bDeviceProtocol
  64,                              // bMaxPacketSize
  USB_VENDOR_ID,                   // idVendor
  USB_PRODUCT_ID,                  // idProduct
  htole16(0x0100),                 // bcdDevice
  1,                               // iManufacturer
  2,                               // iProduct
  3,                               // iSerialNumber
  1,                               // bNumConfigurations
};

SI_SEGMENT_VARIABLE(configDesc[],
                    const uint8_t,
                    SI_SEG_CODE) =
{
  USB_CONFIG_DESCSIZE,             // bLength
  USB_CONFIG_DESCRIPTOR,           // bLength
  0x22,                            // wTotalLength(LSB)
  0x00,                            // wTotalLength(MSB)
  1,                               // bNumInterfaces
  1,                               // bConfigurationValue
  0,                               // iConfiguration

  CONFIG_DESC_BM_RESERVED_D7 |     // bmAttrib: Self powered
  CONFIG_DESC_BM_SELFPOWERED,

  CONFIG_DESC_MAXPOWER_mA(100),    // bMaxPower: 100 mA

  //Interface 0 Descriptor
  USB_INTERFACE_DESCSIZE,          // bLength
  USB_INTERFACE_DESCRIPTOR,        // bDescriptorType
  0,                               // bInterfaceNumber
  0,                               // bAlternateSetting
  1,                               // bNumEndpoints
  3,                               // bInterfaceClass: HID (Human Interface Device)
  0,                               // bInterfaceSubClass
  1,                               // bInterfaceProtocol
  0,                               // iInterface

  //HID Descriptor
  USB_HID_DESCSIZE,                // bLength
  USB_HID_DESCRIPTOR,              // bLength
  0x11,                            // bcdHID (LSB)
  0x01,                            // bcdHID (MSB)
  0,                               // bCountryCode
  1,                               // bNumDescriptors
  USB_HID_REPORT_DESCRIPTOR,       // bDescriptorType
  sizeof( ReportDescriptor0 ),     // wDescriptorLength(LSB)
  sizeof( ReportDescriptor0 )>>8,    // wDescriptorLength(MSB)

  //Endpoint 1 IN Descriptor
  USB_ENDPOINT_DESCSIZE,           // bLength
  USB_ENDPOINT_DESCRIPTOR,         // bDescriptorType
  0x81,                            // bEndpointAddress
  USB_EPTYPE_INTR,                 // bAttrib
  0x40,                            // wMaxPacketSize (LSB)
  0x00,                            // wMaxPacketSize (MSB)
  24,                              // bInterval
};

SI_SEGMENT_VARIABLE(bosDesc,
		    const struct{USB_BOSDescriptor_TypeDef bos; WebUSB_DevCapability_TypeDef cap;},
		    SI_SEG_CODE) =
{
  // BOS Descriptor
  {
    USB_BOS_DESCRIPTOR_SIZE,  // Size of descriptor
    USB_BOS_DESCRIPTOR_TYPE,  // BOS Descriptor type
    USB_BOS_DESCRIPTOR_SIZE + // Length of this descriptor
      WEBUSB_CAPABILITY_SIZE, // and all of its sub-descriptors
    1                         // The number of separate device capability descriptors in the BOS
  },
  // WebUSB Capability Descriptor
  {
    WEBUSB_CAPABILITY_SIZE, // Size of descriptor (24)
    WEBUSB_CAPABILITY_TYPE, // Device Capability descriptor type (0x10)
    WEBUSB_PLATFORM_TYPE,   // Platform capability type (0x05).
    0,                      // This field is reserved and shall be set to zero.
    {
      0x38, 0xB6, 0x08, 0x34, 0xA9, 0x09, 0xA0, 0x47,
      0x8B, 0xFD, 0xA0, 0x76, 0x88, 0x15, 0xB6, 0x65
    },                      // WebUSB UUID {3408b638-09a9-47a0-8bfd-a0768815b665}.
    0x0100,                 // Protocol version supported. Must be set to 0x0100.
    WEBUSB_BREQUEST,        // bRequest value used for issuing WebUSB requests.
    1                       // URL Descriptor index of the device's landing page.
  }
};

#define LANG_STRING   htole16( SLAB_USB_LANGUAGE )
#define MFR_STRING    'A','s','t','r','o','K','e','y','\0'
#define MFR_SIZE      9
#define PROD_STRING   'A','s','t','r','o','K','e','y','\0'
#define PROD_SIZE     9
#define SER_STRING    '0','1','2','3','4','5','6','7','8','A','B','C','D','E','F','\0'
#define SER_SIZE      16

#define URL0_STRING    'a','s','t','r','o','k','e','y','.','i','o','\0'
#define URL0_SIZE      9
#define URL1_STRING   'A','s','t','r','o','K','e','y','\0'
#define URL1_SIZE     9


LANGID_STATIC_CONST_STRING_DESC( langDesc[], LANG_STRING);
UTF16LE_PACKED_STATIC_CONST_STRING_DESC( mfrDesc[], MFR_STRING, MFR_SIZE );
UTF16LE_PACKED_STATIC_CONST_STRING_DESC( prodDesc[], PROD_STRING, PROD_SIZE );
UTF16LE_PACKED_STATIC_CONST_STRING_DESC( serDesc[], SER_STRING, SER_SIZE );

//-----------------------------------------------------------------------------
SI_SEGMENT_VARIABLE_SEGMENT_POINTER(myUsbStringTable_USEnglish[], static const USB_StringDescriptor_TypeDef, SI_SEG_GENERIC, const SI_SEG_CODE) = 
{
  (SI_VARIABLE_SEGMENT_POINTER(, uint8_t, SI_SEG_CODE))langDesc,
  mfrDesc,
  prodDesc,
  serDesc,

};

//-----------------------------------------------------------------------------
SI_SEGMENT_VARIABLE(initstruct,
                    const USBD_Init_TypeDef,
                    SI_SEG_CODE) =
{
  (SI_VARIABLE_SEGMENT_POINTER(, USB_DeviceDescriptor_TypeDef, SI_SEG_GENERIC))deviceDesc,              // deviceDescriptor
  (SI_VARIABLE_SEGMENT_POINTER(, USB_ConfigurationDescriptor_TypeDef, SI_SEG_GENERIC))configDesc,       // configDescriptor
  (SI_VARIABLE_SEGMENT_POINTER(, USB_StringTable_TypeDef, SI_SEG_GENERIC))myUsbStringTable_USEnglish,   // stringDescriptors
  sizeof(myUsbStringTable_USEnglish) / sizeof(myUsbStringTable_USEnglish[0])                            // numberOfStrings
};

//-----------------------------------------------------------------------------
SI_SEGMENT_VARIABLE_SEGMENT_POINTER(WebUSB_URLTable[], static const USB_StringDescriptor_TypeDef, SI_SEG_GENERIC, const SI_SEG_CODE) =
{
  (SI_VARIABLE_SEGMENT_POINTER(, uint8_t, SI_SEG_CODE))langDesc,
  mfrDesc,
  prodDesc,
  serDesc,

};


#ifdef __cplusplus
}
#endif


