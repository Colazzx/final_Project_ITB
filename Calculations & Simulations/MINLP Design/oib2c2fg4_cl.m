function [tt,xx] = oib2c2fg4_cl(x,xd,tspan)
    M = zeros(5);
    idm = [1 3]; nl = length(idm);
    M(idm,idm) = eye(nl,nl);
    x0 = [xd; x(2:4); x(11)];
    p1 = [x(6:10)];
    options = odeset('Mass',M);
    if ~any(or(isnan(x),isinf(x)))
        [tt,xx] = ode15s(@ab2c2dae,tspan,x0,options,x,xd); 
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
        
        % System characteristics
        K   = [2.28  2.67  3.31];
        Tau = [1369.3  1331.4  2155.9];
        % gamma = [1e-06 1e-06 1e-07];
        theta = [0.7 0.5 0.4];
        out = zeros(5,1);
        
        % Tank1
        ab1 = round(p1(7) + p1(8) + 1);
        %ab1_mrac = round(p1(7) + p1(8));
        
        % Tank2
        ab2 = round(p1(9) + p1(10) + 1);
        %ab2_mrac = round(p1(9) + p1(10)); 
        
        % Reference model
        x_ref = 100 * exp(-0.0015 * t) + 100.667;
        
        % MRAC control law parameters
        gamma = 1;  % Adaptation gain
        % theta_hat1 = 0;  % Adaptive parameter for Tank 1
        % theta_hat2 = 0;  % Adaptive parameter for Tank 2
        % persistent theta1 theta2;
        % if isempty(theta1)
        %     theta1 = 0.1;
        %     theta_r1 = 0.1;
        % end
        % if isempty(theta2)
        %     theta2 = 0.1;
        %     theta_r2 = 0.1;
        % end
        
        % Control Input MRAC (Theta dianggap konstan)
        u1 = y(2) - theta(ab1) * (x_ref - y(1));
        u2 = y(4) - theta(ab2) * (x_ref - y(3));
        % u1 = y(2) - gamma * (x_ref - y(1));
        % u2 = y(4) - gamma * (x_ref - y(3));
        
        % Adaptive Laws
        % theta(ab1) = theta(ab1) + gamma * (x_ref - y(1)) * y(2);
        % theta(ab2) = theta(ab2) + gamma * (x_ref - y(3)) * y(4);
        
        % Dynamics
        % Tank 1
        out(1) = (K(ab1) * u1 - y(1)) / Tau(ab1);
        out(2) = u1 - p1(2);

        % Tank 2
        out(3) = (K(ab2) * u2 - y(3)) / Tau(ab2);
        out(4) = u2 - p1(4);
        
        % Profit variation
        out(5) = y(5) + 0.4 * p1(5) * (p2 - (1 - p1(6)) * y(1) - p1(6) * y(3)) - 2 * (u1 + u2) -0.000000004*(ab1 + ab2);
    end
end
