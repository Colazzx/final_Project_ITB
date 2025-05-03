function [f] = ob2c2ob14(x,de,dda,cp,tspan,d2n)

% x,p1 = [200 50  200 50  5   0   0   0   0   0   100]';
% x,p1 = [N1  Fp1 N2  Fp2 Fl  y1  y2  y3  y4  y5  Profit]
% p2   = [Nl]

ab1    = round(x(7)+x(8)+1);
ab2    = round(x(9)+x(10)+1);

f      = -0.4*x(5)*(d2n-round(1-x(6))*x(1)-round(x(6))*x(3))+2*(x(2)+x(4))+(ab1+ab2);
