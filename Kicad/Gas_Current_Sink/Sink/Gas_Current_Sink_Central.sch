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
LIBS:Gas_Current_Sink_Central-cache
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
L ARDUINO_DUE_SHIELD SHIELD1
U 1 1 59E73C76
P 5650 3850
F 0 "SHIELD1" H 5250 6500 60  0000 C CNN
F 1 "ARDUINO_DUE_SHIELD" H 5650 3850 60  0000 C CNN
F 2 "freetronics_footprints:ARDUINO_DUE_SHIELD" H 5650 3650 50  0001 C CNN
F 3 "" H 5650 3850 60  0000 C CNN
	1    5650 3850
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x01 J8
U 1 1 59E73CE5
P 5150 7200
F 0 "J8" H 5150 7300 50  0000 C CNN
F 1 "CO2_shield" H 5150 7100 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x01_Pitch2.54mm" H 5150 7200 50  0001 C CNN
F 3 "" H 5150 7200 50  0001 C CNN
	1    5150 7200
	0    -1   -1   0   
$EndComp
$Comp
L Conn_01x01 J7
U 1 1 59E73DAB
P 4850 7200
F 0 "J7" H 4850 7300 50  0000 C CNN
F 1 "Current_shield" H 4850 7100 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x01_Pitch2.54mm" H 4850 7200 50  0001 C CNN
F 3 "" H 4850 7200 50  0001 C CNN
	1    4850 7200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 59E73E72
P 5000 7550
F 0 "#PWR01" H 5000 7300 50  0001 C CNN
F 1 "GND" H 5000 7400 50  0000 C CNN
F 2 "" H 5000 7550 50  0001 C CNN
F 3 "" H 5000 7550 50  0001 C CNN
	1    5000 7550
	1    0    0    -1  
$EndComp
$Comp
L PHR-4 P2
U 1 1 59E741EA
P 3550 2750
F 0 "P2" H 3550 2750 50  0000 L CNN
F 1 "Current" H 3440 2450 50  0000 L CNN
F 2 "ecoPlanos_custom:JST_PHR-4" V 3750 2550 50  0001 L CNN
F 3 "JST" H 3500 3050 50  0001 L CNN
	1    3550 2750
	-1   0    0    1   
$EndComp
$Comp
L PHR-4 P1
U 1 1 59E742CF
P 3550 3350
F 0 "P1" H 3550 3350 50  0000 L CNN
F 1 "Gas_Analog" H 3440 3050 50  0000 L CNN
F 2 "ecoPlanos_custom:JST_PHR-4" V 3750 3150 50  0001 L CNN
F 3 "JST" H 3500 3650 50  0001 L CNN
	1    3550 3350
	-1   0    0    1   
$EndComp
$Comp
L PHR-4 P3
U 1 1 59E74304
P 8150 1450
F 0 "P3" H 8150 1450 50  0000 L CNN
F 1 "Gas_Digital" H 8040 1150 50  0000 L CNN
F 2 "ecoPlanos_custom:JST_PHR-4" V 8350 1250 50  0001 L CNN
F 3 "JST" H 8100 1750 50  0001 L CNN
	1    8150 1450
	1    0    0    -1  
$EndComp
Text Label 5350 2900 0    60   ~ 0
ACTIVITY_LED
Text Label 5300 2800 0    60   ~ 0
CCS811_nRSET
Text Label 6900 1700 0    60   ~ 0
CCS811_nWAK
Text Label 6900 1800 0    60   ~ 0
CCS811_nINT
Text Label 3850 2600 0    60   ~ 0
ACS770_OUT
Text Label 3850 2700 0    60   ~ 0
ACS712_OUT
Text Label 3850 2800 0    60   ~ 0
PA3208_OUT
Text Label 3850 2900 0    60   ~ 0
SCT013_OUT
Text Label 3850 3200 0    60   ~ 0
MQ135_OUT
Text Label 3850 3300 0    60   ~ 0
MG811_OUT
$Comp
L Conn_01x01 J9
U 1 1 59E776F1
P 5450 7200
F 0 "J9" H 5450 7300 50  0000 C CNN
F 1 "CO2_shield2" H 5450 7100 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x01_Pitch2.54mm" H 5450 7200 50  0001 C CNN
F 3 "" H 5450 7200 50  0001 C CNN
	1    5450 7200
	0    -1   -1   0   
