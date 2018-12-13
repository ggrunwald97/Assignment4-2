set -x
sudo yum -y install nfs-utils nfs-utils-lib

sudo mkdir -p /users/GG850091/software
sudo chmod 777 /users/GG850091/software

sudo mkdir -p /users/GG850091/scratch
sudo chmod 777 /users/GG850091/scratch

sudo mount -t nfs 192.168.1.1:/software /users/GG850091/software
sudo mount -t nfs 192.168.1.3:/scratch /users/GG850091/scratch

echo '192.168.1.1:/software /users/GG850091/software  nfs defaults 0 0' >> /etc/fstab
echo '192.168.1.3:/scratch /users/GG850091/scratch  nfs defaults 0 0' >> /etc/fstab

#echo "export PATH='$PATH:/users/GG850091/software/openmpi/3.1.2/bin'" >> /users/GG850091/.bashrc
#echo "export LD_LIBRARY_PATH='$LD_LIBRARY_PATH:/users/GG850091/software/openmpi/3.1.2/lib/'" >> /users/GG850091/.bashrc
