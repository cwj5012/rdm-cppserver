```shell script
# 端口配置
master    连接 none       监听端口 6091-7000
service   连接 master     监听端口 6051-6090 
node      连接 service 
```