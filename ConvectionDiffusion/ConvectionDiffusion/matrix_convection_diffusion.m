close all
clc

format long

fA = fopen( 'matrix.txt' , 'r' );
fB = fopen( 'load.txt' , 'r' );
matA = (fscanf(fA, '%f', [3 Inf] ))';
load = (fscanf(fB, '%f', [1 Inf] ))';

max = size(load);
max = max(1);
A = zeros(max, max);


maxA = size(matA);
maxA = maxA(1);

for i=1:maxA
    A( matA(i,1)+1, matA(i,2)+1 ) = matA(i,3);
end

% x = cgs(A,load, 10^-10, 1000);

clear fA fB
clear i