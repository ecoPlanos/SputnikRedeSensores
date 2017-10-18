EESchema Schematic File Version 2
LIBS:ecoPlanos_custom
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
LIBS:Common-Parts-Library
LIBS:freetronics_schematic
LIBS:Current-cache
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
L +3.3V #PWR01
U 1 1 599C10B4
P 1150 1150
F 0 "#PWR01" H 1150 1000 50  0001 C CNN
F 1 "+3.3V" H 1150 1290 50  0000 C CNN
F 2 "" H 1150 1150 50  0001 C CNN
F 3 "" H 1150 1150 50  0001 C CNN
	1    1150 1150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR02
U 1 1 59DBFA34
P 1450 1150
F 0 "#PWR02" H 1450 1000 50  0001 C CNN
F 1 "+5V" H 1450 1290 50  0000 C CNN
F 2 "" H 1450 1150 50  0001 C CNN
F 3 "" H 1450 1150 50  0001 C CNN
	1    1450 1150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J5
U 1 1 59DC05D4
P 7450 1800
F 0 "J5" H 7450 1950 50  0000 C CNN
F 1 "SCT" V 7550 1800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 7450 1800 50  0001 C CNN
F 3 "" H 7450 1800 50  0001 C CNN
	1    7450 1800
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR03
U 1 1 59DC06A6
P 1400 3600
F 0 "#PWR03" H 1400 3350 50  0001 C CNN
F 1 "GND" H 1400 3450 50  0000 C CNN
F 2 "" H 1400 3600 50  0001 C CNN
F 3 "" H 1400 3600 50  0001 C CNN
	1    1400 3600
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 59DBF4BF
P 7450 2150
F 0 "R8" V 7530 2150 50  0000 C CNN
F 1 "467" V 7450 2150 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7380 2150 50  0001 C CNN
F 3 "" H 7450 2150 50  0001 C CNN
	1    7450 2150
	0    1    1    0   
$EndComp
$Comp
L R R9
U 1 1 59DBFC66
P 8300 1900
F 0 "R9" V 8380 1900 50  0000 C CNN
F 1 "9k82" V 8300 1900 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8230 1900 50  0001 C CNN
F 3 "" H 8300 1900 50  0001 C CNN
	1    8300 1900
	-1   0    0    1   
$EndComp
$Comp
L R R10
U 1 1 59DBFCD3
P 8300 2300
F 0 "R10" V 8380 2300 50  0000 C CNN
F 1 "9k88" V 8300 2300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8230 2300 50  0001 C CNN
F 3 "" H 8300 2300 50  0001 C CNN
	1    8300 2300
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 59DC56D2
P 3650 2250
F 0 "R4" V 3730 2250 50  0000 C CNN
F 1 "1k" V 3650 2250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3580 2250 50  0001 C CNN
F 3 "" H 3650 2250 50  0001 C CNN
	1    3650 2250
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 59DC57A1
P 3650 2650
F 0 "R5" V 3730 2650 50  0000 C CNN
F 1 "4k7" V 3650 2650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3580 2650 50  0001 C CNN
F 3 "" H 3650 2650 50  0001 C CNN
	1    3650 2650
	1    0    0    -1  
$EndComp
$Comp
L LM324N U1
U 1 1 59DCBEB0
P 1800 2350
F 0 "U1" H 1800 2550 50  0000 L CNN
F 1 "LM324N" H 1800 2150 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm" H 1750 2450 50  0001 C CNN
F 3 "" H 1850 2550 50  0001 C CNN
	1    1800 2350
	1    0    0    -1  
$EndComp
$Comp
L LM324N U1
U 2 1 59DCBF45
P 6500 2050
F 0 "U1" H 6500 2250 50  0000 L CNN
F 1 "LM324N" H 6500 1850 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm" H 6450 2150 50  0001 C CNN
F 3 "" H 6550 2250 50  0001 C CNN
	2    6500 2050
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 59DCC575
P 1300 2950
F 0 "R2" V 1380 2950 50  0000 C CNN
F 1 "10k" V 1300 2950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 1230 2950 50  0001 C CNN
F 3 "" H 1300 2950 50  0001 C CNN
	1    1300 2950
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 59DCD99D
P 6050 2750
F 0 "R6" V 6130 2750 50  0000 C CNN
F 1 "10" V 6050 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5980 2750 50  0001 C CNN
F 3 "" H 6050 2750 50  0001 C CNN
	1    6050 2750
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 59DCDA50
P 6600 2450
F 0 "R7" V 6680 2450 50  0000 C CNN
F 1 "17k" V 6600 2450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6530 2450 50  0001 C CNN
F 3 "" H 6600 2450 50  0001 C CNN
	1    6600 2450
	0    1    1    0   
