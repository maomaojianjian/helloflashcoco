cd build
# rm -rf ./*
# cmake ..
make -j32
mpirun -np 2 ./MyNCCLDemo
# mpirun --prefix /usr/local/openmpi -np 4 -H maojianping:2,mjp1:2 ./MyNCCLDemo
cd ..