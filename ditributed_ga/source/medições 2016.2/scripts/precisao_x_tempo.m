
%para 10, exibe onda irregular
%f(x) = x
%população 120 1 variável
precisao = [4,6,8,10,12,14];
tempo = [27.79, 27.88 ,27.88, 28.12, 28.13,  27.96];


 


hold;
plot(precisao,tempo,'r*',precisao,tempo,'b--');
%plot(size_pop,tempo,'b--');

xlabel('Precisão');
ylabel('Tempo (ms)');
title('Tempo de execução do GA para diferentes Precisões (tamanho do cromossomo) ');
axis([2 16 25 29])
grid on;
%linhas na horizontal
%set(gca,'ygrid','on');

a = num2str(tempo(:));
b = cellstr(a);
c = strtrim(b);
h = text(precisao,tempo,c);