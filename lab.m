n = 100;
#X[i] = 0 , 1£¬Y[i] = 0 . 1´ú±íÊÇºÚÇò£¬0´ú±íÊÇ°×Çò
X = [1 1 1];#¼×
Y = [0 0 0];#ÒÒ
y = ones(1,n);
y(1) = 3;
frequency = [0 0 0 0];
T = zeros(4,4);
N = zeros(1,4);
for i= 2 : n   
   k1 = randi(3); #Ñ¡Ò»¸öÇò½»»»
   k2 = randi(3); #Ñ¡Ò»¸öÇò½»»»
   X2=X;
   Y2=Y;
   frequency(sum(X2) + 1) = frequency(sum(X2) + 1) + 1;
   t = X(k1);
   X(k1) = Y(k2);
   Y(k2) = t;
   y(i) = sum(X); 
   T(sum(X2)+ 1,sum(X) + 1) = T(sum(X2)+ 1,sum(X) + 1) + 1;
   N(sum(X2)+ 1) = N(sum(X2)+ 1) + 1;
   if i == 2
     subplot(2,2,2); 
      title('Each time the ball is simulated')
      hold on
     # »­³ö¼×µÄ×´Ì¬ 
     for j = 1 :6
      if j > 3 && X2(j - 3) == 1
      alpha=0:pi/20:2*pi;   %½Ç¶È[0,2*pi] 
      R=0.18;                %°ë¾¶ 
      x=R*cos(alpha)+R; 
      y=R*sin(alpha) +j*2*R  + R + 1 ; 
      plot(x,y,'-') 
      axis equal
      fill(x,y,'k')
      %xlim([0 3])
      %ylim([0 3])
      hold on
    endif
      if j > 3 && X2(j-3) == 0
      alpha=0:pi/20:2*pi;   %½Ç¶È[0,2*pi] 
      R=0.18;                %°ë¾¶ 
      x=R*cos(alpha)+R; 
      y=R*sin(alpha) +j*2*R  + R + 1 ; 
      plot(x,y,'-') 
      axis equal
      fill(x,y,'m')
      %xlim([0 3])
      %ylim([0 3])
      hold on
    endif
      
       #if(X(j)==0)
      #plot(1,j,'ro')
      #fill(x,y,'r')
      if j <=3 && X(j) == 1
      alpha=0:pi/20:2*pi;   %½Ç¶È[0,2*pi] 
      R=0.18;                %°ë¾¶ 
      x=R*cos(alpha)+R; 
      y=R*sin(alpha) +j*2*R  + R; 
      plot(x,y,'-') 
      axis equal
      fill(x,y,'k')
      %xlim([0 3])
      %ylim([0 3])
      hold on
    endif
      if j <=3 && X(j) == 0
      alpha=0:pi/20:2*pi;   %½Ç¶È[0,2*pi] 
      R=0.18;                %°ë¾¶ 
      x=R*cos(alpha)+R; 
      y=R*sin(alpha) +j*2*R  + R; 
      plot(x,y,'-') 
      axis equal
      fill(x,y,'m')
      %xlim([0 3])
      %ylim([0 3])
      hold on
    endif
    
   endfor
   
   # »­³öÒÒµÄ×´Ì¬ 
     sha = 1.5;
     for j = 1 :6
      if j > 3 && Y2(j - 3) == 1
      alpha=0:pi/20:2*pi;   %½Ç¶È[0,2*pi] 
      R=0.18;                %°ë¾¶ 
      x=R*cos(alpha)+R +sha; 
      y=R*sin(alpha) +j*2*R  + R + 1 ; 
      plot(x,y,'-') 
      axis equal
      fill(x,y,'k')
      %xlim([0 3])
      %ylim([0 3])
      hold on
    endif
      if j > 3 && Y2(j-3) == 0
      alpha=0:pi/20:2*pi;   %½Ç¶È[0,2*pi] 
      R=0.18;                %°ë¾¶ 
      x=R*cos(alpha)+R +sha; 
      y=R*sin(alpha) +j*2*R  + R + 1 ; 
      plot(x,y,'-') 
      axis equal
      fill(x,y,'m')
      %xlim([0 3])
      %ylim([0 3])
      hold on
    endif
      
       #if(X(j)==0)
      #plot(1,j,'ro')
      #fill(x,y,'r')
      if j <=3 && Y(j) == 1
      alpha=0:pi/20:2*pi;   %½Ç¶È[0,2*pi] 
      R=0.18;                %°ë¾¶ 
      x=R*cos(alpha)+R +sha; 
      y=R*sin(alpha) +j*2*R  + R; 
      plot(x,y,'-') 
      axis equal
      fill(x,y,'k')
      %xlim([0 3])
      %ylim([0 3])
      hold on
    endif
      if j <=3 && Y(j) == 0
      alpha=0:pi/20:2*pi;   %½Ç¶È[0,2*pi] 
      R=0.18;                %°ë¾¶ 
      x=R*cos(alpha)+R +sha; 
      y=R*sin(alpha) +j*2*R  + R; 
      plot(x,y,'-') 
      axis equal
      fill(x,y,'m')
      
      hold on
    endif
    
   endfor
   
   endif     
endfor
subplot(2,2,4);
frequency = frequency./n;
plot([0 1 2 3],frequency,'r*');
hold on
plot([0 1 2 3],frequency,'m-');
hold on
xlim([-.5 3.5])
ylim([0 1])
P = [0 1 0 0 ;1/9 4/9 4/9 0;0 4/9 4/9 1/9; 0 0 1 0];
Pn=P^n;

plot([0 1 2 3],Pn(1,:),'g-');
hold on;
x = 1:n;

title('Probability distributions')
hold on
subplot(2,2,1);
plot(x,y,'-g')
hold on
plot(x,y,'*r')
xlim([0 100])
ylim([0 3])
set(gca,'YTick',[1:1:3]) 
for i = 1:4
  T(i,:)= T(i,:)./N(i);
endfor
title('Markov chain simulation experiment')
hold on
subplot(2,2,3);

for i = 1:4
  plot([0 1 2 3],T(i,:)+i - 1,'g-');
  hold on
  plot([0 1 2 3],T(i,:)+i - 1,'r*');
  hold on
  
  plot([0 1 2 3],P(i,:)+i - 1,'m-');
  hold on
  plot([0 1 2 3],P(i,:)+i - 1,'k*');
  hold on
  if i <4
  x = -1.5:0.1:3.5;
  y = ones(1,length(x))*i;
  plot(x,y','b-')
  hold on
  endif
endfor
xlim([-0.5 3.5])
title('Transition probability')
hold on
#ylim([-0.5 3.5])