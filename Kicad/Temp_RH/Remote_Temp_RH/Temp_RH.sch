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
P 2050 2200
F 0 "J1" H 2050 2450 50  0000 C CNN
F 1 "DHT 11" V 2150 2200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch1.27mm" H 2050 2200 50  0001 C CNN
F 3 "" H 2050 2200 50  0001 C CNN
	1    2050 2200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 J3
U 1 1 595D0957
P 3350 2200
F 0 "J3" H 3350 2450 50  0000 C CNN
F 1 "DHT 22" V 3450 2200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch1.27mm" H 3350 2200 50  0001 C CNN
F 3 "" H 3350 2200 50  0001 C CNN
	1    3350 2200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 J4
U 1 1 595D098A
P 4550 2200
F 0 "J4" H 4550 2450 50  0000 C CNN
F 1 "SHT 75" V 4650 2200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch1.27mm" H 4550 2200 50  0001 C CNN
F 3 "" H 4550 2200 50  0001 C CNN
	1    4550 2200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR01
U 1 1 595D0C18
P 6450 600
F 0 "#PWR01" H 6450 450 50  0001 C CNN
F 1 "+3.3V" H 6450 740 50  0000 C CNN
F 2 "" H 6450 600 50  0001 C CNN
F 3 "" H 6450 600 50  0001 C CNN
	1    6450 600 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 595D0C34
P 6450 3250
F 0 "#PWR02" H 6450 3000 50  0001 C CNN
F 1 "GND" H 6450 3100 50  0000 C CNN
F 2 "" H 6450 3250 50  0001 C CNN
F 3 "" H 6450 3250 50  0001 C CNN
	1    6450 3250
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 595D19A6
P 3850 1650
F 0 "R3" V 3930 1650 50  0000 C CNN
F 1 "10K" V 3850 1650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3780 1650 50  0001 C CNN
F 3 "" H 3850 1650 50  0001 C CNN
	1    3850 1650
	1    0    0    -1  
$EndComp
Text Label 4000 2350 0    39   ~ 0
DataSHT75
Text Label 4050 2050 0    39   ~ 0
SKC_SHT75
Text Label 2800 2050 0    39   ~ 0
Data_DHT22
Text Label 2200 1900 0    39   ~ 0
Data_DHT11
$Comp
L CONN_01X07 J5
U 1 1 595D421D
P 5750 2350
F 0 "J5" H 5750 2750 50  0000 C CNN
F 1 "SHT 31" V 5850 2350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch1.27mm" H 5750 2350 50  0001 C CNN
F 3 "" H 5750 2350 50  0001 C CNN
	1    5750 2350
	1    0    0    -1  
$EndComp
Text Label 5450 1650 0    39   ~ 0
Reset
Text Label 4750 1350 0    39   ~ 0
SCL
Text Label 4700 1450 0    39   ~ 0
SDA
$Comp
L R R1
U 1 1 5963B018
P 1750 1650
F 0 "R1" V 1830 1650 50  0000 C CNN
F 1 "10k" V 1750 1650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1680 1650 50  0001 C CNN
F 3 "" H 1750 1650 50  0001 C CNN
	1    1750 1650
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5963B4BA
P 2750 1950
F 0 "R2" V 2830 1950 50  0000 C CNN
F 1 "10k" V 2750 1950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2680 1950 50  0001 C CNN
F 3 "" H 2750 1950 50  0001 C CNN
	1    2750 1950
	1    0    0    -1  
$EndComp
NoConn ~ 5550 2250
NoConn ~ 5550 2050
NoConn ~ 3150 2350
NoConn ~ 1850 2250
$Comp
L CP C1
U 1 1 59665A74
P 6450 1350
F 0 "C1" H 6475 1450 50  0000 L CNN
F 1 "1u" H 6475 1250 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D4.0mm_P1.50mm" H 6488 1200 50  0001 C CNN
F 3 "" H 6450 1350 50  0001 C CNN
	1    6450 1350
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 596664A3
P 7350 1450
F 0 "R4" V 7430 1450 50  0000 C CNN
F 1 "1k" V 7350 1450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7280 1450 50  0001 C CNN
F 3 "" H 7350 1450 50  0001 C CNN
	1    7350 1450
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 59666750
P 7600 1450
F 0 "R5" V 7680 1450 50  0000 C CNN
F 1 "1k" V 7600 1450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7530 1450 50  0001 C CNN
F 3 "" H 7600 1450 50  0001 C CNN
	1    7600 1450
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 596667D0
P 7350 2050
F 0 "D1" H 7350 2150 50  0000 C CNN
F 1 "LED" H 7350 1950 50  0000 C CNN
F 2 "LEDs:LED_D1.8mm_W3.3mm_H2.4mm" H 7350 2050 50  0001 C CNN
F 3 "" H 7350 2050 50  0001 C CNN
	1    7350 2050
	0    -1   -1   0   
$EndComp
Text Label 7600 800  0    60   ~ 0
LedPower
Wire Wire Line
	3850 1800 3850 2350
Wire Wire Line
	3850 650  3850 1500
