close all
clc

format long

fA = fopen( 'point.txt' , 'r' );
fAc = fopen( 'cpoint.txt' , 'r' );
fAp = fopen( 'ppoint.txt' , 'r' );
fB = fopen( 'element.txt', 'r');
fC = fopen( 'eltnum.txt', 'r');
point = (fscanf(fA, '%f', [3 Inf] ))';
cpoint = (fscanf(fAc, '%f', [3 Inf] ))';
ppoint = (fscanf(fAp, '%f', [3 Inf] ))';
ptnum = (fscanf(fB, '%f', [3 Inf] ))';
eltnum = (fscanf(fC, '%f', [3 Inf] ))';

maxelt = size(ptnum);
maxelt = maxelt(1);

maxpt = size(point);
maxpt = maxpt(1);

figure(1)
hold on
for e=1:maxelt
    x = [point( ptnum(e,3)+1,1 ); point( ptnum(e,1)+1,1 ); point( ptnum(e,2)+1,1 ); point( ptnum(e,3)+1,1 ) ];
    y = [point( ptnum(e,3)+1,2 ); point( ptnum(e,1)+1,2 ); point( ptnum(e,2)+1,2 ); point( ptnum(e,3)+1,2 ) ];
    plot(x,y, 'k' )
end

% Element number
% for e=1:maxelt
%     k=num2str( e );
%     x1=point(ptnum(e,1)+1,:);
%     x2=point(ptnum(e,2)+1,:);
%     x3=point(ptnum(e,3)+1,:);
%     m=(x1+x2+x3)/3;
%     text( m(1), m(2) , k);
% end

%%% Adjoint number
% for e=1:maxelt
%     for i=1:3
%         k=num2str( eltnum(e,i)+1 );
%         text( point( ptnum(e,i)+1,1 ), point( ptnum(e,i)+1,2 ), k );
%     end
% end

% Point number
% for i=1:maxpt
%     k=num2str( i );
%     text( point(i,1) , point(i,2) , k );
% end

% Boundary number
% for i=1:maxpt
%     k=num2str( point(i,3) );
%     text( point(i,1) , point(i,2) , k );
% end


figure(2)
hold on
for e=1:maxelt
    x = [cpoint( ptnum(e,3)+1,1 ); cpoint( ptnum(e,1)+1,1 ); cpoint( ptnum(e,2)+1,1 ); cpoint( ptnum(e,3)+1,1 ) ];
    y = [cpoint( ptnum(e,3)+1,2 ); cpoint( ptnum(e,1)+1,2 ); cpoint( ptnum(e,2)+1,2 ); cpoint( ptnum(e,3)+1,2 ) ];
    plot(x,y, 'k' )
end


% Point number
% for i=1:maxpt
%     k=num2str( i );
%     text( cpoint(i,1) , cpoint(i,2) , k );
% end

% Boundary number
% for i=1:maxpt
%     k=num2str( cpoint(i,3) );
%     text( cpoint(i,1) , cpoint(i,2) , k );
% end

% Element number
% for i=1:maxpt
%     k=num2str( cpoint(i,4) );
%     text( cpoint(i,1) , cpoint(i,2) , k );
% end

figure(3)
hold on
for e=1:maxelt
    x = [ppoint( ptnum(e,3)+1,1 ); ppoint( ptnum(e,1)+1,1 ); ppoint( ptnum(e,2)+1,1 ); ppoint( ptnum(e,3)+1,1 ) ];
    y = [ppoint( ptnum(e,3)+1,2 ); ppoint( ptnum(e,1)+1,2 ); ppoint( ptnum(e,2)+1,2 ); ppoint( ptnum(e,3)+1,2 ) ];
    plot(x,y, 'k' )
end

% Point number
% for i=1:maxpt
%     k=num2str( i );
%     text( ppoint(i,1) , ppoint(i,2) , k );
% end

% Boundary number
% for i=1:maxpt
%     k=num2str( ppoint(i,3) );
%     text( ppoint(i,1) , ppoint(i,2) , k );
% end

% Element number
% for i=1:maxpt
%     k=num2str( ppoint(i,4) );
%     text( ppoint(i,1) , ppoint(i,2) , k );
% end

clear fA fB fC fAc fAp
clear e k x y m
clear x1 x2 x3
