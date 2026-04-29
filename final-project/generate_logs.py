import random

def generate_log(filename, num_entries):
    with open(filename, "w") as f:
        for _ in range(num_entries):
            ip = ".".join(str(random.randint(0, 255)) for _ in range(4))
            status = random.choice([200, 200, 200, 404, 500])  # more 200s
            f.write(f"{ip} - - [timestamp] \"GET /index.html HTTP/1.1\" {status}\n")

# Generate files
generate_log("log_100k.txt", 100_000)
generate_log("log_500k.txt", 500_000)
generate_log("log_1m.txt", 1_000_000)
generate_log("log_2m.txt", 2_000_000)