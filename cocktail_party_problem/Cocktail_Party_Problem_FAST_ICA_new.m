[x1, Fs1] = audioread('rsm2_mA.wav');
[x2, Fs2] = audioread('rsm2_mB.wav');
X = [x1, x2]';
%m = size(x1,1);
%n = 2;
[d, m] = size(X);
% Subtract off the mean of each dimension.
X = X - repmat(mean(X,2),1,m);
% Calculate the whitening filter.
[E, D] = eig(cov(X'));
% Whiten the data
X_w = sqrtm(pinv(D))*E'*X;

xx=X_w;
w1 = randn(d, 1);
w1 = w1/norm(w1,2);
w0 = randn(d, 1);
w0 = w0/norm(w0, 2);

while abs(abs(w0'*w1)-1) > 0.001
    w0 = w1;
    w1 = xx*G(w1'*xx)'/m - mean(DG(w1'*xx), 2)*w1;
    w1 = w1/norm(w1, 2);
end

w2 = randn(d, 1);
w2 = w2/norm(w2,2);
w0 = randn(d, 1);
w0 = w0/norm(w0, 2);

while abs(abs(w0'*w2)-1) > 0.001
    w0 = w2;
    w2 = xx*G(w2'*xx)'/m - mean(DG(w2'*xx), 2)*w2;
    w2 = w2 - w2'*w1*w1;
    w2 = w2/norm(w2, 2);
end

x=[x1' ;x2'];
w = [w1 w2];
s = w*x;
s1 = s(1,:);
s2 = s(2,:);

% Writes out the extracted sound signals into two different wav files.
audiowrite(  'out1.wav',s1',Fs1 );
audiowrite(  'out2.wav',s2',Fs2 );