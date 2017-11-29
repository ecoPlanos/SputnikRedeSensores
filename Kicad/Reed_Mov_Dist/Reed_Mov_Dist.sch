EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ecoPlanos_custom
LIBS:freetronics_schematic
LIBS:ArduProMiniTKB
LIBS:lis3dh
LIBS:agg-kicad
LIBS:Reed_Mov_Dist-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ARDUPROMINI-6 uP1
U 1 1 5A1D41F9
P 5600 4450
F 0 "uP1" H 5000 3650 60  0000 C CNN
F 1 "ARDUPROMINI-6" H 5000 3750 60  0000 C CNN
F 2 "ArduProMiniTKB:ArduProMini-6" H 5600 4450 60  0001 C CNN
F 3 "" H 5600 4450 60  0000 C CNN
	1    5600 4450
	1    0    0    -1  
$EndComp
Text GLabel 5750 5650 2    60   Input ~ 0
GND
Text GLabel 4250 5850 0    60   Input ~ 0
GND
Text Notes 1600 1250 0    99   ~ 0
Reed Sensors\n\n
Text Notes 4400 4850 0    99   ~ 0
Arduino Pro Mini
Text Notes 8300 1250 0    99   ~ 0
Distance Sensors\n\n
Text Notes 4700 1050 0    99   ~ 0
Accelerometers\n
$Comp
L Conn_01x02 J2
U 1 1 5A1D4B8B
P 1700 1950
F 0 "J2" H 1700 2050 50  0000 C CNN
F 1 "Conn_01x02" H 1700 1750 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02_Pitch2.54mm" H 1700 1950 50  0001 C CNN
F 3 "" H 1700 1950 50  0001 C CNN
	1    1700 1950
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x02 J3
U 1 1 5A1D4FAE
P 1700 2650
F 0 "J3" H 1700 2750 50  0000 C CNN
F 1 "Conn_01x02" H 1700 2450 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02_Pitch2.54mm" H 1700 2650 50  0001 C CNN
F 3 "" H 1700 2650 50  0001 C CNN
	1    1700 2650
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x02 J4
U 1 1 5A1D502F
P 1700 3400
F 0 "J4" H 1700 3500 50  0000 C CNN
F 1 "Conn_01x02" H 1700 3200 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02_Pitch2.54mm" H 1700 3400 50  0001 C CNN
F 3 "" H 1700 3400 50  0001 C CNN
	1    1700 3400
	-1   0    0    1   
$EndComp
Text GLabel 4650 7000 0    60   Input ~ 0
SDA
Text GLabel 4650 7150 0    60   Input ~ 0
SCL
$Comp
L Conn_01x06 J6
U 1 1 5A1D5294
P 5200 3050
F 0 "J6" H 5200 3350 50  0000 C CNN
F 1 "ITG3200" H 5200 2650 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x06_Pitch2.54mm" H 5200 3050 50  0001 C CNN
F 3 "" H 5200 3050 50  0001 C CNN
	1    5200 3050
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x06 J5
U 1 1 5A1D5413
P 5200 1900
F 0 "J5" H 5200 2200 50  0000 C CNN
F 1 "LIS3DH_1" H 5100 1450 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x06_Pitch2.54mm" H 5200 1900 50  0001 C CNN
F 3 "" H 5200 1900 50  0001 C CNN
	1    5200 1900
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x06 J7
U 1 1 5A1D5489
P 5550 1900
F 0 "J7" H 5550 2200 50  0000 C CNN
F 1 "LIS3DH_2" H 5450 1450 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x06_Pitch2.54mm" H 5550 1900 50  0001 C CNN
F 3 "" H 5550 1900 50  0001 C CNN
	1    5550 1900
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x04 J10
U 1 1 5A1D563B
P 9450 1700
F 0 "J10" H 9450 1900 50  0000 C CNN
F 1 "HC-SRO4" H 9450 1400 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x04_Pitch2.54mm" H 9450 1700 50  0001 C CNN
F 3 "" H 9450 1700 50  0001 C CNN
	1    9450 1700
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x09 J11
U 1 1 5A1D5738
P 9450 2750
F 0 "J11" H 9450 3250 50  0000 C CNN
F 1 "URM37" H 9450 2250 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x09_Pitch2.54mm" H 9450 2750 50  0001 C CNN
F 3 "" H 9450 2750 50  0001 C CNN
	1    9450 2750
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x07 J12
U 1 1 5A1D582C
P 9450 3950
F 0 "J12" H 9450 4350 50  0000 C CNN
F 1 "LV-MaxSonar-EZ1" H 9450 3550 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x07_Pitch2.54mm" H 9450 3950 50  0001 C CNN
F 3 "" H 9450 3950 50  0001 C CNN
	1    9450 3950
	1    0    0    -1  