$EndComp
$Comp
L Conn_01x06 J5
U 1 1 59E777D3
P 3100 700
F 0 "J5" H 3100 1000 50  0000 C CNN
F 1 "SD_card" V 3200 700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 3100 700 50  0001 C CNN
F 3 "" H 3100 700 50  0001 C CNN
	1    3100 700 
	0    -1   -1   0   
$EndComp
$Comp
L Conn_01x06 J6
U 1 1 59E778E0
P 3100 1450
F 0 "J6" H 3100 1750 50  0000 C CNN
F 1 "RTC" V 3200 1450 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x06_Pitch2.54mm" H 3100 1450 50  0001 C CNN
F 3 "" H 3100 1450 50  0001 C CNN
	1    3100 1450
	0    -1   -1   0   
$EndComp
$Comp
L LM7805_TO220 U2
U 1 1 59E77AB2
P 1200 2050
F 0 "U2" H 1050 1925 50  0000 C CNN
F 1 "LM337_TO220" H 1200 1925 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 1200 1850 50  0001 C CIN
F 3 "" H 1200 2050 50  0001 C CNN
	1    1200 2050
	1    0    0    -1  
$EndComp
$Comp
L LM7805_TO220 U1
U 1 1 59E77B4E
P 1200 900
F 0 "U1" H 1050 1025 50  0000 C CNN
F 1 "LM7805_TO220" H 1200 1025 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 1200 1125 50  0001 C CIN
F 3 "" H 1200 850 50  0001 C CNN
	1    1200 900 
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J1
U 1 1 59E78020
P 600 1000
F 0 "J1" H 600 1100 50  0000 C CNN
F 1 "12V_input" H 600 800 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 600 1000 50  0001 C CNN
F 3 "" H 600 1000 50  0001 C CNN
	1    600  1000
	-1   0    0    1   
$EndComp
Text Label 1500 2050 0    60   ~ 0
3V3_Regul
Text Label 1850 900  0    60   ~ 0
5V_Regul
$Comp
L Conn_01x02 J2
U 1 1 59E782D0
P 800 3100
F 0 "J2" H 800 3200 50  0000 C CNN
F 1 "Current_pwr" H 800 2900 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 800 3100 50  0001 C CNN
F 3 "" H 800 3100 50  0001 C CNN
	1    800  3100
	0    1    1    0   
$EndComp
$Comp
L Conn_01x02 J3
U 1 1 59E7833C
P 1200 3100
F 0 "J3" H 1200 3200 50  0000 C CNN
F 1 "CO2_pwr" H 1200 2900 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 1200 3100 50  0001 C CNN
F 3 "" H 1200 3100 50  0001 C CNN
	1    1200 3100
	0    1    1    0   
$EndComp
$Comp
L Conn_01x02 J4
U 1 1 59E783BE
P 1600 3100
F 0 "J4" H 1600 3200 50  0000 C CNN
F 1 "CO2_pwr" H 1600 2900 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 1600 3100 50  0001 C CNN
F 3 "" H 1600 3100 50  0001 C CNN
	1    1600 3100
	0    1    1    0   
$EndComp
Text Label 800  2900 1    60   ~ 0
5V_Regul
Text Label 1200 2900 1    60   ~ 0
5V_Regul
Text Label 1600 2900 1    60   ~ 0
3V3_Regul
$Comp
L GND #PWR02
U 1 1 59E7848D
P 1100 3500
F 0 "#PWR02" H 1100 3250 50  0001 C CNN
F 1 "GND" H 1100 3350 50  0000 C CNN
F 2 "" H 1100 3500 50  0001 C CNN
F 3 "" H 1100 3500 50  0001 C CNN
	1    1100 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 59E784BF
P 1200 1400
F 0 "#PWR03" H 1200 1150 50  0001 C CNN
F 1 "GND" H 1200 1250 50  0000 C CNN
F 2 "" H 1200 1400 50  0001 C CNN
F 3 "" H 1200 1400 50  0001 C CNN
	1    1200 1400
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 59E789B2
P 2100 1900
F 0 "C1" H 2125 2000 50  0000 L CNN
F 1 "100uF" H 2125 1800 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_Tantal_D10.5mm_P5.00mm" H 2100 1900 50  0001 C CNN
F 3 "" H 2100 1900 50  0001 C CNN
	1    2100 1900
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 7550 6850 7550
Wire Wire Line
	5150 7550 5150 7400
