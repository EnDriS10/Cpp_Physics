% EJEMPLO_GRAFICAR_DAT  Lee ficheros .dat (x e y) de la carpeta de este script

clear; clc; close all

carpeta = fileparts(mfilename('fullpath'));   % carpeta donde esta este script
if isempty(carpeta), carpeta = pwd; end       % por si se ejecuta pegando el codigo


[tol, iter1_arr] = leer_xy_2col(carpeta, 'iter1_arr.dat');
[tol, iter2_arr] = leer_xy_2col(carpeta, 'iter2_arr.dat');


 graficar_subplots({tol, tol}, {iter1_arr, iter2_arr}, ...
     {'Num iter Jacobi vs Precision', 'Num iter Gauss vs Precision'}, ...
     'log(Precision)', 'Numero de Iter', ...
     2, 1, 'Metodos y sus Precisiones');

% exportgraphics(gcf, 'grafica.png', 'Resolution', 300);   % guardar la figura


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

function graficar_subplots(xs, ys, titulos, etiquetas_x, etiquetas_y, filas, cols, titulo_general)
% Grafica multiples curvas en subplots manteniendo el estilo minimalista.
    if ~iscell(ys), ys = num2cell(ys, 1); end
    n = numel(ys);
    if ~iscell(xs), xs = repmat({xs}, 1, n); end
    if ~iscell(titulos), titulos = repmat({titulos}, 1, n); end
    if ~iscell(etiquetas_x), etiquetas_x = repmat({etiquetas_x}, 1, n); end
    if ~iscell(etiquetas_y), etiquetas_y = repmat({etiquetas_y}, 1, n); end

    if nargin < 6 || isempty(filas) || isempty(cols)
        if n <= 3
            filas = n; cols = 1;
        else
            cols = ceil(sqrt(n));
            filas = ceil(n / cols);
        end
    end

    colores = [
        0.00 0.45 0.74;   % azul
        0.85 0.33 0.10;   % naranja
        0.47 0.67 0.19;   % verde
        0.49 0.18 0.56;   % morado
        0.93 0.69 0.13;   % amarillo
        0.30 0.75 0.93    % cian
    ];

    figure('Color', 'w');
    for k = 1:n
        subplot(filas, cols, k);
        color_k = colores(mod(k - 1, size(colores, 1)) + 1, :);
        plot(xs{k}, ys{k}, 'LineWidth', 1.8, 'Color', color_k);
        h.XRange = [-12 -3];       % Limites eje X
        h.YRange = [0 15]; 
        ax = gca;
        ax.FontSize  = 11;
        ax.GridAlpha = 0.15;
        ax.TickDir   = 'out';
        grid on; box off;

        title(titulos{k}, 'FontWeight', 'normal', 'FontSize', 13);
        xlabel(etiquetas_x{k});
        ylabel(etiquetas_y{k});
    end

    if nargin >= 8 && ~isempty(titulo_general)
        sgtitle(titulo_general, 'FontWeight', 'normal', 'FontSize', 15);
    end
end