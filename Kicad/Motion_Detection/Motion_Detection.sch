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
LIBS:Common-Parts-Library
LIBS:freetronics_schematic
LIBS:Adafruit Feather M0 Basic rev C
LIBS:ecoPlanos_custom
LIBS:Motion_Detection-cache
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
L Conn_01x03 J3
U 1 1 5A09C7B6
P 1600 5700
F 0 "J3" H 1600 5900 50  0000 C CNN
F 1 "SEN0192_MW" H 1600 5500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 1600 5700 50  0001 C CNN
F 3 "" H 1600 5700 50  0001 C CNN
	1    1600 5700
	1    0    0    -1  
$EndComp
$Comp
L LM324 U2
U 1 1 5A0A2348
P 2500 2550
F 0 "U2" H 2500 2750 50  0000 L CNN
F 1 "LM324" H 2500 2350 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm" H 2450 2650 50  0001 C CNN
F 3 "" H 2550 2750 50  0001 C CNN
	1    2500 2550
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03 J2
U 1 1 5A0A238B
P 1600 3150
F 0 "J2" H 1600 3350 50  0000 C CNN
F 1 "SE-10" H 1600 2950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 1600 3150 50  0001 C CNN
F 3 "" H 1600 3150 50  0001 C CNN
	1    1600 3150
	1    0    0    -1  
$EndComp
Text GLabel 1350 5600 0    60   Input ~ 0
GND
Text GLabel 1350 5700 0    60   Input ~ 0
5V
Text GLabel 1350 5800 0    60   Output ~ 0
SEN0192_OUT
Text GLabel 1400 3050 0    60   Input ~ 0
GND
Text GLabel 1400 3150 0    60   Output ~ 0
SE-10_OUT
Text GLabel 1400 3250 0    60   Input ~ 0
12V
Text GLabel 2400 3800 3    60   Input ~ 0
GND
Text GLabel 2400 2250 1    60   Input ~ 0
5V
Text GLabel 1400 2450 0    60   Input ~ 0
SE-10_OUT
$Comp
L R R6
U 1 1 5A0A2480
P 2700 3250
F 0 "R6" V 2780 3250 50  0000 C CNN
F 1 "14.82K" V 2600 3250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2630 3250 50  0001 C CNN
F 3 "" H 2700 3250 50  0001 C CNN
	1    2700 3250
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5A0A24BF
P 2300 3250
F 0 "R3" V 2380 3250 50  0000 C CNN
F 1 "9.87K" V 2200 3250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2230 3250 50  0001 C CNN
F 3 "" H 2300 3250 50  0001 C CNN
	1    2300 3250
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5A0A2504
P 2150 3550
F 0 "R2" V 2230 3550 50  0000 C CNN
F 1 "9.85K" V 2050 3550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2080 3550 50  0001 C CNN
F 3 "" H 2150 3550 50  0001 C CNN
	1    2150 3550
	1    0    0    -1  
$EndComp
$Comp
L Barrel_Jack J1
U 1 1 5A0A296F
P 1200 1050
F 0 "J1" H 1200 1150 50  0000 C CNN
F 1 "12V input" H 1200 850 50  0000 C CNN
F 2 "Connectors:BARREL_JACK" H 1200 1050 50  0001 C CNN
F 3 "" H 1200 1050 50  0001 C CNN
	1    1200 1050
	1    0    0    -1  
$EndComp
Text GLabel 950  1150 0    60   Input ~ 0
GND
Text GLabel 950  1050 0    60   Input ~ 0
12V
$Comp
L LM7805_TO220 U1
U 1 1 5A0A2A43
P 2000 1000
F 0 "U1" H 1850 1125 50  0000 C CNN
F 1 "LM7805_TO220" H 2000 1125 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 2000 1225 50  0001 C CIN
F 3 "" H 2000 950 50  0001 C CNN
	1    2000 1000
	1    0    0    -1  
