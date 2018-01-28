clear all
clc
x=imread('segmentation_3.tif');
N=max(x(:));
image(x)
colormap(rand(N,3))
axis('image')