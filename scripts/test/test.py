import Image, numpy, json
import matplotlib.pyplot as plt

im = Image.open("she.png")
im.load()
arr = numpy.array(im)
plt.imshow(im)

foo = open("she.ctf")
ctf = json.loads(foo.read())
foo.close()

ctf.append(ctf[1])
triangles = []

for i in range(len(ctf) - 2):
	n = i+1
	x = [ctf[n][1], ctf[n+1][1], ctf[0][1], ctf[n][1]]
	y = [ctf[n][0], ctf[n+1][0], ctf[0][0], ctf[n][0]]
	triangles.append([x, y])

for i, p in enumerate(triangles):
	plt.plot(p[0], p[1])
plt.show()