

#include "chuProtocol.h"

#include <string.h>
#include <netinet/in.h>

#include "logger.h"

int serializeChuProtocol(ChuProtocol* chuProtocol, uint8_t* buffer[12])
{
    if (chuProtocol->magicNumber != CHUPROTOCOL_MAGIC_NUMBER)
    {
        LOG(WARNING, "magicNumber: %d is not valid", chuProtocol->magicNumber);
        return -1;
    }
    size_t offset = 0;
    uint16_t magicNumber = htons(chuProtocol->magicNumber);
    memcpy(&buffer[offset], &magicNumber, 2);
    offset += 2;
    memcpy(&buffer[offset], &chuProtocol->version, 1);
    offset += 1;
    memcpy(&buffer[offset], &chuProtocol->messageType, 1);
    offset += 1;
    memcpy(&buffer[offset], &chuProtocol->clientId, 4);
    offset += 4;
    memcpy(&buffer[offset], &chuProtocol->payloadSize, 4);
    return 0;
};

int deserializeChuProtocol(ChuProtocol* chuProtocol, uint8_t* buffer[12])
{
    size_t offset = 0;
    uint16_t magicNumber;
    uint32_t clientId;
    uint32_t payloadSize;

    memcpy(&magicNumber, buffer[offset], 2);
    offset += 2;
    chuProtocol->magicNumber = ntohs(magicNumber);

    if (chuProtocol->magicNumber != CHUPROTOCOL_MAGIC_NUMBER)
    {
        LOG(WARNING, "magicNumber: %d is not valid", chuProtocol->magicNumber);
        return -1;
    }

    memcpy(&chuProtocol->version, buffer[offset], 1);
    offset += 1;
    memcpy(&chuProtocol->messageType, buffer[offset], 1);
    offset += 1;
    memcpy(&clientId, buffer[offset], 4);
    offset += 4;
    memcpy(&payloadSize, buffer[offset], 4);

    chuProtocol->clientId = ntohl(clientId);
    chuProtocol->payloadSize = ntohl(payloadSize);

    return 0;
}