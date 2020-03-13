#include <REGX52.H>
#include <INTRINS.H>
#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();}
sbit SDA = 0xA6; /* 数据线 */
sbit SCL = 0xA5; /* 控制线 */
char a;          //a为读出的数据
void todelay(int z)
{
  int x, y;
  for (x = z; x > 0; x--)
    for (y = 110; y > 0; y--)
      ;
}
//启动
void IIC_Start(void)
{

  SDA = 1;
  SCL = 1;
  somenop;
  SDA = 0;
  somenop;
  SCL = 0;
}
//停止
void IIC_Stop(void)
{
  SDA = 0;
  SCL = 1;
  somenop;
  SDA = 1;
}
//等待响应
bit IIC_WaitAck(void)
{
  SDA = 1;
  somenop;
  SCL = 1;
  somenop;
  if (SDA)
  {
    SCL = 0;
    IIC_Stop();
    return 0;
  }
  else
  {
    SCL = 0;
    return 1;
  }
}
//发送一个字节
void IIC_SendByte(unsigned char byt)
{
  unsigned char i;
  for (i = 0; i < 8; i++)
  {
    if (byt & 0x80)
    {
      SDA = 1;
    }
    else
    {
      SDA = 0;
    }
    somenop;
    SCL = 1;
    byt <<= 1;
    somenop;
    SCL = 0;
  }
}
//接收一个字节
unsigned char IIC_RecByte(void)
{
  unsigned char da;
  unsigned char i;
  for (i = 0; i < 8; i++)
  {
    SCL = 1;
    somenop;
    da <<= 1;
    if (SDA)
      da |= 0x01;
    SCL = 0;
    somenop;
  }
  return da;
}
void rom_write(char add, da)
{
  IIC_Start();
  IIC_SendByte(0xa0);
  IIC_WaitAck();
  IIC_SendByte(add);
  IIC_WaitAck();
  IIC_SendByte(da);
  IIC_WaitAck();
  IIC_Stop();
  todelay(5);
}
char rom_read(char add)
{
  char t;
  IIC_Start();
  IIC_SendByte(0xa0);
  IIC_WaitAck();
  IIC_SendByte(add);
  IIC_WaitAck();
  IIC_Start();
  IIC_SendByte(0xa1);
  IIC_WaitAck();
  t = IIC_RecByte();
  return t;
  todelay(5);
}