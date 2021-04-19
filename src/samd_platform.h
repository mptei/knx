#include "arduino_platform.h"

#include "Arduino.h"

#if defined(__SAMD51__)
// SAMD51 from section 9.6 of the datasheet
#define SERIAL_NUMBER_WORD_0 *(volatile uint32_t*)(0x008061FC)
#define SERIAL_NUMBER_WORD_1 *(volatile uint32_t*)(0x00806010)
#define SERIAL_NUMBER_WORD_2 *(volatile uint32_t*)(0x00806014)
#define SERIAL_NUMBER_WORD_3 *(volatile uint32_t*)(0x00806018)
#else
//#elif defined (__SAMD21E17A__) || defined(__SAMD21G18A__)  || defined(__SAMD21E18A__) || defined(__SAMD21J18A__)
// SAMD21 from section 9.3.3 of the datasheet
#define SERIAL_NUMBER_WORD_0 *(volatile uint32_t*)(0x0080A00C)
#define SERIAL_NUMBER_WORD_1 *(volatile uint32_t*)(0x0080A040)
#define SERIAL_NUMBER_WORD_2 *(volatile uint32_t*)(0x0080A044)
#define SERIAL_NUMBER_WORD_3 *(volatile uint32_t*)(0x0080A048)
#endif

#ifdef ARDUINO_ARCH_SAMD

//define which memory type is used for non-volatile memory
#define INTERN_FLASH_MEMORY
//#define EXTERN_EEPROM_MEMORY
//#define RAM_EMULATED_MEMORY       //like FlashStorage lib

#ifndef INTERN_FLASH_MEMORY
#define MAX_MEMORY_BLOCKS   6

typedef struct{
    uint32_t ID;
    size_t  size;
    uint8_t* data;
}MemoryBlock_t;
#endif

class SamdPlatform : public ArduinoPlatform
{
public:
    SamdPlatform();
    SamdPlatform( HardwareSerial* s);

    uint32_t uniqueSerialNumber() override;
    void restart();
    bool writeNVMemory(uint8_t* addr,uint8_t data);
    uint8_t readNVMemory(uint8_t* addr);
    uint8_t* allocNVMemory(size_t size,uint32_t ID);
    uint8_t* reloadNVMemory(uint32_t ID, bool pointerAccess);
    void finishNVMemory();
    void freeNVMemory(uint32_t ID);
    uint8_t* referenceNVMemory();
private:
#ifndef INTERN_FLASH_MEMORY
    void initNVMemory();
    MemoryBlock_t _memoryBlocks[MAX_MEMORY_BLOCKS];
    bool _MemoryInitialized = false;
#endif
};

#endif