Wire Wire Line
	4850 7550 4850 7400
Connection ~ 5000 7550
Wire Wire Line
	4650 4450 4650 4550
Wire Wire Line
	4650 2200 4650 2300
Wire Wire Line
	6550 1600 7550 1600
Wire Wire Line
	7550 1600 7550 6500
Wire Wire Line
	7550 6500 6850 6500
Wire Wire Line
	6850 6500 6850 7550
Connection ~ 5150 7550
Wire Wire Line
	4650 2250 2900 2250
Wire Wire Line
	2900 2250 2900 7550
Wire Wire Line
	2900 4500 4650 4500
Connection ~ 4650 4500
Connection ~ 4650 2250
Connection ~ 4850 7550
Connection ~ 2900 4500
Wire Wire Line
	6550 1300 7850 1300
Wire Wire Line
	7850 1400 6550 1400
Wire Wire Line
	7850 1500 7700 1500
Wire Wire Line
	7700 1500 7700 1700
Wire Wire Line
	7700 1700 6550 1700
Wire Wire Line
	6550 1800 7850 1800
Wire Wire Line
	7850 1800 7850 1600
Wire Wire Line
	4650 2600 3850 2600
Wire Wire Line
	4650 2700 3850 2700
Wire Wire Line
	4650 3000 4400 3000
Wire Wire Line
	4400 3000 4400 3200
Wire Wire Line
	4650 3100 4450 3100
Wire Wire Line
	4450 3100 4450 3300
Wire Wire Line
	4450 3300 3850 3300
Wire Wire Line
	4650 3200 4500 3200
Wire Wire Line
	4500 3200 4500 3400
Wire Wire Line
	4500 3400 3850 3400
Wire Wire Line
	4650 3300 4550 3300
Wire Wire Line
	4550 3300 4550 3500
Wire Wire Line
	4550 3500 3850 3500
Wire Wire Line
	5450 7400 5450 7550
Connection ~ 5450 7550
Wire Wire Line
	1500 900  2900 900 
Wire Wire Line
	3000 900  3000 1650
Wire Wire Line
	800  1200 3000 1200
Wire Wire Line
	800  1200 800  1000
Connection ~ 1200 1200
Wire Wire Line
	900  900  800  900 
Wire Wire Line
	2050 900  2050 1650
Connection ~ 2050 900 
Wire Wire Line
	2050 1650 900  1650
Wire Wire Line
	900  1650 900  2050
Wire Wire Line
	1200 1400 1200 1200
Wire Wire Line
	700  2900 550  2900
Wire Wire Line
	550  2900 550  3500
Wire Wire Line
	550  3500 1900 3500
Wire Wire Line
	1100 2900 1000 2900
Wire Wire Line
	1000 2900 1000 3200
Wire Wire Line
	1000 3200 1100 3200
Wire Wire Line
	1100 3200 1100 3500
Wire Wire Line
	1400 3500 1400 2900
Wire Wire Line
	1400 2900 1500 2900
Connection ~ 1100 3500
Wire Wire Line
	6550 1000 6800 1000
Wire Wire Line
	6800 1000 6800 700 
Wire Wire Line
	6800 700  3800 700 
Wire Wire Line
	3800 700  3800 1200
Wire Wire Line
	3800 1200 3100 1200
Wire Wire Line
	3100 1200 3100 900 
Wire Wire Line
	3200 900  3200 1150
Wire Wire Line
	3200 1150 3750 1150
Wire Wire Line
	3750 1150 3750 650 
Wire Wire Line
	3750 650  7050 650 
Wire Wire Line
	7050 650  7050 2700
Wire Wire Line
	7050 2700 6550 2700
Wire Wire Line
	3300 900  3300 1000
Wire Wire Line
	3300 1000 5450 1000
Wire Wire Line
	3400 900  5450 900 
Wire Wire Line
	1200 1750 2100 1750
