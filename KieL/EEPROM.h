#ifndef __EEPROM_h__ ;
#define __EEPROM_h__ ;


void IIC_Start(void);
void IIC_Stop(void);
bit IIC_WaitAck(void);
void IIC_SendByte(unsigned char byt);
unsigned char IIC_RecByte(void);
void rom_write(char add,da);
char rom_read(char add);



#endif