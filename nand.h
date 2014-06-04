#ifndef _NAND_H_
#define _NAND_H_

void nand_select_chip(void);
void nand_write_cmd(unsigned char cmd);
void nand_wait_idle(void);
void nand_deselect_chip(void);
void nand_reset(void);
void nand_init(void);
void nand_write_addr(unsigned addr);
unsigned char nand_read_data(void);
void nand_read(unsigned char *buf, unsigned long start, int size);


#endif /* _NAND_H_ */