$EndComp
Text GLabel 2300 1000 2    60   Output ~ 0
5V
$Comp
L +12V #PWR01
U 1 1 5A0A2D65
P 1450 800
F 0 "#PWR01" H 1450 650 50  0001 C CNN
F 1 "+12V" H 1450 940 50  0000 C CNN
F 2 "" H 1450 800 50  0001 C CNN
F 3 "" H 1450 800 50  0001 C CNN
	1    1450 800 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5A0A2D89
P 1450 1450
F 0 "#PWR02" H 1450 1200 50  0001 C CNN
F 1 "GND" H 1450 1300 50  0000 C CNN
F 2 "" H 1450 1450 50  0001 C CNN
F 3 "" H 1450 1450 50  0001 C CNN
	1    1450 1450
	1    0    0    -1  
$EndComp
Text Notes 2100 1800 0    60   ~ 12
Power input
Text Notes 1250 4250 0    60   ~ 12
SE-10 PIR motion sensor
Text Notes 1150 6600 0    60   ~ 12
SEN0192 microwave motion sensor
$Comp
L R R4
U 1 1 5A0A4684
P 2350 5450
F 0 "R4" V 2430 5450 50  0000 C CNN
F 1 "1.491K" V 2250 5450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2280 5450 50  0001 C CNN
F 3 "" H 2350 5450 50  0001 C CNN
	1    2350 5450
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5A0A4730
P 2350 5850
F 0 "R5" V 2430 5850 50  0000 C CNN
F 1 "2.18K" V 2250 5850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2280 5850 50  0001 C CNN
F 3 "" H 2350 5850 50  0001 C CNN
	1    2350 5850
	1    0    0    -1  
$EndComp
Text GLabel 2350 6050 3    60   Input ~ 0
GND
Text GLabel 2350 5150 0    60   Input ~ 0
SEN0192_OUT
Text GLabel 2900 2550 2    60   Output ~ 0
SE-10_OUT_
Text GLabel 2500 5650 2    60   Output ~ 0
SEN0192_OUT_
Text Notes 5450 3150 0    60   ~ 12
ZRE200GE
$Comp
L C C1
U 1 1 5A0C1F63
P 1700 2450
F 0 "C1" H 1725 2550 50  0000 L CNN
F 1 "22u" H 1725 2350 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 1738 2300 50  0001 C CNN
F 3 "" H 1700 2450 50  0001 C CNN
	1    1700 2450
	0    1    1    0   
$EndComp
$Comp
L MICROBUILDER_HEADER-1X12 JP1
U 1 1 5A0C6AF5
P 8650 2200
F 0 "JP1" H 8400 2925 45  0000 L BNN
F 1 "MICROBUILDER_HEADER-1X12" H 7750 1500 45  0000 L BNN
F 2 "Adafruit Feather M0 Basic rev C:MICROBUILDER_1X12_ROUND" H 8680 2350 20  0001 C CNN
F 3 "" H 8650 2200 60  0001 C CNN
	1    8650 2200
	1    0    0    -1  
$EndComp
$Comp
L MICROBUILDER_HEADER-1X16 JP2
U 1 1 5A0C6B64
P 10300 2300
F 0 "JP2" H 10050 3125 45  0000 L BNN
F 1 "MICROBUILDER_HEADER-1X162MM_OVAL" V 10500 1600 45  0000 L BNN
F 2 "Adafruit Feather M0 Basic rev C:MICROBUILDER_1X16_ROUND" H 10330 2450 20  0001 C CNN
F 3 "" H 10300 2300 60  0001 C CNN
	1    10300 2300
	1    0    0    -1  
