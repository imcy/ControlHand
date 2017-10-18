%%%%%%%%%%%%%%%%正运动学计算与逆运动学计算，验证公式的正确性%%%%
%%以食指为例
clc;
isThumb=0;
a1=20.871;
a2=50.059;
a3=44.621;
a4=25.014;

L1=24.331;
L2=37.685;
L3=40.220;
L4=40.220;
d1=-46.186;
d2=-20.941;
d3=-0.669;
d4=23.204;
t1= 0;
t2=88.5;
t3=96.5;
t4=(2*t3)/3;
fprintf('四个指关节取值角度如下:\n');
fprintf('theta1=%.2f,theta2=%.2f,theta3=%.2f,theta4=%.2f\n',t1,t2,t3,t4);
theta1=(t1*pi)/180;
theta2=(t2*pi)/180;
theta3=(t3*pi)/180;
theta4=(2/3)*theta3;

if isThumb==0
px=sin(theta1)*(a1+a2*cos(theta2)+a3*cos(theta2+theta3)+a4*cos(theta2+theta3+theta4))-d3;
py=cos(theta1)*(a1+a2*cos(theta2)+a3*cos(theta2+theta3)+a4*cos(theta2+theta3+theta4))+L3;
pz=a2*sin(theta2)+a3*sin(theta2+theta3)+a4*sin(theta2+theta3+theta4);
fprintf('计算得到的坐标为:x=%.2f,y=%.2f,z=%.2f\n', px,py,pz)

[res]= CalculateThetaByCoordinate_Palm(px,py,pz,a1,a2,a3,a4,L3,d3,0);
fprintf('实验结果为:theta1=%.2f,theta2=%.2f,theta3=%.2f,theta4=%.2f\n', res)


else
theta1=((t1+60)*pi)/180;

px=cos(theta1)*(a1+a2*cos(theta2)+a3*cos(theta2+theta3)+a4*cos(theta2+theta3+theta4))-d1;
py=sin(theta1)*(a1+a2*cos(theta2)+a3*cos(theta2+theta3)+a4*cos(theta2+theta3+theta4))+L1;
pz=a2*sin(theta2)+a3*sin(theta2+theta3)+a4*sin(theta2+theta3+theta4);
fprintf('0计算得到的坐标为:x=%.2f,y=%.2f,z=%.2f\n', px,py,pz)

[res]= CalculateThetaByCoordinate_Palm(px,py,pz,a1,a2,a3,a4,L1,d1,1);
fprintf('实验结果为:theta1=%.2f,theta2=%.2f,theta3=%.2f,theta4=%.2f\n', res)
end
