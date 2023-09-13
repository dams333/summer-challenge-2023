str = input()

table = {
  "R": "U",
  "B": "P",
  "K": "D",
  "L": "O",
  "U": "W",
  "O": "N",
  "E": "L",
  "Q": "E",
  "X": "F",
  "F": "T",
  "T": "R",
  "Y": "I",
  "H": "G",
  "P": "H",
  "F": "T",
  "N": "M",
  "V": "Y",
  "J": "C",
  "A": "A",
  "W": "S",
  "I": "B"
}

for c in str:
	if c.isalpha():
		c = c.upper()
		if c in table:
			print(table[c], end="")
		else:
			print("?", end="")
	else:
		print(c, end="")

print()