$EndComp
Text Notes 9250 6350 0    60   ~ 12
Feather
Text GLabel 8350 1600 0    60   Input ~ 12
VBAT
Text GLabel 8350 1700 0    60   Input ~ 12
EN
Text GLabel 8250 800  0    60   Input ~ 12
5V
Text GLabel 8350 1900 0    60   Output ~ 12
ACTIVITY_LED
Text GLabel 8350 2000 0    60   Input ~ 12
D12
Text GLabel 8350 2100 0    60   Input ~ 12
D11
Text GLabel 8350 2300 0    60   Input ~ 12
ZRE200_OUT_
Text GLabel 8350 2200 0    60   Input ~ 12
D10
Text GLabel 8350 2600 0    60   Output ~ 12
SCL
Text GLabel 8350 2700 0    60   BiDi ~ 12
SDA
Text GLabel 10000 1600 0    60   UnSpc ~ 12
GND
Text GLabel 10000 1900 0    60   Output ~ 12
MISO
Text GLabel 10000 2000 0    60   Input ~ 12
MOSI
Text GLabel 10000 2100 0    60   Output ~ 12
SCK
Text GLabel 8350 2400 0    60   Input ~ 12
EKMB_OUT_
Text GLabel 10000 2300 0    60   Input ~ 12
XBee_ON
Text GLabel 10000 2400 0    60   Input ~ 12
A3
Text GLabel 10000 2500 0    60   Input ~ 12
SEN0192_OUT_
Text GLabel 10000 2600 0    60   Input ~ 12
A1
Text GLabel 10000 2700 0    60   Input ~ 12
SE-10_OUT_
Text GLabel 10000 2800 0    60   UnSpc ~ 12
GND
Text GLabel 10000 3000 0    60   Output ~ 12
3V3
Text GLabel 10000 3100 0    60   Input ~ 12
nRESET
$Comp
L Conn_01x02 J7
U 1 1 5A0C7672
P 8450 1050
F 0 "J7" H 8450 1150 50  0000 C CNN
F 1 "5V Ext" V 8600 1000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 8450 1050 50  0001 C CNN
F 3 "" H 8450 1050 50  0001 C CNN
	1    8450 1050
	0    1    1    0   
$EndComp
Text GLabel 8550 800  2    60   Output ~ 12
VBUS
Text GLabel 8350 1800 0    60   Input ~ 12
VBUS
Text GLabel 10000 2900 0    60   Input ~ 12
AREF
Text GLabel 10000 1800 0    60   Input ~ 12
RX
Text GLabel 10000 1700 0    60   Output ~ 12
TX
Text GLabel 10000 2200 0    60   Output ~ 12
XBee_nRESET
Text GLabel 8350 2500 0    60   Input ~ 12
D5
NoConn ~ 10200 2900
$Comp
L Conn_01x02 J8
U 1 1 5A0C91FE
P 9350 1050
F 0 "J8" H 9350 1150 50  0000 C CNN
F 1 "3V3 EN" V 9500 1000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 9350 1050 50  0001 C CNN
F 3 "" H 9350 1050 50  0001 C CNN
	1    9350 1050
	0    1    1    0   
$EndComp
Text GLabel 9150 800  0    60   Input ~ 12
EN
Text GLabel 9450 800  2    60   UnSpc ~ 12
GND
NoConn ~ 10200 3100
Text Notes 5050 5050 0    60   ~ 12
EKMB1101111 PIR Sensor
Text GLabel 6600 4150 2    60   Output ~ 12
EKMB_OUT_
Text GLabel 4500 1800 1    60   Input ~ 12
ZRE200_OUT
Text GLabel 7150 2650 0    60   Output ~ 12
ZRE200_OUT_
Text GLabel 4700 3650 0    60   Input ~ 12
EKMB_OUT
$Comp
L PHR-4 P1
U 1 1 5A0CCDDB
P 5850 6600
F 0 "P1" H 5850 6600 50  0000 L CNN
F 1 "XBee" V 6050 6500 50  0000 L CNN
F 2 "JST_PHR-4" V 6050 6400 50  0001 L CNN
F 3 "JST" H 5800 6900 50  0001 L CNN
	1    5850 6600
	0    1    1    0   
