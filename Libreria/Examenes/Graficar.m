clear; clc;

%1D

% % Añadir etiquetas de ejes y título
%  plot(a,b,'g*') ;
%  xlabel('tiempo (s)') ;
%  ylabel('desplazamiento (cm)') ;
%  title('movimiento oscilatorio') ;


 % Representación gráfica de varios vectores (b frente a y d frente a c):
 % >> plot(a,b,'r--',c,d,'bo:') ;
 % Leyenda
 % >> legend('oscilador 1','oscilador 2') ;


 % Comandos:
 % grid on (off) pinta (o no) una cuadrícula sobre la gráfica
 % figure(n) Crea una figura número n (si no existe) o activa la figura n.
 % close(n) Cierra la figura n
 % close all Cierra todas las figuras
 % axis equal los ejes de abscisas y ordenadas tienen el mismo intervalo
 % axis square los ejes de abscisas y ordenadas tienen la misma longitud en pantalla


 % Graficar con subplots
 % subplot(a,b,c) ;
% a==numero total de filas
% b==numero total de columnas
% a==numero de grafica

 % x1=linspace(0,4*pi,100) ; y1=sin(x1).^2 ;
 % subplot(2,3,1) ;
 % plot(x1,y1,'r') ;
 % y2=sin(x1).^4 ;
 % subplot(2,3,5) ;
 % plot(x1,y2,'b') ;
 % axis equal ;    
 % % sólo el subplot 5
 % grid on ; % mostrar retícula


 %Nota axis equal solo tiene sentido en algunas graficas


%  figure(1)
% subplot(1,2,1) ;
% plot(x, EE(1,:,1)) ;
% xlabel('Desplazamiento en X (m)') ;
% ylabel('Campo Electrico (N/C)') ;
% title('Campo Electrico a lo largo de una linea') ;
% %axis equal;
% grid on;

%leg=legend('r<r_1','r<r_2','r<r_3','r\leqda','foco','Location','southwest') ; 
%leg=legend('r<r_1','r<r_2','r<r_3','r\leqda','foco','Location','northwest') ; 
%leg=legend('r<r_1','r<r_2','r<r_3','r\leqda','foco','Location','eastoutside') ;

%plot 3d
% subplot(2,1,1) ; plot3(rr(1,:),rr(2,:),rr(3,:)) ;
% title('trayectoria') ;
% xlabel('x(m)') ; ylabel('y(m)') ; zlabel('z(m)') ; grid on ; %axis equal ;


%%

%hist(x,N)
%x es un vector y N es el numero de bins

%scatter(x,y,100,'r','filled')

%%
%fimplicit(@(x,y) x.^2 + y.^2 -25)
%axis equal
%Genera un circulo de radio 5




%% SCRIPT RESUMEN PROPIEDADES FIMPLICIT

clc; clear; close all;

%% Crear grafica implicita

h = fimplicit(@(x,y) x.^2 + y.^2 - 25);


% ===== PROPIEDADES VISUALES BASICAS =====

h.Color = 'r';              % Color: 'r','g','b','k','m','c','y'
% h.Color = [0 0.5 1];     % Color RGB personalizado

h.LineWidth = 2;           % Grosor de linea (default = 0.5)

h.LineStyle = '--';        % Tipo de linea:
                           % '-'   solida
                           % '--'  discontinua
                           % ':'   punteada
                           % '-.'  guion-punto


% ===== CONTROL DE RANGO =====

h.XRange = [-10 10];       % Limites eje X
h.YRange = [-10 10];       % Limites eje Y


% ===== RESOLUCION =====

h.MeshDensity = 200;      % Calidad de la curva
                          % default = 71
                          % mayor = mas suave


% ===== VISIBILIDAD =====

h.Visible = 'on';        % 'on' o 'off'


% ===== DATOS INTERNOS =====

x = h.XData;             % Coordenadas X
y = h.YData;             % Coordenadas Y

% ejemplo: graficar puntos
hold on
scatter(x,y,20,'filled')


% ===== PROPIEDADES DEL GRAFICO GENERAL =====

axis equal

grid on

title('Circulo')

xlabel('x')

ylabel('y')


% ===== TRANSPARENCIA (solo algunas versiones) =====

% h.Color(4) = 0.5;  % transparencia si soportado


% ===== EJEMPLO PROFESIONAL FINAL =====

figure

h = fimplicit(@(x,y) x.^2 + y.^2 -25);

h.Color = [0 0.6 1];

h.LineWidth = 3;

h.LineStyle = '-.';

h.MeshDensity = 300;

axis equal

grid on

title('Grafica Implicita Profesional')
 %%

 %2D

 % [XM,YM]=meshgrid(x,y) ; % genera todos los pares de coordenadas x,y
 % Z=XM.^2+YM.^2 ; % operación 'vectorizada'
 % surf(XM,YM,Z) ;      %genera el gráfico


%zlabel, title, zlim


%colorbar 
%Muestra una barra de colores al lado de una gráfica que usa colores para representar valores numéricos 
% (por ejemplo, un mapa de calor o una superficie 3D).

% shading flat → Colorea cada celda con un solo color, sin bordes (más uniforme).
% shading faceted → (por defecto) Cada celda tiene bordes negros. 
% shading interp → Interpola suavemente los colores entre los vértices (efecto más realista).

% Ejemplo: 
% surf(peaks)
% shading interp
% colorbar