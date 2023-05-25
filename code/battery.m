clear all;
close all;
clc;
file_path_1 = 'F:\PX4\log\honver\2\��Ҷ������_battery_status_0.csv'; %��Ҷ���ļ�·��
file_path_2 = 'F:\PX4\log\honver\3\��Ҷ������_battery_status_0.csv'; %��Ҷ���ļ�·��
file_path_3 = 'F:\PX4\log\honver\4\��Ҷ������_battery_status_0.csv'; %��Ҷ���ļ�·��

x_column = 1; %ѡ��ڼ�����ΪX��
y_column = 3; %ѡ��ڼ�����ΪY��
data1 = readmatrix(file_path_1);
data2 = readmatrix(file_path_2);
data3 = readmatrix(file_path_3);

x_data = data1(:,x_column); %ѡ��X������,��ʱ��ʱ�����λΪ΢�ת��Ϊ��
x_data = x_data / 1e6;
voltage_data_1 = data1(:,y_column); %ѡ��Y������
voltage_data_2 = data2(:,y_column);
voltage_data_3 = data3(:,y_column);

current_data_1 = data1(:,5);
current_data_2 = data2(:,5);
current_data_3 = data3(:,5);

figure;
%���Ƶ�ѹ����
%{
%subplot(3,1,1);
plot(x_data,voltage_data_1,'LineWidth',2,'color','red');
hold on;
plot(x_data(1:length(voltage_data_2)),voltage_data_2,'LineWidth',2,'color','blue');
hold on;
plot(x_data(1:length(voltage_data_3)),voltage_data_3,'LineWidth',2,'color','green');
title('��ͣ��ѹ����','FontSize',24);
xlabel('ʱ��(S)','FontSize',24);
ylabel('��ѹ(V)','FontSize',24);
legend('��Ҷ��','��Ҷ��','��Ҷ��','FontSize',16);
hold off;
%}

%���Ƶ�������
%subplot(3,1,2);
plot(x_data,current_data_1,'LineWidth',2,'color','red');
hold on;
plot(x_data(1:length(current_data_2)),current_data_2,'LineWidth',2,'color','blue');
hold on;
plot(x_data(1:length(current_data_3)),current_data_3,'LineWidth',2,'color','green');
title('��ͣ��������','FontSize',24);
xlabel('ʱ��(S)','FontSize',24);
ylabel('����(A)','FontSize',24);
legend('��Ҷ��','��Ҷ��','��Ҷ��','FontSize',16);
hold off;


%���ƹ�������
power_data_1 = voltage_data_1 .* current_data_1;
power_data_2 = voltage_data_2 .* current_data_2;
power_data_3 = voltage_data_3 .* current_data_3;

%{
%subplot(3,1,3);
plot(x_data,power_data_1,'LineWidth',3,'color','red');
hold on;
plot(x_data(1:length(power_data_2)),power_data_2,'LineWidth',2,'color','blue');
hold on;
plot(x_data(1:length(power_data_3)),power_data_3,'LineWidth',2,'color','green');
title('��ͣ��������','Interpreter','latex','FontSize',24);
xlabel('ʱ��(S)','FontSize',24);
ylabel('����(W)','FontSize',24);
legend('��Ҷ��','��Ҷ��','��Ҷ��','FontSize',16);
hold off;
%}