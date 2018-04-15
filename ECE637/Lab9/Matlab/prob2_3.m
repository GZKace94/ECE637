clear all
clc
load coeff_ga_1.mat
coeff_ga_1 = dct_blk;
[row, column]=size(coeff_ga_1);
n=1;
for i = 1:row
    for j = 1: column
        if(mod(i,8)== 1 && mod(j,8)== 1)
        DCcoeff(n) = coeff_ga_1(i,j);
        n = n + 1;
        end
    end
end

DC_2D = reshape(DCcoeff,[column/8,row/8])';
img_DC = DC_2D + 128;
figure(1)
image(uint8(img_DC))
truesize;
colormap(gray(256));
imwrite(uint8(img_DC), sprintf('imgDC.jpg'));

%% zig order
load Zig.mat
ACarraywithDC = ones(1,64);
C = mat2cell(coeff_ga_1,8*ones(96,1),8*ones(1,64));    
m = 1;
for i = 1: 96
    for j = 1:64
        block = C{i,j};
        ACarraywithDC(m,:) = block(Zig);
        m = m+1;
    end
end
ACarray = ACarraywithDC(:,2:end);
ACmean = mean(abs(ACarray));
figure(2)
plot(ACmean)
ylabel('Zigzag mean')
xlabel('AC coefficient in Zigzag order')