$EndComp
$Comp
L Barrel_Jack J1
U 1 1 5A1D6102
P 950 4950
F 0 "J1" H 950 5160 50  0000 C CNN
F 1 "Barrel_Jack" H 950 4775 50  0000 C CNN
F 2 "Connectors:BARREL_JACK" H 1000 4910 50  0001 C CNN
F 3 "" H 1000 4910 50  0001 C CNN
	1    950  4950
	1    0    0    -1  
$EndComp
$Comp
L LM7805_TO220 U1
U 1 1 5A1D61C7
P 2150 4850
F 0 "U1" H 2000 4975 50  0000 C CNN
F 1 "LM7805_TO220" H 2150 4975 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 2150 5075 50  0001 C CIN
F 3 "" H 2150 4800 50  0001 C CNN
	1    2150 4850
	1    0    0    -1  
$EndComp
Text GLabel 2200 5400 2    60   Input ~ 0
GND
Text GLabel 2700 4850 2    60   Input ~ 0
5V
Text Notes 1500 4600 0    99   ~ 0
Power Supply\n
$Comp
L CP C1
U 1 1 5A1D64A0
P 2550 5050
F 0 "C1" H 2575 5150 50  0000 L CNN
F 1 "10uF" H 2575 4950 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D4.0mm_P2.00mm" H 2588 4900 50  0001 C CNN
F 3 "" H 2550 5050 50  0001 C CNN
	1    2550 5050
	1    0    0    -1  
$EndComp
Text GLabel 5750 5550 2    60   Input ~ 0
5V
Text GLabel 5750 5850 2    60   Input ~ 0
3V3
Text GLabel 1900 1400 0    60   Input ~ 0
3V3
$Comp
L R R1
U 1 1 5A1D6B64
P 2100 1650
F 0 "R1" V 2180 1650 50  0000 C CNN
F 1 "1K" V 2100 1650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2030 1650 50  0001 C CNN
F 3 "" H 2100 1650 50  0001 C CNN
	1    2100 1650
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5A1D6C4D
P 2100 2350
F 0 "R2" V 2180 2350 50  0000 C CNN
F 1 "1K" V 2100 2350 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2030 2350 50  0001 C CNN
F 3 "" H 2100 2350 50  0001 C CNN
	1    2100 2350
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5A1D6CB2
P 2100 3100
F 0 "R3" V 2180 3100 50  0000 C CNN
F 1 "1K" V 2100 3100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2030 3100 50  0001 C CNN
F 3 "" H 2100 3100 50  0001 C CNN
	1    2100 3100
	1    0    0    -1  
