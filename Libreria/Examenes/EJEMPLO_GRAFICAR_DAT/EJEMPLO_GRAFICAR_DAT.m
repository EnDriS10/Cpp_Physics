% EJEMPLO_GRAFICAR_DAT  Lee dos ficheros .dat (x e y) de la carpeta de este
% script y los representa en una grafica limpia.
%
% Requiere MATLAB R2016b o superior (funciones locales dentro de un script).

clear; clc; close all

carpeta = fileparts(mfilename('fullpath'));   % carpeta donde esta este script
if isempty(carpeta), carpeta = pwd; end       % por si se ejecuta pegando el codigo

% --- Ejemplo: oscilador amortiguado (x.dat = tiempo, y.dat = amplitud) ---
[x, y] = leer_xy(carpeta, 'x.dat', 'y.dat');
graficar_xy(x, y, 'Oscilador amortiguado', 'Tiempo (s)', 'Amplitud (u.a.)');

% exportgraphics(gcf, 'grafica.png', 'Resolution', 300);   % guardar la figura

% Para otros datos basta con cambiar los nombres y las etiquetas:
%   [t, v] = leer_xy(carpeta, 'tiempo.dat', 'voltaje.dat');
%   graficar_xy(t, v, 'Carga del condensador', 't (s)', 'V (V)');


%% ========================================================================
%  FUNCIONES
%  ========================================================================

function [x, y] = leer_xy(carpeta, archivo_x, archivo_y)
% Lee dos ficheros .dat (una columna cada uno) de la carpeta indicada.
    x = leer_columna(fullfile(carpeta, archivo_x));
    y = leer_columna(fullfile(carpeta, archivo_y));
    assert(numel(x) == numel(y), ...
        'x (%d datos) e y (%d datos) deben tener la misma longitud.', numel(x), numel(y));
end

function v = leer_columna(ruta)
% Lee un fichero numerico de texto con una sola columna.
    assert(exist(ruta, 'file') == 2, 'No se encuentra el fichero: %s', ruta);
    v = load(ruta);
    assert(isvector(v), 'El fichero %s debe tener una sola columna.', ruta);
    v = v(:);
end

function graficar_xy(x, y, titulo, etiqueta_x, etiqueta_y)
% Grafica y(x) con un estilo minimalista.
    figure('Color', 'w');
    plot(x, y, 'LineWidth', 1.8, 'Color', [0.00 0.45 0.74]);

    ax = gca;
    ax.FontSize  = 12;
    ax.GridAlpha = 0.15;
    ax.TickDir   = 'out';
    grid on; box off;

    title(titulo, 'FontWeight', 'normal', 'FontSize', 14);
    xlabel(etiqueta_x);
    ylabel(etiqueta_y);
end
