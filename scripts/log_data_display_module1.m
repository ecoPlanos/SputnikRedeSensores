data=importdata('2H20M13.CSV',',');
data_length=length(data(:,1));
t_ms=data(:,1);
dht11_t=data(:,2);
dht11_hr=data(:,3);
dht22_t=data(:,4);
dht22_hr=data(:,5);
sht75_t=data(:,6);
sht75_hr=data(:,7);
sht75_dewp=data(:,8);
ntc_r=data(:,10);
pt100_r=data(:,9);
sht31_t=data(:,11);
sht31_hr=data(:,12);
mlx_t=data(:,13);
mlx_t_obj=data(:,14);
thermopar_raw=data(:,15);

figure(); plot([dht11_hr,dht22_hr,sht31_hr,sht75_hr],'.-'); grid on;
legend('DHT11','DHT22','SHT31','SHT75');
title('Humidade');
ylabel('%');
xlabel('sample')
figure(); plot([dht11_t,dht22_t,sht31_t,sht75_t,mlx_t,mlx_t_obj],'.-'); grid on;
legend('DHT11','DHT22','SHT31','SHT75','MLX90614 Ambient','MLX90614 Object');
title('Temperatura');
ylabel([char(176),'C']);
xlabel('sample')
figure(); plot(ntc_r,'.-'); grid on;
title('NTC 100K resistance');
ylabel('Ohm');
xlabel('sample')
figure(); plot(pt100_r,'.-'); grid on;
title('PT100 resistance');
ylabel('Ohm');
xlabel('sample')
figure(); plot(thermopar_raw,'.-'); grid on;
title('Thermopar raw');
xlabel('sample')

figure(); plot(t_ms,'.-'); grid on;
title('Time');
ylabel('t (ms)');
xlabel('Sample');

figure(); plot(diff(t_ms),'.-'); grid on;
title('Time Intervals');
ylabel('dt (ms)');
xlabel('dSample');
