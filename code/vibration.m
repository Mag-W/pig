clear all;
close all;
clc;
file_path_1 = 'F:\PX4\log\honver\5-17\2\二叶桨_vehicle_imu_status_1.csv'; %二叶桨文件路径
file_path_2 = 'F:\PX4\log\honver\5-17\3\三叶桨_vehicle_imu_status_1.csv'; %三叶桨文件路径
file_path_3 = 'F:\PX4\log\5-22\vibration\vibration_vehicle_imu_status_1.csv'; %四叶桨文件路径

%悬停时PWM输出
file_path_4 = 'F:\PX4\log\honver\2\二叶桨数据_actuator_outputs_0.csv'; %二
file_path_5 = 'F:\PX4\log\honver\3\三叶桨数据_actuator_outputs_0.csv'; %三叶桨文件路径
file_path_6 = 'F:\PX4\log\honver\4\四叶桨数据_actuator_outputs_0.csv'; %四叶桨文件路径

x_column = 1; %选择第几列作为X轴
y_column = 13;%选择第几列作为Y轴
y_gyro = 14;

y_pwm_0 = 3;
y_pwm_1 = 4;
y_pwm_2 = 5;
y_pwm_3 = 6;

data1 = readmatrix(file_path_1);
data2 = readmatrix(file_path_2);
data3 = readmatrix(file_path_3);

data4 = readmatrix(file_path_4);
data5 = readmatrix(file_path_5);
data6 = readmatrix(file_path_6);

x_data = data1(:,x_column); %选择X轴数据,此时的时间戳单位为微妙，转化为秒
x_data = x_data / 1e6;
x_pwm = data4(:,x_column) / 1e6;
accel_vibration_metric_1 = data1(:,y_column); %选择Y轴数据
gyro_vibration_metric_1 = data1(:,y_gyro);

accel_vibration_metric_2 = data2(:,y_column);
gyro_vibration_metric_2 = data2(:,y_gyro);

accel_vibration_metric_3 = data3(:,y_column);
gyro_vibration_metric_3 = data3(:,y_gyro);

pwm_2_0 = data4(:,y_pwm_0);pwm_2_1 = data4(:,y_pwm_1);pwm_2_2 = data4(:,y_pwm_2);pwm_2_3 = data4(:,y_pwm_3); %二叶桨四个pwm输出
pwm_3_0 = data5(:,y_pwm_0);pwm_3_1 = data5(:,y_pwm_1);pwm_3_2 = data5(:,y_pwm_2);pwm_3_3 = data5(:,y_pwm_3); %二叶桨四个pwm输出
pwm_4_0 = data6(:,y_pwm_0);pwm_4_1 = data6(:,y_pwm_1);pwm_4_2 = data6(:,y_pwm_2);pwm_4_3 = data6(:,y_pwm_3); %二叶桨四个pwm输出


figure;

%{
plot(x_data,accel_vibration_metric_1,'LineWidth',2,'color','red');
hold on;
plot(1:length(accel_vibration_metric_2),accel_vibration_metric_2,'LineWidth',2,'color','blue');
plot(1:length(accel_vibration_metric_3),accel_vibration_metric_3,'LineWidth',2,'color','green');
title('加速度计振动指标','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('加速度(m/s^2)','FontSize',24);
legend('二叶桨','三叶桨','四叶桨','FontSize',16);
%}

%{
plot(x_data,gyro_vibration_metric_1,'LineWidth',2,'color','red');
hold on;
plot(1:length(gyro_vibration_metric_2),gyro_vibration_metric_2,'LineWidth',2,'color','blue');
plot(1:length(gyro_vibration_metric_3),gyro_vibration_metric_3,'LineWidth',2,'color','green');
title('陀螺仪振动指标','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('加速度(m/s^2)','FontSize',24);
legend('二叶桨','三叶桨','四叶桨','FontSize',16);
%}

plot(x_pwm,pwm_2_0,'LineWidth',1,'color','red');  %二叶桨pwm
hold on;
plot(x_pwm(1:length(pwm_3_0)),pwm_3_0,'LineWidth',1,'color','blue');     %三叶桨pwm
plot(x_pwm(1:length(pwm_4_0)),pwm_4_0,'LineWidth',1,'color','green');    %四叶桨pwm
plot(x_pwm,pwm_2_1,'LineWidth',1,'color','red');
plot(x_pwm,pwm_2_2,'LineWidth',1,'color','red');
plot(x_pwm,pwm_2_3,'LineWidth',1,'color','red');
plot(x_pwm(end), data1(12), 'o', 'Color', 'red', 'MarkerSize', 5); % 添加标注

plot(x_pwm(1:length(pwm_3_0)),pwm_3_0,'LineWidth',1,'color','blue');     %三叶桨pwm
plot(x_pwm(1:length(pwm_3_1)),pwm_3_1,'LineWidth',1,'color','blue');
plot(x_pwm(1:length(pwm_3_2)),pwm_3_2,'LineWidth',1,'color','blue');
plot(x_pwm(1:length(pwm_3_3)),pwm_3_3,'LineWidth',1,'color','blue');

plot(x_pwm(1:length(pwm_4_0)),pwm_4_0,'LineWidth',1,'color','green');    %四叶桨pwm
plot(x_pwm(1:length(pwm_4_1)),pwm_4_1,'LineWidth',1,'color','green');
plot(x_pwm(1:length(pwm_4_2)),pwm_4_2,'LineWidth',1,'color','green');
plot(x_pwm(1:length(pwm_4_3)),pwm_4_3,'LineWidth',1,'color','green');

ylim([1000, 2000]);
title('PWM输出曲线','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('PWM值','FontSize',24);

legend('二叶桨','三叶桨','四叶桨','FontSize',16);


hold off;