$EndComp
$Comp
L CONN_01X03 J2
U 1 1 59DD152B
P 900 1800
F 0 "J2" H 900 2000 50  0000 C CNN
F 1 "ACS770" V 1000 1800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 900 1800 50  0001 C CNN
F 3 "" H 900 1800 50  0001 C CNN
	1    900  1800
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 J3
U 1 1 59DD16D9
P 3550 1750
F 0 "J3" H 3550 1950 50  0000 C CNN
F 1 "ACS712" V 3650 1750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 3550 1750 50  0001 C CNN
F 3 "" H 3550 1750 50  0001 C CNN
	1    3550 1750
	0    -1   -1   0   
$EndComp
$Comp
L LM2931AZ-3.3/5.0 U2
U 1 1 59E696D6
P 4650 900
F 0 "U2" H 4650 1150 50  0000 C CNN
F 1 "LM2931AZ-3.3/5.0" H 4650 1100 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220_Vertical" H 4650 1000 50  0001 C CIN
F 3 "" H 4650 900 50  0001 C CNN
	1    4650 900 
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J6
U 1 1 59E69C4F
P 2700 850
F 0 "J6" H 2700 1000 50  0000 C CNN
F 1 "CONN_01X02" V 2800 850 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 2700 850 50  0001 C CNN
F 3 "" H 2700 850 50  0001 C CNN
	1    2700 850 
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 59E712BD
P 8700 2300
F 0 "C1" H 8725 2400 50  0000 L CNN
F 1 "10u1" H 8725 2200 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 8738 2150 50  0001 C CNN
F 3 "" H 8700 2300 50  0001 C CNN
	1    8700 2300
	1    0    0    -1  
$EndComp
$Comp
L PHR-4 P1
U 1 1 59E7244B
P 5500 2650
F 0 "P1" H 5500 2650 50  0000 L CNN
F 1 "PHR-4" H 5390 2350 50  0000 L CNN
F 2 "ecoPlanos_custom:JST_PHR-4" V 5700 2450 50  0001 L CNN
F 3 "JST" H 5450 2950 50  0001 L CNN
	1    5500 2650
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 59E7461E
P 1000 2650
F 0 "R1" H 1080 2650 50  0000 C CNN
F 1 "10k" V 1000 2650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 930 2650 50  0001 C CNN
F 3 "" H 1000 2650 50  0001 C CNN
	1    1000 2650
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 J4
U 1 1 59DBFF54
P 5650 1750
F 0 "J4" H 5650 1950 50  0000 C CNN
F 1 "PA3208" V 5750 1750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 5650 1750 50  0001 C CNN
F 3 "" H 5650 1750 50  0001 C CNN
	1    5650 1750
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 59DCC4DE
P 1500 2750
F 0 "R3" V 1580 2750 50  0000 C CNN
F 1 "100k" V 1500 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 1430 2750 50  0001 C CNN
F 3 "" H 1500 2750 50  0001 C CNN
	1    1500 2750
	0    1    1    0   
$EndComp
$Comp
L CP C2
U 1 1 59E75C72
P 1000 2250
F 0 "C2" H 1025 2350 50  0000 L CNN
F 1 "10u1" H 1025 2150 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 1038 2100 50  0001 C CNN
F 3 "" H 1000 2250 50  0001 C CNN
	1    1000 2250
	1    0    0    -1  
$EndComp
Connection ~ 1000 3150
Wire Wire Line
	1000 2800 1000 3150
Connection ~ 1000 2450
Wire Wire Line
	1200 2250 1500 2250
Wire Wire Line
	1200 2450 1200 2250
Wire Wire Line
	1000 2450 1200 2450
Wire Wire Line
	1000 2400 1000 2500
Wire Wire Line
	1200 2000 1200 1550
Wire Wire Line
	900  2000 1200 2000
Connection ~ 1300 3150
Wire Wire Line
	800  2000 800  3150
Wire Wire Line
	1000 2100 1000 2000
Connection ~ 1700 1350
Wire Wire Line
	1700 2050 1700 1350
