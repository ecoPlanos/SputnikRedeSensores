EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:Temp_RH-cache
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
L CONN_01X04 J1
U 1 1 595D08DD
P 1600 1300
F 0 "J1" H 1600 1550 50  0000 C CNN
F 1 "DHT 11" V 1700 1300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch1.27mm" H 1600 1300 50  0001 C CNN
F 3 "" H 1600 1300 50  0001 C CNN
	1    1600 1300
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR01
U 1 1 595D0C18
P 5750 700
F 0 "#PWR01" H 5750 550 50  0001 C CNN
F 1 "+3.3V" H 5750 840 50  0000 C CNN
F 2 "" H 5750 700 50  0001 C CNN
F 3 "" H 5750 700 50  0001 C CNN
	1    5750 700 
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 595D19A6
P 2700 1900
F 0 "R3" V 2780 1900 50  0000 C CNN
F 1 "10K" V 2700 1900 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2630 1900 50  0001 C CNN
F 3 "" H 2700 1900 50  0001 C CNN
	1    2700 1900
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5963B018
P 1450 2250
F 0 "R1" V 1530 2250 50  0000 C CNN
F 1 "10k" V 1450 2250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1380 2250 50  0001 C CNN
F 3 "" H 1450 2250 50  0001 C CNN
	1    1450 2250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5963B4BA
P 2000 1850
F 0 "R2" V 2080 1850 50  0000 C CNN
F 1 "10k" V 2000 1850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1930 1850 50  0001 C CNN
F 3 "" H 2000 1850 50  0001 C CNN
	1    2000 1850
	1    0    0    -1  
$EndComp
$Comp
L CP Decouplador1
U 1 1 59665A74
P 9550 2650
F 0 "Decouplador1" H 9575 2750 50  0000 L CNN
F 1 "1u" H 9575 2550 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D4.0mm_P1.50mm" H 9588 2500 50  0001 C CNN
F 3 "" H 9550 2650 50  0001 C CNN
	1    9550 2650
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 596664A3
P 4800 1750
F 0 "R4" V 4880 1750 50  0000 C CNN
F 1 "10k" V 4800 1750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 4730 1750 50  0001 C CNN
F 3 "" H 4800 1750 50  0001 C CNN
	1    4800 1750
	1    0    0    -1  
$EndComp
NoConn ~ 1650 1500
$Comp
L CONN_01X04 J2
U 1 1 5975ED9D
P 2050 1300
F 0 "J2" H 2050 1550 50  0000 C CNN
F 1 "DHT 22" V 2150 1300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch1.27mm" H 2050 1300 50  0001 C CNN
F 3 "" H 2050 1300 50  0001 C CNN
	1    2050 1300
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X04 J3
U 1 1 59760071
P 2550 1300
F 0 "J3" H 2550 1550 50  0000 C CNN
F 1 "SHT 75" V 2650 1300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch1.27mm" H 2550 1300 50  0001 C CNN
F 3 "" H 2550 1300 50  0001 C CNN
	1    2550 1300
	0    -1   -1   0   
$EndComp
Text Label 3750 4150 0    47   ~ 0
Data75
NoConn ~ 2100 1500
$Comp
L CONN_01X07 J5
U 1 1 59764088
P 3250 1250
F 0 "J5" H 3250 1650 50  0000 C CNN
F 1 "SHT 31" V 3350 1250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch1.27mm" H 3250 1250 50  0001 C CNN
F 3 "" H 3250 1250 50  0001 C CNN
	1    3250 1250
	0    -1   -1   0   
$EndComp
NoConn ~ 2950 1450
NoConn ~ 3150 1450
Text Label 3900 4300 0    47   ~ 0
SDA31
Text Label 3100 1550 0    47   ~ 0
SDA31
Text Label 2600 1600 0    47   ~ 0
Data75
Text Label 1900 1600 0    47   ~ 0
Data22
Text Label 1400 1600 0    47   ~ 0
Data11
Text Label 4150 4350 0    47   ~ 0
SLC31
Text Label 3250 1450 0    47   ~ 0
SCL31
$Comp
L GND #PWR02
U 1 1 59766242
P 3950 5050
F 0 "#PWR02" H 3950 4800 50  0001 C CNN
F 1 "GND" H 3950 4900 50  0000 C CNN
F 2 "" H 3950 5050 50  0001 C CNN
F 3 "" H 3950 5050 50  0001 C CNN
	1    3950 5050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J7
