#include <iostream>

#define TEST

#define DPS310__REG_INFO_TEMP_MR 			DPS310__REG_ADR_TEMP_MR, \
											DPS310__REG_MASK_TEMP_MR, \
											DPS310__REG_SHIFT_TEMP_MR

#define DPS310__REG_ADR_TEMP_MR 			0x07U
#define DPS310__REG_MASK_TEMP_MR 			0x70U
#define DPS310__REG_SHIFT_TEMP_MR 			4U

#define DPS310__REG_INFO_TEMP_OSR 			DPS310__REG_ADR_TEMP_OSR, \
											DPS310__REG_MASK_TEMP_OSR, \
											DPS310__REG_SHIFT_TEMP_OSR

#define DPS310__REG_ADR_TEMP_OSR 			0x17U
#define DPS310__REG_MASK_TEMP_OSR 			0x07U
#define DPS310__REG_SHIFT_TEMP_OSR 			0U


#define P(x)	printf(#x " = %d\n",x);

#define MAX(ab,bb)                        (((ab) > (bb))? (ab) : (bb))

#define ATB0_ANA_ENG_REG    0x3F
/**
 *@brief Analog Test Bus 1 register
 */
#define ATB1_ANA_ENG_REG    0x3E
/**
 *@brief Rate Multiplier 1 register 
 */
#define RM1_DIG_ENG_REG     0x3C
/**
 *@brief Low Frequency Clock and SMPS register
 */
#define CLOCK_LOW_ENG_REG   0x3B
/**
 *@brief High Frequency Clock register
 */
#define CLOCK_HIGH_ENG_REG  0x3A
/**
 *@brief Power Management register
 */
#define PMU_ANA_ENG_REG     0x39
/**
 *@brief System Clock register
 */
#define CLOCK_ANA_USER_REG  0x34
/**
 *@brief System Power Management register
 */
#define PMU_ANA_USER_REG    0x35
/**
 *@brief Modulator register
 */
#define MOD_ANA_ENG_REG     0x21
//@} \\Device Configuration Registers

#define NUMBER_CONFIG_BYTE  0x02

#define USER_MODE_ATB0 0x00
#define USER_MODE_ATB1 0x30

#define SMPS_10uH_RM1 0x00
#define SMPS_ON 0x30

#define HIGH_FREQ_16M 0x00
#define SMPS_10uH_PMU 0x30

#define LOW_FREQ_XO 0x00
#define PMU_ANA_USER_RESET_VALUE 0x30

#define END_CONFIG 0xff

#define COLD_START_CONFIGURATION                                      \
{                                                                     \
  NUMBER_CONFIG_BYTE, ATB0_ANA_ENG_REG,   USER_MODE_ATB0,             \
  NUMBER_CONFIG_BYTE, ATB1_ANA_ENG_REG,   USER_MODE_ATB1,             \
  NUMBER_CONFIG_BYTE, RM1_DIG_ENG_REG,    SMPS_10uH_RM1,              \
  NUMBER_CONFIG_BYTE, CLOCK_LOW_ENG_REG,  SMPS_ON,                    \
  NUMBER_CONFIG_BYTE, CLOCK_HIGH_ENG_REG, HIGH_FREQ_16M,              \
  NUMBER_CONFIG_BYTE, PMU_ANA_ENG_REG,    SMPS_10uH_PMU,              \
  NUMBER_CONFIG_BYTE, CLOCK_ANA_USER_REG, LOW_FREQ_XO,                \
  NUMBER_CONFIG_BYTE, PMU_ANA_USER_REG,   PMU_ANA_USER_RESET_VALUE,   \
  END_CONFIG                                                          \
}

unsigned long at_hash(const unsigned char * str)
{
    unsigned long hash = 5381;
    int c;
/*
	unsigned char cold_start_config[] = COLD_START_CONFIGURATION;
	printf("hash %x %d\r\n",COLD_START_CONFIGURATION);
*/
    while((c = *str++))
    {
    	printf("hash %x %d\r\n",c,hash);
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    printf("\r\n",hash);

    return hash;
}

char get_swver(char * value)
{
	printf("swver T [ %s ] \r\n",value);	
	for(char a = 0 ; *value ; a++, value++ );	
//	printf("swver [ %d ] \r\n",a);
	
	sprintf(value,"swver [ %s ] \r\n","TEST");
	return 1;
}

typedef char (*at_callback)(unsigned char *value);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	unsigned char tempMr,tempOsr;
	
	unsigned long ptr; 	
	tempMr = 0x73;	
	tempOsr = 0x73; 
	
	int a = 5, b =3 ;
	P( a + b );
	
	at_hash((const unsigned char *)"SWVER");
	at_hash((const unsigned char *)"HWVER");
	
	(at_callback)get_swver("TEST");
		
	tempMr &= DPS310__REG_MASK_TEMP_MR >> DPS310__REG_SHIFT_TEMP_MR;
	
	tempOsr = tempOsr & (DPS310__REG_MASK_TEMP_MR >> DPS310__REG_SHIFT_TEMP_MR);
//	tempOsr &= DPS310__REG_MASK_TEMP_OSR >> DPS310__REG_SHIFT_TEMP_OSR;
	
	printf("TTA %d %x %x %x \r\n", 5382<<5 ,tempMr , tempOsr , DPS310__REG_INFO_TEMP_OSR );
	
	printf("1<<2 %x %d  MAX(%d) \r\n", 0x01<<2, ((5381<<5 )+ 5381), MAX(5,3) );
	
	ptr = 0x800000;
	
	if(ptr & ((unsigned long)1<<23) )
	{
		printf("FLOAT OK %lx %lx\r\n", ptr,(unsigned long)1<<24);
		ptr -= (unsigned long)1 << 24;
		printf("FLOAT OK %lx \r\n", ptr);
	}
	else
	{
		printf("FLOAT %lx \r\n", 1<<23);
	}

#ifdef TEST
	printf("2 %x\r\n", 0x30<<2);
#else
	printf("3 %x\r\n", 0x30<<3);
#endif 
	return 0;
}

