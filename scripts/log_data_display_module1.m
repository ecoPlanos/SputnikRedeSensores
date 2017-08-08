data=importdata('20H24M27.CSV',',');
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
ntc_t=data(:,12);

figure(); plot([dht11_hr,dht22_hr,sht31_hr,sht75_hr],'.-'); grid on;
legend('DHT11','DHT22','SHT31','SHT75');
title('Humidade');
ylabel('%');
xlabel('t (s)')
figure(); plot([dht11_t,dht22_t,sht31_t,sht75_t,mlx_t,mlx_t_obj,ntc_t],'.-'); grid on;
legend('DHT11','DHT22','SHT31','SHT75','MLX90614 Ambient','MLX90614 Object', 'NTC');
title('Temperatura');
ylabel([char(176),'C']);
xlabel('t (s)')

figure(); plot(t_ms,'.-'); grid on;
title('Time');
ylabel('t (ms)');
xlabel('Sample');

figure(); plot(diff(t_ms),'.-'); grid on;
title('Time Intervals');
ylabel('dt (ms)');
xlabel('dSample');
