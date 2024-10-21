import ipaddress

def get_ip_class(ip):
    first_octet = int(ip.split('.')[0])

    if 1 <= first_octet <= 126:
        return 'A', '255.0.0.0'
    elif 128 <= first_octet <= 191:
        return 'B', '255.255.0.0'
    elif 192 <= first_octet <= 223:
        return 'C', '255.255.255.0'
    elif 224 <= first_octet <= 239:
        return 'D', 'Reserved (Multicast)'
    else:
        return 'E', 'Reserved (Experimental)'

def calculate_network(ip):
    ip_network = ipaddress.ip_network(ip, strict=False)
    return ip_network.network_address, ip_network.broadcast_address, ip_network.num_addresses, ip_network

def get_usable_ips(network):
    first_usable = list(network.hosts())[0]
    last_usable = list(network.hosts())[-1]
    return first_usable, last_usable

ip = input("Enter an IP address (e.g., 192.168.1.1/24): ")

ip_class, default_mask = get_ip_class(ip)
network_address, broadcast_address, total_addresses, network = calculate_network(ip)
first_usable_ip, last_usable_ip = get_usable_ips(network)

print(f"IP Address: {ip}")
print(f"Class: {ip_class}")
print(f"Default Mask: {default_mask}")
print(f"Network Address: {network_address}")
print(f"Broadcast Address: {broadcast_address}")
print(f"Total Number of Addresses: {total_addresses}")
print(f"First Usable IP: {first_usable_ip}")
print(f"Last Usable IP: {last_usable_ip}")