$EndComp
Text GLabel 5700 6200 1    60   Input ~ 0
Rx
Text GLabel 5800 6200 1    60   Output ~ 0
Tx
Text GLabel 5900 6200 1    60   Output ~ 0
XBee_nRESET
Text GLabel 6000 6200 1    60   Input ~ 0
XBee_ON
$Comp
L LM324 U2
U 3 1 5A0CDA11
P 5200 2050
F 0 "U2" H 5200 2250 50  0000 L CNN
F 1 "LM324" H 5200 1850 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm" H 5150 2150 50  0001 C CNN
F 3 "" H 5250 2250 50  0001 C CNN
	3    5200 2050
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03 J6
U 1 1 5A0CE7C5
P 6350 800
F 0 "J6" H 6350 1000 50  0000 C CNN
F 1 "ZRE200GE" H 6350 600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 6350 800 50  0001 C CNN
F 3 "" H 6350 800 50  0001 C CNN
	1    6350 800 
	1    0    0    -1  
$EndComp
Text GLabel 5850 1750 0    60   Input ~ 0
GND
Text GLabel 5150 800  0    60   Output ~ 0
ZRE200_OUT
Text GLabel 5050 1650 0    60   Input ~ 0
5V
$Comp
L Conn_01x03 J4
U 1 1 5A0CE86A
P 4900 4650
F 0 "J4" H 4900 4850 50  0000 C CNN
F 1 "EKMB" H 4900 4450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 4900 4650 50  0001 C CNN
F 3 "" H 4900 4650 50  0001 C CNN
	1    4900 4650
	1    0    0    -1  
$EndComp
Text GLabel 4700 4550 0    60   Input ~ 0
GND
Text GLabel 4700 4650 0    60   Output ~ 0
EKMB_OUT
Text GLabel 4700 4750 0    60   Input ~ 0
5V
$Comp
L Conn_01x02 J5
U 1 1 5A0CEAD1
P 5200 6700
F 0 "J5" H 5200 6800 50  0000 C CNN
F 1 "3V3 Output" V 5300 6650 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 5200 6700 50  0001 C CNN
F 3 "" H 5200 6700 50  0001 C CNN
	1    5200 6700
	0    1    1    0   
$EndComp
Text GLabel 5100 6400 1    60   Input ~ 0
GND
Text GLabel 5200 6400 1    60   Input ~ 0
3V3
Text GLabel 4350 2950 0    60   Input ~ 0
GND
Text Notes 5500 7100 2    60   ~ 12
XBee
$Comp
L R R1
U 1 1 5A0DEF5A
P 1900 2750
F 0 "R1" V 1980 2750 50  0000 C CNN
F 1 "4.62K" V 1800 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 1830 2750 50  0001 C CNN
F 3 "" H 1900 2750 50  0001 C CNN
	1    1900 2750
	1    0    0    -1  
$EndComp
$Comp
L LM324 U2
U 4 1 5A0ED240
P 6950 2050
F 0 "U2" H 6950 2250 50  0000 L CNN
F 1 "LM324" H 6950 1850 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm" H 6900 2150 50  0001 C CNN
F 3 "" H 7000 2250 50  0001 C CNN
	4    6950 2050
	1    0    0    -1  
$EndComp
$Comp
L R Ra2
U 1 1 5A0EF000
P 4750 2350
F 0 "Ra2" V 4830 2350 50  0000 C CNN
F 1 "10K" V 4650 2350 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4680 2350 50  0001 C CNN
F 3 "" H 4750 2350 50  0001 C CNN
	1    4750 2350
	1    0    0    -1  
$EndComp
$Comp
L R Ra3
U 1 1 5A0EF0C9
P 5100 1200
F 0 "Ra3" V 5180 1200 50  0000 C CNN
F 1 "1M" V 5000 1200 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5030 1200 50  0001 C CNN
F 3 "" H 5100 1200 50  0001 C CNN
	1    5100 1200
	0    1    1    0   
