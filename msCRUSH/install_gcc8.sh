echo ""
echo "Installing GCC-8"

sudo yum -y install centos-release-scl
sudo yum -y install devtoolset-8-gcc devtoolset-8-gcc-c++
scl enable devtoolset-8 -- bash
