function GenerateArraypattern(level)
check_pattern = [255*ones(2,2),zeros(2,2);zeros(2,2),255*ones(2,2)];
check_sub_stripe = [check_pattern;check_pattern;check_pattern;check_pattern];
check_stripe = [];
for i = 4:4:256;
    check_stripe = [check_stripe,check_sub_stripe];
end
grey_stripe = level * ones(size(check_stripe));
Arraypattern = check_stripe;
for i = 2:1:16
    if mod(i,2) ==1
        Arraypattern = [Arraypattern;check_stripe];
    else
        Arraypattern = [Arraypattern;grey_stripe];
    end
end
figure(1)
image(Arraypattern + 1);
axis('image');
graymap = [0:255; 0:255; 0:255]'/255;
colormap(graymap);
end