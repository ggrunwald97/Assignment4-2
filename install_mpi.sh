#!/bin/bash
set -x
cd /software
sudo yum -y group install "Development Tools"
sudo wget https://download.open-mpi.org/release/open-mpi/v3.1/openmpi-3.1.2.tar.gz
sudo tar xzf openmpi-3.1.2.tar.gz
cd openmpi-3.1.2
#sudo ./configure --prefix=/opt/openmpi/3.1.2
sudo ./configure --prefix=/software/openmpi/3.1.2
sudo make
sudo make all install
echo "export PATH='$PATH:/software/openmpi/3.1.2/bin'" >> /users/GG850091/.bashrc
echo "export LD_LIBRARY_PATH='$LD_LIBRARY_PATH:/software/openmpi/3.1.2/lib'" >> /users/GG850091/.bashrc
#cd ..
cd /software
sudo rm -Rf openmpi-3.1.2
sudo rm -Rf openmpi-3.1.2.tar.gz
