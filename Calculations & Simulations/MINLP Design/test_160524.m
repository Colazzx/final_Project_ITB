itk   = 1;
tspan = [0:1:3600];
%xol  = [200 50  200 50  5   0   0   0   0   0   100]';
%p1   = [N1  Fp1 N2  Fp2 Fl  y1  y2  y3  y4  y5  Profit]
%y    = [N1  Fp1 N2  Fp2 Profit]
%        1   2   3   4   5   6   7   8   9   10  11
xd    = 200;

[tt,xx]=oib2c2fg4_cl(xol(:,itk),xd,tspan);
plot(tt,xx(:,1),'r')