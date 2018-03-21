function [Y,Xout]= equalize(X)
h = hist(X(:), [0:255]);
denumerator = sum(h);
Y(1) = h(1)/denumerator;
for i = 2 : 1 :256;
    Y(i) = (Y(i-1) * denumerator + h(i))/denumerator;
end
Z = round(255 * (Y - min(Y))./(max(Y) - min(Y)));
sizeX = size(X);
for i = 1 : sizeX(1)
    for j = 1 : sizeX(2)
        Xout(i,j) = Z(X(i,j)+1);
    end
end

end
