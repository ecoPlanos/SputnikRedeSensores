data=importdata('DATALOG.CSV',',');
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

figure(); plot([dht11_hr,dht22_hr,sht31_hr,sht75_hr],'.-'); grid on;
legend('DHT11','DHT22','SHT31','SHT75');
title('Humidade');
ylabel('%');
xlabel('t (ms)')
figure(); plot([dht11_t,dht22_t,sht31_t,sht75_t,mlx_t,mlx_t_obj],'.-'); grid on;
legend('DHT11','DHT22','SHT31','SHT75','MLX90614 Ambient','MLX90614 Object');
title('Temperatura');
ylabel([char(176),'C']);
xlabel('t (ms)')
