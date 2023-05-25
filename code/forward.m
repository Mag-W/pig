clear all;
close all;
clc;

file_path_1 = 'F:\PX4\log\forward\5-17\2\��Ҷ��_vehicle_attitude_setpoint_0.csv'; %ǰ��ʱ���ýǶ�
file_path_2 = 'F:\PX4\log\forward\5-17\3\��Ҷ��_vehicle_attitude_setpoint_0.csv'; %ǰ��ʱ���ýǶ�
file_path_3 = 'F:\PX4\log\forward\5-17\4\��Ҷ��_vehicle_attitude_setpoint_0.csv'; %ǰ��ʱ���ýǶ�

file_path_4 = 'F:\PX4\log\forward\5-17\2\��Ҷ��_vehicle_attitude_setpoint_0.csv'; %ǰ��ʵ�ʽǶ�
file_path_5 = 'F:\PX4\log\forward\5-17\3\��Ҷ��_vehicle_attitude_setpoint_0.csv'; %ǰ��ʵ�ʽǶ�
file_path_6 = 'F:\PX4\log\forward\5-17\4\��Ҷ��_vehicle_attitude_setpoint_0.csv'; %ǰ��ʵ�ʽǶ�

file_path_7 = 'F:\PX4\log\forward\5-17\2\��Ҷ��_vehicle_local_position_0.csv'; %ǰ��ʱy���ٶ�
file_path_8 = 'F:\PX4\log\forward\5-17\3\��Ҷ��_vehicle_local_position_0.csv'; %ǰ��ʱy���ٶ�
file_path_9 = 'F:\PX4\log\forward\5-17\4\��Ҷ��_vehicle_local_position_0.csv'; %ǰ��ʱy���ٶ�

x_column = 1; %ѡ��ڼ�����ΪX��
y_column = 3; %ѡ��ڼ�����ΪY�� 
y_vy = 13; %y�����ٶ�

data1 = readmatrix(file_path_1);
data2 = readmatrix(file_path_2);
data3 = readmatrix(file_path_3);

data4 = readmatrix(file_path_4);
data5 = readmatrix(file_path_5);
data6 = readmatrix(file_path_6);

data7 = readmatrix(file_path_7);
data8 = readmatrix(file_path_8);
data9 = readmatrix(file_path_9);

x_data = data1(:,x_column); %ѡ��X������,��ʱ��ʱ�����λΪ΢�ת��Ϊ��
x_data_2 = data7(:,x_column);
x_data = x_data / 1e6;
x_data_2 = x_data_2 / 1e6;
pitch_setpoint_1 = data1(:,y_column) .*(180/pi); %ѡ��Y������ ����ת��Ϊ��

pitch_setpoint_2 = data2(:,y_column) .*(180/pi);    
pitch_setpoint_2 = pitch_setpoint_2(1:400);
pitch_setpoint_3 = data3(:,y_column) .*(180/pi);

vy_1 = data7(:,y_vy);
vy_2 = data8(:,y_vy);
vy_2 = vy_2(100:250); %ȡ���е�100����250�����ݣ���Ϊ̫����
vy_3 = data9(:,y_vy);

figure;

%����pitch�Ƕ�ͼƬ
plot(x_data,pitch_setpoint_1,'LineWidth',2,'color','red');
hold on;
plot(x_data(1:length(pitch_setpoint_2)),pitch_setpoint_2,'LineWidth',2,'color','blue');
plot(x_data(1:length(pitch_setpoint_3)),pitch_setpoint_3,'LineWidth',2,'color','green');
title('��������pitch��Ƕ�','FontSize',24);
xlabel('ʱ��(S)','FontSize',24);
ylabel('�Ƕȣ��㣩','FontSize',24);
legend('��Ҷ��','��Ҷ��','��Ҷ��','FontSize',16);


%{
%����y����ͼƬ
plot(x_data_2,vy_1,'LineWidth',2,'color','red');
hold on;
plot(x_data_2(1:length(vy_2)),vy_2,'LineWidth',2,'color','blue');
plot(x_data_2(1:length(vy_3)),vy_3,'LineWidth',2,'color','green');
title('��������y���ٶ�','FontSize',24);
xlabel('ʱ��(S)','FontSize',24);
ylabel('�ٶȣ�m/s��','FontSize',24);
legend('��Ҷ��','��Ҷ��','��Ҷ��','FontSize',16);
%}