$EndComp
$Comp
L R Ra4
U 1 1 5A0EF163
P 5700 2300
F 0 "Ra4" V 5780 2300 50  0000 C CNN
F 1 "100K" V 5600 2300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5630 2300 50  0001 C CNN
F 3 "" H 5700 2300 50  0001 C CNN
	1    5700 2300
	0    -1   -1   0   
$EndComp
$Comp
L R Ra7
U 1 1 5A0EF4B0
P 6050 2300
F 0 "Ra7" V 6130 2300 50  0000 C CNN
F 1 "10K" V 5950 2300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5980 2300 50  0001 C CNN
F 3 "" H 6050 2300 50  0001 C CNN
	1    6050 2300
	0    -1   -1   0   
$EndComp
$Comp
L R Ra1
U 1 1 5A0EF98C
P 4500 2250
F 0 "Ra1" V 4580 2250 50  0000 C CNN
F 1 "47K" V 4400 2250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4430 2250 50  0001 C CNN
F 3 "" H 4500 2250 50  0001 C CNN
	1    4500 2250
	1    0    0    -1  
$EndComp
$Comp
L R Ra10
U 1 1 5A0EFDB1
P 6900 1150
F 0 "Ra10" V 6980 1150 50  0000 C CNN
F 1 "1M2" V 6800 1150 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6830 1150 50  0001 C CNN
F 3 "" H 6900 1150 50  0001 C CNN
	1    6900 1150
	0    -1   -1   0   
$EndComp
$Comp
L C C3
U 1 1 5A0EFE3D
P 5100 1400
F 0 "C3" H 5125 1500 50  0000 L CNN
F 1 "10n" H 5125 1300 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 5138 1250 50  0001 C CNN
F 3 "" H 5100 1400 50  0001 C CNN
	1    5100 1400
	0    1    1    0   
$EndComp
$Comp
L C C7
U 1 1 5A0EFF5E
P 6900 1400
F 0 "C7" H 6925 1500 50  0000 L CNN
F 1 "10n" H 6925 1300 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 6938 1250 50  0001 C CNN
F 3 "" H 6900 1400 50  0001 C CNN
	1    6900 1400
	0    1    1    0   
$EndComp
$Comp
L CP C2
U 1 1 5A0F06AA
P 4750 2700
F 0 "C2" H 4775 2800 50  0000 L CNN
F 1 "10u" H 4775 2600 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 4788 2550 50  0001 C CNN
F 3 "" H 4750 2700 50  0001 C CNN
	1    4750 2700
	1    0    0    -1  
$EndComp
$Comp
L CP C6
U 1 1 5A0F08DA
P 6400 2300
F 0 "C6" H 6425 2400 50  0000 L CNN
F 1 "10u" H 6425 2200 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 6438 2150 50  0001 C CNN
F 3 "" H 6400 2300 50  0001 C CNN
	1    6400 2300
	0    1    1    0   
$EndComp
$Comp
L R Ra6
U 1 1 5A0F225E
P 5900 2600
F 0 "Ra6" V 5980 2600 50  0000 C CNN
F 1 "1M" V 5800 2600 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5830 2600 50  0001 C CNN
F 3 "" H 5900 2600 50  0001 C CNN
	1    5900 2600
	1    0    0    -1  
$EndComp
Text GLabel 6750 1650 0    60   Input ~ 0
5V
Text GLabel 6250 1250 0    60   Input ~ 0
5V
$Comp
L R Ra8
U 1 1 5A0F7661
P 6100 1750
F 0 "Ra8" V 6180 1750 50  0000 C CNN
F 1 "470K" V 6000 1750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6030 1750 50  0001 C CNN
F 3 "" H 6100 1750 50  0001 C CNN
	1    6100 1750
	0    -1   -1   0   
