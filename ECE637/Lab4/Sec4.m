clear all
clc
level = 184;
GenerateArraypattern(level);
gamma = log(0.5)/log(level/255)

%% gamma correction
% X = imread('linear.tif');
% X = double(X);
% X_corrected = 255.* exp( log(X./255)/ gamma);
% image(X_corrected + 1);
% axis('image');
% graymap = [0:255; 0:255; 0:255]'/255;
% colormap(graymap);

%%
X_gamma = imread('gamma15.tif');
X_gamma = double(X_gamma);
X_linear = 255 * (X_gamma./255).^1.5;
X_mycorrected = 255.* exp( log(X_linear./255)/ gamma);
figure(1)
image(X_linear + 1);
axis('image');
graymap = [0:255; 0:255; 0:255]'/255;
colormap(graymap);
figure(2)
image(X_mycorrected + 1);
axis('image');
graymap = [0:255; 0:255; 0:255]'/255;
colormap(graymap);


