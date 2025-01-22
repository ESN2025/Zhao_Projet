#include<stdio.h>
#include<stdint.h>
#include <unistd.h>
#include "system.h"
#include <sys/alt_irq.h>
#include <io.h>
#include <alt_types.h>
#include <sys/alt_stdio.h>
#include "sys/alt_sys_init.h"
#include "opencores_i2c.h"
#include "opencores_i2c_regs.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "altera_avalon_pio_regs.h"

uint8_t X0, X1, Y0, Y1, Z0, Z1;
int16_t X, Y, Z;
uint8_t flag = 0;

#define ADXL345_addr 0x1D
#define I2C_SPEED 400000
#define DATAX0 0x32
#define DATAX1 0x33
#define DATAY0 0x34
#define DATAY1 0x35
#define DATAZ0 0x36
#define DATAZ1 0x37
#define reg_OFSX 0x1E
#define reg_OFSY 0x1F
#define reg_OFSZ 0x20

uint8_t read_adxl345(int addr) {
    uint8_t data;
    I2C_start(OPENCORES_I2C_0_BASE, ADXL345_addr, 0);
    I2C_write(OPENCORES_I2C_0_BASE, addr, 0);
    I2C_start(OPENCORES_I2C_0_BASE, ADXL345_addr, 1);
    data = I2C_read(OPENCORES_I2C_0_BASE, 1);
    return data;
}

void write_adxl345(int addr, int value) {
    I2C_start(OPENCORES_I2C_0_BASE, ADXL345_addr, 0);
    I2C_write(OPENCORES_I2C_0_BASE, addr, 0);
    I2C_write(OPENCORES_I2C_0_BASE, value, 1);
}

void calibrate_adxl345() {
    write_adxl345(reg_OFSX, 0);
    write_adxl345(reg_OFSY, 0);
    write_adxl345(reg_OFSZ, -28);
}

int16_t complement(int16_t value) {
    value = -(0xFFFF - value + 1);
    return value * 3.9;
}

void print7seg(int16_t value) {
    uint8_t data[5] = {0, 0, 0, 0, 0};
    if (value < 0) {
        data[0] = -value % 10;
        data[1] = (-value / 10) % 10;
        data[2] = (-value / 100) % 10;
        data[3] = -value / 1000;
        data[4] = 15;
    } else {
        data[0] = value % 10;
        data[1] = (value / 10) % 10;
        data[2] = (value / 100) % 10;
        data[3] = value / 1000;
        data[4] = 0;
    }
    IOWR_ALTERA_AVALON_PIO_DATA(SEG0_BASE, data[0]);
    IOWR_ALTERA_AVALON_PIO_DATA(SEG1_BASE, data[1]);
    IOWR_ALTERA_AVALON_PIO_DATA(SEG2_BASE, data[2]);
    IOWR_ALTERA_AVALON_PIO_DATA(SEG3_BASE, data[3]);
    IOWR_ALTERA_AVALON_PIO_DATA(SEG4_BASE, data[4]);
}

int main() {
    I2C_init(OPENCORES_I2C_0_BASE, ALT_CPU_CPU_FREQ, I2C_SPEED);
    write_adxl345(0x31, 0b111);
    calibrate_adxl345();
    alt_printf("DATA_FORMAT %x OFFSET : %x %x %x \n", read_adxl345(0x31), read_adxl345(reg_OFSX), read_adxl345(reg_OFSY), read_adxl345(reg_OFSZ));

    while (1) {
        X0 = read_adxl345(DATAX0);
        X1 = read_adxl345(DATAX1);
        Y0 = read_adxl345(DATAY0);
        Y1 = read_adxl345(DATAY1);
        Z0 = read_adxl345(DATAZ0);
        Z1 = read_adxl345(DATAZ1);
        X = (X1 << 8) | X0;
        Y = (Y1 << 8) | Y0;
        Z = (Z1 << 8) | Z0;
        complement(X);
        complement(Y);
        complement(Z);
        alt_printf("X: %x%x Y: %x%x Z: %x%x\n", X0,X1,Y0,Y1,Z0,Z1);
        switch (flag) {
            case 0:
                print7seg(X);
                break;
            case 1:
                print7seg(Y);
                break;
            case 2:
                print7seg(Z);
                break;
        }
        usleep(100000); // Add a delay to avoid overwhelming the system
    }
    return 0;
}
