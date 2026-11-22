clear;clc;


%  Se guarda todo el workspace en un fichero con extensión .mat, en un formato 
% sólo legible por MATLAB.
%  >> save('nombre_fichero.mat')
%  Guardar sólo algunas variables
%  >> save('nombre_fichero.mat','var1','var2')
%  Añadir variables a un fichero existente
%  >> save('nombre_fichero.mat','var3','-append')
%  Importar datos de un fichero .mat al workspace (añadir o sustituir)
%  >> load('nombre_fichero.mat')
%  >> load('nombre_fichero.mat','var1','var2')
%  Importar/exportar datos en fichero de texto ASCII
%  >> var=importdata('nombre_fichero.txt')