$EndComp
Text GLabel 2000 3600 2    60   Input ~ 0
GND
Text GLabel 2400 1850 2    60   Input ~ 0
Reed_Red
Text GLabel 2400 3300 2    60   Input ~ 0
Reed_Small_White
Text GLabel 2400 2550 2    60   Input ~ 0
Reed_Big_White
Text GLabel 4250 5950 0    60   Input ~ 0
Reed_Red
Text GLabel 4250 6050 0    60   Input ~ 0
Reed_Big_White
Text GLabel 4250 6150 0    60   Input ~ 0
Reed_Small_White
Text GLabel 9000 1600 0    60   Input ~ 0
5V
Text GLabel 9000 1700 0    60   Input ~ 0
TRIG_HC_HV
Text GLabel 9000 1800 0    60   Input ~ 0
ECHO_HC_HV
Text GLabel 9000 1900 0    60   Input ~ 0
GND
Text GLabel 9000 2650 0    60   Input ~ 0
TRIG_URM_HV
Text GLabel 9000 2850 0    60   Input ~ 0
ECHO_URM_HV
Text GLabel 9000 3150 0    60   Input ~ 0
5V
Text GLabel 9000 3000 0    60   Input ~ 0
GND
NoConn ~ 9250 2350
NoConn ~ 9250 2450
NoConn ~ 9250 2550
NoConn ~ 9250 2750
Text GLabel 9050 4150 0    60   Input ~ 0
3V3
Text GLabel 9050 4250 0    60   Input ~ 0
GND
Text GLabel 9050 3750 0    60   Input ~ 0
ECHO_EZ1
Text GLabel 9050 3950 0    60   Input ~ 0
TRIG_EZ1
Text GLabel 4250 6350 0    60   Input ~ 0
TRIG_HC
Text GLabel 4250 6450 0    60   Input ~ 0
ECHO_HC
Text GLabel 4250 6550 0    60   Input ~ 0
TRIG_URM
Text GLabel 4250 6650 0    60   Input ~ 0
ECHO_URM
Text GLabel 5700 6550 2    60   Input ~ 0
TRIG_EZ1
Text GLabel 5700 6150 2    60   Input ~ 0
ECHO_EZ1
NoConn ~ 9250 3650
Text GLabel 9050 3850 0    60   Input ~ 0
ADC_EZ1
NoConn ~ 9250 4050
Text GLabel 5700 6250 2    60   Input ~ 0
ADC_EZ1
NoConn ~ 9250 2950
Text GLabel 5950 2100 2    60   Input ~ 0
3V3
Text GLabel 4800 2200 0    60   Input ~ 0
GND
Text GLabel 4850 2950 0    60   Input ~ 0
GND
Text GLabel 4850 2850 0    60   Input ~ 0
3V3
Text GLabel 4850 3050 0    60   Input ~ 0
SDA
Text GLabel 4850 3150 0    60   Input ~ 0
SCL
NoConn ~ 5000 3350
NoConn ~ 5000 3250
NoConn ~ 5000 2100
NoConn ~ 5000 2000
NoConn ~ 5000 1900
NoConn ~ 5000 1800
NoConn ~ 5000 1700
Text GLabel 5950 2200 2    60   Input ~ 0
GND
Text GLabel 5950 2000 2    60   Input ~ 0
SDA
Text GLabel 5950 1900 2    60   Input ~ 0
SCL
NoConn ~ 5750 1800
NoConn ~ 5750 1700
Text GLabel 9600 5400 2    60   Input ~ 0
TRIG_HC_HV
Text GLabel 9600 5300 2    60   Input ~ 0
ECHO_HC_HV
Text GLabel 9600 5600 2    60   Input ~ 0
TRIG_URM_HV
Text GLabel 9600 5500 2    60   Input ~ 0
ECHO_URM_HV
Text GLabel 8600 5300 0    60   Input ~ 0
TRIG_HC
Text GLabel 8600 5400 0    60   Input ~ 0
ECHO_HC
Text GLabel 8600 5500 0    60   Input ~ 0
TRIG_URM
Text GLabel 8600 5600 0    60   Input ~ 0
ECHO_URM
$Comp
L Conn_01x06 J8
U 1 1 5A1D5A9C
P 8950 5400
F 0 "J8" H 8950 5700 50  0000 C CNN
F 1 "TTL_Level_Shifter_1" H 8600 4900 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x06_Pitch2.54mm" H 8950 5400 50  0001 C CNN
F 3 "" H 8950 5400 50  0001 C CNN
	1    8950 5400
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x06 J9
U 1 1 5A1D5B83
P 9250 5400
F 0 "J9" H 9250 5700 50  0000 C CNN
F 1 "TTL_Level_Shifter_2" H 9000 4900 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x06_Pitch2.54mm" H 9250 5400 50  0001 C CNN
F 3 "" H 9250 5400 50  0001 C CNN
	1    9250 5400
	-1   0    0    -1  
$EndComp
Text GLabel 8600 5700 0    60   Input ~ 0
GND
Text GLabel 8600 5200 0    60   Input ~ 0
3V3
Text GLabel 9600 5700 2    60   Input ~ 0
GND
Text GLabel 9600 5200 2    60   Input ~ 0
5V
$Comp
L XBEE U2
U 1 1 5A1DA5A7
P 1950 6750
F 0 "U2" H 1700 7400 50  0000 L CNN
F 1 "XBEE" H 1550 6150 50  0000 L CNN
F 2 "unchecked:XBEE" H 1550 6050 50  0001 L CNN
F 3 "" H 1450 7150 50  0001 C CNN
	1    1950 6750
	1    0    0    -1  
