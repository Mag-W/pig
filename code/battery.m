clear all;
close all;
clc;
file_path_1 = 'F:\PX4\log\honver\2\二叶桨数据_battery_status_0.csv'; %二叶桨文件路径
file_path_2 = 'F:\PX4\log\honver\3\三叶桨数据_battery_status_0.csv'; %三叶桨文件路径
file_path_3 = 'F:\PX4\log\honver\4\四叶桨数据_battery_status_0.csv'; %四叶桨文件路径

x_column = 1; %选择第几列作为X轴
y_column = 3; %选择第几列作为Y轴
data1 = readmatrix(file_path_1);
data2 = readmatrix(file_path_2);
data3 = readmatrix(file_path_3);

x_data = data1(:,x_column); %选择X轴数据,此时的时间戳单位为微妙，转化为秒
x_data = x_data / 1e6;
voltage_data_1 = data1(:,y_column); %选择Y轴数据
voltage_data_2 = data2(:,y_column);
voltage_data_3 = data3(:,y_column);

current_data_1 = data1(:,5);
current_data_2 = data2(:,5);
current_data_3 = data3(:,5);

figure;
%绘制电压曲线
%{
%subplot(3,1,1);
plot(x_data,voltage_data_1,'LineWidth',2,'color','red');
hold on;
plot(x_data(1:length(voltage_data_2)),voltage_data_2,'LineWidth',2,'color','blue');
hold on;
plot(x_data(1:length(voltage_data_3)),voltage_data_3,'LineWidth',2,'color','green');
title('悬停电压曲线','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('电压(V)','FontSize',24);
legend('二叶桨','三叶桨','四叶桨','FontSize',16);
hold off;
%}

%绘制电流曲线
%subplot(3,1,2);
plot(x_data,current_data_1,'LineWidth',2,'color','red');
hold on;
plot(x_data(1:length(current_data_2)),current_data_2,'LineWidth',2,'color','blue');
hold on;
plot(x_data(1:length(current_data_3)),current_data_3,'LineWidth',2,'color','green');
title('悬停电流曲线','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('电流(A)','FontSize',24);
legend('二叶桨','三叶桨','四叶桨','FontSize',16);
hold off;


%绘制功率曲线
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
title('悬停功率曲线','Interpreter','latex','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('功率(W)','FontSize',24);
legend('二叶桨','三叶桨','四叶桨','FontSize',16);
hold off;
%}