function Xout = stretch(X, T1, T2)

sizeX = size(X);
for i = 1 : sizeX(1)
    for j = 1 : sizeX(2)
        if (X(i,j) <= T1)
            Xout(i,j) = 0;
        else if (X(i,j) >= T2)
            Xout(i,j) = 255;
            else
                Xout(i,j) = round((255 / ( T2 - T1 )) * ( X(i,j) - T1 )); 
            end
        end
    end
end

end