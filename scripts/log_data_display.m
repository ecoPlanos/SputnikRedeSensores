data=importdata('DATALOG_4.CSV',',');
data_length=length(data(:,1));
dht11_t=data(:,1);
dht11_hr=data(:,2);
dht22_t=data(:,3);
dht22_hr=data(:,4);
sht31_t=data(:,5);
sht31_hr=data(:,6);
sht75_t=data(:,7);
sht75_hr=data(:,8);
mlx_t=data(:,9);
mlx_t_obj=data(:,10);
mg811_analog=data(:,11);
mq135_analog=data(:,12);
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
