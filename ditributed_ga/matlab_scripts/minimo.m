function y = minimo()
  t = 5:0.1:20;
  
  minimo = feval(5);
  x = 5;
  for t = 5:0.1:20
      if(feval(t) < minimo)
          minimo = feval(t);
          x = t;
      end
  end
  disp(x);
  y = minimo;
end

function y =  feval(t)
    y = (0.01*t.^2).*sin(t);
end
