
%
%f(x) = x
%população 120, 1 variável, 12 bits
size_pop = [30, 60, 90, 120, 150];
tempo = [7.65, 14.83, 22.24, 29.48, 36.85];



hold;
plot(size_pop,tempo,'r*',size_pop,tempo,'b--');
%plot(size_pop,tempo,'b--');

xlabel('Tamanho da poulação');
ylabel('Tempo (ms)');
title('Tempo de execução do GA para diferentes Tamanhos de população f(x) = x+5');
axis([25 155 6 40])
grid on;
%linhas na horizontal
%set(gca,'ygrid','on');

a = num2str(tempo(:));
b = cellstr(a);
c = strtrim(b);
h = text(size_pop,tempo,c);