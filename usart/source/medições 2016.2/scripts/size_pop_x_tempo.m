
%
%f(x) = x
%popula��o 120, 1 vari�vel, 12 bits
size_pop = [30, 60, 90, 120, 150];
tempo = [7.58, 14.75, 22.12, 29.26 , 36.61];

hold;
plot(size_pop,tempo,'r*',size_pop,tempo,'b--');
%plot(size_pop,tempo,'b--');

xlabel('Tamanho da poula��o');
ylabel('Tempo (ms)');
title('Tempo de execu��o do GA para diferentes Tamanhos de popula��o f(x) = 2x');
axis([25 155 6 40])
grid on;
%linhas na horizontal
%set(gca,'ygrid','on');

a = num2str(tempo(:));
b = cellstr(a);
c = strtrim(b);
h = text(size_pop,tempo,c);