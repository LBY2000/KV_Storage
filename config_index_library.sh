cd My_CCEH_DRAM
g++ -fPIC -shared -o libexhash.so Extendible_Hash.cpp
sudo cp libexhash.so /usr/lib
cd ..
cd ARTree
g++ -fPIC -shared -o libartree.so art.cpp
sudo cp libartree.so /usr/lib