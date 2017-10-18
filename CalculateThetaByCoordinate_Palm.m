function res=CalculateThetaByCoordinate_Palm(x,y,z,a1,a2,a3,a4,L,d,isThumb)
%x,y,z
%a1,a2,a3,a4分别为各个指节的长度
%isThumb=0表示当前要计算的不是大拇指,否则表示大拇指
%返回结果为各个指关节的转动角度,theta1,theta2,theta3,theta4
% a1=20.871;
% a2=50.059;
% a3=44.621;
% a4=25.014;
% d1=-46.186;
% L1=24.331;
%先将指尖在手掌的坐标转化成指尖在系关节坐标系中的坐标
if isThumb==0
    %非大拇指
    px=y-L;
    py=-x-d;
    pz=z;
else
    %大拇指
    px=x+d;
    py=y-L;
    pz=z;
end

[res]=CalculateThetaByCoordinate(px,py,pz,a1,a2,a3,a4);
end