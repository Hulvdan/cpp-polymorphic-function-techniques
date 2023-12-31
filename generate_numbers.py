from random import randint

for i in range(7):
    count = 10 ** (i + 1)
    numbers = [str(randint(0, count)) for _ in range(count)]
    with open(f"numbers_{count}.txt", "w") as out_file:
        out_file.write(" ".join(numbers))

