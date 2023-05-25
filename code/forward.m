clear all;
close all;
clc;

file_path_1 = 'F:\PX4\log\forward\5-17\2\二叶桨_vehicle_attitude_setpoint_0.csv'; %前飞时设置角度
file_path_2 = 'F:\PX4\log\forward\5-17\3\三叶桨_vehicle_attitude_setpoint_0.csv'; %前飞时设置角度
file_path_3 = 'F:\PX4\log\forward\5-17\4\四叶桨_vehicle_attitude_setpoint_0.csv'; %前飞时设置角度

file_path_4 = 'F:\PX4\log\forward\5-17\2\二叶桨_vehicle_attitude_setpoint_0.csv'; %前飞实际角度
file_path_5 = 'F:\PX4\log\forward\5-17\3\三叶桨_vehicle_attitude_setpoint_0.csv'; %前飞实际角度
file_path_6 = 'F:\PX4\log\forward\5-17\4\四叶桨_vehicle_attitude_setpoint_0.csv'; %前飞实际角度

file_path_7 = 'F:\PX4\log\forward\5-17\2\二叶桨_vehicle_local_position_0.csv'; %前飞时y轴速度
file_path_8 = 'F:\PX4\log\forward\5-17\3\三叶桨_vehicle_local_position_0.csv'; %前飞时y轴速度
file_path_9 = 'F:\PX4\log\forward\5-17\4\四叶桨_vehicle_local_position_0.csv'; %前飞时y轴速度

x_column = 1; %选择第几列作为X轴
y_column = 3; %选择第几列作为Y轴 
y_vy = 13; %y方向速度

data1 = readmatrix(file_path_1);
data2 = readmatrix(file_path_2);
data3 = readmatrix(file_path_3);

data4 = readmatrix(file_path_4);
data5 = readmatrix(file_path_5);
data6 = readmatrix(file_path_6);

data7 = readmatrix(file_path_7);
data8 = readmatrix(file_path_8);
data9 = readmatrix(file_path_9);

x_data = data1(:,x_column); %选择X轴数据,此时的时间戳单位为微妙，转化为秒
x_data_2 = data7(:,x_column);
x_data = x_data / 1e6;
x_data_2 = x_data_2 / 1e6;
pitch_setpoint_1 = data1(:,y_column) .*(180/pi); %选择Y轴数据 弧度转化为度

pitch_setpoint_2 = data2(:,y_column) .*(180/pi);    
pitch_setpoint_2 = pitch_setpoint_2(1:400);
pitch_setpoint_3 = data3(:,y_column) .*(180/pi);

vy_1 = data7(:,y_vy);
vy_2 = data8(:,y_vy);
vy_2 = vy_2(100:250); %取其中第100个到250个数据，因为太多了
vy_3 = data9(:,y_vy);

figure;

%绘制pitch角度图片
plot(x_data,pitch_setpoint_1,'LineWidth',2,'color','red');
hold on;
plot(x_data(1:length(pitch_setpoint_2)),pitch_setpoint_2,'LineWidth',2,'color','blue');
plot(x_data(1:length(pitch_setpoint_3)),pitch_setpoint_3,'LineWidth',2,'color','green');
title('俯仰飞行pitch轴角度','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('角度（°）','FontSize',24);
legend('二叶桨','三叶桨','四叶桨','FontSize',16);


%{
%绘制y方向图片
plot(x_data_2,vy_1,'LineWidth',2,'color','red');
hold on;
plot(x_data_2(1:length(vy_2)),vy_2,'LineWidth',2,'color','blue');
plot(x_data_2(1:length(vy_3)),vy_3,'LineWidth',2,'color','green');
title('俯仰飞行y轴速度','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('速度（m/s）','FontSize',24);
legend('二叶桨','三叶桨','四叶桨','FontSize',16);
%}


