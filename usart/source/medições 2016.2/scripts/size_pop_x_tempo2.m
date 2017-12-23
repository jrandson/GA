
%
%f(x) = x
%popula��o 120, 1 vari�vel, 12 bits
size_pop = [30, 60, 90, 120, 150];
tempo = [8.55, 16.75, 25.11, 33.34, 41.48];

   

hold;
plot(size_pop,tempo,'r*',size_pop,tempo,'b--');
%plot(size_pop,tempo,'b--');

xlabel('Tamanho da poula��o');
ylabel('Tempo (ms)');
title('Tempo de execu��o do GA para diferentes Tamanhos de popula��o f(x) = x�');
axis([25 155 6 50])
grid on;
%linhas na horizontal
%set(gca,'ygrid','on');

a = num2str(tempo(:));
b = cellstr(a);
c = strtrim(b);
h = text(size_pop,tempo,c);