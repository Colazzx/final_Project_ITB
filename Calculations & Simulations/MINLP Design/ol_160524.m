Fl = 0; Nl = 200; Fp1 = 70; Fp01 = 69; Fp02 = 50;
V1 = 800; xr = 100;
% Define the differential equation function
f1 = @(t, N1) -(Fl*Nl+Fp1*(N1-100)-Fp01*(N1-100))/V1;
% Time span
tspan = 0:15:3600;

% Solve the differential equation
[~, x1] = ode45(f1, tspan, Nl);

plot(tspan,x1)