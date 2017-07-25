data=importdata('13H21M53.CSV',',');
data_length=length(data(:,1));
t_ms=data(:,1);
dht11_t=data(:,2);
dht11_hr=data(:,3);
dht22_t=data(:,4);
dht22_hr=data(:,5);
sht31_t=data(:,6);
sht31_hr=data(:,7);
sht75_t=data(:,8);
sht75_hr=data(:,9);
mlx_t=data(:,10);
mlx_t_obj=data(:,11);
mg811_analog=data(:,12);
mq135_analog=data(:,13);
ccs811_co2=data(:,14);
ccs811_tvoc=data(:,15);
mg811_analog_percent = mg811_analog/1023*100;
mq135_analog_percent = mq135_analog/1023*100;
figure(); plot([dht11_hr,dht22_hr,sht31_hr,sht75_hr],'.-'); grid on;
legend('DHT11','DHT22','SHT31','SHT75');
title('Humidade');
ylabel('%');
xlabel('t (s)')
figure(); plot([dht11_t,dht22_t,sht31_t,sht75_t,mlx_t,mlx_t_obj],'.-'); grid on;
legend('DHT11','DHT22','SHT31','SHT75','MLX90614 Ambient','MLX90614 Object');
title('Temperatura');
ylabel([char(176),'C']);
xlabel('t (s)')

figure(); plot([mg811_analog_percent, mq135_analog_percent],'.-'); grid on;
legend('MG811 CO2 Sensor', 'MQ135 Gas Sensor');
title('Gas Sensors');
ylabel('Level (%)');
xlabel('t (s)');
axis([0 data_length 0 100]);

figure(); plot(ccs811_co2,'.-'); grid on;
title('Gas Sensors - CCS811');
ylabel('CO2 (ppm)');
xlabel('t (s)');

figure(); plot(ccs811_tvoc,'.-'); grid on;
title('Gas Sensors - CCS811');
ylabel('TVOC');
xlabel('t (s)');

figure(); plot(t_ms,'.-'); grid on;
title('Time');
ylabel('t (ms)');
xlabel('Sample');

figure(); plot(diff(t_ms),'.-'); grid on;
title('Time Intervals');
ylabel('dt (ms)');
xlabel('dSample');