$EndComp
Text GLabel 1300 6350 0    60   Input ~ 0
3V3
Text GLabel 1300 7250 0    60   Input ~ 0
GND
Text GLabel 4250 5650 0    60   Input ~ 0
Rx
Text GLabel 4250 5550 0    60   Input ~ 0
Tx
Text GLabel 1300 6550 0    60   Input ~ 0
Tx
Text GLabel 1300 6450 0    60   Input ~ 0
Rx
Wire Wire Line
	4250 5850 4400 5850
Wire Wire Line
	5750 5650 5600 5650
Wire Notes Line
	6700 4350 6700 7600
Wire Notes Line
	7000 6300 11000 6300
Wire Notes Line
	11000 6300 11000 700 
Wire Notes Line
	11000 700  7000 700 
Wire Notes Line
	7000 700  7000 6300
Wire Notes Line
	6700 4100 6700 700 
Wire Notes Line
	6700 700  4000 700 
Wire Notes Line
	4000 700  4000 4100
Wire Notes Line
	4000 4100 6700 4100
Wire Notes Line
	3700 700  3700 4100
Wire Notes Line
	3700 4100 700  4100
Wire Notes Line
	700  4100 700  700 
Wire Notes Line
	700  700  3700 700 
Wire Wire Line
	4800 7150 4650 7150
Wire Wire Line
	4650 7000 4800 7000
Wire Notes Line
	3350 4350 6700 4350
Wire Notes Line
	3350 4350 3350 7600
Wire Notes Line
	3350 7600 6700 7600
Wire Notes Line
	3100 4350 3100 7600
Wire Notes Line
	3100 7600 700  7600
Wire Notes Line
	700  7600 700  4350
Wire Notes Line
	700  4350 3100 4350
Wire Wire Line
	2450 4850 2700 4850
Wire Wire Line
	1600 5050 1600 5250
Wire Wire Line
	1600 5250 2550 5250
Wire Wire Line
	2550 5250 2550 5200
Wire Wire Line
	2150 5150 2150 5400
Connection ~ 2150 5250
Wire Wire Line
	2150 5400 2200 5400
Wire Wire Line
	2550 4900 2550 4850
Connection ~ 2550 4850
Wire Wire Line
	5600 5550 5750 5550
Wire Wire Line
	5600 5850 5750 5850
Wire Wire Line
	1900 1400 2000 1400
Wire Wire Line
	2000 1400 2000 2950
Wire Wire Line
	2000 2950 2100 2950
Wire Wire Line
	2000 2200 2100 2200
Connection ~ 2000 2200
Wire Wire Line
	2000 1500 2100 1500
Connection ~ 2000 1500
Wire Wire Line
	1900 1850 2400 1850
Wire Wire Line
	2100 1850 2100 1800
Wire Wire Line
	2100 2500 2100 2550
Wire Wire Line
	1900 2550 2400 2550
Wire Wire Line
	1900 3300 2400 3300
Wire Wire Line
	2100 3300 2100 3250
Wire Wire Line
	1900 1950 1950 1950
Wire Wire Line
	1950 1950 1950 3600
Wire Wire Line
	1950 3400 1900 3400
Wire Wire Line
	1900 2650 1950 2650
Connection ~ 1950 2650
Wire Wire Line
	1950 3600 2000 3600
Connection ~ 1950 3400
Connection ~ 2100 1850
Connection ~ 2100 2550
Connection ~ 2100 3300
Wire Wire Line
	9000 3000 9150 3000
Wire Wire Line
	9150 3000 9150 3050
Wire Wire Line
	9150 3050 9250 3050
Wire Wire Line
	9250 3150 9000 3150
Wire Wire Line
	9250 2850 9000 2850
Wire Wire Line
	9000 2650 9250 2650
Wire Wire Line
	9000 1600 9250 1600
Wire Wire Line
	9000 1700 9250 1700
Wire Wire Line
	9250 1800 9000 1800
Wire Wire Line
	9000 1900 9250 1900
Wire Wire Line
	9250 4250 9050 4250
Wire Wire Line
	9050 4150 9250 4150
