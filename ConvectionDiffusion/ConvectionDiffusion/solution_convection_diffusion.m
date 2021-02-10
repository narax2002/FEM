close all
clc

format long

fA = fopen( 'point.txt' , 'r' );
fB = fopen( 'element.txt', 'r');
fC = fopen( 'solution.txt', 'r');
fD = fopen( 'exact_u.txt', 'r');
point = (fscanf(fA, '%f', [3 Inf] ))';
ptnum = (fscanf(fB, '%f', [3 Inf] ))';
sol_u = (fscanf(fC, '%f', [3 Inf] ))';
exact_u = (fscanf(fD, '%f', [2 Inf] ))';

max = size(ptnum);
max = max(1);

% figure(1)
% hold on
% for e=1:max
%     x = [ point( ptnum(e,1)+1, 1 ); point( ptnum(e,2)+1, 1 ); point( ptnum(e,3)+1, 1 ) ];
%     y = [ point( ptnum(e,1)+1, 2 ); point( ptnum(e,2)+1, 2 ); point( ptnum(e,3)+1, 2 ) ];
%     u = [ exact_u( ptnum(e,1)+1, 2 ); exact_u( ptnum(e,2)+1, 2 ); exact_u( ptnum(e,3)+1, 2 )];
%     tri=delaunay(x,y);
%     tr=triangulation(tri,x(:),y(:),u(:));
%     trisurf(tr)
%     title('z = u(x,y)','Fontsize',20)
%     xlabel('x')
%     ylabel('y')
%     view(3) % three-dimensional view
% end
% 
% figure(2)
% hold on
% for e=1:max
%     x = [ point( ptnum(e,1)+1, 1 ); point( ptnum(e,2)+1, 1 ); point( ptnum(e,3)+1, 1 ) ];
%     y = [ point( ptnum(e,1)+1, 2 ); point( ptnum(e,2)+1, 2 ); point( ptnum(e,3)+1, 2 ) ];
%     u = [ sol_u( ptnum(e,1)+1, 3 ); sol_u( ptnum(e,2)+1, 3 ); sol_u( ptnum(e,3)+1, 3 )];
%     tri=delaunay(x,y);
%     tr=triangulation(tri,x(:),y(:),u(:));
%     trisurf(tr)
%     title('z = u_h(x,y)','Fontsize',20)
%     xlabel('x')
%     ylabel('y')
%     view(3) % three-dimensional view
% end
% 
% figure(3)
% hold on
% for e=1:max
%     x = [ point( ptnum(e,1)+1, 1 ); point( ptnum(e,2)+1, 1 ); point( ptnum(e,3)+1, 1 ) ];
%     y = [ point( ptnum(e,1)+1, 2 ); point( ptnum(e,2)+1, 2 ); point( ptnum(e,3)+1, 2 ) ];
%     u = [ sol_u( ptnum(e,1)+1, 3 ) - exact_u( ptnum(e,1)+1, 1 ) ;...
%         sol_u( ptnum(e,2)+1, 3 ) - exact_u( ptnum(e,2)+1, 1 ) ;...
%         sol_u( ptnum(e,3)+1, 3 ) - exact_u( ptnum(e,3)+1, 1 ) ];
%     tri=delaunay(x,y);
%     tr=triangulation(tri,x(:),y(:),u(:));
%     trisurf(tr)
%     title('z = u_h-u','Fontsize',20)
%     xlabel('x')
%     ylabel('y')
%     view(3) % three-dimensional view
% end


clear fA fB fC fD
clear e k x y u
clear x1 x2 x3
clear i tr tri