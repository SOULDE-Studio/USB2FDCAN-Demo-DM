#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum FrameType {
    STANDARD = 0,
    EXTENDED = 1
};
enum CANType {
    CAN = 0,
    FDCAN = 1,
    FDCAN_BRS = 2
};
enum FDCAN_Speed {
    FDCAN_500K = 0,
    FDCAN_1M,
    FDCAN_2M,
    FDCAN_4M,
    FDCAN_5M
};
enum DLC {
    FDCAN_0BYTES = 0,
    FDCAN_1BYTES,
    FDCAN_2BYTES,
    FDCAN_3BYTES,
    FDCAN_4BYTES,
    FDCAN_5BYTES,
    FDCAN_6BYTES,
    FDCAN_7BYTES,
    FDCAN_8BYTES,
    FDCAN_12BYTES = 9,
    FDCAN_16BYTES,
    FDCAN_20BYTES,
    FDCAN_24BYTES,
    FDCAN_32BYTES,
    FDCAN_48BYTES,
    FDCAN_64BYTES
};
#pragma pack(1)
typedef struct FrameInfo {
    uint32_t canID; // CAN frame ID
    uint8_t frameType; // 0 for Standard frame and 1 for Extended frame
    uint8_t dataLength; //CAN frame data length
} FrameInfo;
#pragma pack()

//!
//! \param dev device handler returned by openUSBCAN
//! \return majar version in first 8 bits and minor version in last 8 bits
int16_t getVersionUSB2CAN(int32_t dev);

//!
//! \param devName "/dev/USB2CAN*" in Linux or "COM*" in Windows
//! \return device handler for further operations
int32_t openUSBCAN(const char *devName);

//!
//! \param dev device handler returned by openUSBCAN
//! \return serial close return value
int32_t closeUSBCAN(int32_t dev);

//!
//! \param dev device handler
//! \param channel the CAN transmitter used to send data, USB2CAN-CAN-Dual can choose 1 or 2.
//! \param info the pointer of FrameInfo structure, which contains the CAN ID, frame type and data length
//! \param data CAN frame data
//! \return transmit return value, 8 for success and -1 for failure
int32_t sendUSBCAN(int32_t dev, uint8_t channel, FrameInfo *info, uint8_t *data);

//!
//! \param dev device handler
//! \param channel the CAN transmitter received data, USB2CAN-CAN-Dual can be 1 or 2.
//! \param info the pointer of FrameInfo structure, which contains the CAN ID, frame type and data length of the received frame
//! \param data CAN frame data received
//! \param timeout timeout value in us
//! \return -1 for time out and 0 for success
int32_t readUSBCAN(int32_t dev, uint8_t *channel, FrameInfo *info, uint8_t *data, int32_t timeout);

int32_t configUSBCAN(int32_t dev, uint8_t channel, uint8_t type, uint8_t nominalSpeed, uint8_t dataSpeed);

#ifdef __cplusplus
}
#endif