$EndComp
$Comp
L R Ra9
U 1 1 5A0F7727
P 6350 1500
F 0 "Ra9" V 6430 1500 50  0000 C CNN
F 1 "810K" V 6250 1500 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6280 1500 50  0001 C CNN
F 3 "" H 6350 1500 50  0001 C CNN
	1    6350 1500
	1    0    0    -1  
$EndComp
Text GLabel 5150 950  0    60   Input ~ 0
5V
Text GLabel 5150 650  0    60   Input ~ 0
GND
$Comp
L C C5
U 1 1 5A102930
P 6000 1150
F 0 "C5" H 6025 1250 50  0000 L CNN
F 1 "10u" H 5950 1050 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 6038 1000 50  0001 C CNN
F 3 "" H 6000 1150 50  0001 C CNN
	1    6000 1150
	-1   0    0    1   
$EndComp
$Comp
L C C4
U 1 1 5A1029EB
P 5600 1150
F 0 "C4" H 5625 1250 50  0000 L CNN
F 1 "100u" H 5625 1050 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 5638 1000 50  0001 C CNN
F 3 "" H 5600 1150 50  0001 C CNN
	1    5600 1150
	-1   0    0    1   
$EndComp
$Comp
L R Ra5
U 1 1 5A1031A3
P 5800 950
F 0 "Ra5" V 5880 950 50  0000 C CNN
F 1 "1K" V 5700 950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5730 950 50  0001 C CNN
F 3 "" H 5800 950 50  0001 C CNN
	1    5800 950 
	0    -1   -1   0   
$EndComp
Text GLabel 5800 1350 3    60   Input ~ 0
GND
Wire Wire Line
	2800 2550 2900 2550
Wire Wire Line
	2850 2550 2850 3250
Wire Wire Line
	2550 3250 2450 3250
Wire Wire Line
	2150 2650 2150 3400
Wire Wire Line
	2150 2650 2200 2650
Connection ~ 2150 3250
Wire Wire Line
	2150 3700 2150 3800
Wire Wire Line
	1900 3800 2400 3800
Wire Wire Line
	1000 1050 1000 1000
Wire Wire Line
	1000 1000 1700 1000
Wire Wire Line
	950  1050 1000 1050
Wire Wire Line
	950  1150 1000 1150
Wire Wire Line
	1000 1300 2000 1300
Wire Wire Line
	1000 1150 1000 1300
Connection ~ 1450 1000
Wire Wire Line
	1450 1450 1450 1300
Connection ~ 1450 1300
Wire Wire Line
	1400 5600 1350 5600
Wire Wire Line
	1400 5700 1350 5700
Wire Wire Line
	1400 5800 1350 5800
Wire Wire Line
	2400 3800 2400 2850
Connection ~ 2400 3800
Wire Wire Line
	1450 800  1450 1000
Wire Notes Line
	500  1900 2800 1900
Wire Notes Line
	2800 1900 2800 500 
Wire Notes Line
	2800 500  500  500 
Wire Notes Line
	500  500  500  1900
Wire Notes Line
	3800 2000 3800 4550
Wire Notes Line
	3800 4550 500  4550
Wire Notes Line
	500  4550 500  2000
Wire Notes Line
	500  2000 3800 2000
Wire Notes Line
	500  4650 500  6800
Wire Notes Line
	500  6800 3350 6800
Wire Notes Line
	3350 6800 3350 4650
Wire Notes Line
	3350 4650 500  4650
Wire Wire Line
	2350 6050 2350 6000
Wire Wire Line
	2350 5600 2350 5700
Connection ~ 2350 5650
Connection ~ 2850 2550
Wire Wire Line
	2500 5650 2350 5650
Wire Wire Line
	2350 5150 2350 5300
Wire Notes Line
	4000 550  4000 3200
Wire Notes Line
	7300 550  7300 3200
Wire Notes Line
	7300 550  4000 550 
Wire Wire Line
	2200 2450 1850 2450
Wire Wire Line
	1550 2450 1400 2450