U 1 1 59768262
P 4650 1250
F 0 "J7" H 4650 1400 50  0000 C CNN
F 1 "NTC" V 4750 1250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 4650 1250 50  0001 C CNN
F 3 "" H 4650 1250 50  0001 C CNN
	1    4650 1250
	0    -1   -1   0   
$EndComp
Text Label 4300 4200 0    47   ~ 0
DataNTC
$Comp
L CONN_01X04 J8
U 1 1 5976F356
P 4150 1100
F 0 "J8" H 4150 1350 50  0000 C CNN
F 1 "MLX" V 4250 1100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch1.27mm" H 4150 1100 50  0001 C CNN
F 3 "" H 4150 1100 50  0001 C CNN
	1    4150 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	850  800  9150 800 
Wire Wire Line
	10000 4900 750  4900
Wire Wire Line
	750  4900 750  1650
Wire Wire Line
	10000 950  10000 4900
Wire Wire Line
	9150 4800 850  4800
Wire Wire Line
	850  4800 850  800 
Connection ~ 9150 800 
Wire Wire Line
	9150 750  9150 4800
Wire Wire Line
	1450 1500 1300 1500
Wire Wire Line
	1300 1500 1300 800 
Connection ~ 1300 800 
Wire Wire Line
	1550 1500 1550 2100
Wire Wire Line
	1450 2100 3250 2100
Wire Wire Line
	1450 2400 1250 2400
Wire Wire Line
	1250 2400 1250 800 
Connection ~ 1250 800 
Wire Wire Line
	3250 2100 3250 4400
Connection ~ 1550 2100
Wire Wire Line
	1750 1500 1750 1650
Wire Wire Line
	750  1650 2200 1650
Connection ~ 750  1650
Wire Wire Line
	1900 1500 1900 1550
Wire Wire Line
	2000 1500 2000 1700
Wire Wire Line
	2000 2000 1200 2000
Wire Wire Line
	1200 2000 1200 800 
Connection ~ 1200 800 
Wire Wire Line
	1900 1550 1150 1550
Wire Wire Line
	1150 1550 1150 800 
Connection ~ 1150 800 
Wire Wire Line
	2200 1650 2200 1500
Connection ~ 1750 1650
Wire Wire Line
	2000 1700 3450 1700
Wire Wire Line
	3450 1700 3450 4400
Wire Wire Line
	3650 4400 3650 1650
Wire Wire Line
	3650 1650 2400 1650
Wire Wire Line
	2400 1650 2400 1500
Wire Wire Line
	2500 1500 2500 1550
Wire Wire Line
	2500 1550 2300 1550
Wire Wire Line
	2300 800  2300 2050
Connection ~ 2300 800 
Wire Wire Line
	2600 1500 2600 1600
Wire Wire Line
	2600 1600 2200 1600
Connection ~ 2200 1600
Wire Wire Line
	2700 1500 2700 1750
Wire Wire Line
	2300 2050 2700 2050
Connection ~ 2300 1550
Wire Wire Line
	3050 1450 3050 1550
Wire Wire Line
	3050 1550 2850 1550
Wire Wire Line
	2850 1550 2850 800 
Connection ~ 2850 800 
Wire Wire Line
	3550 1450 3700 1450
Wire Wire Line
	3700 1450 3700 800 
Connection ~ 3700 800 
Wire Wire Line
	3450 1450 3450 1500
Wire Wire Line
	3450 1500 3850 1500
Wire Wire Line
	3850 1500 3850 950 
Wire Wire Line
	3850 950  10000 950 
Connection ~ 10000 950 
Wire Wire Line
	9550 2500 9150 2500
