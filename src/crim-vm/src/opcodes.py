def shrinkSpaces(arg):
	return " ".join(arg.split())

def main():
	n = 0
	text = []
	op_list = []
	i = 1
	with open("instruction.rs", "r") as f:
		line = f.readline()
		n +=1
		point = 0
		while shrinkSpaces(line) != "pub enum Opcode {":
			point = f.tell()
			line = f.readline()
			n += 1
		f.seek(point)
		n -= 1
		while shrinkSpaces(line) != "IGL":
			if line != "":
				for o in shrinkSpaces(line).split(","):
					if o != "":
						op_list += [o,]
			line = f.readline()
			n += 1
		print("finished opcodes")
		while shrinkSpaces(line) != "match v {":
			line = f.readline()
			n += 1
		line = f.readline()
		n +=1
		while shrinkSpaces(line) != "":
			line = f.readline()
			n +=1
			i += 1
		n -= 1
		i += 1
		op_list = op_list[i:]
		i -= 2
		f.seek(0)
		text = f.readlines()

	print(op_list)
	print("found end of current ops")

	for op in op_list:
		text.insert(n, f"\t\t\t{i} => return Opcode::{op},\n")
		i += 1
		n += 1

	with open("instruction.rs", "w") as f:
		f.write("".join(text))
			
main()