Wire Wire Line
	1850 2050 1850 650 
Wire Wire Line
	1850 2350 1850 3150
Wire Wire Line
	3150 2050 2600 2050
Wire Wire Line
	2600 2050 2600 650 
Wire Wire Line
	2500 2150 3150 2150
Wire Wire Line
	1750 2150 1850 2150
Wire Wire Line
	1750 1800 1750 2150
Wire Wire Line
	3550 1600 3550 2350
Wire Wire Line
	3650 2150 3650 1550
Wire Wire Line
	5550 2150 5450 2150
Wire Wire Line
	5000 1350 5000 2450
Wire Wire Line
	4900 2350 4900 1450
Wire Wire Line
	6450 600  6450 1200
Wire Wire Line
	6450 1500 6450 3250
Connection ~ 5450 3150
Wire Wire Line
	1800 650  7600 650 
Connection ~ 5550 650 
Connection ~ 5350 650 
Connection ~ 3850 650 
Connection ~ 2600 650 
Wire Wire Line
	3150 2250 3050 2250
Wire Wire Line
	3050 2250 3050 3150
Connection ~ 3050 3150
Wire Wire Line
	2750 2150 2750 2100
Wire Wire Line
	2750 1800 2750 650 
Connection ~ 2750 650 
Connection ~ 1750 1900
Wire Wire Line
	1800 1500 1800 650 
Connection ~ 1850 650 
Wire Wire Line
	1750 1500 1800 1500
Wire Wire Line
	3700 1350 3700 700 
Wire Wire Line
	5000 1350 3700 1350
Wire Wire Line
	3500 700  3500 1450
Wire Wire Line
	2300 700  2300 1900
Wire Wire Line
	2500 700  2500 2150
Wire Wire Line
	2300 1900 1750 1900
Connection ~ 2500 2150
Wire Wire Line
	3500 1450 4900 1450
Wire Wire Line
	3650 1550 3300 1550
Wire Wire Line
	3300 1550 3300 700 
Wire Wire Line
	3550 1600 2700 1600
Wire Wire Line
	2700 1600 2700 700 
Wire Wire Line
	2900 700  2900 650 
Connection ~ 2900 650 
Wire Wire Line
	3100 700  3100 1800
Wire Wire Line
	3100 1800 3500 1800
Wire Wire Line
	3500 1800 3500 3150
Connection ~ 3500 3150
Wire Wire Line
	3550 2350 4350 2350
Connection ~ 3850 2350
Wire Wire Line
	3650 2150 4050 2150
Wire Wire Line
	4050 2150 4050 2050
Wire Wire Line
	4050 2050 4350 2050
Connection ~ 4100 650 
Connection ~ 4350 650 
Wire Wire Line
	4350 2150 4200 2150
Wire Wire Line
	4200 2150 4200 650 
Connection ~ 4200 650 
Wire Wire Line
	4350 2250 4200 2250
Wire Wire Line
	4200 2250 4200 3150
Connection ~ 4200 3150
Wire Wire Line
	5550 2650 6200 2650
Wire Wire Line
	6200 2650 6200 650 
Connection ~ 6200 650 
Wire Wire Line
	5550 2550 5450 2550
Wire Wire Line
	5450 2550 5450 3150
Wire Wire Line
	5000 2450 5550 2450
Wire Wire Line
	5550 2350 4900 2350
Wire Wire Line
	5450 2150 5450 650 
Wire Wire Line
	5450 650  5550 650 
Connection ~ 6450 650 
Connection ~ 6450 3150
Wire Wire Line
	7600 650  7600 1300
Connection ~ 7350 650 
Wire Wire Line
	7350 1300 7350 1150
Wire Wire Line
	7600 1600 7600 1900
$Comp
L Screw_Terminal_1x10 J2
U 1 1 59668A2D
P 3200 900
F 0 "J2" H 3200 1950 50  0000 C TNN
F 1 "Arduino" V 3050 900 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_10pol" H 3200 -125 50  0001 C CNN
F 3 "" H 3175 1700 50  0001 C CNN
	1    3200 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7350 1150 3900 1150
Wire Wire Line
	3900 1150 3900 700 
Text Label 6900 1150 0    39   ~ 0
LedOut
$Comp
L LED D2
U 1 1 5966685B
P 7600 2050
F 0 "D2" H 7600 2150 50  0000 C CNN
F 1 "LED" H 7600 1950 50  0000 C CNN
F 2 "LEDs:LED_D1.8mm_W3.3mm_H2.4mm" H 7600 2050 50  0001 C CNN
F 3 "" H 7600 2050 50  0001 C CNN
	1    7600 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7350 1600 7350 1900
Wire Wire Line
	7350 3150 7350 2200
Wire Wire Line
	7600 3150 7600 2200
Connection ~ 7350 3150
NoConn ~ 4100 700 
Text Label 4650 3150 0    60   ~ 0
Ground´
Wire Wire Line
	2900 2150 2750 2150
Connection ~ 2750 2150
Connection ~ 2900 2150
Wire Wire Line
	1850 3150 7600 3150
$EndSCHEMATC