Wire Notes Line
	7550 550  7550 6500
Wire Notes Line
	7550 6500 11150 6500
Wire Notes Line
	11150 6500 11150 550 
Wire Notes Line
	11150 550  7550 550 
Wire Wire Line
	8350 850  8350 800 
Wire Wire Line
	8350 800  8250 800 
Wire Wire Line
	8550 800  8450 800 
Wire Wire Line
	8450 800  8450 850 
Wire Wire Line
	8350 2600 8550 2600
Wire Wire Line
	8550 2700 8350 2700
Wire Wire Line
	8550 1600 8350 1600
Wire Wire Line
	8350 1700 8550 1700
Wire Wire Line
	8550 1800 8350 1800
Wire Wire Line
	8350 1900 8550 1900
Wire Wire Line
	8550 2000 8350 2000
Wire Wire Line
	8350 2100 8550 2100
Wire Wire Line
	8550 2200 8350 2200
Wire Wire Line
	8350 2300 8550 2300
Wire Wire Line
	10000 2200 10200 2200
Wire Wire Line
	10200 2300 10000 2300
Wire Wire Line
	10200 2400 10000 2400
Wire Wire Line
	10200 2500 10000 2500
Wire Wire Line
	10200 2600 10000 2600
Wire Wire Line
	10200 2700 10000 2700
Wire Wire Line
	10200 2800 10000 2800
Wire Wire Line
	10200 2900 10000 2900
Wire Wire Line
	10000 3000 10200 3000
Wire Wire Line
	10200 3100 10000 3100
Wire Wire Line
	10200 2100 10000 2100
Wire Wire Line
	10000 2000 10200 2000
Wire Wire Line
	10200 1900 10000 1900
Wire Wire Line
	10200 1800 10000 1800
Wire Wire Line
	10000 1700 10200 1700
Wire Wire Line
	10200 1600 10000 1600
Wire Wire Line
	8550 2500 8350 2500
Wire Wire Line
	8350 2400 8550 2400
Wire Wire Line
	9250 850  9250 800 
Wire Wire Line
	9250 800  9150 800 
Wire Wire Line
	9350 850  9350 800 
Wire Wire Line
	9350 800  9450 800 
Wire Notes Line
	4000 5150 7300 5150
Wire Notes Line
	7300 3400 4000 3400
Wire Wire Line
	6000 6300 6000 6200
Wire Wire Line
	5900 6300 5900 6200
Wire Wire Line
	5800 6200 5800 6300
Wire Wire Line
	5700 6200 5700 6300
Wire Wire Line
	5200 6500 5200 6400
Wire Wire Line
	5100 6500 5100 6400
Wire Notes Line
	4000 5250 6900 5250
Wire Notes Line
	6900 5250 6900 7200
Wire Notes Line
	6900 7200 4000 7200
Wire Notes Line
	4000 7200 4000 5250
Wire Wire Line
	1900 2450 1900 2600
Connection ~ 1900 2450
Wire Wire Line
	1900 2900 1900 3800
Connection ~ 2150 3800
Wire Wire Line
	5100 2350 5100 2950
Wire Wire Line
	6850 2950 6850 2350
Wire Wire Line
	5500 2050 5550 2050
Wire Wire Line
	6200 2300 6250 2300
Wire Wire Line
	5050 1650 5100 1650
Wire Wire Line
	5100 1650 5100 1750
Wire Wire Line
	6750 1650 6850 1650
Wire Wire Line
	6850 1650 6850 1750
Wire Wire Line
	6550 1400 6750 1400
Wire Wire Line
	6750 1150 6550 1150
Connection ~ 6550 1400
Wire Wire Line
	7050 1150 7250 1150
Wire Wire Line
	7250 1150 7250 2650
Wire Wire Line
	7050 1400 7250 1400
Connection ~ 7250 1400
Wire Wire Line
	4750 2550 4750 2500
