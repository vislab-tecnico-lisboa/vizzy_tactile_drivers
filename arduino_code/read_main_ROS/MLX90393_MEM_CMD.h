///////////////
// MEMORY MAP
///////////////
#define MEM_ADD_0        0x0 // RESERVED_LOW[15:9], BIST[8], Z_SERIES[7], GAIN_SEL[6:4], HALLCONF[3:0]
#define MEM_ADD_1        0x1 // TRIG_INT_SEL[15], COMM_MODE[14:13], WOC_DIFF[12], EXT_TRIG[11], TCMP_EN[10], BURST_SEL[9:6], BURST_DATA_RATE[5:0]
#define MEM_ADD_2        0x2 // RESERVED[15:13], OSR2[12:11], RES_Z[10:9], RES_Y[8:7], RES_X[6:5], DIG_FILT[4:2], OSR[1:0]
                             //                               ^<<<<<<<<RES_XYZ [10:5]>>>>>>>>>>>^
#define MEM_ADD_3        0x3 // SENS_TC_HT[15:8], SENS_TC_LT[7:0]
#define MEM_ADD_OFFSET_X 0x4  
#define MEM_ADD_OFFSET_Y 0x5
#define MEM_ADD_OFFSET_Z 0x6
#define MEM_ADD_7        0x7 // WOXY_THRESHOLD[15:0]
#define MEM_ADD_8        0x8 // WOZ_THRESHOLD[15:0]
#define MEM_ADD_9        0x9 // WOT_THRESHOLD[15:0]
// MEMORY AREA 0x0A~0x1F can be used to store anything

////////////////////////////
// CONFIGURATION BITS
////////////////////////////
// ADDRESS 0 
// HALLCONF (address 0[3:0]); Spining and Chopping rate adjustment // maybe don't need to mess with this for now
#define HALLCONF_DEF 0xC // default
#define HALLCONF_00  0x0 // Allow OSR and DIG_FILT to be 00,01,10 --> less conversion time
// GAIN_SEL (address 0[4:6]) // relates to RES_XYZ
#define GAINSEL_0    0x0<<4
#define GAINSEL_1    0x1<<4
#define GAINSEL_2    0x2<<4
#define GAINSEL_3    0x3<<4
#define GAINSEL_4    0x4<<4
#define GAINSEL_5    0x5<<4
#define GAINSEL_6    0x6<<4
#define GAINSEL_7    0x7<<4
#define GAINSEL_DEF  GAINSEL_0  // ours default, K:why zero but not 7? 
#define GAINSEL_DEF2 GAINSEL_7  // A: We use 7 for higher sensitivity (drawback? time?)
// Z_SERIES (address 0[7]); Connection of the Hall plates for Z-axis measurements
#define Z_SERIES_DEF  0x0<<7 // default and recommended value
// BIST (address 0(8)); Built-In Self Test
#define BIST_ON   0x1<<8
#define BIST_OFF  0x0<<8
#define BIST_DEF  BIST_OFF

// ADDRESS 1
// BURST_DATA_RATE (address 1[5:0])
#define BURST_DATA_RATE_CONT     0x00 // continuous burst mode (20 ms * This = actual rate)
#define BURST_DATA_RATE_20MS     0x01 
#define BURST_DATA_RATE_320MS    0x10
#define BURST_DATA_RATE_640MS    0x20
#define BURST_DATA_RATE_960MS    0x30
#define BURST_DATA_RATE_1260MS   0x3F // the slowest burst rate possible
#define BURST_DATA_RATE_DEF      BURST_DATA_RATE_CONT // ours default
// BURST_SEL (address 1[9:6], [9:6] = [ZYXT]) 
#define BURST_SEL_DEF  0xF<<6  // Enable all here because Start Busrt mode can specify which to measure anyway 
// TCMP_EN (address 1[10]); Enables the temperature compensation
#define TCMP_EN_ON  0x1<<10 // enable this will limit resolution RES to only 1 maximum
#define TCMP_EN_OFF 0x0<<10
#define TCMP_EN_DEF TCMP_EN_ON
// EXT_TRIG (address 1[11]); Start a measurement with INT/TRIG pin
#define EXT_TRIG_ON   0x1<<11 // will be ignore if TRIC_INT_SEL is set
#define EXT_TRIG_OFF  0x0<<11 // ours default
#define EXT_TRIG_DEF  EXT_TRIG_OFF // ours default
// WOC_DIFF (address 1[12]); Absolute or derivative WOC mode; WOC = wake-up-on-change to safe energy?
#define WOC_DIFF_ON   0x1<<12 // Measurements are compared to the previous ones
#define WOC_DIFF_OFF  0x0<<12 // Measurements are compared to the first measurements
#define WOC_DIFF_DEF  WOC_DIFF_OFF // Don't care which one
// COMM_MODE (address 1[14:13]); Defines the communication mode
#define COMM_MODE_BOTH 0x1<<13 // both I2C and SPI can be used, 0x1 
#define COMM_MODE_SPI  0x2<<13 // only SPI
#define COMM_MODE_I2C  0x3<<13 // only I2C <-- ours default
#define COMM_MODE_DEF  COMM_MODE_I2C // ours default
// TRIG_INT_SEL (address 1[15]); Selects the function of the INT/TRIG pin
#define TRIG_INT_SEL_ON  0x1<<15 // the pin will be a digital output
#define TRIG_INT_SEL_OFF 0x0<<15 // the pin will be an input
#define TRIG_INT_SEL_DEF TRIG_INT_SEL_OFF // Don't care which one

