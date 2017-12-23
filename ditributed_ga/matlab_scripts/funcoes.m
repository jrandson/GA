

x = -20:0.1:80;
e = 2,718
%y = 1./(1+e.^(-x))


%---
%y = -10*e.^(-(x.^2)/2*sigma^2).*cos(0.6*sin(x))

%---
y = -5.25*e.^(-(x.^2)/2*sigma^2)

%---
%y = -sin(0.05*x)

%x = 0:0.1:2*pi
%y = sin(x)
plot(x,y)

[l c] = size(y)
min = y(1)
for i = 1:c
    if y(i) < min
        min = y(i)
    end
end

    