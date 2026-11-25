% EJEMPLO_GRAFICAR_DAT  Lee ficheros .dat (x e y) de la carpeta de este script

clear; clc; close all

carpeta = fileparts(mfilename('fullpath'));   % carpeta donde esta este script
if isempty(carpeta), carpeta = pwd; end       % por si se ejecuta pegando el codigo


 %--- 2. Ejemplo: un solo fichero .dat con dos columnas [x, y] ---
 [t, EE] = leer_xy_2col(carpeta, 'E(t).dat');
 graficar_xy(t, EE, 'Anomalía Excéntrica vs Tiempo', 't (a)', 'E (rad)');


%% ========================================================================
%  FUNCIONES
%  ========================================================================

function [x, y] = leer_xy_2col(carpeta, archivo)
% Lee un unico fichero .dat con dos columnas: columna 1 -> x, columna 2 -> y.
    ruta = fullfile(carpeta, archivo);
    assert(exist(ruta, 'file') == 2, 'No se encuentra el fichero: %s', ruta);
    datos = load(ruta);
    assert(ismatrix(datos) && size(datos, 2) == 2, ...
        'El fichero %s debe tener exactamente dos columnas.', ruta);
    x = datos(:, 1);
    y = datos(:, 2);
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