Connection ~ 1400 3150
Wire Wire Line
	1400 3600 1400 3150
Wire Wire Line
	1300 3100 1300 3150
Connection ~ 1700 3150
Wire Wire Line
	1700 2650 1700 3150
Connection ~ 1300 2750
Wire Wire Line
	1300 2450 1500 2450
Wire Wire Line
	1300 2450 1300 2800
Wire Wire Line
	1350 2750 1300 2750
Wire Wire Line
	1650 2750 2100 2750
Wire Wire Line
	5900 1950 6200 1950
Connection ~ 5300 1350
Wire Wire Line
	5300 1350 5300 850 
Wire Wire Line
	5300 850  5050 850 
Wire Wire Line
	3000 850  3000 1550
Wire Wire Line
	4250 850  3000 850 
Connection ~ 3100 3150
Wire Wire Line
	3100 1150 3100 3150
Wire Wire Line
	4650 1150 3100 1150
Connection ~ 2050 1550
Wire Wire Line
	2050 800  2050 1550
Wire Wire Line
	2500 800  2050 800 
Connection ~ 2200 3150
Wire Wire Line
	2200 900  2500 900 
Wire Wire Line
	2200 3150 2200 900 
Wire Wire Line
	5550 3050 5550 2950
Connection ~ 3650 2450
Wire Wire Line
	5450 3050 5450 2950
Wire Wire Line
	5100 3050 5450 3050
Wire Wire Line
	5100 2450 5100 3050
Wire Wire Line
	3650 2450 5100 2450
Connection ~ 3650 3150
Wire Wire Line
	3650 3150 3650 2800
Wire Wire Line
	3650 2400 3650 2500
Wire Wire Line
	3650 1950 3650 2100
Connection ~ 3550 3150
Connection ~ 7300 2150
Wire Wire Line
	7400 2000 7300 2000
Wire Wire Line
	7600 2000 7600 2150
Wire Wire Line
	7500 2000 7600 2000
Wire Wire Line
	7600 2150 8700 2150
Wire Wire Line
	8300 2050 8300 2150
Wire Wire Line
	8300 1350 8300 1750
Connection ~ 8300 2150
Wire Wire Line
	6200 2150 6050 2150
Wire Wire Line
	6050 2150 6050 2600
Wire Wire Line
	6450 2450 6050 2450
Connection ~ 6050 2450
Wire Wire Line
	6750 2450 6900 2450
Wire Wire Line
	6900 2450 6900 2050
Wire Wire Line
	6800 2050 7000 2050
Wire Wire Line
	6050 2900 6050 3150
Connection ~ 6050 3150
Wire Wire Line
	7000 2050 7000 3050
Connection ~ 6900 2050
Wire Wire Line
	5650 1950 5750 1950
Wire Wire Line
	6400 2350 6400 3150
Connection ~ 6400 3150
Wire Wire Line
	6400 2350 5700 2350
Wire Wire Line
	5700 2350 5700 1950
Connection ~ 5700 1950
Wire Wire Line
	5550 1950 5550 2100
Wire Wire Line
	5550 2100 5900 2100
Wire Wire Line
	5900 2100 5900 1950
Wire Wire Line
	2100 2350 2100 3000
Wire Wire Line
	2100 3000 5350 3000
Wire Wire Line
	5350 3000 5350 2950
Connection ~ 2100 2750
Wire Wire Line
	1200 1550 3300 1550
Wire Wire Line
	1450 1150 1450 1550
Connection ~ 1450 1550
Wire Wire Line
	1150 1150 1150 1350
Wire Wire Line
	3550 1950 3550 2100
Wire Wire Line
	3550 2100 3300 2100
Wire Wire Line
	3450 1950 3450 3150
Connection ~ 3450 3150
Wire Wire Line
	6400 1350 6400 1750
Wire Wire Line
	1150 1350 8300 1350
Connection ~ 6400 1350
Wire Wire Line
	800  3150 8700 3150
Wire Wire Line
	8300 2450 8300 3150
Connection ~ 8300 3150
Wire Wire Line
	8700 3150 8700 2450
Wire Wire Line
	7000 3050 5550 3050
Wire Wire Line
	5650 2950 7300 2950
Wire Wire Line
	7300 2950 7300 2000
Wire Wire Line
	3300 2100 3300 1550
Connection ~ 3000 1550
$EndSCHEMATC
