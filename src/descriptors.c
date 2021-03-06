//-----------------------------------------------------------------------------
// descriptors.c
//-----------------------------------------------------------------------------
// Copyright 2018 AstroKey
// https://github.com/AstroKey/astrokey_firmware/blob/master/LICENSE
//
// File Description:
//
// Implementations of AstroKey USB descriptors.
//
#include <si_toolchain.h>
#include <endian.h>
#include <stdlib.h>
#include <string.h>
#include <efm8_usb.h>
#include "astrokey.h"
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
  0x15, 0x00,                      // LOGICAL_MINIMUM (0)  // Modifiers
  0x25, 0x01,                      // LOGICAL_MAXIMUM (1)  // Modifiers
  0x75, 0x01,                      // REPORT_SIZE (1)      // Modifiers
  0x95, 0x08,                      // REPORT_COUNT (8)     // Modifiers
  0x81, 0x02,                      // INPUT (Data,Var,Abs) // Modifiers
  0x15, 0x00,                      // LOGICAL_MINIMUM (0)  // Reserved
  0x25, 0x01,                      // LOGICAL_MAXIMUM (1)  // Reserved
  0x75, 0x01,                      // REPORT_SIZE (1)      // Reserved
  0x95, 0x08,                      // REPORT_COUNT (8)     // Reserved
  0x81, 0x01,                      // INPUT (Cnst,Ary,Abs) // Reserved
  0x19, 0x00,                      // USAGE_MINIMUM (Reserved (no event indicated))  // Keys
  0x29, 0x65,                      // USAGE_MAXIMUM (Keyboard Application)           // Keys
  0x15, 0x00,                      // LOGICAL_MINIMUM (0)                            // Keys
  0x25, 0x65,                      // LOGICAL_MAXIMUM (101)                          // Keys
  0x75, 0x08,                      // REPORT_SIZE (8)                                // Keys
  0x95, 0x06,                      // REPORT_COUNT (6)                               // Keys
  0x81, 0x00,                      // INPUT (Data,Ary,Abs)                           // Keys
  0x05, 0x08,                      // USAGE_PAGE (LEDs)           // LEDs
  0x19, 0x01,                      // USAGE_MINIMUM (Num Lock)    // LEDs
  0x29, 0x03,                      // USAGE_MAXIMUM (Scroll Lock) // LEDs
  0x15, 0x00,                      // LOGICAL_MINIMUM (0)         // LEDs
  0x25, 0x01,                      // LOGICAL_MAXIMUM (1)         // LEDs
  0x75, 0x01,                      // REPORT_SIZE (1)             // LEDs
  0x95, 0x03,                      // REPORT_COUNT (3)            // LEDs
  0x91, 0x02,                      // OUTPUT (Data,Var,Abs)       // LEDs
  0x75, 0x01,                      // REPORT_SIZE (1)             // Padding
  0x95, 0x05,                      // REPORT_COUNT (5)            // Padding
  0x91, 0x01,                      // OUTPUT (Cnst,Ary,Abs)       // Padding
  0xc0                             // END_COLLECTION

};

// USB Device Descriptor
SI_SEGMENT_VARIABLE(deviceDesc[],
                    const USB_DeviceDescriptor_TypeDef,
                    SI_SEG_CODE) =
{
  USB_DEVICE_DESCSIZE,             // bLength
  USB_DEVICE_DESCRIPTOR,           // bLength
  htole16(0x0210),                 // bcdUSB
  0,                               // bDeviceClass (classes defined in interface descriptors)
  0,                               // bDeviceSubClass
  0,                               // bDeviceProtocol
  64,                              // bMaxPacketSize
  USB_VENDOR_ID,                   // idVendor
  USB_PRODUCT_ID,                  // idProduct
  htole16(0x0002),                 // bcdDevice
  1,                               // iManufacturer
  2,                               // iProduct
  3,                               // iSerialNumber
  1,                               // bNumConfigurations
};

// USB Configuration Descriptor for Configuration 1
SI_SEGMENT_VARIABLE(configDesc[],
                    const uint8_t,
                    SI_SEG_CODE) =
{
  USB_CONFIG_DESCSIZE,             // bLength
  USB_CONFIG_DESCRIPTOR,           // bDescriptorType
  0x2B,                            // wTotalLength(LSB)
  0x00,                            // wTotalLength(MSB)
  2,                               // bNumInterfaces
  1,                               // bConfigurationValue
  0,                               // iConfiguration

  CONFIG_DESC_BM_RESERVED_D7,      // bmAttrib: Bus-powered

  CONFIG_DESC_MAXPOWER_mA(500),    // bMaxPower: 100 mA

  //Interface 0 Descriptor
  USB_INTERFACE_DESCSIZE,          // bLength
  USB_INTERFACE_DESCRIPTOR,        // bDescriptorType
  0,                               // bInterfaceNumber
  0,                               // bAlternateSetting
  0,                               // bNumEndpoints
  0xFF,                            // bInterfaceClass: Vendor Specific
  0,                               // bInterfaceSubClass
  0,                               // bInterfaceProtocol
  0,                               // iInterface

  //Interface 1 Descriptor
  USB_INTERFACE_DESCSIZE,          // bLength
  USB_INTERFACE_DESCRIPTOR,        // bDescriptorType
  1,                               // bInterfaceNumber
  0,                               // bAlternateSetting
  1,                               // bNumEndpoints
  3,                               // bInterfaceClass: HID (Human Interface Device)
  0,                               // bInterfaceSubClass (0 = not bootable)
  1,                               // bInterfaceProtocol (1 = keyboard)
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
  sizeof( ReportDescriptor0 )>>8,  // wDescriptorLength(MSB)

  //Endpoint 1 IN Descriptor
  USB_ENDPOINT_DESCSIZE,           // bLength
  USB_ENDPOINT_DESCRIPTOR,         // bDescriptorType
  USB_EP_DIR_IN | 1,               // bEndpointAddress
  USB_EPTYPE_INTR,                 // bAttrib
  0x40,                            // wMaxPacketSize (LSB)
  0x00,                            // wMaxPacketSize (MSB)
  1,                               // bInterval
};