Connection ~ 9150 2500
Wire Wire Line
	4600 1450 4400 1450
Wire Wire Line
	4400 1450 4400 800 
Connection ~ 4400 800 
Wire Wire Line
	4450 1550 4800 1550
Wire Wire Line
	4450 1550 4450 4400
Wire Wire Line
	4700 1450 4700 1550
Wire Wire Line
	4800 1550 4800 1600
Connection ~ 4700 1550
Wire Wire Line
	4800 1900 10000 1900
Connection ~ 10000 1900
Wire Wire Line
	3250 1450 3250 1600
Wire Wire Line
	4050 1600 4050 4400
Wire Wire Line
	3350 1450 3350 1550
Wire Wire Line
	3350 1550 4250 1550
Wire Wire Line
	4250 1550 4250 4400
Wire Wire Line
	3800 1400 4350 1400
Wire Wire Line
	3800 1400 3800 800 
Connection ~ 3800 800 
Wire Wire Line
	9550 2800 10000 2800
Connection ~ 10000 2800
$Comp
L CP C2
U 1 1 59770AF2
P 4950 2350
F 0 "C2" H 4975 2450 50  0000 L CNN
F 1 "1u" H 4975 2250 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D4.0mm_P1.50mm" H 4988 2200 50  0001 C CNN
F 3 "" H 4950 2350 50  0001 C CNN
	1    4950 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1400 4350 2200
Wire Wire Line
	4350 2200 4950 2200
Wire Wire Line
	4950 2500 5300 2500
Wire Wire Line
	5300 2500 5300 2200
Wire Wire Line
	5300 2200 10000 2200
Connection ~ 10000 2200
Wire Wire Line
	4300 1300 4300 2050
Wire Wire Line
	4300 2050 10000 2050
Connection ~ 10000 2050
Wire Wire Line
	3850 4400 3850 1750
Wire Wire Line
	3850 1750 2700 1750
Wire Wire Line
	5750 800  5750 700 
Connection ~ 5750 800 
Wire Wire Line
	3950 5050 3950 4900
Connection ~ 3950 4900
Wire Wire Line
	2850 4400 2850 4900
Connection ~ 2850 4900
Wire Wire Line
	3050 4400 3050 4800
Connection ~ 3050 4800
Text Label 3100 4400 0    60   Italic 12
Data11
Text Label 3350 4250 0    60   Italic 12
Data22
Text Label 3450 4100 0    60   Italic 12
Clock75
$Comp
L Screw_Terminal_1x12 J4
U 1 1 59769CE6
P 3950 4600
F 0 "J4" H 3950 5850 50  0000 C TNN
F 1 "Screw_Terminal_1x12" V 3800 4600 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_12pol" H 3950 3375 50  0001 C CNN
F 3 "" H 3925 5600 50  0001 C CNN
	1    3950 4600
	0    -1   -1   0   
$EndComp
Connection ~ 4200 1400
Wire Wire Line
	4200 1300 4200 1400
Wire Wire Line
	3250 1600 4050 1600
Wire Wire Line
	4000 1300 4000 1500
Wire Wire Line
	4000 1500 4100 1500
Wire Wire Line
	4100 1500 4100 3950
Wire Wire Line
	4100 3950 4650 3950
Wire Wire Line
	4650 3950 4650 4400
Wire Wire Line
	4100 1300 4100 1450
Wire Wire Line
	4100 1450 4150 1450
Wire Wire Line
	4150 1450 4150 3900
Wire Wire Line
	4150 3900 5050 3900
Wire Wire Line
	4850 3900 4850 4400
Text Label 3850 1300 0    60   ~ 0
SCL
Text Label 4050 1300 0    60   ~ 0
SDA
Text Label 4600 4350 0    60   ~ 0
SCL
Text Label 4750 4300 0    60   ~ 0
SDA
NoConn ~ 1300 -50 
Wire Wire Line
	5050 3900 5050 4400
Connection ~ 4850 3900
$EndSCHEMATC