Wire Wire Line
	9250 3950 9050 3950
Wire Wire Line
	9050 3850 9250 3850
Wire Wire Line
	9250 3750 9050 3750
Wire Wire Line
	4850 3150 5000 3150
Wire Wire Line
	5000 3050 4850 3050
Wire Wire Line
	4850 2950 5000 2950
Wire Wire Line
	5000 2850 4850 2850
Wire Wire Line
	4800 2200 5000 2200
Wire Wire Line
	5750 1900 5950 1900
Wire Wire Line
	5950 2000 5750 2000
Wire Wire Line
	5750 2100 5950 2100
Wire Wire Line
	5950 2200 5750 2200
Wire Wire Line
	8600 5200 8750 5200
Wire Wire Line
	8600 5300 8750 5300
Wire Wire Line
	8600 5400 8750 5400
Wire Wire Line
	8600 5500 8750 5500
Wire Wire Line
	8750 5600 8600 5600
Wire Wire Line
	8600 5700 8750 5700
Wire Wire Line
	9450 5200 9600 5200
Wire Wire Line
	9600 5300 9450 5300
Wire Wire Line
	9450 5400 9600 5400
Wire Wire Line
	9600 5500 9450 5500
Wire Wire Line
	9450 5600 9600 5600
Wire Wire Line
	9600 5700 9450 5700
Wire Wire Line
	4250 5950 4400 5950
Wire Wire Line
	4400 6050 4250 6050
Wire Wire Line
	4250 6150 4400 6150
Wire Wire Line
	4400 6350 4250 6350
Wire Wire Line
	4250 6450 4400 6450
Wire Wire Line
	4400 6550 4250 6550
Wire Wire Line
	4250 6650 4400 6650
Wire Wire Line
	5600 6550 5700 6550
Wire Wire Line
	5600 6250 5700 6250
Wire Wire Line
	4400 5650 4250 5650
Wire Wire Line
	4250 5550 4400 5550
Wire Wire Line
	1450 6350 1300 6350
Wire Wire Line
	1300 6450 1450 6450
Wire Wire Line
	1450 6550 1300 6550
Wire Wire Line
	1300 7250 1450 7250
NoConn ~ 2450 6350
NoConn ~ 2450 6450
NoConn ~ 2450 6550
NoConn ~ 2450 6650
NoConn ~ 2450 6750
NoConn ~ 2450 6850
NoConn ~ 2450 6950
NoConn ~ 2450 7050
NoConn ~ 2450 7150
NoConn ~ 2450 7250
NoConn ~ 1450 6650
NoConn ~ 1450 6750
NoConn ~ 1450 6850
NoConn ~ 1450 6950
NoConn ~ 1450 7050
NoConn ~ 1450 7150
NoConn ~ 4400 5750
NoConn ~ 4400 6250
NoConn ~ 5600 6350
NoConn ~ 5600 6050
NoConn ~ 5600 5950
NoConn ~ 5600 5750
$Comp
L CP C2
U 1 1 5A1DC206
P 1800 5050
F 0 "C2" H 1825 5150 50  0000 L CNN
F 1 "220uF" H 1825 4950 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D7.5mm_P2.50mm" H 1838 4900 50  0001 C CNN
F 3 "" H 1800 5050 50  0001 C CNN
	1    1800 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4900 1800 4850
Connection ~ 1800 4850
Wire Wire Line
	1800 5200 1800 5250
Connection ~ 1800 5250
Wire Wire Line
	1250 4850 1350 4850
Wire Wire Line
	1650 4850 1850 4850
Wire Wire Line
	1250 4950 1300 4950
Wire Wire Line
	1300 4950 1300 5050
Wire Wire Line
	1250 5050 1600 5050
Connection ~ 1300 5050
$Comp
L D D1
U 1 1 5A1DCD3A
P 1500 4850
F 0 "D1" H 1500 4950 50  0000 C CNN
F 1 "D" H 1500 4750 50  0000 C CNN
F 2 "Diodes_THT:D_T-1_P5.08mm_Horizontal" H 1500 4850 50  0001 C CNN
F 3 "" H 1500 4850 50  0001 C CNN
	1    1500 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5600 6150 5700 6150
NoConn ~ 5600 6450
$EndSCHEMATC
