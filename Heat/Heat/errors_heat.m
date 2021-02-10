close all
clc

format long

A = fopen( 'L2error_u.txt', 'r' );
B = fopen( 'H1error_u.txt', 'r' );
L2error = (fscanf(A, '%f', [10 Inf] ))';
H1error = (fscanf(B, '%f', [10 Inf] ))';

% max = size(error);
% error = [error(:,1), zeros(max(1),1), error(:,2), zeros(max(1),1)];
% 
% for i=2:max(1)
%     if error(i,1)==0
%         break;
%     end
%     error(i,2) = log( error(i-1,1) / error(i,1) ) / log(2);
%     error(i,4) = log( error(i-1,3) / error(i,3) ) / log(2);
% end
% 
% T = table(error(:,1:2),error(:,3:4),'VariableNames',{'L2norm' 'H1norm'});

% T1 = array2table(error(:,1:2),'VariableNames',{'error' 'rate'});
% T2 = array2table(error(:,3:4),'VariableNames',{'error' 'rate'});
% T = table(T1,T2,'VariableNames',{'L2norm' 'H1norm'});
% T(1:(i-1),:)

clear A B max i