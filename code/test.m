clear all;
close all;
clc;
file_path_1 = 'F:\PX4\log\honver\2\二叶桨数据_battery_status_0.csv'; %二叶桨文件路径
x_column = 1; %选择第几列作为X轴
y_column = 3; %选择第几列作为Y轴
data1 = readmatrix(file_path_1);
x_data = data1(:,x_column); %选择X轴数据,此时的时间戳单位为微妙，转化为秒
x_data = x_data / 1e6;
voltage_data_1 = data1(:,y_column); %选择Y轴数据
figure;
plot(x_data,voltage_data_1,'LineWidth',2,'color','red');
title('悬停电压曲线','FontSize',24);
xlabel('时间(S)','FontSize',24);
ylabel('电压(V)','FontSize',24);
legend('二叶桨','FontSize',16);
