
%popula��o:120; precisao: 12 bits
%fun��o: f= x1 + x2 + x3 + .. + xn
qtd_var = [1, 2, 4, 6];
tempo = [28.09, 32.68, 42.26, 51.76];

hold;
plot(qtd_var,tempo,'r*',qtd_var,tempo,'b--');
%plot(size_pop,tempo,'b--');

xlabel('N�mero de vari�veis ');
ylabel('Tempo (ms)');
title('Tempo de execu��o do GA para diferentes vari�veis');
grid on;
%linhas na horizontal
%set(gca,'ygrid','on');

a = num2str(tempo(:));
b = cellstr(a);
c = strtrim(b);
h = text(qtd_var,tempo,c);