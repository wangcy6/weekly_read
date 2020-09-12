# 深入理解计算机系统
## to_do
### 制作电子书，上传到微信读书 ）

> 参考别人的：https://legacy.gitbook.com/book/dreamanddead/csapp-3e-solutions
>
> 下面命令执行失败。

~~~shell
git clone https://github.com/DreamAndDead/CSAPP-3e-Solutions.git
cd CSAPP-3e-Solutions
make test

wget https://nodejs.org/dist/v12.18.3/node-v12.18.3.tar.gz ### need c++11

./configure
make install
node -v
v10.22.0
npm config set registry=http://registry.npm.taobao.org -g

npm install gitbook-cli -g
npm install -g gitbook-cli@2.3.0
gitbook -V
gitbook ls-remote


###插件
npm install gitbook-plugin-disqus -g
npm install gitbook-plugin-multipart -g
npm install gitbook-plugin-flexible-alerts  t -g   
npm install gitbook-plugin-include -g
npm install gitbook-plugin-katex -g
npm install gitbook-plugin-ga -g
npm install gitbook-plugin-richquotes -g

/////////////////////////
cd /root/work/CSAPP-3e-Solutions
make plugin ###  install gitbook plugins
make serve ### generate site in ./_book/

make html ### generate E-books in

make pdf
make mobi
make epub

电子版：
链接：https://pan.baidu.com/s/1HR6SOjo5lQUYqvp7g4RV2w 
提取码：wyuc
~~~







