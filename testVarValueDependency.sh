# Default values slicing from first email.
echo "================================================================================"
bin/diffkemp 3.10 4.11 net/ipv4/netfilter -m nf_nat_snmp_basic -p debug --debug
bin/diffkemp 3.10 4.11 net/ipv4/netfilter -m nf_nat_snmp_basic -p debug:default --debug
echo "================================================================================"
read -n 1 -s -re -p "Press any key to continue"

echo "================================================================================"
bin/diffkemp 3.10 4.11 drivers/block/drbd -m drbd -p fault_devs --debug
bin/diffkemp 3.10 4.11 drivers/block/drbd -m drbd -p fault_devs:default --debug
echo "================================================================================"
read -n 1 -s -re -p "Press any key to continue"

# Non default values from first email

echo "================================================================================"
bin/diffkemp 3.10 4.11 net/ipv4/netfilter -m tcp_cubic -p hystart --debug
bin/diffkemp 3.10 4.11 net/ipv4/netfilter -m tcp_cubic -p hystart:0 --debug
echo "================================================================================"
read -n 1 -s -re -p "Press any key to continue"

echo "================================================================================"
bin/diffkemp 3.10 4.11 net/ipv4 -m tcp_probe -p bufsize --debug
bin/diffkemp 3.10 4.11 net/ipv4 -m tcp_probe -p bufsize:0 --debug
echo "================================================================================"
read -n 1 -s -re -p "Press any key to continue"

echo "================================================================================"
bin/diffkemp 3.10 4.11 drivers/block -m nbd -p max_part --debug
bin/diffkemp 3.10 4.11 drivers/block -m nbd -p max_part:-1 --debug
echo "================================================================================"
read -n 1 -s -re -p "Press any key to continue"

# Second email
echo "================================================================================"
bin/diffkemp 3.10 4.11 drivers/char/ipmi -m ipmi_watchdog -p ifnum_to_use --debug
bin/diffkemp 3.10 4.11 drivers/char/ipmi -m ipmi_watchdog -p ifnum_to_use:default --debug
echo "================================================================================"
read -n 1 -s -re -p "Press any key to continue"

echo "================================================================================"
bin/diffkemp 3.10 4.11 drivers/char -m lp -p reset --debug
bin/diffkemp 3.10 4.11 drivers/char -m lp -p reset:default --debug
echo "================================================================================"
read -n 1 -s -re -p "Press any key to continue"

# Might be also working out
echo "================================================================================"
bin/diffkemp 3.10 4.11 drivers/char -m applicom -p mem --debug
bin/diffkemp 3.10 4.11 drivers/char -m applicom -p mem:default --debug
echo "================================================================================"
read -n 1 -s -re -p "Press any key to continue"

echo "================================================================================"
bin/diffkemp 3.10 4.11 drivers/char -m applicom -p irq --debug
bin/diffkemp 3.10 4.11 drivers/char -m applicom -p irq:default --debug
echo "================================================================================"
