#include "AT89C51RC2.h"
#include "port.h"
#include "sdcard.h"
#include "SPI.h"
#include "print_bytes.h"
#include <stdio.h>

static uint8_t idata SD_Card_Type;

uint8_t send_command(uint8_t command, uint32_t argument) {
	uint8_t SPIsend;
	uint8_t return_val;
	uint8_t SPIreturn;
	uint8_t error_flag;

	return_val = no_errors;

	if(command < 64) {
		SPIsend = command | 0x40;
		error_flag = SPI_Transfer(SPIsend, &SPIreturn);
		if((error_flag) == no_errors) {
			SPIsend = argument >> 24;
			error_flag = SPI_Transfer(SPIsend, &SPIreturn);
		} else
			return_val = SPI_error;
		if((return_val == no_errors) && (error_flag == no_errors)) {
			argument = argument & 0x00FFFFFF;
			SPIsend = argument >> 16;
			error_flag = SPI_Transfer(SPIsend, &SPIreturn);
		} else
			return_val = SPI_error;
		if((return_val == no_errors)  && (error_flag == no_errors)) {
			argument = argument & 0x0000FFFF;
			SPIsend = argument >> 8;
			error_flag = SPI_Transfer(SPIsend, &SPIreturn);
		} else
			return_val = SPI_error;
		if((return_val == no_errors) && (error_flag == no_errors)) {
			SPIsend = argument & 0x000000FF;
			error_flag = SPI_Transfer(SPIsend, &SPIreturn);
		} else
			return_val = SPI_error;
		if((return_val == no_errors) && (error_flag == no_errors)) {
			if(command)
				SPIsend = 0x95;
			else if(command == 8)
				SPIsend = 0x87;
			else
				SPIsend = 0x01;
			error_flag = SPI_Transfer(SPIsend, &SPIreturn);
		}

	}
	else
		return_val = illegal_command;

	return return_val;
}

uint8_t receive_response(uint8_t numBytes, uint8_t * arrayName) {
	uint8_t index;
	uint8_t return_val;
	uint8_t error_flag;
	uint8_t SPIreturn;

	return_val = no_errors;

	do {
		error_flag = SPI_Transfer(0xFF, &SPIreturn);
		index++;
	}while(((SPIreturn&0x80) == 0x80) && (index != 0) && (error_flag == no_errors));
	if(error_flag != no_errors)
		return_val = SPI_error;
	else if(index == 0)
		return_val = timeout_error;
	else {
		*arrayName = SPIreturn;
		if((SPIreturn == 0x00) || (SPIreturn == 0x01)) {
			if(numBytes > 1) {
				for(index = 1; index < numBytes; index++){
					error_flag = SPI_Transfer(0xFF, &SPIreturn);
				}
			}
		} else
			return_val = response_error;
	}
	error_flag = SPI_Transfer(0xFF, &SPIreturn);

	return return_val;
}

