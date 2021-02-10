close all
clc

format long

fA = fopen( 'point.txt' , 'r' );
fB = fopen( 'element.txt', 'r');
fC = fopen( 'eltnum.txt', 'r');
point = (fscanf(fA, '%f', [3 Inf] ))';
ptnum = (fscanf(fB, '%f', [3 Inf] ))';
eltnum = (fscanf(fC, '%f', [3 Inf] ))';

max = size(ptnum);
max = max(1);

figure(1)
hold on
for e=1:max
    x = [point( ptnum(e,3)+1,1 ); point( ptnum(e,1)+1,1 ); point( ptnum(e,2)+1,1 ); point( ptnum(e,3)+1,1 ) ];
    y = [point( ptnum(e,3)+1,2 ); point( ptnum(e,1)+1,2 ); point( ptnum(e,2)+1,2 ); point( ptnum(e,3)+1,2 ) ];
    plot(x,y, 'k' )
end

% Element number
% for e=1:max
%     k=num2str( e );
%     x1=point(ptnum(e,1)+1,:);
%     x2=point(ptnum(e,2)+1,:);
%     x3=point(ptnum(e,3)+1,:);
%     m=(x1+x2+x3)/3;
%     text( m(1), m(2) , k);
% end

% Across number
% for e=1:max
%     for i=1:3
%         k=num2str( eltnum(e,i)+1 );
%         text( point( ptnum(e,i)+1,1 ), point( ptnum(e,i)+1,2 ), k );
%     end
% end

max = size(point);
max = max(1);
% Point number
% for i=1:max
%     k=num2str( i );
%     text( point(i,1) , point(i,2) , k );
% end

% Boundary number
% for i=1:max
%     k=num2str( point(i,3) );
%     text( point(i,1) , point(i,2) , k );
% end



clear fA fB fC
clear e k x y m
clear x1 x2 x3
