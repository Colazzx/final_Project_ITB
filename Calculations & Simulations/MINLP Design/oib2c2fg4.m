 function [tt,xx] = oib2c2fg4(x,xd,tspan)
 M = zeros(5);
 idm = [1 3];nl = length(idm);
 M(idm,idm) = eye(nl,nl);
 x0 = [xd; x(2:4); x(11)];
 p1 = [x(6:10)];
 options = odeset('Mass',M);
 if ~any(or(isnan(x),isinf(x)))
     [tt,xx]=ode15s(@ab2c2dae,tspan,x0,options,x,xd); 
 else
     xx = x0;
     tt = 0;
 end
 %-------------------------------------------------------------
 function out = ab2c2dae(t,y,p1,p2)

 % p1 = [200 50  200 50  5   0   0   0   0   0   100]';
 % p1 = [N1  Fp1 N2  Fp2 Fl  y1  y2  y3  y4  y5  Profit]
 % y  = [N1  Fp1 N2  Fp2 Profit]
 %       1   2   3   4   5   6   7   8   9   10  11
 % p2 = [Nl]
 
 % Karakteristik sistem open loop
 K   = [2.28  2.67  3.31];
 Tau = [1369.3  1331.4  2155.9];

 out = zeros(5,1);
  
 %Tank1
 ab1    = round(p1(7)+p1(8)+1);

 out(1) = (K(ab1)*y(2)-y(1))/Tau(ab1);
 out(2) = y(2)-p1(2);

 %Tank2
 ab2    = round(p1(9)+p1(10)+1);

 out(3) = (K(ab2)*y(4)-y(3))/Tau(ab2);
 out(4) = y(4)-p1(4);
 
 %Profit variation
 out(5) = y(5)+0.4*p1(5)*(p2-(1-p1(6))*y(1)-p1(6)*y(3))-2*(y(2)+y(4))-(ab1+ab2);