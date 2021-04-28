set -e    # Stop script when en error occurs

apt-get update
apt-get -y upgrade

apt-get -y install openssh-server openssh-client iptables-persistent
apt-get -y install cmake
apt-get -y install nginx 
apt-get -y install mc links
apt-get -y install gcc make python3 python3-pip python3-venv build-essential gdb
apt-get -y install libssl-dev libx11-dev libxrandr-dev mesa-common-dev libgl1-mesa-dev libasound2-dev
apt-get -y install sysstat curl

pip3 install cmake
