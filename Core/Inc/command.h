/*
 * command.h
 *
 *  Created on: Apr 26, 2022
 *      Author: nchernov
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

void read_all_memory();
void read_memory();
void write_memory();
void erase_memory();

void data_init_out();
void data_init_in();
void addr_calculation();
void deinit_all ();
#endif /* INC_COMMAND_H_ */
