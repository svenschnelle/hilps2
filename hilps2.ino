#include "src/PS2Keyboard/PS2Keyboard.h"

#define PS2_DATA 2
#define PS2_CLK 3

#define PSI 4
#define PSO 5
#define PSK 6
#define HILINT 7
#define CS 8


#define HIL_IFC 0
#define HIL_EPT 1
#define HIL_ELB 2
#define HIL_IDD 3
#define HIL_DSR 4
#define HIL_PST 5
#define HIL_ACF 8
#define HIL_POL 0x10
#define HIL_CAE 0xfd

#define HIL_A 0x5a
#define HIL_B 0x30
#define HIL_C 0x34
#define HIL_D 0x56
#define HIL_E 0x68
#define HIL_F 0x54
#define HIL_G 0x52
#define HIL_H 0x50
#define HIL_I 0xc0
#define HIL_J 0xd0
#define HIL_K 0xd2
#define HIL_L 0xd4
#define HIL_M 0xe0
#define HIL_N 0xf0
#define HIL_O 0xc2
#define HIL_P 0xc4
#define HIL_Q 0x6c
#define HIL_R 0x66
#define HIL_S 0x58
#define HIL_T 0x64
#define HIL_U 0x60
#define HIL_V 0x32
#define HIL_W 0x6a
#define HIL_X 0x36
#define HIL_Y 0x62
#define HIL_Z 0x38

#define HIL_0 0xb4
#define HIL_1 0x7c
#define HIL_2 0x7a
#define HIL_3 0x78
#define HIL_4 0x76
#define HIL_5 0x74
#define HIL_6 0x72
#define HIL_7 0x70
#define HIL_8 0xb0
#define HIL_9 0xb2

#define HIL_SPACE 0xf2
#define HIL_TAB 0x4c
#define HIL_ENTER 0xda
#define HIL_DEL 0xce
#define HIL_BS  0xba
#define HIL_CAPS 0x5e
#define HIL_LSH 0x0a
#define HIL_RSH 0x08
#define HIL_F1 0x98
#define HIL_F2 0x96
#define HIL_F3 0x94
#define HIL_F4 0x92
#define HIL_F5 0xa2
#define HIL_F6 0xa4
#define HIL_F7 0xa6
#define HIL_F8 0xa8

#define HIL_UP 0xfc
#define HIL_DOWN 0xfa
#define HIL_LEFT 0xf8
#define HIL_RIGHT 0xfe
#define HIL_ESC 0x3e

static const char hil_keymap[128] = {
/*           F9          F5    F3    F1    F2   F12  */
/* 0x00 */ 0x00, 0x00, 0x00, HIL_F5, HIL_F3, HIL_F1, HIL_F2, 0x00,
/*                F10   F8    F6    F4    TAB    `        */
/* 0x08 */ 0x00, 0x00, 0x00, 0x00, 0x00, HIL_TAB, 0x00, 0x00,
/*               LALT  LSHF        LCTRL  Q     1         */
/* 0x10 */ 0x00, 0x00, HIL_LSH, 0x00, 0x00, HIL_Q, HIL_1, 0x00,
/*                      Z     S     A     W     2    LGUI */
/* 0x18 */ 0x00, 0x00, HIL_Z, HIL_S, HIL_A, HIL_W, HIL_2, 0x00,
/*                 C    X     D     E     4     3         */
/* 0x20 */ 0x00, HIL_C, HIL_X, HIL_D, HIL_E, HIL_4, HIL_3, 0x00,
/*               SP     V     F     T     R     5         */
/* 0x28 */ 0x00, HIL_SPACE, HIL_V, HIL_F, HIL_T, HIL_R, HIL_5, 0x00,
/*                N     B     H     G     Y     6         */
/* 0x30 */ 0x00, HIL_N, HIL_B, HIL_H, HIL_G, HIL_Y, HIL_6, 0x00,
/*                      M     J     U     7     8         */
/* 0x38 */ 0x00, 0x00, HIL_M, HIL_J, HIL_U, HIL_7, HIL_8, 0x00,
/*                ,     K     I     O     0     9         */
/* 0x40 */ 0x00, 0x00, HIL_K, HIL_I, HIL_O, HIL_0, HIL_9, 0x00,
/*                .     /     L           P     -         */
/* 0x48 */ 0x00, 0x00, 0x00, HIL_L, 0x00, HIL_P, 0x00, 0x00,
/*                      '           [     =               */
/* 0x50 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*         CAPS  RSHFT ENTER  ]           \               */
/* 0x58 */ HIL_CAPS, HIL_RSH, HIL_ENTER, 0x00, 0x00, 0x00, 0x00, 0x00,
/*                                       BKSP             */
/* 0x60 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, HIL_BS, 0x00,
/*                                                       */
/* 0x68 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*                                       ESC   NUM        */
/* 0x70 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, HIL_ESC, 0x00,
/*          F11                                SCRL       */
/* 0x78 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const char hil_extkeymap[128] = {
  /* 0x00 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x08 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x10 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x18 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x20 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x28 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x30 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x38 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x40 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x48 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x50 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x58 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x60 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0x68 */ 0x00, 0x00, 0x00, HIL_LEFT, 0x00, 0x00, 0x00, 0x00,
  /* 0x70 */ 0x00, HIL_DEL, HIL_DOWN, 0x00, HIL_RIGHT, HIL_UP, 0x00, 0x00,
  /* 0x78 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};

static int myaddr;
static PS2Keyboard keyboard;
static uint8_t kbdfifo[16];
static bool isext;
static bool isbreak;

static void hil_send_bit(int bit)
{
    delayMicroseconds(2);
    digitalWrite(PSI, bit ? 1 : 0);
    delayMicroseconds(2);
    digitalWrite(PSK, HIGH);
    delayMicroseconds(2);
    digitalWrite(PSK, LOW);
}

static int hil_read_bit(void)
{
    int bit;
    digitalWrite(PSK, HIGH);
    delayMicroseconds(2);
    bit = digitalRead(PSO);
    digitalWrite(PSK, LOW);
    delayMicroseconds(2);
    return bit;
}

static void hil_write(int reg, int bits, uint16_t data)
{
  //Serial.println(data, HEX);
    digitalWrite(CS, HIGH);
    hil_send_bit(0); /* Write */
    hil_send_bit(reg); /* Reg number */

    for (int i = bits; i >= 0; i--)
         hil_send_bit(data & (1 << i));

    digitalWrite(CS, LOW);
}