Wire Wire Line
	1350 1750 1350 1200
Connection ~ 1350 1200
Connection ~ 1350 1750
Wire Wire Line
	900  1100 900  1200
Connection ~ 900  1200
Wire Wire Line
	1500 2050 2900 2050
Wire Wire Line
	2900 2050 2900 1650
Connection ~ 2100 2050
Connection ~ 3000 1200
Wire Wire Line
	3100 1650 3100 1300
Wire Wire Line
	3100 1300 4600 1300
Wire Wire Line
	4600 1300 4600 900 
Connection ~ 4600 900 
Wire Wire Line
	3200 1750 4150 1750
Wire Wire Line
	4150 1750 4150 700 
Connection ~ 4150 700 
Wire Wire Line
	3200 1750 3200 1650
Wire Wire Line
	3300 1650 3300 1700
Wire Wire Line
	3300 1700 4000 1700
Wire Wire Line
	4000 1700 4000 1000
Connection ~ 4000 1000
Wire Wire Line
	3400 1650 5900 1650
Wire Wire Line
	5900 1650 5900 2000
Wire Wire Line
	5900 2000 6550 2000
Text Label 4400 1650 0    60   ~ 0
RTC_CS
Text Label 6850 650  0    60   ~ 0
SD_CS
Wire Wire Line
	1200 2350 1200 1750
$Comp
L Conn_01x04 J10
U 1 1 59E7921E
P 7400 3800
F 0 "J10" H 7400 4000 50  0000 C CNN
F 1 "Xbee" H 7400 3500 50  0000 C CNN
F 2 "ecoPlanos_custom:JST_PHR-4" H 7400 3800 50  0001 C CNN
F 3 "" H 7400 3800 50  0001 C CNN
	1    7400 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3700 7200 3700
Wire Wire Line
	6550 3800 7200 3800
Connection ~ 7550 4000
$Comp
L Conn_02x04_Odd_Even J11
U 1 1 59E79754
P 7400 4450
F 0 "J11" H 7400 4650 50  0000 C CNN
F 1 "Xbee_SEL" H 7400 4150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x04_Pitch2.54mm" H 7400 4450 50  0001 C CNN
F 3 "" H 7400 4450 50  0001 C CNN
	1    7400 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5350 6650 5350
Wire Wire Line
	6650 5350 6650 4650
Wire Wire Line
	6650 4650 7700 4650
Wire Wire Line
	6600 4450 7700 4450
Wire Wire Line
	6600 4450 6600 4900
Wire Wire Line
	6600 4900 6550 4900
Wire Wire Line
	7050 4550 7700 4550
Wire Wire Line
	7050 4550 7050 3900
Wire Wire Line
	7050 3900 7200 3900
Wire Wire Line
	7200 4350 7200 4000
Connection ~ 7200 4550
Connection ~ 7200 4450
Connection ~ 7200 4650
Wire Wire Line
	7200 4350 7700 4350
Connection ~ 7200 4350
$Comp
L Conn_01x02 J12
U 1 1 59E7A8B0
P 2000 3100
F 0 "J12" H 2000 3200 50  0000 C CNN
F 1 "Xbee_pwr" H 2000 2900 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 2000 3100 50  0001 C CNN
F 3 "" H 2000 3100 50  0001 C CNN
	1    2000 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 3500 1900 2900
Connection ~ 1400 3500
Text Label 2000 2900 1    60   ~ 0
3V3_Regul
Wire Wire Line
	4650 2800 3850 2800
Wire Wire Line
	3850 2900 4650 2900
Wire Wire Line
	4400 3200 3850 3200
$Comp
L Conn_01x01 J13
U 1 1 59E7F29A
P 5750 7200
F 0 "J13" H 5750 7300 50  0000 C CNN
F 1 "xbee_shield" H 5750 7100 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x01_Pitch2.54mm" H 5750 7200 50  0001 C CNN
F 3 "" H 5750 7200 50  0001 C CNN
	1    5750 7200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5750 7400 5750 7550
Connection ~ 5750 7550
Text Label 3850 3500 0    60   ~ 0
Activity_LED
Text Label 3850 3400 0    60   ~ 0
CCS811_nRST
$EndSCHEMATC
