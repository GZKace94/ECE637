clear all
clc
X = imread('kids.tif');
[Y,Xout] = equalize(X); % y is cdf, Xout is equzklized image
figure(1)
plot(Y)
xlabel('i')
ylabel('Y')
title('CDF of original image')
figure(2)
image(Xout + 1);
axis('image');
graymap = [0:255; 0:255; 0:255]'/255;
colormap(graymap);

[Yout,X2] = equalize(Xout);
figure(3)
plot(Yout);
xlabel('i')
ylabel('Y')
title('CDF of equalized image')
figure(4)
hist(Xout(:),[0:255])
title('histograms of equalized kids image');