static uint16_t hil_read(int reg, int bits)
{
    uint16_t data = 0;
    
    digitalWrite(CS, HIGH);

    hil_send_bit(1); /* Read */
    hil_send_bit(reg); /* Reg number */

    for(int i = bits; i >= 0; i--)
        data |= (hil_read_bit() << i);

    digitalWrite(CS, LOW);
    digitalWrite(PSI, LOW);
    digitalWrite(PSK, LOW);
    return data;
}

static void hil_send_command(uint8_t addr, uint8_t data)
{
    while(hil_read(1, 0));
    hil_write(0, 11, (1 << 11) | (addr << 8) | data);
}

static void hil_send_data(uint8_t addr, uint8_t data)
{
    while(hil_read(1, 0));
    hil_write(0, 11, (addr << 8) | data);
}

static void hil_setup(int passthrough, int address)
{
    uint16_t tmp = (passthrough ? 8 : 0) | address;
    hil_write(1, 6, tmp);
}

static uint8_t mapkey(bool isext, bool isbreak, uint8_t c)
{
  uint8_t ret = 0;
  if (isext)
    ret = hil_extkeymap[c & 0x7f];
  else
    ret = hil_keymap[c & 0x7f];
  if (isbreak)
    ret |= 1;
  return ret;
}

static void handle_hil_command(int addr, uint8_t data)
{
    char buf[16];
    int count = 0;
    uint8_t c;
    bool hdr;
    
    if (data != 0 && data != 0x10) {
        sprintf(buf, "addr %d, command %02x\n", addr, data);
        Serial.print(buf);
    }

  switch(data) {
    case HIL_IFC:
      hil_send_command(0, 0);
      break;
 
    case HIL_EPT:
        hil_setup(0, myaddr);
        hil_send_command(myaddr, HIL_EPT);
        break;
 
    case HIL_ELB:
        hil_setup(1, myaddr);
        hil_send_command(myaddr, HIL_ELB);
        break;
 
    case HIL_IDD:
        hil_send_data(myaddr, 0xbf);
        hil_send_data(myaddr, 0);
        hil_send_command(myaddr, HIL_IDD);
        break;

    case HIL_ACF:
        hil_send_command(0, HIL_CAE);
        break;

    case HIL_ACF+1 ... HIL_ACF+7:
        myaddr = data & 7;
        data &= ~7;
        data |= (addr + 1) & 7;
        sprintf(buf, "my addr: %d\n", myaddr);
        Serial.print(buf);
        hil_setup(0, myaddr);
        hil_send_command(0, data);
        break;

    case HIL_POL ... HIL_POL+15:
      count = HIL_POL & 0xf;

      hdr = false;
      
      while ((c = keyboard.get_scan_code())) {
      Serial.println(c, HEX);
        if (c == 0xf0) {
          isbreak = true;
          continue;
        } else if (c == 0xe0) {
          isext = true;
          continue;
        }

        if (!hdr) {
          hil_send_data(myaddr, 0x40);
          hdr = true;
        }
        hil_send_data(myaddr, mapkey(isext, isbreak, c));
        isext = false;
        isbreak = false;
 
        if (++count > 14)
          break;
      }

      hil_send_command(0, HIL_POL + count);
      break;

    default:
      sprintf(buf, "addr %d, command %02x\n", addr, data);
      Serial.print(buf);
 }
}

void setup() {
  pinMode(PSO, INPUT);
  pinMode(PSI, OUTPUT);
  pinMode(PSK, OUTPUT);
  pinMode(HILINT, INPUT);
  pinMode(CS, OUTPUT);  
  Serial.begin(115200);
  Serial.print("startup\n");
  keyboard.begin(PS2_DATA, PS2_CLK);
  hil_setup(0, 0);
}

void loop() {  
  if (!digitalRead(HILINT)) {
      uint16_t data = hil_read(0, 13);
      if (data & 0x800) {
        handle_hil_command((data >> 8) & 7, data & 0xff);
      }       
  }
}
