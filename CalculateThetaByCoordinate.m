function res=CalculateThetaByCoordinate(px,py,pz,a1,a2,a3,a4)
%通过空间坐标求解角度，即运动学逆问题
%px,py,pz为空间坐标;a1,a2,a3,a4分别为基关节、近基关节、中间关节及末梢关节的长度
res=[0,0,0,0];

if px==0 
   theta1=0;
else
   theta1=atan(py/px);   %theta1
end

res(1)=theta1;
%求theta3
d=((px/cos(theta1)-a1)^2+pz^2-a2^2-a3^2-a4^2)/(2*a2*a3*a4);
result=fzero( ['cos(x)/' num2str(a4) '+cos(5*x/3)/' num2str(a3) '+cos(2*x/3)/' num2str(a2)  '-' num2str(d)] ,pi/2);
theta3=result;
theta4=2*theta3/3;%thet4=2*theta3/3
res(3)=theta3;
res(4)=theta4;

A=px/cos(theta1)-a1;
B=pz;
D=a2+a3*cos(theta3)+a4*cos(theta3+theta4);
r1=atan((-A*B-D*sqrt(A^2+B^2-D^2))/(B^2-D^2));
r2=atan((-A*B+D*sqrt(A^2+B^2-D^2))/(B^2-D^2));
if r2<0|| r2>90    %要求求解结果在[0,90]区间内
   res(2) =r1;
else
    res(2)=r2;
end
for i=1:1:4
   res(i)=round((res(i)*180/pi)*100)/100;%转化成角度，并且保留两位小数
end
end