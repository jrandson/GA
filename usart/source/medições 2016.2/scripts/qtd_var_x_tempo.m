
%população:120; precisao: 12 bits
%função: f= x1 + x2 + x3 + .. + xn
qtd_var = [1, 2, 4, 6];
tempo = [28.09, 32.68, 42.26, 51.76];

hold;
plot(qtd_var,tempo,'r*',qtd_var,tempo,'b--');
%plot(size_pop,tempo,'b--');

xlabel('Número de variáveis ');
ylabel('Tempo (ms)');
title('Tempo de execução do GA para diferentes variáveis');
grid on;
%linhas na horizontal
%set(gca,'ygrid','on');

a = num2str(tempo(:));
b = cellstr(a);
c = strtrim(b);
h = text(qtd_var,tempo,c);