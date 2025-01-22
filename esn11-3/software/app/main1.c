#include<stdio.h>
#include<stdint.h>
#include <unistd.h>
#include "system.h"
#include <io.h>
#include <alt_types.h>
#include <sys/alt_irq.h>
#include <sys/alt_stdio.h>
#include "sys/alt_sys_init.h"
#include "opencores_i2c.h"
#include "opencores_i2c_regs.h"



// Read a Single Byte from ADXL345
uint8_t read_adxl345(int addr) {
    uint8_t data;
    I2C_start(OPENCORES_I2C_0_BASE, 0x1D, 0);    // Start I2C in write mode
    I2C_write(OPENCORES_I2C_0_BASE, addr, 0);    // Send register address
    I2C_start(OPENCORES_I2C_0_BASE, 0x1D, 1);    // Repeated start in read mode
    data = I2C_read(OPENCORES_I2C_0_BASE, 1);    // Read data
    return data;                                 // Return the read value
}

int main() {
    uint8_t x0, x1, y0, y1, z0, z1;
    //uint16_t X, Y, Z;

    while (1) {
        // Read X, Y, Z data from ADXL345
        x0 = read_adxl345(0x32);
        x1 = read_adxl345(0x33);
        y0 = read_adxl345(0x34);
        y1 = read_adxl345(0x35);
        z0 = read_adxl345(0x36);
        z1 = read_adxl345(0x37);

        // Combine high and low bytes
        //X = (x1 << 8) | x0;
        //Y = (y1 << 8) | y0;
        //Z = (z1 << 8) | z0;

        // Print acceleration values
        alt_printf("X = %x%x, Y = %x%x, Z = %x%x\n", x0,x1, y0,y1, z0,z1);
        usleep(100000); // 100ms delay
    }

    return 0;
}
