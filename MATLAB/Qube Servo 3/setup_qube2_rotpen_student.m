%% Load Model
clear
qube2_rotpen_param;
% Set open-loop state-space model of rotary single-inverted pendulum (SIP)
rotpen_ABCD_eqns_ip;
% Display matrices
A
B
Q= [1 0 0 0;0 1 0 0;0 0 1 0;0 0 0 1];
R=1;
N=0;
[K,S,P] = lqr(A,B,Q,R,N);