// USB Binary Object Store Descriptor
SI_SEGMENT_VARIABLE(bosDesc,
		    const USB_BOS_TypeDef,
		    SI_SEG_CODE) =
{
  // BOS Descriptor
  {
    sizeof(USB_BOSDescriptor_TypeDef), // Size of descriptor (5)
    USB_BOS_DESCRIPTOR_TYPE,           // BOS Descriptor type (0x0F)
    htole16(sizeof(USB_BOS_TypeDef)),  // Length of this descriptor and all of its sub-descriptors
    3                                  // The number of separate device capability descriptors in the BOS
  },
  // USB 2.0 Extension Capability Descriptor
  {
    sizeof(USB20_ExtCapability_TypeDef), // Size of descriptor (7)
    USB_BOS_CAPABILITY_TYPE,             // DEVICE CAPABILITY Descriptor type (0x10)
    USB_BOS_EXTENSION_CAPABILITY,        // USB 2.0 EXTENSION (0x02)
    htole32(0x00000000)                  // Bitmap encoding of supported device level features.
  },
  // WebUSB Capability Descriptor
  {
    sizeof(WebUSB_DevCapability_TypeDef), // Size of descriptor (24)
    USB_BOS_CAPABILITY_TYPE,              // Device Capability descriptor type (0x10)
    USB_BOS_PLATFORM_CAPABILITY,          // Platform capability type (0x05).
    0,                                    // This field is reserved and shall be set to zero.
    WEBUSB_DEVCAPABILITY_UUID,            // WebUSB UUID {3408b638-09a9-47a0-8bfd-a0768815b665}.
    htole16(0x0100),        // Protocol version supported. Must be set to 0x0100.
    WEBUSB_BREQUEST,        // bRequest value used for issuing WebUSB requests.
    1                       // URL Descriptor index of the device's landing page.
  },
  // MS_OS_20 Capability Descriptor
  {
    sizeof(MS_OS_20_DevCapability_TypeDef),          // Size of descriptor
    USB_BOS_CAPABILITY_TYPE,                         // Device Capability descriptor type (0x10)
    USB_BOS_PLATFORM_CAPABILITY,                     // Platform capability type (0x05).
    0,                                               // This field is reserved and shall be set to zero.
    MS_OS_20_DEVCAPABILITY_UUID,                     // Must be set to {D8DD60DF-4589-4CC7-9CD2-659D9E648A9F}.
    MS_OS_20_WINDOWS_VERSION,                        // Windows version
    htole16(sizeof(MS_OS_20_DescriptorSet_TypeDef)), // The length, in bytes of the MS OS 2.0 descriptor set.
    MS_OS_20_BREQEUST,                                // Vendor defined code to use to retrieve this version of the MS OS 2.0 descriptor and also to set alternate enumeration behavior on the device.
    0                                                // A non-zero value to send to the device to indicate that the device may return non-default USB descriptors for enumeration.
  }
};

