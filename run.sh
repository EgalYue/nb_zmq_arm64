cd build

for i in {1..100}  
do  
echo "===================="  $i;  

./zmqRepServer tcp://127.0.0.1 SlamStartup
done 



cd ..