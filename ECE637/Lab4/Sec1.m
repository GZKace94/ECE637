clear all
clc
figure(1)
x = imread('kids.tif');
hist(x(:),[0:255])
title('histograms of kids image');
figure(2)
x = imread('race.tif');
hist(x(:),[0:255]);
title('histograms of race image');