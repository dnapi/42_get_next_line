https://github.com/pasqualerossi/Born2BeRoot-Guide

https://github.com/ayoub0x1/born2beroot
https://github.com/achrafelkhnissi/Born2beroot/blob/master/Installation_and_setup.md
Disk space analyzer :  Disk Inventory X

c2r4p11  pass = asdMoipass83&	
# temp shasum f0af0a626a55f712ddf910e962b75fd5d8a09c65


encryption passphrase = vm.pass4moi

Debian 
su - 
apt-get update -y
apt-get upgrade -y
apt install sudo
usermod -aG sudo apimikov 
getent group sudo  # list of users in sudo group
sudo visudo # to modify sudoers file
apimikov  	ALL=(ALL) ALL  # User privilege specification
# to all users ( all group : all host) run command as any other user 

apt install git openssh-server ufw libpam-pwquality net-tools 
git --version


## host name
# hostnamectl 
#hostnamectl set-hostname new_hostname_name

date -s "2 OCT 2006 18:00:00"

## ssh, sshd (server) 
vim /etc/ssh/sshd_config  
# change port 
# no root ssh login
# PermitRootLogin prohibit-password  ->  PermitRootLogin no
sudo service ssh restart 
sudo systemctl status ssh

## ufw  
ufw enable
ufw status numbered
sudo ufw delete number 
ufw allow ssh
ufw allow 4242
# set network
systemctl restart ssh
service sshd stat


ssh apimikov@127.0.0.1 -p 4242 # on HOST machine


## Password Policy 
sudo apt-get install libpam-pwquality
sudo vim /etc/pam.d/common-password
# modify 
# password  requisite   pam_pwquality.so  retry=3 minlen=10 ucredit=-1 dcredit=-1 maxrepeat=3 reject_username
# password [success=1 default=ignore] pam_pwquality.so difok=7
sudo vim /etc/login.def   # applies only for new user
#change PASS_MAX_DAYS 30 and PASS_MIN_DAYS 2
chage -l username    #check the password rules
chage --mindays 2 --maxdays 30 --warndays 7 username
chage -m 2 -M 30 -W 7 username
passwd  # change password


##Creating group 
groupadd user42
usermod -aG user42 apimikov 
getent group user42

## Creating user
cut -d: -f1 /etc/passwd # to list groups and their users 
adduser username
usermod -aG user42 username
userdel username 
rm -rf /home/username

## Creating sudo.log
mkdir /var/log/sudo
touch /var/log/sudo/sudo.log
sudo vim /etc/sudoers # the same as sudo visudo
# modify 
#	Defaults	env_reset
#	Defaults	mail_badpass
#	Defaults	secure_path="/usr/local/sbin:/usr/local/bin:/usr/bin:/sbin:/bin"
#	Defaults	badpass_message="Password is wrong, please try again!"
#	Defaults	passwd_tries=3
#	Defaults	logfile="/var/log/sudo.log"
#	Defaults	log_input, log_output
#	Defaults	requiretty

## cron 
crontab -u root -e 
# modify 
# */10 * * * * sh /usr/local/bin/monitoring.sh

you must redirect the output of echo to certain file
1.- run this command: tty
It will tell you something like /dev/pts/X Check for the number X
2.- modify your cron job with the command
*/1 * * * * echo "Hello every minute" > /dev/pts/X
And that's all friend.





#####      EVALUATION

| $ sudo adduser username                    | <- creating new user (yes (no))
| $ sudo chage -l username                   | <- Verify password expire info for new user
| $ sudo adduser username sudo               |
| $ sudo adduser username user42             | <- assign new user to sudo and user42 group
	groupadd groupname 
	



| 1) lsblk                              1 <- Check partitions
| 2) sudo aa-status                     2 <- AppArmor status

| 3) getent group sudo                  3 <- sudo group users
| 4) getent group user42                4 <- user42 group users

| 5) sudo service ssh status            5 <- ssh status, yep
| 6) sudo ufw status                    6 <- ufw status
	uname -a 

| 7) ssh username@ipadress -p 4242      7 <- connect to VM from your host (physical) machine via SSH


| 8) sudo visudo or nano /etc/sudoers.d/<filename>     8 <- yes, sudo config file. You can $ ls /etc/sudoers.d first
| 9) nano /etc/login.defs               9 <- password expire policy
| 10) nano /etc/pam.d/common-password  10 <- password policy
| 11) sudo crontab -l                  11 <- cron schedule


hostnamectl 
hostnamectl set-hostname new_hostname # to change the current hostname

lsblk
dpkg -l | grep sudo 

dpkg -l | grep ufw
sudo ufw status
sudo ufw allow port_number 



sudoreplay -d /var/log/sudo-io/00/00 4A
/etc/hosts 
sudo ufw delete allow 8080



possible problems:
# password policy ( one not for root)
# logs of sudo commands
# during evaluation do we open copy of machine? will sha
