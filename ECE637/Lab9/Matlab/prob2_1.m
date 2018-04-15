clear all
clc
load Quant.mat
gamma = 1;
img = imread('img03y.tif');
X = double(img)-128;
fn = @(x) round(dct2(x.data,[8,8])./(Quant*gamma));
dct_blk = blockproc(X,[8,8],fn);
[rows, column] = size(dct_blk)
fid = fopen(sprintf('img03y_%d.dq', gamma),'w');
fwrite(fid,[rows],'integer*2');
fwrite(fid,[column],'integer*2');
fwrite(fid,dct_blk','integer*2');

%% restore
frd = fopen(sprintf('img03y_%d.dq', gamma));
Xread = fread(frd,'integer*2');
Xread = reshape(Xread(3:end),[Xread(2) Xread(1)])';

fn = @(x) round(idct2(x.data.* Quant * gamma,[8,8]));
idct_blk = blockproc(Xread,[8,8],fn);
res_img = idct_blk+128;

%% error 
img_error = (img - uint8(res_img))*10+128;
figure(1)
image(img)
truesize;
colormap(gray(256));
title('Original Image')
imwrite(uint8(img), sprintf('img03y_orig.jpg', gamma));

figure(2)
image(uint8(res_img))
truesize;
colormap(gray(256));
title('Restored Image')
imwrite(uint8(res_img), sprintf('img03y_res_%d.jpg', gamma));

figure(3)
image(uint8(img_error))
truesize;
colormap(gray(256));
title('Diff Image')
imwrite(uint8(img_error), sprintf('img03y_diff_%d.jpg', gamma));