// Microsoft OS 2.0 Descriptor Set
SI_SEGMENT_VARIABLE(msDesc, const MS_OS_20_DescriptorSet_TypeDef, SI_SEG_CODE) =
{
  {
    MS_DSH_S,                       // The length, in bytes, of this header. Shall be set to 10.
    MS_OS_20_SET_HEADER_DESCRIPTOR, // MS_OS_20_SET_HEADER_DESCRIPTOR
    MS_OS_20_WINDOWS_VERSION,       // Windows version.
    MS_DS_S                         // The size of entire MS OS 2.0 descriptor set. The value shall match the value in the descriptor set information structure.
  },
  {
    MS_CSH_S,                                 // The length, in bytes, of this subset header. Shall be set to 8.
    MS_OS_20_SUBSET_HEADER_CONFIGURATION,     // MS_OS_20_SUBSET_HEADER_CONFIGURATION
    0,                                        // The configuration value for the USB configuration to which this subset applies.
    0,                                        // Shall be set to 0.
    MS_CSH_S + MS_FSH_S + MS_CID_S + MS_DIG_S // The size of entire configuration subset including this header.
  },
  {
    MS_FSH_S,                        // The length, in bytes, of this subset header. Shall be set to 8.
    MS_OS_20_SUBSET_HEADER_FUNCTION, // MS_OS_20_SUBSET_HEADER_FUNCTION
    0,                               // The interface number for the first interface of the function to which this subset applies.
    0,                               // Shall be set to 0.
    MS_FSH_S + MS_CID_S + MS_DIG_S   // The size of entire function subset including this header.
  },
  {
    MS_CID_S,                          // The length, bytes, of the compatible ID descriptor including value descriptors. Shall be set to 20.
    MS_OS_20_FEATURE_COMPATIBLE_ID,    // MS_OS_20_FEATURE_COMPATIBLE_ID
    {'W','I','N','U','S','B',  0,  0}, // Compatible ID String
    {  0,  0,  0,  0,  0,  0,  0,  0}  // Sub-compatible ID String
  },
  {
    MS_DIG_S,                      // The length, in bytes, of this descriptor.
    MS_OS_20_FEATURE_REG_PROPERTY, // MS_OS_20_FEATURE_REG_PROPERTY
    MS_OS_20_REG_MULTI_SZ,         // The type of registry property. See Table 15. (REG_MULTI_SZ)
    htole16(0x2A),                 // The length of the property name. (0x2A)
    MS_OS_20_DEVICE_INT_GUID_NAME, // The name of registry property. ("DeviceInterfaceGUIDs")
    htole16(0x50),                 // The length of property data.
    {                              // Property data - GUID a74ea70e-6af5-4f72-a0c6-06d4f9390b27
      '{',0x00, 'a',0x00, '7',0x00, '4',0x00, 'e',0x00, 'a',0x00, '7',0x00, '0',0x00,
      'e',0x00, '-',0x00, '6',0x00, 'a',0x00, 'f',0x00, '5',0x00, '-',0x00, '4',0x00,
      'f',0x00, '7',0x00, '2',0x00, '-',0x00, 'a',0x00, '0',0x00, 'c',0x00, '6',0x00,
      '-',0x00, '0',0x00, '6',0x00, 'd',0x00, '4',0x00, 'f',0x00, '9',0x00, '3',0x00,
      '9',0x00, '0',0x00, 'b',0x00, '2',0x00, '7',0x00, '}',0x00,0x00,0x00,0x00,0x00
    }
  }
};

#define LANG_STRING   htole16( SLAB_USB_LANGUAGE )
#define MFR_STRING    'A','s','t','r','o','K','e','y','\0'
#define MFR_SIZE      9
#define PROD_STRING   'A','s','t','r','o','K','e','y','\0'
#define PROD_SIZE     9


LANGID_STATIC_CONST_STRING_DESC( langDesc[], LANG_STRING);
UTF16LE_PACKED_STATIC_CONST_STRING_DESC( mfrDesc[], MFR_STRING, MFR_SIZE );
UTF16LE_PACKED_STATIC_CONST_STRING_DESC( prodDesc[], PROD_STRING, PROD_SIZE );

// USB String Table
SI_SEGMENT_VARIABLE_SEGMENT_POINTER(myUsbStringTable_USEnglish[], static const USB_StringDescriptor_TypeDef, SI_SEG_GENERIC, const SI_SEG_CODE) =
{
  (SI_VARIABLE_SEGMENT_POINTER(, uint8_t, SI_SEG_CODE))langDesc,
  mfrDesc,
  prodDesc,
  serDesc,
};
// USB Initalization Struct
SI_SEGMENT_VARIABLE(initstruct,
                    const USBD_Init_TypeDef,
                    SI_SEG_CODE) =
{
  (SI_VARIABLE_SEGMENT_POINTER(, USB_DeviceDescriptor_TypeDef, SI_SEG_GENERIC))deviceDesc,              // deviceDescriptor
  (SI_VARIABLE_SEGMENT_POINTER(, USB_ConfigurationDescriptor_TypeDef, SI_SEG_GENERIC))configDesc,       // configDescriptor
  (SI_VARIABLE_SEGMENT_POINTER(, USB_StringTable_TypeDef, SI_SEG_GENERIC))myUsbStringTable_USEnglish,   // stringDescriptors
  sizeof(myUsbStringTable_USEnglish) / sizeof(myUsbStringTable_USEnglish[0])                            // numberOfStrings
};

#define URL0_STRING    'a','s','t','r','o','k','e','y','.','g','i','t','h','u','b','.','i','o'
#define URL0_SIZE      18

// WebUSB Landing Page URL Descriptor
URL_DESC( landingPage[] , URL0_SIZE, WEBUSB_SCHEME_HTTPS, URL0_STRING);

// WebUSB URL Descriptor Table
SI_SEGMENT_VARIABLE_SEGMENT_POINTER(myURLs[], const USB_URLDescriptor_TypeDef, SI_SEG_GENERIC, const SI_SEG_CODE) =
{
  landingPage,
};

uint16_t numUrls = sizeof(landingPage) / sizeof(landingPage[0]);

#ifdef __cplusplus
}
#endif