Wire Wire Line
	4900 2150 4750 2150
Wire Wire Line
	4750 1200 4750 2200
Wire Wire Line
	4750 1400 4950 1400
Connection ~ 4750 2150
Wire Wire Line
	4950 1200 4750 1200
Connection ~ 4750 1400
Wire Wire Line
	5250 1200 5500 1200
Wire Wire Line
	5500 1200 5500 2050
Wire Wire Line
	5250 1400 5500 1400
Connection ~ 5500 1400
Wire Wire Line
	4350 2950 6850 2950
Wire Wire Line
	4750 2950 4750 2850
Connection ~ 4750 2950
Connection ~ 5900 2950
Connection ~ 5100 2950
Connection ~ 4500 2950
Wire Wire Line
	4900 1950 4500 1950
Wire Wire Line
	4500 2950 4500 2400
Wire Notes Line
	4000 3400 4000 5150
Wire Notes Line
	7300 5150 7300 3400
Wire Notes Line
	7300 3200 4000 3200
Wire Wire Line
	6250 1750 6650 1750
Wire Wire Line
	6350 1350 6350 1250
Wire Wire Line
	6350 1250 6250 1250
Wire Wire Line
	6650 1750 6650 1950
Connection ~ 4500 1950
Wire Wire Line
	7250 2650 7150 2650
Connection ~ 7250 2050
Wire Wire Line
	4500 2100 4500 1800
Wire Wire Line
	4700 3650 6450 3650
Wire Wire Line
	5600 1300 6000 1300
Wire Wire Line
	5150 950  5650 950 
Wire Wire Line
	5600 950  5600 1000
Wire Wire Line
	5950 950  6150 950 
Wire Wire Line
	6000 950  6000 1000
Connection ~ 5600 950 
Wire Wire Line
	5150 800  6150 800 
Wire Wire Line
	6150 950  6150 900 
Connection ~ 6000 950 
Wire Wire Line
	5150 650  5850 650 
Wire Wire Line
	5850 650  5850 700 
Wire Wire Line
	5850 700  6150 700 
Wire Wire Line
	5800 1350 5800 1300
Connection ~ 5800 1300
Wire Wire Line
	5550 2050 5550 2300
Wire Wire Line
	5850 2300 5900 2300
Wire Wire Line
	5900 2300 5900 2450
Wire Wire Line
	5900 2750 5900 2950
Wire Wire Line
	6550 2300 6650 2300
Wire Wire Line
	6650 2300 6650 2150
Wire Wire Line
	5950 1750 5850 1750
Connection ~ 5900 1750
Wire Wire Line
	6350 1650 6350 1750
Connection ~ 6350 1750
Wire Wire Line
	6550 1150 6550 2300
$Comp
L R R7
U 1 1 5A10C5A4
P 6450 3950
F 0 "R7" V 6530 3950 50  0000 C CNN
F 1 "1.491K" V 6350 3950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6380 3950 50  0001 C CNN
F 3 "" H 6450 3950 50  0001 C CNN
	1    6450 3950
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 5A10C5AA
P 6450 4350
F 0 "R8" V 6530 4350 50  0000 C CNN
F 1 "2.18K" V 6350 4350 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6380 4350 50  0001 C CNN
F 3 "" H 6450 4350 50  0001 C CNN
	1    6450 4350
	1    0    0    -1  
$EndComp
Text GLabel 6450 4550 3    60   Input ~ 0
GND
Wire Wire Line
	6450 4550 6450 4500
Wire Wire Line
	6450 4100 6450 4200
Connection ~ 6450 4150
Wire Wire Line
	6600 4150 6450 4150
Wire Wire Line
	6450 3650 6450 3800
Wire Wire Line
	1500 1050 1500 1300
Connection ~ 1500 1300
Connection ~ 1500 1150
Wire Wire Line
	1500 1000 1500 950 
Connection ~ 1500 1000
$EndSCHEMATC
