
%
%f(x) = x
%população 120, 1 variável, 12 bits
% f(x1,x2) = 21.5 + x1*sin(4*pi*x) + x2*sin(20*pi*x2)
size_pop = [30, 60, 90, 120, 150];
tempo = [19.23, 37.64, 57.01, 73.31, 94.75 ];



hold;
plot(size_pop,tempo,'r*',size_pop,tempo,'b--');
%plot(size_pop,tempo,'b--');

xlabel('Tamanho da poulação');
ylabel('Tempo (ms)');
title('Tempo de execução do GA para diferentes Tamanhos de população ');
axis([25 155 6 100])
grid on;
%linhas na horizontal
%set(gca,'ygrid','on');

a = num2str(tempo(:));
b = cellstr(a);
c = strtrim(b);
h = text(size_pop,tempo,c);