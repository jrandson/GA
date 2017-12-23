
x = [];
y = [];

for i= 1:0
    x = [x 50*rand]
    y = [y 50*rand]
end

x = [12.7548   34.9538   47.9646    6.9312   12.8754   12.7141   12.1762   17.4992   12.5542   23.6644]
y = [25.2979   44.5452   27.3608    7.4647   42.0359   40.7142   46.4632    9.8298   30.8022   17.5830]

px = [min(x) max(x)]
py = [min(y) max(y)]

pontosPerc = []
distperc = 0;
pontoIncial = [px(1) py(1)];
alvo = [px(2) py(2)];
pontoAtual = pontoIncial;

proximoPonto = []

distperc = distperc + dist(pontoAtual, proximoPonto)







hold;
plot(x,y,'o')
plot(px,py,'ro')

function y = dist_total(distperc, pontoAtual,proximoPonto,alvo)
    y = distperc + dist(pontoAtual,proximo)+dist(proximo,alvo) 
end

function y = dist(p1,p2)
    y = sqrt((p2(1)-p1(1))^2 + (p2(2)-p1(2))^2);
end

function y = contain(vetor,x)
    l,c = size(vetor)
    y = 0;
    for i = 1:c
        if x == vetor(i)
            y = 1;
            break;
    end
end