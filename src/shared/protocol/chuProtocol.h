//
// Created by greenman on 11/22/26.
//

#ifndef CHUNGO_CHUPROTOCOL_H
#define CHUNGO_CHUPROTOCOL_H
#include <stdint.h>


uint16_t CHUPROTOCOL_MAGIC_NUMBER = 0x7CAB;
uint8_t CHUPROTOL_VERSION = 1;

typedef enum MessageType
{
    TASK,
    STATUS
} MessageType;

typedef struct ChuProtocol
{
    uint16_t magicNumber;
    uint8_t version;
    MessageType messageType;
    uint32_t clientId;
    uint32_t payloadSize;
} ChuProtocol;


int serializeChuProtocol(ChuProtocol* chuProtocol, uint8_t* buffer[12]);
int deserializeChuProtocol(ChuProtocol* chuProtocol, uint8_t* buffer[12]);

#endif //CHUNGO_CHUPROTOCOL_H
