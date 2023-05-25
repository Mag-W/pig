clear all;
close all;
clc;
file_path_1 = 'F:\PX4\log\honver\2\��Ҷ������_battery_status_0.csv'; %��Ҷ���ļ�·��
x_column = 1; %ѡ��ڼ�����ΪX��
y_column = 3; %ѡ��ڼ�����ΪY��
data1 = readmatrix(file_path_1);
x_data = data1(:,x_column); %ѡ��X������,��ʱ��ʱ�����λΪ΢�ת��Ϊ��
x_data = x_data / 1e6;
voltage_data_1 = data1(:,y_column); %ѡ��Y������
figure;
plot(x_data,voltage_data_1,'LineWidth',2,'color','red');
title('��ͣ��ѹ����','FontSize',24);
xlabel('ʱ��(S)','FontSize',24);
ylabel('��ѹ(V)','FontSize',24);
legend('��Ҷ��','FontSize',16);
