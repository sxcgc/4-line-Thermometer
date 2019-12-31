#include "myflash.h"

uint64_t writeFlashData;
uint32_t addr1 = 0x0800F000;
uint32_t addr2 = 0x0800F400;
uint32_t addr3 = 0x0800F800;
uint32_t addr4 = 0x0800FC00;

void writeFlash(uint32_t addr,uint64_t writeFlashData)
{
    //1、解锁FLASH
  HAL_FLASH_Unlock();

    //2、擦除FLASH
    //初始化FLASH_EraseInitTypeDef
  FLASH_EraseInitTypeDef f;
  f.TypeErase = FLASH_TYPEERASE_PAGES;
  f.PageAddress = addr;
  f.NbPages = 1;
    //设置PageError
  uint32_t PageError = 0;
    //调用擦除函数
  HAL_FLASHEx_Erase(&f, &PageError);

    //3、对FLASH烧写
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, writeFlashData);

    //4、锁住FLASH
  HAL_FLASH_Lock();
}

