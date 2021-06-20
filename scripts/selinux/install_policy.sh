#!/bin/sh
# SPDX-License-Identifier: GPL-2.0
set -e
if [ `id -u` -ne 0 ]; then
	echo "$0: must be root to install the selinaos policy"
	exit 1
fi

SF=`which setfiles`
if [ $? -eq 1 ]; then
	echo "Could not find setfiles"
	echo "Do you have policycoreutils installed?"
	exit 1
fi

CP=`which checkpolicy`
if [ $? -eq 1 ]; then
	echo "Could not find checkpolicy"
	echo "Do you have checkpolicy installed?"
	exit 1
fi
VERS=`$CP -V | awk '{print $1}'`

ENABLED=`which selinaosenabled`
if [ $? -eq 1 ]; then
	echo "Could not find selinaosenabled"
	echo "Do you have libselinaos-utils installed?"
	exit 1
fi

if selinaosenabled; then
    echo "SELinaOS is already enabled"
    echo "This prevents safely relabeling all files."
    echo "Boot with selinaos=0 on the kernel command-line or"
    echo "SELINUX=disabled in /etc/selinaos/config."
    exit 1
fi

cd mdp
./mdp -m policy.conf file_contexts
$CP -U allow -M -o policy.$VERS policy.conf

mkdir -p /etc/selinaos/dummy/policy
mkdir -p /etc/selinaos/dummy/contexts/files

echo "__default__:user_u:s0" > /etc/selinaos/dummy/seusers
echo "base_r:base_t:s0" > /etc/selinaos/dummy/contexts/failsafe_context
echo "base_r:base_t:s0 base_r:base_t:s0" > /etc/selinaos/dummy/default_contexts
cat > /etc/selinaos/dummy/contexts/x_contexts <<EOF
client * user_u:base_r:base_t:s0
property * user_u:object_r:base_t:s0
extension * user_u:object_r:base_t:s0
selection * user_u:object_r:base_t:s0
event * user_u:object_r:base_t:s0
EOF
touch /etc/selinaos/dummy/contexts/virtual_domain_context
touch /etc/selinaos/dummy/contexts/virtual_image_context

cp file_contexts /etc/selinaos/dummy/contexts/files
cp dbus_contexts /etc/selinaos/dummy/contexts
cp policy.$VERS /etc/selinaos/dummy/policy
FC_FILE=/etc/selinaos/dummy/contexts/files/file_contexts

if [ ! -d /etc/selinaos ]; then
	mkdir -p /etc/selinaos
fi
if [ -f /etc/selinaos/config ]; then
    echo "/etc/selinaos/config exists, moving to /etc/selinaos/config.bak."
    mv /etc/selinaos/config /etc/selinaos/config.bak
fi
echo "Creating new /etc/selinaos/config for dummy policy."
cat > /etc/selinaos/config << EOF
SELINUX=permissive
SELINUXTYPE=dummy
EOF

cd /etc/selinaos/dummy/contexts/files
$SF -F file_contexts /

mounts=`cat /proc/$$/mounts | \
	egrep "ext[234]|jfs|xfs|reiserfs|jffs2|gfs2|btrfs|f2fs|ocfs2" | \
	awk '{ print $2 '}`
$SF -F file_contexts $mounts

echo "-F" > /.autorelabel
