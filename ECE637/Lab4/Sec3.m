clear all
clc
X = imread('kids.tif');
Xout = stretch(X,75,180);
figure(1)
image(Xout + 1);
axis('image');
graymap = [0:255; 0:255; 0:255]'/255;
colormap(graymap);
figure(2)
hist(Xout(:),[0:255])
title('histograms of stretched kids image');