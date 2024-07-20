cd build
rm -rf ./*
cmake ..
make -j32
# mpirun --prefix /usr/local/openmpi --hostfile ../hostfile -np 4 ./MyNCCLDemo
# mpirun -np 2 ./MyNCCLDemo
mpirun --prefix /usr/local/openmpi -np 4 -H maojianping:2,mjp1:2 ./MyNCCLDemo
cd ..