uint8_t SD_Card_Init(void) {
	uint8_t temp;
	uint8_t error_status;
	uint8_t error_flag;
	uint8_t arr[8];
	uint8_t SPIreturn;
	uint16_t timeout;
	uint32_t argument;

	error_status = no_errors;
	SD_Card_Type = unknown;
	nCS0 = 1;
	printf("SD Card Initialization ... \n\r" );
	for(temp = 0; temp < 10; temp++) {
		error_flag = SPI_Transfer(0xFF, &SPIreturn);
	}
	GREENLED = 0;
	printf("CMD0 sent ... ");
	nCS0 = 0;
	error_flag = send_command(CMD0, 0);
	if(error_flag == no_errors) {
		error_flag = receive_response(1, arr;);
		nCS0 = 1;
		GREENLED = 1;
		printf("Response = %2.2bX\n\r",arr[0]);
	} else {
		nCS0 = 1;
		GREENLED = 1;
		REDLED = 0;
	}
	if(error_flag != no_errors)
		error_status = error_flag;
	if(error_status == no_errors) {
		GREENLED = 0;
		printf("CMD0 sent ... ");
		nCS0 = 0;
		error_flag = send_command(CMD0, 0x00001AA);
		if(error_flag == no_errors) {
			error_flag = receive_response(5,arr);
			nCS0 = 1;
			GREENLED = 1;
			printf("Response = ");
			for(temp = 0; temp < 5; temp++) {
				printf("2.2bX",arr[temp]);
			}
			putchar(CR);
			putchar(LF);
			if(arr[4] != 0xAA)
				error_flag = response_error;
			else {
				nCS0 = 1;
				GREENLED = 1;
				REDLED = 0;
			}
		}
		if(error_flag != no_errors) {
			if(error_flag == illegal_command) {
				error_status = no_errors;
				SD_Card_Type = Standard_Capacity;
				printf("Version 1 SD Card detected.\n\r");
				printf("Standard Capacity Card detected.\n\r");
			} else
				error_status = error_flag;
		} else {
			SD_Card_Type = Ver2;
			printf("Version 2 SD Card detected.\n\r");
		}
	}
	if(error_status == no_errors) {
		GREENLED = 0;
		printf("CMD58 sent ... ");
		nCS0 = 0;
		error_flag = send_command(CMD58,0);
		if(error_flag == no_errors) {
			error_flag = receive_response(5,arr);
			nCS0 = 1;
			GREENLED = 1;
			printf("Response = ");
			for(temp = 0; temp < 5; temp++) {
				printf("%2.2bX",arr[temp]);
			}
			putchar(CR);
			putchar(LF);
			if((arr[2]&0xFC) != 0xFC)
				error_flag = voltage_error;
			else {
				nCS0 = 1;
				GREENLED = 1;
				REDLED = 0;
			}
		}
		if(error_flag != no_errors)
			error_status = error_flag;
	}
	if(error_status == no_errors) {
		if(SD_Card_Type == Ver2)
			argument = 0x40000000;
		else
			argument = 0;
		timeout = 0;
		GREENLED = 0;
		printf("ACMD41 sent ... ");
		nCS0 = 0;
		do {
			P3_5 = 0;
			error_flag = send_command(CMD55,0);
			if(error_flag == no_errors)
				error_flag = receive_response(1,arr);
			P3_5 = 1;
			if((arr[0] == 0x01) || (arr[0] == 0x00))
				error_flag = send_command(ACMD41,argument);
			if(error_flag == no_errors)
				receive_response(1,arr);
			timeout++;
			if(timeout == 0)
				error_flag = timeout_error;
		}while(((arr[0]&0x01) == 0x01) && (error_flag == no_errors));
		if(error_flag == no_errors) {
			nCS0 = 1;
			GREENLED = 1;
			printf("Response = %2.2bX\n\r",arr[0]);
		} else {
			nCS0 = 1;
			GREENLED = 1;
			REDLED = 0;
		}
		if(error_flag != no_errors)
			error_status = error_flag;
	}
		if((error_status == no_errors) && (SD_Card_Type == Ver2)) {
			GREENLED = 0;
			printf("CMD58 sent ... ");
			nCS0 = 0;
			error_flag = send_command(CMD58,0);
			if(error_flag == no_errors) {
				error_flag = receive_response(5,arr);
				nCS0 = 1;
				GREENLED = 1;
				printf("Response = ");
				for(temp = 0; temp < 5; temp++) {
					printf("%2.2bX ",arr[temp]);
				}
				putchar(CR);
				putchar(LF);
				if((arr[temp]&0x80) != 0x80)
					error_flag = card_inactive;
				else {
					if((arr[1]&0xC0) == 0xC0) {
						SD_Card_Type = High_Capacity;
						printf("High Capacity Card detected\n\r");
					} else {
						SD_Card_Type = Standard_Capacity;
						printf("Standard Capacity Card detected\n\r");
						GREENLED = 0;
						printf("CMD16 sent ... ");
						nCS0 = 0;
						error_flag = send_command(CMD16,512);
						if(error_flag == no_errors) {
							error_flag = receive_response(1,arr);
							nCS0 = 1;
							GREENLED = 1;
							printf("Response = %2.2bX \n\r",arr[0]);
							printf("Block size set to 512 bytes\n\r");
						}
					}
				}
			} else {
				nCS0 = 1;
				GREENLED = 1;
				REDLED = 0;
			}
			if(error_flag != no_errors) {
				error_status = error_flag;
				print_error(error_status);
			}
		}
		if(error_status != no_errors)
			print_error(error_status);
		
	return error_status;
}

uint8_t read_block(uint16_t numBytes, uint8_t * array) {
	uint8_t error_flag;
	uint8_t return_val;
	uint8_t SPIreturn;
	uint16_t index;

	index = 0;

	return_val = no_errors;
	do {
      error_flag = SPI_Transfer(0xFF,&SPIreturn);
      index++;
    }while(((SPIreturn&0x80) == 0x80) && (index != 0) && (error_flag == no_errors));
   if(error_flag != no_errors)
      return_val=SPI_error;
   else if(index == 0)
      return_val = timeout_error;
   else
   {
     if (SPIreturn == 0x00)
     {
        index = 0;
	    do
        { 
           error_flag = SPI_Transfer(0xFF,&SPIreturn); 
           index++;
        }while((SPIreturn == 0xFF) && (index != 0) && (error_flag == no_errors)); 
        if(error_flag != no_errors)
           return_val = SPI_error;
        else if(index == 0)
          return_val = timeout_error;
        else if(SPIreturn == 0xfe)
        {
          for(index = 0; index < numBytes; index++)
          {
             error_flag=SPI_Transfer(0xFF,&SPIreturn);
             *(array + index) = SPIreturn;
          }
          error_flag = SPI_Transfer(0xFF,&SPIreturn);
          error_flag = SPI_Transfer(0xFF,&SPIreturn); 
        }
	    else
	    {
	      return_val = data_error;
	    }
     }
     else
        return_val = response_error;
   }

	error_flag=SPI_Transfer(0xFF,&SPIreturn);

	return return_val;
}


uint8_t Return_SD_Card_Type(void) {
	return SD_Card_Type;
}



void print_error(uint8_t error) {
   if(error == timeout_error)
   		printf("Timeout Error");
   else if(error == illegal_command)
   		printf("Illegal Command\n\r");
   else if(error == response_error)
   		printf("Response Error");
   else if(error == data_error)
   		printf("Data Token Error");
   else if(error == voltage_error)
   		printf("Incompatible Voltage");
   else if(error == card_inactive) 
   		printf("Card is Inactive");
   else if(error == SPI_error)
   		printf("SPI or Timeout Error");
   else
   		printf("Unknown Error");
}