// ADDRESS 2
// OSR (address 2[1:0]); Defines the oversampling rate of the ADC decimation filter for magnetic measurements
// OSR_ADC = 64 * 2^OSR; This will directly impact the measurement time for magnetic measurements.
// DON'T DO THIS: OSR=0, DIG_FILT=0 OR OSR=0, DIG_FILT=1 OR OSR=1, DIG_FILT=0 --> The chip will not work properly!! UNLESS HALL_CONF=0x0.
#define OSR_0    0x0 // the fastest conversion time possible (w/o risk in making the chip work not properly)
#define OSR_1    0x1
#define OSR_2    0x2
#define OSR_3    0x3
#define OSR_DEF  OSR_0 
// DIG_FILT (address 2[4:2]); A control for the digital filter. 
// An averaging over a certain amount (2^DIG_FILT) will be done
// DON'T DO THIS: OSR=0, DIG_FILT=0 OR OSR=0, DIG_FILT=1 OR OSR=1, DIG_FILT=0 --> The chip will not work properly!! UNLESS HALL_CONF=0x0.
#define DIG_FILT_0    0x0<<2
#define DIG_FILT_1    0x1<<2
#define DIG_FILT_2    0x2<<2 // the fastest conversion time possible (w/o risk in making the chip work not properly)
#define DIG_FILT_3    0x3<<2
#define DIG_FILT_4    0x4<<2
#define DIG_FILT_5    0x5<<2
#define DIG_FILT_6    0x6<<2
#define DIG_FILT_7    0x7<<2
#define DIG_FILT_DEF  DIG_FILT_2 
// RES_XYZ (address 2[10:5]) --> RES_Z[10:9], RES_Y[8:7], RES_X[6:5]
// ours default = all 1 ==> 010101B or 0x15
// if RES_[] == 0 OR 1 and TCMP_EN == 0 --> output will be 2's COMPLEMENT
// if RES_[] == 2 OR 3 OR TCMP_EN == 1 --> output will be UNSIGNED
#define RES_XYZ_ALL_0  0x00<<5
#define RES_XYZ_ALL_1  0x15<<5
#define RES_XYZ_ALL_2  0x2A<<5
#define RES_XYZ_ALL_3  0x3F<<5
#define RES_XYZ_110    0x05<<5 // X and Y are set to 1, while Z are set to 0 --> yield similar sensitivity in all axis
#define RES_XYZ_DEF    RES_XYZ_ALL_1 // ours default, BUT WHY SET Z the same as X and Y? They have different SENSITIVITY
#define RES_XYZ_DEF2   RES_XYZ_ALL_0 
// OSR2 (address 2[12:11]); Defines the oversampling rate of the ADC decimation filter for a temperature measurement
// OSR_ADC = 64 * 2^OSR; This will directly impact the measurement time for the temperature measurement
#define OSR2_0    0x0<<11
#define OSR2_1    0x1<<11
#define OSR2_2    0x2<<11
#define OSR2_3    0x3<<11
#define OSR2_DEF  OSR2_0 // Don't care which one

// TO BE DONE LATER; NOT NECESSARY NOW
// ADDRESS 3
// SENS_TC_LT (address 3[7:0])
// SENS_TC_HT (address 3[15:8])

// WOXY_THRESHOLD (address 7), WOZ_THRESHOLD (address 8) & WOT_THRESHOLD (address 9)
// Defines the wake up thresholds on X, Y, Z axis or on temperature. The resolution of the temperature sensor is 45.2LSB/K.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMMAND                        |CMD byte#1| |CMD byte#2| |CMD byte#3| |CMD byte#4| |# of bytes to read back|
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EXit:                     EX    1000 0000B                                          1 (status byte)
// Read from a Register:     RR    0101 0000B    A[5:0]<<2                             1 (status byte) + 2 (data)
// Write to a Register:      WR    0110 0000B    D[15:8]       D[7:0]     A[5:0]<<2    1 (status byte)
// ReseT:                    RT    1111 0000B                                          1 (status byte)
// Memory Recall:            HR    1101 0000B                                          1 (status byte)
// Memory Store:             HS    1110 0000B                                          1 (status byte)
// No OPeration:             NOP   0000 0000B                                          1 (status byte)
// Start Burst mode:         SB    0001 ZYXTB                                          1 (status byte)
// Start Wake-up On Change:  SWOC  0010 ZYXTB                                          1 (status byte)
// Start Measurement:        SM    0011 ZYXTB                                          1 (status byte)
// Read Measurement:         RM    0100 ZYXTB                                          1 (status byte) + 2*[T+X+Y+Z] (data; high and low bytes)
//
#define EX        0x80
#define RR        0x50
#define WR        0x60
#define RT        0xF0
#define HR        0xD0
#define HS        0xE0
#define NOP       0x00
#define SB        0x10
#define SB_ALL    0x1F
#define SB_XYZ    0x1E
#define SWOC_ALL  0x2F
#define SM        0x30
#define SM_ALL    0x3F
#define SM_XYZ    0x3E
#define RM        0x40
#define RM_ALL    0x4F
#define RM_XYZ    0x4E
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Status Byte(SB): Burst_mode[7], WOC_mode[6], SM_mode[5], ERROR[4], SED[3], RS[2], D1[1], D0[0]
// D1-D0: indicates number of bytes after the SB.
