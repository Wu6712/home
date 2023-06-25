#ifndef __RFID_H__
#define __RFID_H__

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MFRC522_I2C.h"
#include "servos.h"
#include "btn1.h"
MFRC522 mfrc522(0x28);
boolean btnFlag = 0;
String doorPassword = "";

void ShowReaderDetails() {
  //  实现了MFRC522软件
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print(F("MFRC522 Software Version: 0x"));
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown)"));
  Serial.println("");
  // 当返回到0x00或0xFF时，可能无法传输通信信号
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
  }
}

void rfidInit()
{
  Wire.begin();
  mfrc522.PCD_Init();
  ShowReaderDetails();
}

void similarCloseTheDoor()
{
  delay(50);
  doorPassword = "";
  if(btnFlag == 1)
  {
    boolean btnVal = digitalRead(btn1);
    if(btnVal == 0)  //刷卡开门后，点击按钮1关门
      {
        Serial.println("close");
        closeTheDoor();
        btnFlag = 0;
      }
  }
}

void samePasswdAndOpen()
{
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i]);
    doorPassword = doorPassword + String(mfrc522.uid.uidByte[i]);
  }
  // 密码正确
  if (doorPassword == "0311162231" || doorPassword == "16316840190")
  {
    Serial.println("open");
    openTheDoor();
    doorPassword = ""; 
    btnFlag = 1;
  }
  else   //卡号错误，警报器响起
  {
    doorPassword = "";
    Serial.println("error");
  }

}

void doorModule()
{

  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    // mfrc522.PICC_IsNewCardPresent() 是否有卡在感应器上
    // mfrc522.PICC_ReadCardSerial() 读取卡的序列号
    similarCloseTheDoor();
    return;
  }
  samePasswdAndOpen();
}






#endif