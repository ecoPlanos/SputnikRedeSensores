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
LIBS:xbee
LIBS:XBee_Breakout-cache
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
L XBEE U1
U 1 1 5A05AB64
P 4050 3100
F 0 "U1" H 3800 3750 50  0000 L CNN
F 1 "XBEE" H 3650 2500 50  0000 L CNN
F 2 "unchecked:XBEE" H 3650 2400 50  0001 L CNN
F 3 "" H 3550 3500 50  0001 C CNN
	1    4050 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5A05C5C5
P 2700 3900
F 0 "#PWR01" H 2700 3650 50  0001 C CNN
F 1 "GND" H 2700 3750 50  0000 C CNN
F 2 "" H 2700 3900 50  0001 C CNN
F 3 "" H 2700 3900 50  0001 C CNN
	1    2700 3900
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR02
U 1 1 5A05C5DB
P 2700 2200
F 0 "#PWR02" H 2700 2050 50  0001 C CNN
F 1 "+3V3" H 2700 2340 50  0000 C CNN
F 2 "" H 2700 2200 50  0001 C CNN
F 3 "" H 2700 2200 50  0001 C CNN
	1    2700 2200
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J1
U 1 1 5A05C6D4
P 5300 3050
F 0 "J1" H 5300 3150 50  0000 C CNN
F 1 "Conn_01x02" H 5300 2850 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 5300 3050 50  0001 C CNN
F 3 "" H 5300 3050 50  0001 C CNN
	1    5300 3050
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J2
U 1 1 5A05C721
P 2750 3150
F 0 "J2" H 2750 3350 50  0000 C CNN
F 1 "Conn_01x04" H 2750 2850 50  0000 C CNN
F 2 "ecoPlanos_custom:JST_PHR-4" H 2750 3150 50  0001 C CNN
F 3 "" H 2750 3150 50  0001 C CNN
	1    2750 3150
	-1   0    0    1   
$EndComp
$Comp
L LED D2
U 1 1 5A05C819
P 4900 3700
F 0 "D2" H 4900 3800 50  0000 C CNN
F 1 "LED" H 4900 3600 50  0000 C CNN
F 2 "LEDs:LED_D4.0mm" H 4900 3700 50  0001 C CNN
F 3 "" H 4900 3700 50  0001 C CNN
	1    4900 3700
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 5A05C8B2
P 3250 2300
F 0 "D1" H 3250 2400 50  0000 C CNN
F 1 "LED" H 3250 2200 50  0000 C CNN
F 2 "LEDs:LED_D4.0mm" H 3250 2300 50  0001 C CNN
F 3 "" H 3250 2300 50  0001 C CNN
	1    3250 2300
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 5A05C933
P 4900 3400
F 0 "R2" V 4980 3400 50  0000 C CNN
F 1 "R" V 4900 3400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4830 3400 50  0001 C CNN
F 3 "" H 4900 3400 50  0001 C CNN
	1    4900 3400
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A05C9A8
P 2950 2300
F 0 "R1" V 3030 2300 50  0000 C CNN
F 1 "R" V 2950 2300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2880 2300 50  0001 C CNN
F 3 "" H 2950 2300 50  0001 C CNN
	1    2950 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 2200 2700 2700
Wire Wire Line
	2700 3600 2700 3900
Wire Wire Line
	2950 2950 3050 2950
Wire Wire Line
	3050 2950 3050 2800
Wire Wire Line
	3050 2800 3550 2800
Wire Wire Line
	2950 3050 3150 3050
Wire Wire Line
	3150 3050 3150 2900
Wire Wire Line
	3150 2900 3550 2900
Wire Wire Line
	3550 3100 2950 3100
Wire Wire Line
	2950 3100 2950 3150
Wire Wire Line
	4550 2900 4900 2900
Wire Wire Line
	4900 2900 4900 3250
Wire Wire Line
	2700 3850 5100 3850
Connection ~ 2700 3850
Wire Wire Line
	2800 2300 2700 2300
Connection ~ 2700 2300
Connection ~ 4900 3850
Wire Wire Line
	2950 3250 3400 3250
Wire Wire Line
	3400 3250 3400 3150
Wire Wire Line
	3400 3150 4900 3150
Connection ~ 4900 3150
NoConn ~ 4550 2700
NoConn ~ 4550 2800
NoConn ~ 4550 3000
NoConn ~ 4550 3100
NoConn ~ 4550 3200
NoConn ~ 4550 3300
NoConn ~ 4550 3400
NoConn ~ 4550 3500
NoConn ~ 4550 3600
NoConn ~ 3550 3500
NoConn ~ 3550 3300
NoConn ~ 3550 3200
NoConn ~ 3550 3000
Wire Wire Line
	5100 3850 5100 3150
Wire Wire Line
	5100 3050 5100 2450
Text Label 3050 2800 0    60   ~ 0
TX
Text Label 3150 2900 0    60   ~ 0
RX
Text Label 3150 3100 0    60   ~ 0
nRESET
Text Label 3050 3250 0    60   ~ 0
ON
Wire Wire Line
	2700 2700 3550 2700
Wire Wire Line
	3550 3600 2700 3600
Wire Wire Line
	5100 2450 2700 2450
Connection ~ 2700 2450
$Comp
L GND #PWR?
U 1 1 5A0CEF92
P 3550 2300
F 0 "#PWR?" H 3550 2050 50  0001 C CNN
F 1 "GND" H 3550 2150 50  0000 C CNN
F 2 "" H 3550 2300 50  0001 C CNN
F 3 "" H 3550 2300 50  0001 C CNN
	1    3550 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 2300 3550 2300
$EndSCHEMATC
