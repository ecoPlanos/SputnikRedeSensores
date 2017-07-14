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
L CONN_01X10 J?
U 1 1 59693282
P 2150 4350
F 0 "J?" H 2150 4800 50  0000 C CNN
F 1 "T_RH" V 2250 4350 50  0000 C CNN
F 2 "" H 2150 4350 50  0001 C CNN
F 3 "" H 2150 4350 50  0001 C CNN
	1    2150 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 J?
U 1 1 59693758
P 3550 4350
F 0 "J?" H 3550 4700 50  0000 C CNN
F 1 "Gas" V 3650 4350 50  0000 C CNN
F 2 "" H 3550 4350 50  0001 C CNN
F 3 "" H 3550 4350 50  0001 C CNN
	1    3550 4350
	1    0    0    -1  
$EndComp
NoConn ~ 1950 4800
Text GLabel 1950 4700 0    60   Output ~ 0
TRH_Activity_led
Text GLabel 1950 4600 0    60   BiDi ~ 0
SCL
Text GLabel 1950 4500 0    60   BiDi ~ 0
SDA
Text GLabel 1950 4400 0    60   Output ~ 0
SHT75_SCK
$Comp
L GND #PWR?
U 1 1 59693FDE
P 2550 4950
F 0 "#PWR?" H 2550 4700 50  0001 C CNN
F 1 "GND" H 2550 4800 50  0000 C CNN
F 2 "" H 2550 4950 50  0001 C CNN
F 3 "" H 2550 4950 50  0001 C CNN
	1    2550 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 4950 2300 4950
Wire Wire Line
	2300 4950 2300 4300
Wire Wire Line
	2300 4300 1950 4300
$Comp
L +3V3 #PWR?
U 1 1 5969402F
P 2550 3750
F 0 "#PWR?" H 2550 3600 50  0001 C CNN
F 1 "+3V3" H 2550 3890 50  0000 C CNN
F 2 "" H 2550 3750 50  0001 C CNN
F 3 "" H 2550 3750 50  0001 C CNN
	1    2550 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3750 2300 3750
Wire Wire Line
	2300 3750 2300 4200
Wire Wire Line
	2300 4200 1950 4200
Text GLabel 1950 4100 0    60   Input ~ 0
SHT75_DATA
Text GLabel 1950 4000 0    60   Input ~ 0
DHT22_DATA
Text GLabel 1950 3900 0    60   Input ~ 0
DHT11_DATA
$EndSCHEMATC
