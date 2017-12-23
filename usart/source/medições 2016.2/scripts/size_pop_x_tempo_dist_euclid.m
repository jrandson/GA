
%
%f(x) = x
%população 120, 1 variável, 12 bits

%f(x) = d + b*1/d + b*A*C
%d = sqrt((x1 - px)^2 + (x2 - py)^2))

size_pop = [30, 60, 90, 120, 150];
tempo = [13.66, 26.91 , 40.21, 53.41, 66.79];

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